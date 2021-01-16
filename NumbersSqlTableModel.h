#ifndef NUMBERSSQLTABLEMODEL_H
#define NUMBERSSQLTABLEMODEL_H

#include <QObject>
#include <QSqlField>
#include <QSqlRecord>
#include <QtSql/QSqlTableModel>

class NumbersSqlTableModel : public QSqlTableModel {
  Q_OBJECT
 public:
  NumbersSqlTableModel();
  explicit NumbersSqlTableModel(QObject *parent = nullptr,
                                QSqlDatabase db = QSqlDatabase());
  Q_INVOKABLE QVariant data(const QModelIndex &index,
                            int role = Qt::DisplayRole) const override;
  void setTable(const QString &table_name) override;
  Q_INVOKABLE QHash<int, QByteArray> roleNames() const override {
    return roles;
  }
  Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation,
                                  int role = Qt::DisplayRole) const override;

 private:
  QHash<int, QByteArray> roles;
  void generateRoleNames();
  QStringList headerList;
  void generateHeaders();
};

#endif  // NUMBERSSQLTABLEMODEL_H
