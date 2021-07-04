//
// Created by Alex on 7/4/2021.
//

#ifndef QT_DEV_TESTS_GUI_H
#include "Observer.h"
#include <QWidget>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QMainWindow>
#include <qstringlistmodel.h>
#include <QSortFilterProxyModel>
#include <QMessageBox>
#include "AbstractModel.h"
#include "UserRepository.h"
#include "IssueRepository.h"
#define QT_DEV_TESTS_GUI_H


class GUI: public QWidget, public Observer {
    Q_OBJECT
private:
    User& user;
    IssueRepository& issueRepository;
    QLineEdit* description;
    AbstractModel* table;
    QTableView* tableView;
    QSortFilterProxyModel* filterProxyModel;
    QPushButton* add, *remove;
public:
    explicit GUI(User& _user, IssueRepository& _issueRepository, QWidget* parent = nullptr);
    ~GUI() override;
    void initGUI();
    void connectSignalAndSlots();
    void update() override;
    void notifyModel();
    int getSelectedIndex();
public slots:
    void addButton_handler();
    void removeButton_handler();
};


#endif //QT_DEV_TESTS_GUI_H
