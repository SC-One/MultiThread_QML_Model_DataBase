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
      db{new QSqlDatabase}

{
  createDB();
  model.reset(new NumbersSqlTableModel(this, *(db.get())));
  initMain();
  model->record(0);
  model->record(1);
}

void NumbersDB::addFakeValues() {
  QDate date;
  QLocale::system().toString(date);
  QTime time;
  QLocale::system().toString(time);

  model->database().transaction();
  QSqlRecord record = model->record();
  model->select();
  record.setValue("value", "2");
  record.setValue("date", "21");
  record.setValue("time", "21");
  model->insertRecord(-1, record);
  model->submitAll();
  model->lastError();
  db->commit();
}

void NumbersDB::initMain() {
  initModel();
  addFakeValues();
}

void NumbersDB::initModel() {
  model->clear();
  model->setTable(tr("Numbers"));
  model->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
  //  model->select();
  model->setHeaderData(0, Qt::Horizontal, tr("value"));
  model->setHeaderData(1, Qt::Horizontal, tr("date"));
  model->setHeaderData(2, Qt::Horizontal, tr("time"));
}

void NumbersDB::createDB() {
  *db = QSqlDatabase::addDatabase("QSQLITE");
  db->setDatabaseName(":memory:");
  if (!db->open()) qDebug() << "not opened!";

  QSqlQuery query;
  query.exec(
      "create table Numbers (value varchar(20), "
      "date varchar(20) , time varchar(20))");
  query.lastError();
  query.exec("insert into Numbers values('107', '2020-07-08', '20:17')");
  query.lastError();
}
