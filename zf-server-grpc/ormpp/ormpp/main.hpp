#ifdef _MSC_VER
#ifdef _WIN64
#include <WinSock2.h>
#elif _WIN32
#include <winsock.h>
#endif

#include <time.h>

#endif
#include <iostream>
#include <thread>

#ifdef ORMPP_ENABLE_MYSQL
#include "mysql.hpp"
#endif

#ifdef ORMPP_ENABLE_SQLITE3
#include "sqlite.hpp"
#endif

#ifdef ORMPP_ENABLE_PG
#include "postgresql.hpp"
#endif

#include "dbng.hpp"
#include "connection_pool.hpp"
#include "ormpp_cfg.hpp"

/*
#define TEST_MAIN
#include "unit_test.hpp"
*/



#include <exception>
#include <json/json.h>
using namespace std::string_literals;



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

struct answer
{
	std::string uuid;
	std::string user_id;
	std::string question_id;
	std::string body;
	Json::Value photo_attach;
 	std::string video_attach;
	std::string create_time;
	std::string update_time;
	int deleted;
	int nameless;
	int like_count;
	int collect_count;
	int answer_count;

};
REFLECTION(answer, uuid, user_id, question_id, body, photo_attach, video_attach, create_time, update_time, deleted, nameless, like_count, collect_count, answer_count)


struct article{
	std::string uuid;
    std::string user_id;
    std::string title;
    std::string body;
    Json::Value photo_attach;
    std::string video_attach;
    std::string create_time;
    std::string update_time;
    int deleted;
    int like_count;
    int collect_count;
    int comment_count;

};
REFLECTION(article, uuid, user_id, title, body, photo_attach, video_attach, create_time, update_time, deleted, like_count, collect_count, comment_count)

struct comment{
	std::string uuid;
	std::string user_id;
	std::string answer_id;
	std::string comment;
	std::string create_time;
    std::string update_time;
	int deleted;
};
REFLECTION(comment, uuid, user_id, answer_id, comment, create_time, update_time, deleted)

struct draft{
	std::string uuid;
    std::string user_id;
    std::string question_id;
	std::string title;
    std::string body;
    Json::Value photo_attach;
    std::string video_attach;
	int status;
	std::string create_time;
    std::string update_time;
};
REFLECTION(draft, uuid, user_id, question_id, title, body, photo_attach, video_attach, status, create_time, update_time)

struct point{
	std::string uuid;
	std::string rule;
    std::string describe;
    int point_num;
	std::string create_time;
    std::string update_time;
};
REFLECTION(point, uuid, rule, describe, point_num, create_time, update_time)

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

struct reply{
	std::string uuid;
    std::string user_id;
	std::string answer_id;
	std::string comment_id;
	std::string reply_to;
	std::string reply_body;
	std::string create_time;
    std::string update_time;
	int deleted;
};
REFLECTION(reply, uuid, user_id, answer_id, comment_id, reply_to, reply_body, create_time, update_time, deleted)

struct user_answer_later{
	std::string uuid;
    std::string user_id;
	Json::Value later_answer;
	std::string create_time;
    std::string update_time;
};
REFLECTION(user_answer_later, uuid, user_id, later_answer, create_time, update_time)

struct user_collect{
	std::string uuid;
	int type;
	std::string user_id;
    std::string target_id;
	std::string create_time;
    std::string update_time;
};
REFLECTION(user_collect, uuid, type, user_id, target_id, create_time, update_time)

struct user_favorite{
	std::string uuid;
    std::string user_id;
    Json::Value favorite;
    std::string create_time;
    std::string update_time;
};
REFLECTION(user_favorite, uuid, user_id, favorite, create_time, update_time)

struct user_follow{
	std::string uuid;
    std::string user_id;
    std::string create_time;
    std::string update_time;
    std::string target_id;
	int type;
};
REFLECTION(user_follow, uuid, user_id, create_time, update_time, target_id, type)

struct user_likes{
	std::string uuid;
	int type;
	std::string user_id;
    std::string target_id;
    std::string create_time;
    std::string update_time;
};
REFLECTION(user_likes, uuid, type, user_id, target_id, create_time, update_time)

using namespace ormpp;

//由于ormpp没有提供接口，只能用默认的3306端口，所以暂时无法更改
const char* ip = "192.168.141.133"; //my database ip
const char* mysql_name = "root"; //my database login user name
const char* mysql_password = "123456"; //my database login user password
const char* mysql_db = "test"; //my database 
unsigned int port_ = 10133;//这里使用别的端口一样能够成功连接，所以应该如何配置连接的端口呢

/*
const char* ip = "cdb-7np7adgu.cd.tencentcdb.com"; //my database ip
//const char* ip = "CloudDataBase";
const char* mysql_name = "root"; //my database login user name
const char* mysql_password = "liangyue123456"; //my database login user password
const char* mysql_db = "ZhiFou"; //my database 
unsigned int port_ = 10133;//经测试，这里的port_并没有任何作用
*/

//std::vector<std::string> get_my_queston(std::string user_id){
std::vector<std::vector<std::string>> get_my_queston(std::string user_id){

	std::cout<<"func *get_my_queston* start"<< user_id<<std::endl;

	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db, port_);

	std::vector<std::string> res_uuid, res_title, res_username, res_createTime;
	std::string username;

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

		
			res_uuid.emplace_back(item.uuid);
			res_title.emplace_back(item.title);
			//res_username.push_back(username);
			res_username.emplace_back(username);
            		res_createTime.emplace_back(item.create_time);
		}
	}

	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_title);
	res.emplace_back(res_username);
	res.emplace_back(res_createTime);

	return res;

}


std::vector<std::vector<std::string>> get_my_answer(std::string user_id){
	//std::vector<std::string> res_uuid, res_quid, res_title, res_username, res_createTime;

	std::cout<<"func *get_my_answer* start"<< user_id<<std::endl;
	
	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	std::vector<std::string> res_uuid, res_quid, res_title, res_username, res_createTime;
	std::string username;

	auto find_name = mysql.query<user_base>();
	for(auto& item : find_name){
		if(item.uuid == user_id){
			username = item.name;
			break;
		}
	}

	auto result = mysql.query<answer>();
	for(auto& item : result){
		if(item.user_id == user_id){
			res_uuid.emplace_back(item.uuid);

			//根据question_id去对应的question表中找title
			std::string questionTitle;
			auto find_ques = mysql.query<question>();
			for(auto& item2 : find_ques){
				if(item2.uuid == item.question_id){
					questionTitle = item2.title;
					break;
				}
			}
			res_quid.push_back(item.question_id);
			res_title.emplace_back(questionTitle);
		
			res_username.emplace_back(username);
            		res_createTime.emplace_back(item.create_time);
		}
	}

	std::vector<std::vector<std::string>> res;
	
    	res.emplace_back(res_uuid);
    	res.emplace_back(res_quid);
    	res.emplace_back(res_title);
    	res.emplace_back(res_username);
    	res.emplace_back(res_createTime);

    	return res;


}


std::vector<std::vector<std::string>> get_my_article(std::string user_id){

	std::cout<<"func *get_my_article* start"<< user_id<<std::endl;

	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	std::vector<std::string> res_uuid, res_title, res_username, res_createTime;
	std::string username;

	auto find_name = mysql.query<user_base>();
	for(auto& item : find_name){
		if(item.uuid == user_id){
			username = item.name;
			break;
		}
	}

	auto result = mysql.query<article>();
	for(auto& item : result){

		if(item.user_id == user_id){

		
			res_uuid.emplace_back(item.uuid);
			res_title.emplace_back(item.title);
			//res_username.push_back(username);
			res_username.emplace_back(username);
            		res_createTime.emplace_back(item.create_time);
		}
	}

	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_title);
	res.emplace_back(res_username);
	res.emplace_back(res_createTime);

	return res;

}

std::vector<std::vector<std::string>> get_my_fans(std::string user_id){

	std::cout<<"func *get_my_fans* start"<< user_id<<std::endl;
	std::vector<std::string> res_uuid, res_username;
	
	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	auto result = mysql.query<user_follow>();
	for(auto& item : result){
		if((item.type == 2) && (item.target_id == user_id)){
			res_uuid.emplace_back(item.user_id);
			
			std::string username;
			auto find_name = mysql.query<user_base>();
			for(auto& item2 : find_name){
				if(item2.uuid == item.user_id){
					username = item2.name;
					break;
				}
			}			
			res_username.emplace_back(username);
		}
	}

	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_username);

	return res;
}

std::vector<std::vector<std::string>> get_my_following(std::string user_id){

	std::vector<std::string> res_uuid, res_username;
	std::cout<<"func *get_my_following* start"<< user_id<<std::endl;
	
	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	auto result = mysql.query<user_follow>();
	for(auto& item : result){
		if((item.type == 2) && (item.user_id == user_id)){
			res_uuid.emplace_back(item.target_id);
			
			std::string username;
			auto find_name = mysql.query<user_base>();
			for(auto& item2 : find_name){
				if(item2.uuid == item.target_id){
					username = item2.name;
					break;
				}
			}			
			res_username.emplace_back(username);
		}
	}

	
	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_username);

	return res;
}


std::vector<std::vector<std::string>> get_my_favorite_queston(std::string user_id){
	
	std::vector<std::string> res_uuid, res_title, res_username, res_createTime;

	std::cout<<"func *get_my_favorite_queston* start"<< user_id<<std::endl;

	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	//user_favorite表被弃用了，要从user_follow表进行查询
	auto result = mysql.query<user_follow>();
	for(auto& item : result){

		if((item.user_id == user_id) && (item.type == 1)){
			res_uuid.emplace_back(item.target_id);

			auto find_ques = mysql.query<question>();
			for(auto& item2 : find_ques){
				if(item2.uuid == item.target_id){
					res_title.emplace_back(item2.title);
					res_createTime.emplace_back(item2.create_time);
					auto find_name = mysql.query<user_base>();
					for(auto& item3 : find_name){
						if(item3.uuid == item2.user_id){
							res_username.emplace_back(item3.name);
							break;
						}
					}
					break;
				}
				
			}
		}
	}


	std::vector<std::vector<std::string>> res;
	res.emplace_back(res_uuid);
	res.emplace_back(res_title);
	res.emplace_back(res_username);
	res.emplace_back(res_createTime);

	return res;
}


std::vector<std::vector<std::string>> get_my_favorite_article(std::string user_id){
	std::vector<std::string> res_uuid, res_title, res_username, res_createDate;

	std::cout<<"func *get_my_favorite_article* start"<< user_id<<std::endl;

	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);	

	//考虑使用set容器来装目标文章的id
	std::set<std::string> articleId;

	auto result = mysql.query<user_collect>();
	for(auto& item : result){
		if(item.user_id == user_id){

			if(item.type == 2){
				articleId.insert(item.target_id);
			}
		}

	}

	auto result2 = mysql.query<article>();
	for(auto& item : result2){
		//找到一个插入一个，并把已经找到的删除
		if(articleId.find(item.uuid) != articleId.end()){
			res_uuid.emplace_back(item.uuid);
			res_title.emplace_back(item.title);

			//根据user_id去找username
			std::string username;
			auto find_name = mysql.query<user_base>();
			for(auto& item2 : find_name){
				if(item2.uuid == item.user_id){
					username = item2.name;
					break;
				}
			}			

			res_username.emplace_back(username);
            		res_createDate.emplace_back(item.create_time);
			
			articleId.erase(item.uuid);
		}
	}


	std::vector<std::vector<std::string>> res;
	
	res.emplace_back(res_uuid);
	res.emplace_back(res_title);
	res.emplace_back(res_username);
	res.emplace_back(res_createDate);

	return res;
}

std::vector<std::vector<std::string>> get_my_favorite_answer(std::string user_id){
	std::vector<std::string> res_uuid, res_quid, res_title, res_username, res_createTime;

	std::cout<<"func *get_my_favorite_answer* start"<< user_id<<std::endl;
	
	dbng<mysql> mysql;
    	mysql.connect(ip, mysql_name, mysql_password, mysql_db);	

	//考虑使用set容器来装目标回答的id
	std::set<std::string> answerId;

	auto result = mysql.query<user_collect>();
	for(auto& item : result){
		if(item.user_id == user_id){
			if(item.type == 1){
				answerId.insert(item.target_id);
			}
		}
	}
	
	auto result2 = mysql.query<answer>();
	for(auto& item : result2){
		//找到一个插入一个，并把已经找到的删除
		if(answerId.find(item.uuid) != answerId.end()){
			res_uuid.emplace_back(item.uuid);
			res_quid.emplace_back(item.question_id);

			//根据question_id去对应的question表中找title
			std::string questionTitle;
			auto find_ques = mysql.query<question>();
			for(auto& item2 : find_ques){
				if(item2.uuid == item.question_id){
					questionTitle = item2.title;
					break;
				}
			}
			res_title.emplace_back(questionTitle);

			//根据user_id去找username
			std::string username;
			auto find_name = mysql.query<user_base>();
			for(auto& item3 : find_name){
				if(item3.uuid == item.user_id){
					username = item3.name;
					break;
				}
			}			

			res_username.emplace_back(username);
            		res_createTime.emplace_back(item.create_time);
			
			answerId.erase(item.uuid);
		}
	}


	std::vector<std::vector<std::string>> res;
	
    	res.emplace_back(res_uuid);
    	res.emplace_back(res_quid);
    	res.emplace_back(res_title);
    	res.emplace_back(res_username);
    	res.emplace_back(res_createTime);

    	return res;
}


/*
TEST_CASE(get_my_question){//table question
//std:string get_my_question(){
	

	dbng<mysql> mysql;
	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	auto result = mysql.query<question>();

	for(auto& tt : result){
		std::cout<<"uuid:"<<tt.uuid<<",user_id:"<<tt.user_id<<",title:"<<tt.title<<",body:"<<tt.body<<",photo_attach:"<<tt.photo_attach<<",video_attach:"<<tt.video_attach<<",answer_num:"<<tt.answer_num<<",page_views:"<<tt.page_views<<",create_time:"<<tt.create_time<<",update_time:"<<tt.update_time<<",deleted:"<<tt.deleted<<",nameless:"<<tt.nameless<<",draft:"<<tt.draft<<",follow_count:"<<tt.follow_count<<std::endl;
	
	
	}

	std::cout<<"***************************************"<<std::endl;
}
*/

/*
TEST_CASE(get_my_reply){//table reply
	dbng<mysql> mysql;
    mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	try{
		//给timestamp类型赋值
    	time_t t;  //秒时间
    	tm* local; //本地时间
    	char buf[128] = { 0 };
    	t = time(NULL); //获取目前秒时间
   		// cout << t << endl;
    	local = localtime(&t); //转为本地时间
   	//	local->tm_hour = 0;
	  //  local->tm_min = 0;
    	//local->tm_sec = 0;
    	strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
	
	//	reply r = {"2", "2","2", "2","2","我是谁，我在哪", buf, buf, 1};

	//	mysql.insert(r);
		std::string tmp = const_cast<char *>(buf);
		int r = mysql.execute("insert into reply(uuid, user_id, answer_id,comment_id, reply_to, reply_body, deleted) values ('4', '4', '4','4','4','我是谁，我在哪', 2)");
		TEST_REQUIRE(r);
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}

    auto result = mysql.query<reply>();
    
	for(auto& tt : result){
			std::cout<<"uuid:"<<tt.uuid<<",user_id:"<<tt.user_id<<",answer_id:"<<tt.answer_id<<",comment_id:"<<tt.comment_id<<",reply_to:"<<tt.reply_to<<",reply_body:"<<tt.reply_body<<",create_time:"<<tt.create_time<<",update_time:"<<tt.update_time<<",deleted:"<<tt.deleted<<std::endl;
	}

	std::cout<<"***************************************"<<std::endl;
}
*/



/*
TEST_CASE(mysql_more_table){
	dbng<mysql> mysql;

	//给timestamp类型赋值
	time_t t;  //秒时间
    tm* local; //本地时间
    char buf[128] = { 0 };
    t = time(NULL); //获取目前秒时间
   // cout << t << endl;
    local = localtime(&t); //转为本地时间
    local->tm_hour = 0;
    local->tm_min = 0;
    local->tm_sec = 0;
    strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
	
	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	//遇到这种难以赋值的json类型自断，直接用sql语言进行插入	
	//注意这个语句如果出现主键重复会报错，后面要在这里加一个try...catch，或者别的处理程序
	//int	r = mysql.execute("insert into answer(uuid, user_id, question_id) values (0528, 0528, 0528)");
	//TEST_REQUIRE(r);

	auto result = mysql.query<answer>();

	for(auto& tt : result){
		std::cout<<">>> uuid:"<<tt.uuid<<", user_id:"<<tt.user_id<<", question_id:"<<tt.question_id<<std::endl;
	}

	std::cout<<"************************"<<std::endl;
}
*/


/*
TEST_CASE(mysql_performance){

	dbng<mysql> mysql;
	time_t t;  //秒时间
    tm* local; //本地时间
    char buf[128] = { 0 };

    t = time(NULL); //获取目前秒时间
   // cout << t << endl;
    local = localtime(&t); //转为本地时间
    local->tm_hour = 0;
    local->tm_min = 0;
    local->tm_sec = 0;
    strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);

    user_base p = {"1", "test1","meng1","123456","qwer","ttt","c++","107@nihao",1,buf,buf,2};
    user_base p1 = {"2", "test2","meng2","1234567","qwert","ttt1","c++14","108@nihao",2,buf,buf,2};
    user_base p2 = {"3", "test3","meng3","12345678","qwerp","ttt2","c++17","109@nihao",3,buf,buf,2};
    std::vector<user_base> v{p1, p2};

    mysql.connect(ip, "root", "123456", "test");
    //mysql.connect("192.168.141.133", "root", "123456", "test");
//        mysql.create_datatable<user_base>();
    mysql.insert(p);
    mysql.insert(v);

    mysql.update(p);
    mysql.update(v);

    auto result = mysql.query<user_base>(); //vector<person>
    for(auto& user_base : result){
    	std::cout<<user_base.uuid<<" "<<user_base.name<<" "<<user_base.name<<std::endl;
    }

//transaction
    mysql.begin();

	auto r = mysql.query<user_base>();
    auto& ww = r[0];
    	
	auto tmp = ww.email;
	
	for (int i = 0; i < 2; ++i) {
        user_base s = {"5", "test3","meng3","12345678","qwerp","ttt2","C++20",tmp,3,buf,buf,2}; 
		if(!mysql.insert(s)){
            mysql.rollback();
        	//return -1;
        }
    }
    mysql.commit();
	
	std::cout<<"************************"<<std::endl;

}
*/

/*
TEST_CASE(table_question_test){
	
	dbng<mysql> mysql;

	mysql.connect(ip, mysql_name, mysql_password, mysql_db);

	auto res = mysql.query<question>();	
	for(auto& tt : res){
        std::cout<<tt.uuid<<" "<<tt.user_id<<" "<<tt.title<<std::endl;
    }

	std::cout<<"************************"<<std::endl;

}
*/

