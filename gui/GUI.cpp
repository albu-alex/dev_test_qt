//
// Created by Alex on 7/4/2021.
//

#include "GUI.h"

GUI::GUI(User &_user, IssueRepository &_issueRepository, QWidget *parent):user(_user),issueRepository(_issueRepository),QWidget(parent) {
    this->issueRepository.loadFromFile();
    this->issueRepository.addObserver(this);
    this->initGUI();
    this->connectSignalAndSlots();
    this->show();
}

GUI::~GUI(){
    this->issueRepository.removeObserver(this);
}

void GUI::notifyModel() {
    this->table->updateInternalData();
}

void GUI::update() {
    this->notifyModel();
}

void GUI::initGUI() {
    QVBoxLayout* main = new QVBoxLayout{this};
    this->description = new QLineEdit{};
    this->add = new QPushButton{"Add"};
    this->remove = new QPushButton{"Remove"};
    this->resolve = new QPushButton{"Resolve"};

    this->table = new AbstractModel{this->issueRepository};
    this->tableView = new QTableView{};

    this->filterProxyModel = new QSortFilterProxyModel{};
    this->filterProxyModel->setSourceModel(this->table);
    this->tableView->setSortingEnabled(true);
    this->filterProxyModel->sort(2);

    this->tableView->setModel(this->filterProxyModel);

    main->addWidget(this->tableView);

    QGridLayout* buttons = new QGridLayout{};
    buttons->addWidget(this->add, 0, 0);
    buttons->addWidget(this->remove, 0, 2);
    buttons->addWidget(this->resolve, 1, 1);

    main->addLayout(buttons);

    QFormLayout* newDescription = new QFormLayout{};
    newDescription->addRow("Description", this->description);
    main->addLayout(newDescription);

    this->user_name = this->user.getName();
    this->user_type = this->user.getType();
    QWidget::setWindowTitle(QString::fromStdString(this->user_name + ',' + this->user_type));
}

void GUI::connectSignalAndSlots() {
    QObject::connect(this->add, &QPushButton::clicked, this, &GUI::addButton_handler);
    QObject::connect(this->remove, &QPushButton::clicked, this, &GUI::removeButton_handler);
    QObject::connect(this->resolve, &QPushButton::clicked, this, &GUI::resolveButton_handler);
    QObject::connect(this->tableView, &QTableView::clicked, this, &GUI::checkIfRemoveAvailable);
    QObject::connect(this->tableView, &QTableView::clicked, this, &GUI::checkIfResolveAvailable);
}

int GUI::getSelectedIndex() {
    auto selectedIndexes = this->tableView->selectionModel()->selectedIndexes();
    if(selectedIndexes.isEmpty())
        return -1;
    int selectedRow = selectedIndexes.at(0).row();
    return selectedRow;
}

void GUI::addButton_handler() {
    if(this->user_type != "tester"){
        QMessageBox::critical(this, "Error", "Only testers can report new issues!");
        return;
    }
    std::string newDescription = this->description->text().toStdString();
    if(newDescription.empty()){
        QMessageBox::critical(this, "Error", "The description must not be empty!");
        return;
    }
    for(const auto &issue: this->issueRepository.getIssues())
        if(issue.getDescription() == newDescription){
            QMessageBox::critical(this, "Error", "The new description must not match older descriptions!");
            return;
        }
    Issue newIssue{newDescription, "open", this->user_name, NULL_NAME};
    this->issueRepository.add(newIssue);
}

void GUI::checkIfRemoveAvailable() {
    int index = this->getSelectedIndex();
    std::string status = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    if(status != "closed")
        this->remove->setEnabled(false);
    else
        this->remove->setEnabled(true);
}

void GUI::checkIfResolveAvailable() {
    int index = this->getSelectedIndex();
    std::string status = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    if(status != "open")
        this->resolve->setEnabled(false);
    else
        this->resolve->setEnabled(true);
}

void GUI::removeButton_handler() {
    int index = this->getSelectedIndex();
    std::string name = this->filterProxyModel->index(index, 0).data().toString().toStdString();
    std::string status = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    std::string reporter = this->filterProxyModel->index(index, 2).data().toString().toStdString();
    std::string solver = this->filterProxyModel->index(index, 3).data().toString().toStdString();
    Issue removedIssue{name, status, reporter, solver};
    this->issueRepository.remove(removedIssue);
}

void GUI::resolveButton_handler() {
    if(this->user_type != "programmer"){
        QMessageBox::critical(this, "Error", "Only programmers can resolve open issues!");
        return;
    }
    int index = this->getSelectedIndex();
    std::string name = this->filterProxyModel->index(index, 0).data().toString().toStdString();
    std::string status = this->filterProxyModel->index(index, 1).data().toString().toStdString();
    std::string reporter = this->filterProxyModel->index(index, 2).data().toString().toStdString();
    std::string solver = this->filterProxyModel->index(index, 3).data().toString().toStdString();
    Issue resolvedIssue{name, status, reporter, solver};
    this->issueRepository.resolve(resolvedIssue, this->user_name);
}
