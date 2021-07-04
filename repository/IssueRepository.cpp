//
// Created by Alex on 7/4/2021.
//

#include "IssueRepository.h"

bool IssueRepository::add(const Issue &newIssue) {
    auto found = std::find(this->issues.begin(), this->issues.end(), newIssue);
    if(found == this->issues.end()){
        this->issues.push_back(newIssue);
        this->saveToFile();
        this->notify();
        return true;
    }
    return false;
}

bool IssueRepository::remove(const Issue &issue) {
    auto found = std::find(this->issues.begin(), this->issues.end(), issue);
    if(found != this->issues.end() && issue.getStatus() == "closed"){
        this->issues.erase(found);
        this->saveToFile();
        this->notify();
        return true;
    }
    return false;
}

void IssueRepository::saveToFile() {
    std::ofstream output("..\\issues.txt");
    if(!output.is_open())
        throw std::runtime_error("File could not open correctly!");
    for(const auto &issue : this->issues)
        if(&issue == &this->issues.back())
            output << issue;
        else
            output << issue << std::endl;
    output.close();
}

void IssueRepository::loadFromFile() {
    std::ifstream input("..\\issues.txt");
    if(!input.is_open())
        throw std::runtime_error("File could not open correctly!");
    Issue newIssue;
    while(!input.eof() && input >> newIssue)
        this->add(newIssue);
    input.close();
}

std::vector<Issue> IssueRepository::getIssues() const {
    return this->issues;
}