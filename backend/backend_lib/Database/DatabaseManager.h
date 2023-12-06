#pragma once

#include <sqlite3.h> 
#include <string>
#include <opencv2/opencv.hpp>
#include "Logger.h"

class BackendProcessor; // Forward declaration


class DatabaseManager {
public:
    DatabaseManager();
    DatabaseManager(const std::string& dbPath, const std::string& videoFileName);
    ~DatabaseManager();

    void executeInsertStatement(const cv::Rect& rect, float avgR, float avgG, float avgB);
    void openDatabase(const std::string& dbPath);
    void closeDatabase();
    void prepareStatements();
private:
    

    sqlite3* db;
    sqlite3_stmt* insertStmt;
    std::string dbPath;
    std::string videoFileName;
};
