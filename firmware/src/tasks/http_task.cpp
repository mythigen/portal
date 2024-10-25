#include "tasks/tasks.h"

  String getContentType(String filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".jpg")) return "image/jpeg";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    return "text/plain";
  }

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if(!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file) {
    if(file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels) {
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


// HTTP Server Task
void http_task(void *pvParameters) {

  if (LittleFS.begin()) {
    Serial.println("LittleFS File System Info:");
    Serial.printf("Total space:      %u bytes\n", LittleFS.totalBytes());
    Serial.printf("Used space:       %u bytes\n", LittleFS.usedBytes());
    Serial.printf("Free space:       %u bytes\n", LittleFS.totalBytes() - LittleFS.usedBytes());
    // Serial.printf("Block size:       %u bytes\n", LittleFS.blockSize);
    // Serial.printf("Page size:        %u bytes\n", LittleFS.pageSize);
    // Serial.printf("Max open files:   %u\n", LittleFS.maxOpenFiles);
    // Serial.printf("Max path length:  %u\n", LittleFS.maxPathLength);
  } else {
    Serial.println("Failed to retrieve LittleFS info");
  }

  AsyncWebServer server(80);

  if (!LittleFS.begin()) {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  // Serving files from LittleFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    listDir(LittleFS, "/www", 0);
    request->send(LittleFS, "/www/index.html", "text/html");
  });

  // Serve all other files from /www directory
  server.serveStatic("/", LittleFS, "/www/").setDefaultFile("index.html");

  server.onNotFound([](AsyncWebServerRequest *request) {
    String path = request->url();
    if (LittleFS.exists(path)) {
      request->send(LittleFS, path, getContentType(path));
    } else {
      request->send(404, "text/plain", "File not found");
    }
  });

  // Start server
  server.begin();
  while (true) {
    // Placeholder for HTTP server logic
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1-second delay
  }
}

