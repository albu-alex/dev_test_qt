//
// Created by Alex on 7/4/2021.
//

#include "Issue.h"

Issue::Issue(const std::string &_description, const std::string &_status, const std::string &_reporter,
             const std::string &_solver):description(_description),status(_status),reporter(_reporter),solver(_solver) {;}


std::string Issue::getDescription() const {
    return this->description;
}

std::string Issue::getStatus() const {
    return this->status;
}

std::string Issue::getReporter() const {
    return this->reporter;
}

std::string Issue::getSolver() const {
    return this->solver;
}

void Issue::setDescription(const std::string &newDescription) {
    this->description = newDescription;
}

void Issue::setStatus(const std::string &newStatus) {
    this->status = newStatus;
}

void Issue::setReporter(const std::string &newReporter) {
    this->reporter = newReporter;
}

void Issue::setSolver(const std::string &newSolver) {
    this->solver = newSolver;
}

bool Issue::operator==(const Issue &issue) {
    return this->description == issue.description && this->status == issue.status;
}

bool Issue::operator!=(const Issue &issue) {
    return this->description != issue.description || this->status != issue.status;
}

std::istream& operator >>(std::istream& input, Issue& issue){
    std::getline(input, issue.description, ',');
    std::getline(input, issue.status, ',');
    std::getline(input, issue.reporter, ',');
    std::getline(input, issue.solver, '\n');

    return input;
}

std::ostream& operator <<(std::ostream& output, const Issue& issue){
    std::string issue_to_string = issue.description + ',' + issue.status + ',' + issue.reporter + ',' + issue.solver;
    output << issue_to_string;
    return output;
}