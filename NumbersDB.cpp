#include "NumbersDB.h"

#include <QDate>
#include <QDebug>
#include <QLocale>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtWidgets/QTableView>

NumbersDB::NumbersDB(QObject *parent)
    : QObject(parent),
      tableName{"Numbers"}

{
  createTable();
  model.reset(new NumbersSqlTableModel(this, *(dbSQLITE)));
  initMain();
}

void NumbersDB::addFakeValues() {
  QDate date;
  QLocale::system().toString(date);
  QTime time;
  QLocale::system().toString(time);

  model->database().transaction();
  QSqlRecord record = model->record();
  model->select();
  record.setValue("value", "207");
  record.setValue("date", "2020-11-07");
  record.setValue("time", "18:28");
  model->insertRecord(-1, record);
  model->submitAll();
  model->lastError();
  dbSQLITE->commit();
}

void NumbersDB::initMain() {
  initModel();
  addFakeValues();
}

void NumbersDB::initModel() {
  model->clear();
  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
}

void NumbersDB::createTable() {
  dbQuery(
      "create table Numbers (value varchar(20), date varchar(20) , time "
      "varchar(20))");
}
