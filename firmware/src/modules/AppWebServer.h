#ifndef APP_WEBSERVER_H
#define APP_WEBSERVER_H

#include <WebServer.h>

class AppWebServer {
public:
    static void init();
    static void handleClient();
};

#endif
