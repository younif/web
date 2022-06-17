//
// Created by read on 2021/10/7.
//
#include "Server.h"


using namespace std;

int main(int argc, char** argv) {
    Server server("my_server", InetAddress(8888));
    server.run();
}