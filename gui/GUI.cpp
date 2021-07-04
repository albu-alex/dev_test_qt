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

    main->addLayout(buttons);

    QFormLayout* newDescription = new QFormLayout{};
    newDescription->addRow("Description", this->description);
    main->addLayout(newDescription);

    QWidget::setWindowTitle(QString::fromStdString(this->user.getName() + ',' + this->user.getType()));
}

void GUI::connectSignalAndSlots() {
    QObject::connect(this->add, &QPushButton::clicked, this, &GUI::addButton_handler);
    QObject::connect(this->remove, &QPushButton::clicked, this, &GUI::removeButton_handler);
    //check if remove available
}

int GUI::getSelectedIndex() {
    return 0;
}

void GUI::addButton_handler() {
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
    Issue newIssue{newDescription, "open", this->user.getName(), " "};
    this->issueRepository.add(newIssue);
}

void GUI::removeButton_handler() {
    ;
}
