//
// Created by youni on 22-6-14.
//

#include "HttpServer.h"

int main(int argc, char** argv){
  HttpServer http_server(8888);
  http_server.run();
}