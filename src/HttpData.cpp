//
// Created by read on 2021/10/11.
//

#include "HttpData.h"
#include "Logger.h"
#include <experimental/filesystem>

using namespace experimental::filesystem;

HttpData::HttpData(const string &data) {

    // 解析Host值
    auto Host_index_begin = data.find("Host");
    auto Host_index_end = data.find("\r\n", Host_index_begin);
    Host_ = data.substr(Host_index_begin + 6, Host_index_end - Host_index_begin - 6);
    //LOG << "Host:" << Host_;

    //设置路径
    string start_line = data.substr(0, data.find("\r\n"));
    auto index1 = start_line.find(' ');
    auto index2 = start_line.find(' ', index1 + 1);
    URL_ = data.substr(index1 + 1, index2 - index1 - 1);
    //if (URL_ == "/") URL_ = "/index.html";
    //LOG << "request filename:" << URL_;
    URL_ = URL_PATH + URL_;
    if (is_directory(path(URL_))) is_dir_ = true;
    if (!exists(path(URL_))) URL_ = "../html/50x.html";

    string extension = path(URL_).extension().string();
    //LOG << "request file extension is " << extension;

    // 设置MIME类型
    if (extension == ".css") {
        content_type_ = "text/css";
    } else if (extension == ".html") {
        content_type_ = "text/html";
    } else if (extension == ".png") {
        content_type_ = "image/png";
    }
    //LOG << "final filename:" << URL_;
}

string HttpData::URL() {
    return URL_;
}

string HttpData::responseHead() {
    path file(URL_);
    string head;
    head += "HTTP/1.0 200 OK\r\n";
    head += "Content-type:" + content_type_ + "\r\n";
    head += "Connection: keep-alive\r\n";
    if (is_dir_) {
        head += "Content-length:" + to_string(response_body_.size()) + "\r\n\r\n";
    } else {
        head += "Content-length:" + to_string(file_size(file)) + "\r\n\r\n";
    }
    return head;
}

string HttpData::dirBody() {
    if (dir_body_cache_[URL_].empty()) {
        response_body_ += "<!DOCTYPE html>\n"
                          "<html>\n"
                          "\t<head>\n"
                          "\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                          "\t\t<meta charset=\"utf-8\" />\n"
                          "\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />\n"
                          "\t\t<title>reads的个人博客</title>\n"
                          "\t</head>\n"
                          "<body>\n"
                          "<h1>博客目录</h1>";
        response_body_ += "<p><a href=\"/\" title=\"首页\">首页</a></p>";
        directory_iterator list((path(URL_)));
        for (const auto &it: list) {
            response_body_ += "<p><a href=\"" + it.path().relative_path().generic_string().substr(URL_PATH.size()) +
                              "\" title=\"" + it.path().relative_path().generic_string().substr(URL_PATH.size()) +
                              "\">";
            response_body_ += it.path().relative_path().generic_string().substr(URL_PATH.size());
            response_body_ += "</a></p>";
        }
        response_body_ += "</body>\n"
                          "</html>";
        dir_body_cache_[URL_] = response_body_;
    } else {
        response_body_ = dir_body_cache_[URL_];
    }
    return response_body_;
}




