#ifndef MACROS_H
#define MACROS_H

#include "ConnectionDB.h"
#define mcModule "Header.Coding.Company"
#define dbQuery(str) ConnectionDB::getInstance()->queryExec(str)
#define dbSQLITE ConnectionDB::getInstance()->getDB()

#endif  // MACROS_H
