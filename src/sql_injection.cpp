#include <iostream>
#include <string>
#include <sqlite3.h>

// Simple callback to print query results
static int callback(void* data, int argc, char** argv, char** azColName){
    for(int i = 0; i < argc; i++) std::cout << azColName[i] << "=" << (argv[i] ? argv[i] : "NULL") << " ";
    std::cout << std::endl; return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) { std::cerr << "Usage: " << argv[0] << " <username>\n"; return 1; }
    sqlite3* db; sqlite3_open(":memory:", &db);
    sqlite3_exec(db, "CREATE TABLE users(name TEXT); INSERT INTO users VALUES('admin');", 0, 0, 0);
    std::string query = "SELECT * FROM users WHERE name = '" + std::string(argv[1]) + "';"; // Vulnerable line
    std::cout << "Executing: " << query << std::endl;
    char* errMsg = nullptr;
    sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if(errMsg) { std::cerr << "SQL Error: " << errMsg << std::endl; sqlite3_free(errMsg); }
    sqlite3_close(db); return 0;
}
