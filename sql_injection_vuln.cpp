/*
The following is a valid C++ code example that demonstrates a SQL injection vulnerability using the SQLite C API. This code takes user input and directly concatenates it into an SQL query string, making it susceptible to SQL injection attacks
*/

#include <iostream>
#include <cstring>
#include <sqlite3.h>

void vulnerable_query(sqlite3 *db) {
    char userName[100];
    char itemName[100];
    char sql[300] = "SELECT * FROM items WHERE owner = '";

    // Get user input (unsafe)
    std::cout << "Enter owner name: ";
    std::cin.getline(userName, 100);
    std::cout << "Enter item name: ";
    std::cin.getline(itemName, 100);

    // Build SQL query by concatenating user input (vulnerable to SQL injection)
    strcat(sql, userName);
    strcat(sql, "' AND itemname = '");
    strcat(sql, itemName);
    strcat(sql, "'");

    // Execute the SQL query
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Query executed: " << sql << std::endl;
    }
}

/*
How to exploit:
If user enters username as "admin' OR '1'='1", the SQL query becomes:
SELECT * FROM items WHERE owner = 'admin' OR '1'='1';
This would return all users in the database, effectively bypassing authentication.

Mitigation:
Never build SQL queries by directly concatenating user input. Always use prepared statements to prevent SQL injection.
*/
