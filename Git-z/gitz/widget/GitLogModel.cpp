#include "GitLogModel.hpp"


int gitz::widget::GitLogModel::rowCount(const QModelIndex &parent) const {
  qDebug() << "delka" << size;
  return size;
}

int gitz::widget::GitLogModel::columnCount(const QModelIndex &parent) const { return _max_column_; }

QVariant gitz::widget::GitLogModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= size)
    return QVariant{};
  LockedLog log = git.getLogView();
  const GitLogItem &item = (*log)[index.row()];
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case DATE_COLUMN:
      return item.getDate();
    case COMMIT_COLUMN:
      return item.getCommitHash();
    case AUTHOR_COLUMN:
      return item.getAuthor();
    case SUBJECT_COLUMN:
      return item.getSubject();
    }
  }
  return QVariant{};
}

QVariant gitz::widget::GitLogModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if ((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
    switch (section) {
    case DATE_COLUMN:
      return "Date";
    case COMMIT_COLUMN:
      return "#";
    case AUTHOR_COLUMN:
      return "Author";
    case SUBJECT_COLUMN:
      return "Subject";
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
  table->resizeColumnsToContents();
}
