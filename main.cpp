//
// Created by Alex on 7/4/2021.
//

#include "GUI.h"
#include <QtWidgets>

int main(int argc, char** argv){
    QApplication a{argc, argv};
    IssueRepository issueRepository{};
    UserRepository userRepository{};
    userRepository.loadFromFile();
    std::vector<GUI*> gui;
    for(int i=0;i<userRepository.getUsers().size();i++)
        gui.push_back(new GUI{userRepository.getUsers()[i], issueRepository});
    return a.exec();
}