// include/webserver/http_server.h
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

class HttpServer {
public:
    HttpServer();                                 // Constructor
    HttpServer& begin(uint16_t port = 80);        // Initialize server on the specified port
    HttpServer& someMiddleware();                 // Placeholder for middleware setup
    HttpServer& auth();                           // Placeholder for authentication setup
    HttpServer& serveStaticFiles();               // Setup static file routes
    void start();                                 // Start the server (called at the end of the chain)

private:
    AsyncWebServer* server;                       // Pointer to AsyncWebServer for flexibility with port

    String getContentType(String filename);
    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
};

#endif

