#include <ESPAsyncWebServer.h>
#include "Arduino.h"

void captive_portal_callback(AsyncWebServerRequest* request) {
    for (size_t i = 0; i < request->args(); i++) {
	Serial0.printf("%s: %s\n", request->argName(i), request->arg(i));
	request->send(200);
    } 
}
