#ifndef NUMBERSDB_H
#define NUMBERSDB_H

#include <NumbersSqlTableModel.h>

#include <QObject>
#include <QtSql/QSqlTableModel>
#include <thread>
class NumbersDB : public QObject {
  Q_OBJECT
  Q_PROPERTY(QSqlTableModel *model READ getModel NOTIFY modelChanged)
 public:
  explicit NumbersDB(QObject *parent = nullptr);

  QSqlTableModel *getModel() { return model.get(); }
 signals:
  void modelChanged(double to, double from = 0);

 public slots:
  void addFakeValues();

 private:
  void initMain();
  void initModel();
  void createDB();
  std::unique_ptr<QSqlDatabase> db;
  std::unique_ptr<NumbersSqlTableModel> model;
  //  std::thread worker;
};

#endif  // NUMBERSDB_H
