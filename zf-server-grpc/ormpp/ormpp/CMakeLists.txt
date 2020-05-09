cmake_minimum_required(VERSION 3.2)
project(ormpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -std=c++17")
SET(ENABLE_MYSQL ON)
SET(ENABLE_PG OFF)
SET(ENABLE_SQLITE3 OFF)
if (ENABLE_MYSQL)
add_definitions(-DORMPP_ENABLE_MYSQL)
set(SOURCE_FILES test.cpp   main.hpp dbng.hpp pg_types.h        type_mapping.hpp utility.hpp entity.hpp mysql.hpp        connection_pool.hpp ormpp_cfg.hpp)
endif()
if (ENABLE_SQLITE3)
add_definitions(-DORMPP_ENABLE_SQLITE3)
set(SOURCE_FILES main.cpp dbng.hpp unit_test.hpp pg_types.h
        type_mapping.hpp utility.hpp entity.hpp  sqlite.hpp connection_pool.hpp ormpp_cfg.hpp)
endif()
if (ENABLE_PG)
add_definitions(-DORMPP_ENABLE_PG)
set(SOURCE_FILES main.cpp dbng.hpp unit_test.hpp pg_types.h
        type_mapping.hpp utility.hpp entity.hpp  postgresql.hpp connection_pool.hpp ormpp_cfg.hpp)
endif()

INCLUDE_DIRECTORIES(
                    ${CMAKE_SOURCE_DIR}/../iguana
		    /usr/include/mysql
		    /usr/include/postgresql
			/usr/include/c++/7
			)
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)



add_executable(ormpp ${SOURCE_FILES})

target_link_libraries(ormpp json)
if (ENABLE_MYSQL)
target_link_libraries(ormpp mysqlclient)
endif()
if (ENABLE_SQLITE3)
target_link_libraries(ormpp sqlite3)
endif()
if (ENABLE_PG)
target_link_libraries(ormpp pq)
endif()
