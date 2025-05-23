/*
The following is a valid C++ code example that demonstrates a SQL injection vulnerability using the SQLite C API. This code takes user input and directly concatenates it into an SQL query string, making it susceptible to SQL injection attacks
*/

#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(char* argc, char** argv) {
{

  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *pstmt;

  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
  con->setSchema("test");

  char *name1 = argv[2];
  char q1[1000] = {0};
  snprintf(q1, 1000, "SELECT * FROM USERS where name = \"%s\"", name1);

  stmt = con->createStatement();
  stmt->execute(q1); // dcexpect Sqli
  delete stmt;

  char *name2 = argv[2];
  char q2[1000] = {0};
  snprintf(q2, 1000, "SELECT * FROM USERS where name = \"%s\"", name2);

  pstmt = con->prepareStatement(q2); // dcexpect Sqli
  res = pstmt->executeQuery();

  return 0;
}

/*
How to exploit:
If user enters username as "admin' OR '1'='1", the SQL query becomes:
SELECT * FROM USERS WHERE name = 'admin' OR '1'='1';
This would return all users in the database, effectively bypassing authentication.

Mitigation:
Never build SQL queries by directly concatenating user input. Always use prepared statements to prevent SQL injection.
*/
