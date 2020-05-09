
//#pragma once
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <csignal>
#include "main.hpp"


int main(){

	std::vector<std::vector<std::string>> qqq = ormpp::get_my_queston(std::string("5e167f59fe02420f9a2e6e575cfe3abe"));
	for(auto& tt : qqq){
		for(auto& ww : tt){
			std::cout<<ww<<std::endl;
		}
	}
	return 0;

}





/*
#include "dbng.hpp"
//#include "main.cpp"

using namespace ormpp;


struct user_base
{
	std::string uuid;
    std::string work_num;
    std::string name;
    std::string password;
    std::string picture;
    std::string department;
    std::string job;
    std::string email;

    int point;
	std::string create_time;
	std::string update_time;
    int follow_count;
};
REFLECTION(user_base, uuid, work_num, name, password, picture, department, job, email, point, create_time, update_time, follow_count)


struct question{
	std::string uuid;
    std::string user_id;
    std::string title;
    std::string body;
    Json::Value photo_attach;
    std::string video_attach;
	int answer_num;
	int page_views;
	std::string create_time;
    std::string update_time;
	int deleted;
	int nameless;
	int draft;
	int follow_count;
};
REFLECTION(question, uuid, user_id, title, body, photo_attach, video_attach, answer_num, page_views, create_time, update_time, deleted, nameless, draft, follow_count)

const char* ip = "192.168.141.133"; //my database ip
const char* mysql_name = "root"; //my database login user name
const char* mysql_password = "123456"; //my database login user password
const char* mysql_db = "test"; //my database 


std::vector<std::vector<std::string>> get_my_queston(std::string user_id){

//TEST_CASE(get_my_queston){
	
	//user_id = "5e167f59fe02420f9a2e6e575cfe3abe";
	
	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	std::vector<std::string> res_uuid, res_title, res_username, res_createTime;
	std::string tmp, username;

	auto find_name = mysql.query<user_base>();
	for(auto& item : find_name){
		if(item.uuid == user_id){
			username = item.name;
			break;
		}
	}

	auto result = mysql.query<question>();
	for(auto& item : result){
		if(item.user_id == user_id){
//			tmp = item.uuid + item.title + username + item.createTime;
			res_uuid.emplace_back(item.uuid);
			res_title.emplace_back(item.title);
			res_username.emplace_back(username);
            		res_createTime.emplace_back(item.create_time);
		}
	}

	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_title);
	res.emplace_back(res_username);
	res.emplace_back(res_createTime);

	//return res;
}


int main()
{
	std::vector<std::vector<std::string>> qqq = get_my_queston("5e167f59fe02420f9a2e6e575cfe3abe");
	for(auto& tt : qqq){
		for(auto& ww : tt){
			std::cout<<"ww"<<std::endl;
		}
	}
	return 0;
	
}
*/

