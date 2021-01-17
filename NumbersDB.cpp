#include "NumbersDB.h"

#include <QDate>
#include <QDebug>
#include <QLocale>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>
#include <QtWidgets/QTableView>
#include <chrono>
NumbersDB::NumbersDB(QObject* parent)
    : QObject(parent),
      tableName{"Numbers"},
      working{false}

{
  createTable();
  model.reset(new NumbersSqlTableModel(this, *(dbSQLITE)));
  initMain();
}

void NumbersDB::addFakeValues() {
  dbSQLITE->transaction();
  QSqlRecord record = model->record();
  model->select();
  record.setValue("value", QString::number(qrand()));
  record.setValue("date", QDate::currentDate().toString());
  record.setValue("time", QTime::currentTime().toString());
  model->insertRecord(-1, record);
  model->submitAll();
  dbSQLITE->commit();
}

void NumbersDB::startAdding() {
  if (!working) {
    working = true;
    worker = std::thread([&]() {
      using namespace std::chrono_literals;
      while (working) {
        qDebug() << "Hi start adding";
        addFakeValues();
        std::this_thread::sleep_for(1000ms);
      }
    });
  }
}

void NumbersDB::stopAdding() {
  if (working) {
    working = false;
    if (worker.joinable()) worker.join();
    qDebug() << "worker finished";
  }
}

void NumbersDB::initMain() { initModel(); }

void NumbersDB::initModel() {
  model->clear();
  //  model->select();
  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
}

void NumbersDB::createTable() {
  dbQuery(
      "create table Numbers (value varchar(20), date varchar(20) , time "
      "varchar(20))");
}
