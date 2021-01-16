#ifndef CONNECTIONDB_H
#define CONNECTIONDB_H
#include <QObject>
#include <QSqlDatabase>
#include <memory>

class ConnectionDB : public QObject {
  Q_OBJECT
 public:
  ConnectionDB() {}
  ConnectionDB(ConnectionDB& other) = delete;    // deleted
  void operator=(const ConnectionDB&) = delete;  // deleted
  static ConnectionDB* getInstance(const QString str = "QSQLITE",
                                   const QString dbNameStr = ":memory:",
                                   QObject* parent = nullptr);  // static
  QSqlDatabase* getDB() { return &db; }
  bool queryExec(const QString str) const;  // query

 protected:
  ConnectionDB(const QString str = "QSQLITE",
               const QString dbNameStr = ":memory:", QObject* parent = nullptr);
  QSqlDatabase db;
  const QString dbType;
  const QString dbName;
  static ConnectionDB* singleton_;  // main instance
};

#endif  // CONNECTIONDB_H
