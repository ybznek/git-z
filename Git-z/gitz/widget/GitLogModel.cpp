#include "GitLogModel.hpp"


int gitz::widget::GitLogModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "delka" << size;
  return size;
}

int gitz::widget::GitLogModel::columnCount(const QModelIndex &parent) const { return 2; }

QVariant gitz::widget::GitLogModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= size)
    return QVariant{};

  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return "column";
    case 1:
      return "1";
    }
  }
  return QVariant{};
}

QVariant gitz::widget::GitLogModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
    switch (section) {
    case 0:
      return "Prvni";
    case 1:
      return "Druhy";
    }
  }
  return QVariant{};
}

void gitz::widget::GitLogModel::logUpdated() {
  size = git.getLogView()->length();
  qDebug() << "------------------------" << size;
  // todo update only changed values
  emit beginResetModel();
  emit endResetModel();
}
