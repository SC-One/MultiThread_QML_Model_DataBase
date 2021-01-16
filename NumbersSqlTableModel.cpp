#include "NumbersSqlTableModel.h"

#include <QDebug>
#include <QVariant>

NumbersSqlTableModel::NumbersSqlTableModel() {}

NumbersSqlTableModel::NumbersSqlTableModel(QObject *parent, QSqlDatabase db)
    : QSqlTableModel(parent, db)

{
  generateHeaders();
  generateRoleNames();
}

void NumbersSqlTableModel::generateRoleNames() {
  roles.clear();
  generateHeaders();
  for (int i = 0; i < columnCount(); i++) {
    roles[Qt::UserRole + i + 1] =
        QVariant(headerData(i, Qt::Horizontal).toString()).toByteArray();
  }
}

void NumbersSqlTableModel::generateHeaders() {
  headerList.clear();
  for (int i{0}; i < database().record("Numbers").count(); ++i)
    headerList.append(database().record("Numbers").field(i).name());
}

QVariant NumbersSqlTableModel::headerData(int section,
                                          Qt::Orientation orientation,
                                          int role) const

{
  return headerList[section];
}

QVariant NumbersSqlTableModel::data(const QModelIndex &index, int role) const {
  if (index.row() >= rowCount()) {
    return QString("");
  }
  if (role < Qt::UserRole) {
    return QSqlTableModel::data(index, role);
  }

  QModelIndex modelIndex = this->index(index.row(), role - Qt::UserRole - 1);
  return QSqlQueryModel::data(modelIndex, Qt::EditRole);
}

void NumbersSqlTableModel::setTable(const QString &table_name) {
  QSqlTableModel::setTable(table_name);
  generateRoleNames();
}
