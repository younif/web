//
// Created by read on 2021/10/11.
//

#ifndef WEB_HTTPDATA_H
#define WEB_HTTPDATA_H

#include <string>
#include <map>
#include "config.h"

using namespace std;

class HttpData {
public:
    explicit HttpData(const string& data);
    string URL();
    string responseHead();
    string Host(){return Host_;}
    string dirBody();
    bool isDir() const{return is_dir_;}
private:

    string method_;
    string URL_;
    bool is_dir_ = false;
    string version_;
    string Host_;
    string content_type_;
    map<string,string> dir_body_cache_;
    string response_body_;
};


#endif //WEB_HTTPDATA_H
