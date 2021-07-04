//
// Created by Alex on 7/4/2021.
//

#include "AbstractModel.h"

AbstractModel::AbstractModel(IssueRepository &_issueRepository, QObject *parent):issueRepository(_issueRepository),QAbstractTableModel{parent} {;}

AbstractModel::~AbstractModel(){;}

int AbstractModel::rowCount(const QModelIndex &parent) const {
    return this->issueRepository.getIssues().size();
}

int AbstractModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant AbstractModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if(role == Qt::FontRole){
        QFont qFont{QString::fromStdString(this->font_name), this->font_size};
        return qFont;
    }
    if(role == Qt::DisplayRole){
        Issue currentIssue = this->issueRepository.getIssues()[row];
        if(column < 0 || column > 3)
            throw std::exception();
        if(column == 0)
            return QString::fromStdString(currentIssue.getDescription());
        if(column == 1)
            return QString::fromStdString(currentIssue.getStatus());
        if(column == 2)
            return QString::fromStdString(currentIssue.getReporter());
        if(column == 3)
            return QString::fromStdString(currentIssue.getSolver());
    }
    return QVariant();
}

QVariant AbstractModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::FontRole){
        QFont qFont{QString::fromStdString(this->font_name), this->font_size};
        qFont.setBold(true);
        return qFont;
    }
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section < 0 || section > 3)
                throw std::exception();
            if(section == 0)
                return QString{"Description"};
            if(section == 1)
                return QString{"Status"};
            if(section == 2)
                return QString{"Reporter name"};
            if(section == 3)
                return QString{"Solver name"};
        }
    }
    return QVariant();
}

bool AbstractModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::EditRole)
        return false;
    int row = index.row();
    int column = index.column();
    if(row == this->issueRepository.getIssues().size()){
        this->beginInsertRows(QModelIndex{}, row, row);
        if(column < 0 || column > 3)
            throw std::exception();
        if(column == 0)
            this->issueRepository.getIssues().emplace_back(value.toString().toStdString(), "", "", "");
        if(column == 1)
            this->issueRepository.getIssues().emplace_back("", value.toString().toStdString(), "", "");
        if(column == 2)
            this->issueRepository.getIssues().emplace_back("", "", value.toString().toStdString(), "");
        if(column == 3)
            this->issueRepository.getIssues().emplace_back("", "", "", value.toString().toStdString());
        this->endInsertRows();
        return true;
    }
    Issue currentIssue = this->issueRepository.getIssues()[row];
    if(column < 0 || column > 3)
        throw std::exception();
    if(column == 0)
        currentIssue.setDescription(value.toString().toStdString());
    if(column == 1)
        currentIssue.setStatus(value.toString().toStdString());
    if(column == 2)
        currentIssue.setReporter(value.toString().toStdString());
    if(column == 3)
        currentIssue.setSolver(value.toString().toStdString());
    this->issueRepository.getIssues()[row] = currentIssue;
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags AbstractModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void AbstractModel::updateInternalData() {
    endResetModel();
}