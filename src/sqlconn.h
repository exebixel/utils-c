#ifndef SQLCONN_H
#define SQLCONN_H 

#include <mysql/mysql.h>

MYSQL *sqlConnect();

void sqlClose(MYSQL *conn);

int sqlCrud(char *sql);

MYSQL_RES *sqlSelect(char *sql);

#endif
