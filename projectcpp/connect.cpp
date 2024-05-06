#include "connect.h"

Connect::Connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : host(host), user(user), password(password), database(database), connection(nullptr) {}

Connect::~Connect() {
    close();
}

bool Connect::connect() {
    connection = mysql_init(nullptr);
    if (!connection) {
        return false;
    }

    if (!mysql_real_connect(connection, host.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, nullptr, 0)) {
        return false;
    }

    return true;
}

void Connect::close() {
    if (connection) {
        mysql_close(connection);
        connection = nullptr;
    }
}

bool Connect::createTable(const std::string& tableName, const std::vector<std::string>& columns) {
    std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (";
    for (size_t i = 0; i < columns.size(); ++i) {
        query += columns[i];
        if (i != columns.size() - 1) {
            query += ",";
        }
    }
    query += ");";

    if (mysql_query(connection, query.c_str())) {
        return false;
    }

    return true;
}

bool Connect::insert(const std::string& tableName, const std::vector<std::string>& values) {
    std::string query = "INSERT INTO " + tableName + " VALUES (";
    for (size_t i = 0; i < values.size(); ++i) {
        query += "'" + values[i] + "'";
        if (i != values.size() - 1) {
            query += ",";
        }
    }
    query += ");";

    if (mysql_query(connection, query.c_str())) {
        return false;
    }

    return true;
}

bool Connect::update(const std::string& tableName, const std::vector<std::string>& setValues, const std::string& condition) {
    std::string query = "UPDATE " + tableName + " SET ";
    for (size_t i = 0; i < setValues.size(); ++i) {
        query += setValues[i];
        if (i != setValues.size() - 1) {
            query += ",";
        }
    }
    query += " WHERE " + condition + ";";

    if (mysql_query(connection, query.c_str())) {
        return false;
    }

    return true;
}

bool Connect::del(const std::string& tableName, const std::string& condition) {
    std::string query = "DELETE FROM " + tableName + " WHERE " + condition + ";";

    if (mysql_query(connection, query.c_str())) {
        return false;
    }

    return true;
}


int main(){
    
}