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




#include "GRPCAsyncServer.h"
#include "GenericAsyncHandler.h"
#include "zhifou.grpc.pb.h"
#include "zhifou.pb.h"
#include <atomic>
#include <thread>
#include <chrono>
#include <memory>

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <csignal>



#include "../ormpp/ormpp/main.hpp"



#define GRPC_Namespace personalinfo 



//GetQuestion
//在连接到ormpp失败时的辅助测试grpc方法
//这些方法(class PersonalInfoImpl之前的方法)以后要在ormpp中编写
/*
std::vector<std::vector<std::string>> get_my_queston(std::string user_id){
    std::vector<std::string> res_uuid, res_title, res_username, res_createTime;
    res_uuid.emplace_back("7223421ebb3a4bf2b9f3ffdf3132a2ba");
    res_uuid.emplace_back("8510b20c708b40a2ac00ea09a675a918");
    res_uuid.emplace_back("ac2bded82dea48de8d04da2678bb19dc");
    res_uuid.emplace_back("b27c16cdc9044516b766161e98b5dd4f");
        
    res_title.emplace_back("问题2标题");
    res_title.emplace_back("问题3");
    res_title.emplace_back("问题1标题");
    res_title.emplace_back("4标题");

    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");

    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");

    std::vector<std::vector<std::string>> res;
    res.emplace_back(res_uuid);
    res.emplace_back(res_title);
    res.emplace_back(res_username);
    res.emplace_back(res_createTime);

    return res;

}
*/

//GetAnswer
//在连接到ormpp失败时的辅助测试grpc方法
//这些方法(class PersonalInfoImpl之前的方法)以后要在ormpp中编写
/*
std::vector<std::vector<std::string>> get_my_answer(std::string user_id){
    
	std::vector<std::string> res_uuid, res_quid, res_title, res_username, res_createTime;
    res_uuid.emplace_back("7223421ebb3a4bf2b9f3ffdf3132a2ba");
    res_uuid.emplace_back("8510b20c708b40a2ac00ea09a675a918");
    res_uuid.emplace_back("ac2bded82dea48de8d04da2678bb19dc");
    res_uuid.emplace_back("b27c16cdc9044516b766161e98b5dd4f");
	
	res_quid.emplace_back("123");
    res_quid.emplace_back("456");
    res_quid.emplace_back("789");
    res_quid.emplace_back("258");
     
    res_title.emplace_back("问题2标题");
    res_title.emplace_back("问题3");
    res_title.emplace_back("问题1标题");
    res_title.emplace_back("4标题");

    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");
    res_username.emplace_back("meng_test");

    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");
    res_createTime.emplace_back("2020-03-30 13:59:38");
	

    std::vector<std::vector<std::string>> res;
	
    res.emplace_back(res_uuid);
    res.emplace_back(res_quid);
    res.emplace_back(res_title);
    res.emplace_back(res_username);
    res.emplace_back(res_createTime);

    return res;

}

std::vector<std::vector<std::string>> get_my_article(std::string user_id){
	
	std::vector<std::vector<std::string>> res;
	return res;
}

std::vector<std::vector<std::string>> get_my_fans(std::string user_id){
	std::vector<std::vector<std::string>> res;
	return res;
}


std::vector<std::vector<std::string>> get_my_following(std::string user_id){
	std::vector<std::vector<std::string>> res;
	return res;
}

std::vector<std::vector<std::string>> get_my_favorite_queston(std::string user_id){
	std::vector<std::vector<std::string>> res;
	return res;
}

std::vector<std::vector<std::string>> get_my_favorite_article(std::string user_id){
	std::vector<std::vector<std::string>> res;
	return res;
}

std::vector<std::vector<std::string>> get_my_favorite_answer(std::string user_id){
	std::vector<std::vector<std::string>> res;
	return res;
}

*/

//GetMyQuestion
template <class T> 
using AsyncStreamHandlerBase = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Question, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler : public AsyncStreamHandlerBase<AsyncStreamHandler> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler(Args&&... t) : AsyncStreamHandlerBase<AsyncStreamHandler> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {
	if(!flag){
		question_list_ = get_my_queston(request_.userid());
		count_ = (question_list_.size() == 0)?0: (question_list_[0].size() == 0)?0:question_list_[0].size();
		flag = true;
	}
	

	//std::cout<<"request_.userid()2:"<<request_.userid()<<std::endl;
        HandlerStatus status = ACTIVE; 

		//if count_ == 0, return FINISHED directly
		if(count_ == 0){


			GRPC_Namespace::Question response;

			grpc::WriteOptions options;
                	responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			
			GRPC_Namespace::Question response;
			
			response.set_uuid(question_list_[0][question_list_[0].size() - count_ - 1]);
			response.set_title(question_list_[1][question_list_[0].size() - count_ - 1]);
			response.set_username(question_list_[2][question_list_[0].size() - count_ - 1]);
			response.set_createtime(question_list_[3][question_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> question_list_;
    
	int count_;

	bool flag = false;

	
};


//GetMyAnswer
template <class T> 
using AsyncStreamHandlerBase2 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Answer, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler2 : public AsyncStreamHandlerBase2<AsyncStreamHandler2> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler2(Args&&... t) : AsyncStreamHandlerBase2<AsyncStreamHandler2> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {

	if(!flag){
		answer_list_ = get_my_answer(request_.userid());
		count_ = (answer_list_.size() == 0)?0: (answer_list_[0].size() == 0)?0:answer_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		
		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			GRPC_Namespace::Answer response;

			grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {

			
			GRPC_Namespace::Answer response;
			
			response.set_answerid(answer_list_[0][answer_list_[0].size() - count_ - 1]);
			response.set_questionid(answer_list_[1][answer_list_[0].size() - count_ - 1]);
			response.set_questiontitle(answer_list_[2][answer_list_[0].size() - count_ - 1]);
			response.set_username(answer_list_[3][answer_list_[0].size() - count_ - 1]);
			response.set_createtime(answer_list_[4][answer_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> answer_list_;
    
	int count_;

	bool flag = false;
};


//GetMyArticle
template <class T> 
using AsyncStreamHandlerBase3 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Article, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler3 : public AsyncStreamHandlerBase3<AsyncStreamHandler3> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler3(Args&&... t) : AsyncStreamHandlerBase3<AsyncStreamHandler3> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {

	if(!flag){
		article_list_ = get_my_article(request_.userid());
		count_ = (article_list_.size() == 0)?0: (article_list_[0].size() == 0)?0:article_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		

		//if count_ == 0, return FINISHED directly
		if(count_ == 0){

			GRPC_Namespace::Article response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);   
			
			status = FINISHED;
			return status;

		}
		
		const bool is_finished = --count_ == 0;

        try {
			GRPC_Namespace::Article response;
			
			response.set_uuid(article_list_[0][article_list_[0].size() - count_ - 1]);
			response.set_title(article_list_[1][article_list_[0].size() - count_ - 1]);
			response.set_username(article_list_[2][article_list_[0].size() - count_ - 1]);
			response.set_createtime(article_list_[3][article_list_[0].size() - count_ - 1]);
			
			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
		
		
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
		
        return status;
		
    }
private:

	std::vector<std::vector<std::string>> article_list_;
   
	int count_;

	bool flag = false;
};


//GetFans
template <class T> 
using AsyncStreamHandlerBase4 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Fans, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler4 : public AsyncStreamHandlerBase4<AsyncStreamHandler4> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler4(Args&&... t) : AsyncStreamHandlerBase4<AsyncStreamHandler4> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {

	if(!flag){
		fans_list_ = get_my_fans(request_.userid());
		count_ = (fans_list_.size() == 0)?0: (fans_list_[0].size() == 0)?0:fans_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		
		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			
			GRPC_Namespace::Fans response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle); 
			
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			GRPC_Namespace::Fans response;
			
			response.set_uuid(fans_list_[0][fans_list_[0].size() - count_ - 1]);
			//response.set_title(fans_list_[1][fans_list_[0].size() - count_ - 1]);
			response.set_username(fans_list_[1][fans_list_[0].size() - count_ - 1]);
			//response.set_createdate(fans_list_[3][fans_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> fans_list_;
    
	int count_;

	bool flag = false;
};


//GetFollowing
template <class T> 
using AsyncStreamHandlerBase5 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Followings, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler5 : public AsyncStreamHandlerBase5<AsyncStreamHandler5> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler5(Args&&... t) : AsyncStreamHandlerBase5<AsyncStreamHandler5> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {
	if(!flag){
		following_list_ = get_my_following(request_.userid());
		count_ = (following_list_.size() == 0)?0: (following_list_[0].size() == 0)?0:following_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		
		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			
			GRPC_Namespace::Followings response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle); 
			
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			GRPC_Namespace::Followings response;
			
			response.set_uuid(following_list_[0][following_list_[0].size() - count_ - 1]);
			//response.set_title(following_list_[1][following_list_[0].size() - count_ - 1]);
			response.set_username(following_list_[1][following_list_[0].size() - count_ - 1]);
			//response.set_createdate(following_list_[3][following_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> following_list_;
    
	int count_;

	bool flag = false;
};


//GetFavoriteQuestion
template <class T> 
using AsyncStreamHandlerBase6 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Question, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler6 : public AsyncStreamHandlerBase6<AsyncStreamHandler6> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler6(Args&&... t) : AsyncStreamHandlerBase6<AsyncStreamHandler6> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {
	if(!flag){
		question_list_ = get_my_favorite_queston(request_.userid());
		count_ = (question_list_.size() == 0)?0: (question_list_[0].size() == 0)?0:question_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 

		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			
			GRPC_Namespace::Question response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle); 
			
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			GRPC_Namespace::Question response;
			
			response.set_uuid(question_list_[0][question_list_[0].size() - count_ - 1]);
			response.set_title(question_list_[1][question_list_[0].size() - count_ - 1]);
			response.set_username(question_list_[2][question_list_[0].size() - count_ - 1]);
			response.set_createtime(question_list_[3][question_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> question_list_;
    
	int count_;

	bool flag = false;
};


//GetCollectArticle
template <class T> 
using AsyncStreamHandlerBase7 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Article, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler7 : public AsyncStreamHandlerBase7<AsyncStreamHandler7> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler7(Args&&... t) : AsyncStreamHandlerBase7<AsyncStreamHandler7> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {
	if(!flag){
		article_list_ = get_my_favorite_article(request_.userid());
		count_ = (article_list_.size() == 0)?0: (article_list_[0].size() == 0)?0:article_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		
		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			
			GRPC_Namespace::Article response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle); 
			
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			GRPC_Namespace::Article response;
			
			response.set_uuid(article_list_[0][article_list_[0].size() - count_ - 1]);
			response.set_title(article_list_[1][article_list_[0].size() - count_ - 1]);
			response.set_username(article_list_[2][article_list_[0].size() - count_ - 1]);
			response.set_createtime(article_list_[3][article_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> article_list_;
    
	int count_;

	bool flag = false;
};


//GetCollectAnswer
template <class T> 
using AsyncStreamHandlerBase8 = grpcserver::GenericAsyncHandler< 
    GRPC_Namespace::User, GRPC_Namespace::Answer, 
    grpcserver::AsyncStreamingWriter, T>; 
class AsyncStreamHandler8 : public AsyncStreamHandlerBase8<AsyncStreamHandler8> 
{ 
public:
    template<typename... Args> 
    AsyncStreamHandler8(Args&&... t) : AsyncStreamHandlerBase8<AsyncStreamHandler8> 
        (std::forward<Args>(t)...) {} 
    HandlerStatus SendResponse(void* opaque_handle) override 
    {
	if(!flag){
		answer_list_ = get_my_favorite_answer(request_.userid());
		count_ = (answer_list_.size() == 0)?0: (answer_list_[0].size() == 0)?0:answer_list_[0].size();
		flag = true;
	}
        HandlerStatus status = ACTIVE; 
		
		//if count_ == 0, return FINISHED directly
		if(count_ == 0){
			
			GRPC_Namespace::Answer response;
			
			grpc::WriteOptions options;
            responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle); 
			
			status = FINISHED;
			return status;
		}
		
		const bool is_finished = --count_ == 0;
        try {
			GRPC_Namespace::Answer response;
			
			response.set_answerid(answer_list_[0][answer_list_[0].size() - count_ - 1]);
			response.set_questionid(answer_list_[1][answer_list_[0].size() - count_ - 1]);
			response.set_questiontitle(answer_list_[2][answer_list_[0].size() - count_ - 1]);
			response.set_username(answer_list_[3][answer_list_[0].size() - count_ - 1]);
			response.set_createtime(answer_list_[4][answer_list_[0].size() - count_ - 1]);

			if (is_finished) {

				//add the last one at the end
                grpc::WriteOptions options;
                responder_->WriteAndFinish(response, options, grpc::Status::OK, opaque_handle);    
                status = FINISHED;
            }
            else{
                // simulate work by delaying 
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                responder_->Write(response, opaque_handle);   				
            }
        }
        catch(std::runtime_error& err) {
            std::cerr << "Error occurred: " << err.what() << std::endl;
            status = FINISHED;
        }
        catch(...) {
            std::cerr << "Internal error occurred" << std::endl;
            status = FINISHED;
        }
        return status;
    }
private:

	std::vector<std::vector<std::string>> answer_list_;
    	int count_;

	bool flag = false;
};



struct GrpcAsyncServerInfo {
    std::vector<std::shared_ptr<grpc::Service>> services_;
    std::vector<std::shared_ptr<grpcserver::AsyncServiceHandler>> handlers_;
};

void CreateGrpcAsyncServices(std::map<uint16_t /*port*/, GrpcAsyncServerInfo>& server_info_map) 
{
   // #define ServiceRequester(RequestMethod, svc) \
   //     std::bind(RequestMethod, svc, \
   //     std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
    //    std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)
		
	#define ServiceRequester(RequestMethod, svc) \
        std::bind(RequestMethod, svc, \
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
        std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)
		
    using GRPC_Generated_Service = GRPC_Namespace::PersonalInfo::AsyncService;
    auto* strm_svc = new GRPC_Generated_Service;
    auto& entry = server_info_map[9314];
	
	
	entry.handlers_.emplace_back(new AsyncStreamHandler(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetMyQuestion, strm_svc)));
	
	entry.handlers_.emplace_back(new AsyncStreamHandler2(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetMyAnswer, strm_svc)));
	
		
	entry.handlers_.emplace_back(new AsyncStreamHandler3(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetMyArticle, strm_svc)));
	
	entry.handlers_.emplace_back(new AsyncStreamHandler4(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetFans, strm_svc)));
		
	entry.handlers_.emplace_back(new AsyncStreamHandler5(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetFollowing, strm_svc)));
		
	entry.handlers_.emplace_back(new AsyncStreamHandler6(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetFavoriteQuestion, strm_svc)));
		
	entry.handlers_.emplace_back(new AsyncStreamHandler7(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetCollectArticle, strm_svc)));
		
	entry.handlers_.emplace_back(new AsyncStreamHandler8(
        ServiceRequester(&GRPC_Generated_Service::
        RequestGetCollectAnswer, strm_svc)));
	
	
	entry.services_.emplace_back(strm_svc);
}

int main(int, char**) {
   
    std::map<uint16_t, GrpcAsyncServerInfo> async_server_info_map; 
    CreateGrpcAsyncServices(async_server_info_map);
    std::vector<std::thread> async_server_threads;
    std::atomic_bool exit_bool(false);
    for (auto& info : async_server_info_map) {
        async_server_threads.emplace_back([info](
            const std::atomic_bool& should_exit) {
            const uint16_t port = info.first;
            grpcserver::GRPCAsyncServer server(
                port, info.second.services_,
                info.second.handlers_);
                server.Run(should_exit);
        }, std::cref(exit_bool));
    }
    std::cout << "Press Enter to exit..." << std::endl; 
    getchar(); 
    exit_bool = true;
	
	
    for (auto& thr : async_server_threads) 
        thr.join();
	
	
    std::cout << "Exited gracefully." << std::endl; 
  return 0;
}


