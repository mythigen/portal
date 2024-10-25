// src/tasks/http_task.cpp
#include "tasks/tasks.h"
#include "webserver/http_server.h"

void http_task(void *pvParameters) {
    HttpServer httpServer;
    httpServer.begin(80)
              .someMiddleware()
              .auth()
              .serveStaticFiles()
              .start();  // Start the server only after setup is complete

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1-second delay
    }
}

