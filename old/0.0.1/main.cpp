//
// Created by read on 2021/10/7.
//
#include "Server.h"
#include "spdlog/spdlog.h"


using namespace std;

int main(int argc, char** argv) {
    spdlog::set_level(spdlog::level::trace);
    Server server("my_server", 8888,"",1,"");
    server.run();
}