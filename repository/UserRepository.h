//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_USERREPOSITORY_H
#include "Repository.h"
#include "User.h"
#define QT_DEV_TESTS_USERREPOSITORY_H


class UserRepository: public Repository<User>, public ObserverUpdate{
private:
    std::vector<User> users;
    void saveToFile() override;
public:
    UserRepository(){;}
    ~UserRepository() override{;}
    void loadFromFile() override;
    bool add(const User& newUser) override;
    std::vector<User> getUsers() const;
};


#endif //QT_DEV_TESTS_USERREPOSITORY_H
