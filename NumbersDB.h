#ifndef NUMBERSDB_H
#define NUMBERSDB_H

#include <NumbersSqlTableModel.h>

#include <QFuture>
#include <QObject>
#include <QtSql/QSqlTableModel>
#include <thread>

#include "Macros.h"
class NumbersDB : public QObject {
  Q_OBJECT
  Q_PROPERTY(QSqlTableModel *model READ getModel NOTIFY modelChanged)
 public:
  explicit NumbersDB(QObject *parent = nullptr);
  ~NumbersDB() { stopAdding(); }
  QSqlTableModel *getModel() { return model.get(); }

 signals:
  void modelChanged(double to, double from = 0);

 public slots:
  void addFakeValues();
  Q_INVOKABLE void startAdding();
  Q_INVOKABLE void stopAdding();

 private:
  void initMain();
  void initModel();
  void createTable();
  std::unique_ptr<NumbersSqlTableModel> model;
  const QString tableName;
  std::thread worker;
  bool working;
};

#endif  // NUMBERSDB_H
