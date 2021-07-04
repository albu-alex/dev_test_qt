//
// Created by Alex on 7/4/2021.
//

#include "User.h"

User::User(const std::string &_name, const std::string &_type):name(_name),type(_type) {;}

std::string User::getName() const {
    return this->name;
}

std::string User::getType() const {
    return this->type;
}

void User::setName(const std::string &newName) {
    this->name = newName;
}

void User::setType(const std::string &newType) {
    this->type = newType;
}

bool User::operator==(const User &user) {
    return this->name == user.name && this->type == user.type;
}

bool User::operator!=(const User &user) {
    return this->name != user.name || this->type != user.type;
}

std::istream& operator >>(std::istream& input, User& user){
    std::getline(input, user.name, ',');
    std::getline(input, user.type, '\n');

    return input;
}

std::ostream& operator <<(std::ostream& output, const User& user){
    std::string user_to_string = user.name + ',' + user.type;
    output << user_to_string;
    return output;
}