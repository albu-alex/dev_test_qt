//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_USER_H
#include <string>
#define QT_DEV_TESTS_USER_H


class User {
private:
    std::string name;
    std::string type;
public:
    User(){;}
    ~User(){;}
    User(const std::string& _name, const std::string& _type);
    std::string getName() const;
    std::string getType() const;
    void setName(const std::string& newName);
    void setType(const std::string& newType);
    friend std::istream& operator >>(std::istream& input, User& user);
    friend std::ostream& operator <<(std::ostream& output, const User& user);
    bool operator ==(const User& user);
    bool operator !=(const User& user);
};


#endif //QT_DEV_TESTS_USER_H
