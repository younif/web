//
// Created by read on 2021/10/7.
//

#ifndef STD11_WEB_LOGGER_H
#define STD11_WEB_LOGGER_H

#include <iostream>

using namespace std;

class Logger {
public:
    Logger(string file, int line):file_(std::move(file)),line_(line){

    }
    ostream* stream(){
        return &cout;
    }
    ~Logger(){
        cout << " - " << file_ << ":" << line_ << endl ;
    }
private:
    string file_;
    int line_;
};

#define LOG *Logger(__FILE__, __LINE__).stream()


#endif //STD11_WEB_LOGGER_H
