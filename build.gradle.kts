import org.gradle.api.tasks.Exec
import org.gradle.api.tasks.Copy
import java.sql.Connection
import java.sql.DriverManager


plugins {
  id("java")
  id("org.flywaydb.flyway") version "9.8.0"
}

repositories {
  mavenCentral()
}

dependencies {
  implementation("org.xerial:sqlite-jdbc:3.36.0.3")
}

flyway {
  url = "jdbc:sqlite:/home/hani/Development/celec/portal-core/migrations/auth.db"  // Path to SQLite DB
  locations = arrayOf("filesystem:migrations")  // Migration scripts location
  driver = "org.sqlite.JDBC"
  baselineOnMigrate = true
}

// Property to select between Node.js and Bun (default to Bun)
val useNodeJs = project.findProperty("useNodeJs")?.toString()?.toBoolean() ?: false

// Function to define the build command (Bun or Node.js)
fun buildCommand() = if (useNodeJs) "npm" else "bun"

// Define directories
val sveltekitProjectDir = projectDir.resolve("dashboard")
val esp32ProjectDir = projectDir.resolve("firmware")
val esp32DataDir = esp32ProjectDir.resolve("data")
val migrationsDir = projectDir.resolve("migrations")
val sqliteDbFile = migrationsDir.resolve("auth.db")

// Task to install SvelteKit dependencies
val installSvelteKitDependencies by tasks.registering(Exec::class) {
    workingDir = sveltekitProjectDir
    commandLine(buildCommand(), "install")
    outputs.upToDateWhen { sveltekitProjectDir.resolve("node_modules").exists() }
}

// Task to build the SvelteKit project
val buildSvelteKit by tasks.registering(Exec::class) {
    dependsOn(installSvelteKitDependencies)
    workingDir = sveltekitProjectDir
    commandLine(buildCommand(), "run", "build")
}

// Task to run SQLite migrations and initialize the database
val runMigrations by tasks.registering {
  doLast {
    println("Running Flyway Migrations...")
    // tasks.named("flywayMigrate").get().execute()
    exec {
      commandLine("sh", "-c", "./gradlew flywayMigrate")
    }
    println("Migrations completed successfully!")
  }
}

// Task to copy SQLite DB to ESP32 SPIFFS data directory
val copyDbToSPIFFS by tasks.registering(Copy::class) {
    dependsOn(runMigrations)
    from(sqliteDbFile)
    into("${esp32DataDir}/var")
}

// Task to copy SvelteKit build output to ESP32 SPIFFS data directory
val copySvelteKitToSPIFFS by tasks.registering(Copy::class) {
    dependsOn(buildSvelteKit)
    from(sveltekitProjectDir.resolve("build"))
    into("${esp32DataDir}/www")
}

// Task to build the ESP32 firmware using PlatformIO
val buildESP32 by tasks.registering(Exec::class) {
    // dependsOn(copySvelteKitToSPIFFS, copyDbToSPIFFS)
    workingDir = esp32ProjectDir
    commandLine("platformio", "run")
}

// Task to upload the ESP32 firmware to the device
val uploadESP32 by tasks.registering(Exec::class) {
    dependsOn(buildESP32)
    workingDir = esp32ProjectDir
    commandLine("platformio", "run", "--target", "upload")
}
//
// Task to upload the ESP32 filesystem to the device
val uploadESP32FS by tasks.registering(Exec::class) {
    dependsOn(buildESP32)
    workingDir = esp32ProjectDir
    commandLine("platformio", "run", "--target", "uploadfs")
}

// Task to clean the ESP32 build artifacts
val cleanESP32 by tasks.registering(Exec::class) {
    workingDir = esp32ProjectDir
    commandLine("platformio", "run", "--target", "clean")
}

// Task to monitor the ESP32 serial output
val monitorESP32 by tasks.registering(Exec::class) {
    workingDir = esp32ProjectDir
    commandLine("platformio", "device", "monitor")
}

// Task to clean both SvelteKit and ESP32 build artifacts
val cleanAll by tasks.registering {
    dependsOn(cleanESP32)
    doLast {
        val svelteBuildDir = sveltekitProjectDir.resolve("build")
        if (svelteBuildDir.exists()) {
            svelteBuildDir.deleteRecursively()
            println("Cleaned SvelteKit build directory.")
        }

        if (sqliteDbFile.exists()) {
            sqliteDbFile.delete()
            println("Cleaned SQLite database file.")
        }
    }
}

// Composite task to build everything
val buildAll by tasks.registering {
    // dependsOn(copySvelteKitToSPIFFS, copyDbToSPIFFS)
    dependsOn(copySvelteKitToSPIFFS, copyDbToSPIFFS, buildESP32)
}

// Composite task to build and upload everything
val uploadAll by tasks.registering {
    dependsOn(buildAll, uploadESP32, uploadESP32FS)
}

