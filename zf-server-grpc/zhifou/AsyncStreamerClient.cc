/*
 *
 * Copyright 2015 gRPC authors.
 * Copyright 2020 Akamai Technologies, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "zhifou.grpc.pb.h"
#include "zhifou.pb.h"

using namespace personalinfo;
using namespace grpc; 

class AsyncStreamerClient {
 public:
  AsyncStreamerClient(std::shared_ptr<Channel> channel)
      : stub_(PersonalInfo::NewStub(channel)) {
  }

  //GetMyQuestion
  void OpenAndReadFromStream() {
    User req;


    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;
	
	
	Question response;
    std::unique_ptr<ClientReader<Question>> reader(
        stub_->GetMyQuestion(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid()<< ",title:" << response.title() << ",username:" << response.username() << ",createTime:" << response.createtime()  << std::endl;
    }

    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetMyQuestion rpc succeeded." << std::endl;
    } else {
      std::cout << "GetMyQuestion rpc failed." << status.error_message() << std::endl;
    }
  }
  
  //GetMyAnswer
  void OpenAndReadFromStream2() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;
	
    Answer response;
    std::unique_ptr<ClientReader<Answer>> reader(
        stub_->GetMyAnswer(&context, req));
    while (reader->Read(&response)) {
        std::cout << "answerId:" << response.answerid()<< ",questionId:" << response.questionid() << ",questionTitle:" << response.questiontitle() << ",username:" << response.username() << ",createTime:" << response.createtime()  << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetMyAnswer rpc succeeded." << std::endl;
    } else {
      std::cout << "GetMyAnswer rpc failed." << status.error_message() << std::endl;
    }
  }
  
  //GetMyArticle
    void OpenAndReadFromStream3() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;

    Article response;
    std::unique_ptr<ClientReader<Article>> reader(
        stub_->GetMyArticle(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid()<< ",title:" << response.title() << ",username:" << response.username() << ",createtime:" << response.createtime()  << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetMyArticle rpc succeeded." << std::endl;
    } else {
      std::cout << "GetMyArticle rpc failed." << status.error_message() << std::endl;
    }
  }
  
  //GetFans
  void OpenAndReadFromStream4() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;

    Fans response;
    std::unique_ptr<ClientReader<Fans>> reader(
        stub_->GetFans(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid() << ",username:" << response.username() << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetFans rpc succeeded." << std::endl;
    } else {
      std::cout << "GetFans rpc failed." << status.error_message() << std::endl;
    }
  }
  
  
  
  //GetFollowing
  void OpenAndReadFromStream5() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;

    Followings response;
    std::unique_ptr<ClientReader<Followings>> reader(
        stub_->GetFollowing(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid() << ",username:" << response.username() << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetFollowing rpc succeeded." << std::endl;
    } else {
      std::cout << "GetFollowing rpc failed." << status.error_message() << std::endl;
    }
  }
  
  
  
  //GetFavoriteQuestion
  void OpenAndReadFromStream6() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;
	
	
	Question response;
    std::unique_ptr<ClientReader<Question>> reader(
        stub_->GetFavoriteQuestion(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid()<< ",title:" << response.title() << ",username:" << response.username() << ",createTime:" << response.createtime()  << std::endl;
    }

    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetFavoriteQuestion rpc succeeded." << std::endl;
    } else {
      std::cout << "GetFavoriteQuestion rpc failed." << status.error_message() << std::endl;
    }
  }
  
  
  //GetCollectArticle
  void OpenAndReadFromStream7() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;

    Article response;
    std::unique_ptr<ClientReader<Article>> reader(
        stub_->GetCollectArticle(&context, req));
    while (reader->Read(&response)) {
        std::cout << "uuid:" << response.uuid()<< ",title:" << response.title() << ",username:" << response.username() << ",createtime:" << response.createtime()  << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetCollectArticle rpc succeeded." << std::endl;
    } else {
      std::cout << "GetCollectArticle rpc failed." << status.error_message() << std::endl;
    }
  }
  
  
  //GetCollectAnswer
  void OpenAndReadFromStream8() {
    User req;

    req.set_userid(std::string("5e167f59fe02420f9a2e6e575cfe3abe")); 
    ClientContext context;

    Answer response;
    std::unique_ptr<ClientReader<Answer>> reader(
        stub_->GetCollectAnswer(&context, req));
    while (reader->Read(&response)) {
        std::cout << "answerId:" << response.answerid()<< ",questionId:" << response.questionid() << ",questionTitle:" << response.questiontitle() << ",username:" << response.username() << ",createTime:" << response.createtime()  << std::endl;
    }
	
    Status status = reader->Finish();
	
    if (status.ok()) {
      std::cout << "GetCollectAnswer rpc succeeded." << std::endl;
    } else {
      std::cout << "GetCollectAnswer rpc failed." << status.error_message() << std::endl;
    }
  }
  
  
  
private:
     std::unique_ptr<PersonalInfo::Stub> stub_;
};


int main(int argc, char** argv) {
    AsyncStreamerClient client(
        grpc::CreateChannel("localhost:9314",
        grpc::InsecureChannelCredentials()));
		
	std::cout << "*******GetMyQuestion*********" << std::endl;
    client.OpenAndReadFromStream(); 
	std::cout << "*******GetMyAnswer*********" << std::endl;
	
	client.OpenAndReadFromStream2(); 
	
	
	std::cout << "*******GetMyArticle**********" << std::endl;
	client.OpenAndReadFromStream3(); 
	
	
	std::cout << "*******GetFans***********" << std::endl;
	client.OpenAndReadFromStream4(); 
	std::cout << "*******GetFollowing**********" << std::endl;
	client.OpenAndReadFromStream5(); 
	std::cout << "********GetFavoriteQuestion***********" << std::endl;
	client.OpenAndReadFromStream6(); 
	std::cout << "*****GetCollectArticle*******" << std::endl;
	client.OpenAndReadFromStream7(); 
	std::cout << "*****GetCollectAnswer******" << std::endl;
	client.OpenAndReadFromStream8(); 
	
	
    std::cout << "Client exiting." << std::endl;
    return 0;
}

