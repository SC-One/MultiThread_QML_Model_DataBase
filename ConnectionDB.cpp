#include "ConnectionDB.h"

#include <QDebug>
#include <QSqlQuery>

ConnectionDB *ConnectionDB::singleton_{nullptr};
ConnectionDB::ConnectionDB(const QString str, const QString dbNameStr,
                           QObject *parent)
    : QObject(parent),
      db{QSqlDatabase::addDatabase(str)},
      dbType{str},
      dbName(dbNameStr)

{
  db.setDatabaseName(dbNameStr);
  if (!db.open()) std::runtime_error("not opened!");
}

ConnectionDB *ConnectionDB::getInstance(const QString str,
                                        const QString dbNameStr,
                                        QObject *parent)

{
  if (singleton_ == nullptr) {
    singleton_ = new ConnectionDB(str, dbNameStr, parent);
  }
  return singleton_;
}

bool ConnectionDB::queryExec(const QString str) const {
  if (db.isOpen()) {
    QSqlQuery query;
    return query.exec(str);
  }
  return false;
}
