//
// Created by youni on 22-7-24.
//

#ifndef CREACTOR_EXAMPLE_PROTOBUF_CODEC_H_
#define CREACTOR_EXAMPLE_PROTOBUF_CODEC_H_

#include "TcpConnection.h"
class Codec {
 public:
  void onRead(const std::shared_ptr<TcpConnection> &con) {

	con->disableReading();
	con->enableWriting();
  }
};

#endif //CREACTOR_EXAMPLE_PROTOBUF_CODEC_H_
