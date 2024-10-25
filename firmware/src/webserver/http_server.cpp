// src/webserver/http_server.cpp
#include "webserver/http_server.h"

// Constructor - Initializes server as a nullptr (to be created in begin)
HttpServer::HttpServer() : server(nullptr) {}

// Initialize server instance on specified port without starting it
HttpServer& HttpServer::begin(uint16_t port) {
    server = new AsyncWebServer(port);

    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
    } else {
        Serial.println("LittleFS File System Info:");
        Serial.printf("Total space:      %u bytes\n", LittleFS.totalBytes());
        Serial.printf("Used space:       %u bytes\n", LittleFS.usedBytes());
        Serial.printf("Free space:       %u bytes\n", LittleFS.totalBytes() - LittleFS.usedBytes());
    }
    return *this;
}

// Placeholder for adding middleware
HttpServer& HttpServer::someMiddleware() {
    // Define middleware logic here
    Serial.println("Middleware setup called");
    return *this;
}

// Placeholder for adding authentication routes
HttpServer& HttpServer::auth() {
    // Define auth setup here
    Serial.println("Auth setup called");
    return *this;
}

// Sets up routes for serving static files from LittleFS
HttpServer& HttpServer::serveStaticFiles() {
    if (!server) {
        Serial.println("Server must be initialized with begin() before calling serveStaticFiles()");
        return *this;
    }

    // Serve root index
    server->on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        listDir(LittleFS, "/www", 0);
        request->send(LittleFS, "/www/index.html", "text/html");
    });

    // Serve all other files from /www directory
    server->serveStatic("/", LittleFS, "/www/").setDefaultFile("index.html");

    // Handle 404 - Not Found
    server->onNotFound([this](AsyncWebServerRequest *request) {
        String path = request->url();
        if (LittleFS.exists(path)) {
            request->send(LittleFS, path, getContentType(path));
        } else {
            request->send(404, "text/plain", "File not found");
        }
    });

    return *this;
}

// Start the server (final step in the chain)
void HttpServer::start() {
    if (server) {
        server->begin();
        Serial.println("HTTP Server started");
    }
}

// Helper function to get content type based on file extension
String HttpServer::getContentType(String filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".jpg")) return "image/jpeg";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    return "text/plain";
}

// Helper function to list directory contents (for debugging)
void HttpServer::listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.name(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

