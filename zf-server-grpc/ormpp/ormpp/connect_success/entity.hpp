//
// Created by qiyu on 10/20/17.
//
#ifndef ORM_ENTITY_HPP
#define ORM_ENTITY_HPP
#include <set>
#include <string>


struct ormpp_not_null{
	std::string uuid;
    std::string work_num;
    std::string name;
    std::string password;
    std::string department;
    std::string job;
    std::string email;

    int point;
	std::string create_time;
	std::string update_time;
    int follow_count;

};

struct ormpp_key{
	std::string uuid;
};

struct ormpp_auto_key{
};

struct ormpp_unique {
};



/*
#include "dbng.hpp"

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

int main(){
	dbng<mysql> mysql;

	user_base p = {"1", "test1","meng1","123456","qwer","ttt","c++","107@nihao",1,NULL,NULL,2};
        user_base p1 = {"2", "test2","meng2","1234567","qwert","ttt1","c++14","108@nihao",2,NULL,NULL,2};
        user_base p2 = {"3", "test3","meng3","12345678","qwerp","ttt2","c++17","109@nihao",3,NULL,NULL,2};
        std::vector<user_base> v{p1, p2};

        mysql.connect("192.168.141.133", "root", "123456", "test");
        mysql.create_datatable<user_base>();
	mysql.connect("192.168.141.133", "root", "123456", "test");
        mysql.create_datatable<user_base>();

        mysql.insert(p);
        mysql.insert(v);

        mysql.update(p);
        mysql.update(v);

        auto result = mysql.query<user_base>(); //vector<person>
        for(auto& user_base : result){
		std::cout<<user_base.id<<" "<<user_base.name<<" "<<user_base.age<<std::endl;
        }

        mysql.delete_records<user_base>();

        //transaction
        mysql.begin();
        for (int i = 0; i < 10; ++i) {
            user_base s = {"4", "test3","meng3","12345678","qwerp","ttt2","c++17","109@nihao",3,NULL,NULL,2};
                if(!mysql.insert(s)){
                mysql.rollback();
                return -1;
            }
	}
        mysql.commit();


}
*/

#endif //ORM_ENTITY_HPP
