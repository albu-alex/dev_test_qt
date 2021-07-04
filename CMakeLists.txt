cmake_minimum_required(VERSION 3.17)
project(qt_dev_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:\\Cursuri\\qt\\5.15.2\\mingw81_64\\lib\\cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)

find_package(Qt5Widgets REQUIRED)

include_directories(domain)
include_directories(repository)
include_directories(observer)

add_executable(qt_dev_tests
        domain/User.cpp
        domain/User.h
        domain/Issue.cpp
        domain/Issue.h
        repository/Repository.h
        repository/UserRepository.cpp
        repository/UserRepository.h
        observer/Observer.h repository/IssueRepository.cpp repository/IssueRepository.h)

target_link_libraries(qt_dev_tests Qt5::Widgets)
