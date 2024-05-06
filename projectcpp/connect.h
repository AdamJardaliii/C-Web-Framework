#ifndef CONNECT_H
#define CONNECT_H

#include "mysql.h"
#include <string>
#include <vector>

class Connect {
public:
    Connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~Connect();

    bool connect();
    void close();
    bool createTable(const std::string& tableName, const std::vector<std::string>& columns);
    bool insert(const std::string& tableName, const std::vector<std::string>& values);
    bool update(const std::string& tableName, const std::vector<std::string>& setValues, const std::string& condition);
    bool del(const std::string& tableName, const std::string& condition);

private:
    std::string host;
    std::string user;
    std::string password;
    std::string database;
    MYSQL* connection;
};

#endif // CONNECT_H
