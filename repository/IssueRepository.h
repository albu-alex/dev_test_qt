//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_ISSUEREPOSITORY_H
#include "Repository.h"
#include "Issue.h"
#define QT_DEV_TESTS_ISSUEREPOSITORY_H


class IssueRepository:public Repository<Issue>, public ObserverUpdate {
private:
    std::vector<Issue> issues;
    void saveToFile() override;
public:
    IssueRepository(){;}
    ~IssueRepository() override{;}
    void loadFromFile() override;
    bool add(const Issue& newIssue) override;
    std::vector<Issue> getIssues() const;
    bool remove(const Issue& issue);
};


#endif //QT_DEV_TESTS_ISSUEREPOSITORY_H
