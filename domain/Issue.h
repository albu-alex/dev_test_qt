//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_ISSUE_H
#include <string>
#define QT_DEV_TESTS_ISSUE_H


class Issue {
private:
    std::string description;
    std::string status;
    std::string reporter;
    std::string solver;
public:
    Issue(){;}
    ~Issue(){;}
    Issue(const std::string& _description, const std::string& _status, const std::string& _reporter, const std::string& _solver);
    std::string getDescription() const;
    std::string getStatus() const;
    std::string getReporter() const;
    std::string getSolver() const;
    void setDescription(const std::string& newDescription);
    void setStatus(const std::string& newStatus);
    void setReporter(const std::string& newReporter);
    void setSolver(const std::string& newSolver);
    bool operator ==(const Issue& issue);
    bool operator !=(const Issue& issue);
    friend std::istream& operator >>(std::istream& input, Issue& issue);
    friend std::ostream& operator <<(std::ostream& output, const Issue& issue);
};


#endif //QT_DEV_TESTS_ISSUE_H
