#include "GraphViewModel.hpp"


gitz::widget::GraphViewModel::GraphViewModel(QObject *parent) : QAbstractTableModel{parent} { ; }

int gitz::widget::GraphViewModel::rowCount(const QModelIndex &parent) const {

  qDebug() << "model vraci" << list.size();
  return list.size();
}

QVariant gitz::widget::GraphViewModel::headerData(int section, Qt::Orientation orientation, int role) const {
  return "header";
}

int gitz::widget::GraphViewModel::columnCount(const QModelIndex &parent) const { return 4; }

QVariant gitz::widget::GraphViewModel::data(const QModelIndex &index, int role) const { return "ahoj"; }

void gitz::widget::GraphViewModel::notifyDataChanged() {
  auto const log = git->getLogView();
  int length = log->length();
  list.setSize(length);

  for (int i = 0; i < length; ++i) {
    GraphItem &it = list[i];
    const GitLogItem &logIt = (*log)[i];
    it.commit = logIt.getCommitHash();
    it.author = logIt.getAuthor();
    it.subject = logIt.getSubject();
  }
  emit dataChanged(this->index(0, 0), this->index(4, length));
}

void gitz::widget::GraphViewModel::setGit(gitz::Git *git) { this->git = git; }
