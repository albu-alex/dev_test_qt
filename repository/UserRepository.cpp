//
// Created by Alex on 7/4/2021.
//

#include "UserRepository.h"

bool UserRepository::add(const User &newUser) {
    auto found = std::find(this->users.begin(), this->users.end(), newUser);
    if(found == this->users.end()){
        this->users.push_back(newUser);
        this->saveToFile();
        this->notify();
        return true;
    }
    return false;
}

void UserRepository::saveToFile() {
    std::ofstream output("..\\users.txt");
    if(!output.is_open())
        throw std::runtime_error("File could not open correctly!");
    for (const auto& user: this->users)
        if(&user == &this->users.back())
            output << user;
        else
            output << user << std::endl;
    output.close();
}

void UserRepository::loadFromFile() {
    std::ifstream input("..\\users.txt");
    if(!input.is_open())
        throw std::runtime_error("File could not open correctly!");
    User newUser;
    while(!input.eof() && input >> newUser)
        this->add(newUser);
}

std::vector<User> UserRepository::getUsers() const {
    return this->users;
}