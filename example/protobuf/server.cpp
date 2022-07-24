//
// Created by youni on 22-7-24.
//
#include "addressbook.pb.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "Codec.h"
#include "Dispatcher.h"

#include "spdlog/spdlog.h"

class MyServer{

 public:
  MyServer(EventLoop& loop, int port, int threadNum, std::string name)
  	: server_(loop,port,threadNum,name)
  {
	server_.setReadCallback([&](const std::shared_ptr<TcpConnection> &con){codec_.onRead(con);});
  }

 private:
  TcpServer server_;
  Codec codec_;
  Dispatcher dispatcher_;
};



int main(){
	tutorial::AddressBook address_book;
	address_book;

	EventLoop loop;
	MyServer server(loop,8888,3,"protobuf_server");



	google::protobuf::ShutdownProtobufLibrary();
}