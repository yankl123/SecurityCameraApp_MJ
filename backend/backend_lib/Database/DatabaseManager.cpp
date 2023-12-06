#include "DatabaseManager.h"


DatabaseManager::DatabaseManager() : db(nullptr), insertStmt(nullptr) {
    // Default constructor implementation
}

DatabaseManager::DatabaseManager(const std::string & dbPath, const std::string & videoFileName)
    : db(nullptr), insertStmt(nullptr), videoFileName(videoFileName) {
    openDatabase(dbPath);
    prepareStatements();
}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

void DatabaseManager::openDatabase(const std::string& dbPath) {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        //LOG_ERROR("Error opening SQLite database: {}", sqlite3_errmsg(db));
        exit(1);
    }

    // Create the table if it doesn't exist
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS detection_data ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
        "file_name TEXT,"
        "top INTEGER,"
        "left INTEGER,"
        "width INTEGER,"
        "height INTEGER,"
        "avgR REAL,"
        "avgG REAL,"
        "avgB REAL);";
    rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        //LOG_ERROR("Error creating table: {}", sqlite3_errmsg(db));
        exit(1);
    }
}
void DatabaseManager::closeDatabase() {
    if (db) {
        sqlite3_finalize(insertStmt);
        int rc = sqlite3_close(db);
        if (rc != SQLITE_OK) {
            //LOG_ERROR("Error closing SQLite database: {}", sqlite3_errmsg(db));
        }
        db = nullptr; // Reset the pointer after closing
    }
}


void DatabaseManager::prepareStatements() {
    {
        // Prepare SQLite insert statement
        const char* insertSQL = "INSERT INTO detection_data (file_name, top, left, width, height, avgR, avgG, avgB) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
        int rc = sqlite3_prepare_v2(db, insertSQL, -1, &insertStmt, nullptr);
        if (rc != SQLITE_OK) {
            //LOG_ERROR("Error preparing insert statement: {}", sqlite3_errmsg(db));
            exit(1);
        }
    }
}

void DatabaseManager::executeInsertStatement(const cv::Rect& rect, float avgR, float avgG, float avgB) {
    // Bind values to the prepared statement
    sqlite3_bind_text(insertStmt, 1, videoFileName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(insertStmt, 2, rect.y);
    sqlite3_bind_int(insertStmt, 3, rect.x);
    sqlite3_bind_int(insertStmt, 4, rect.width);
    sqlite3_bind_int(insertStmt, 5, rect.height);
    sqlite3_bind_double(insertStmt, 6, avgR);
    sqlite3_bind_double(insertStmt, 7, avgG);
    sqlite3_bind_double(insertStmt, 8, avgB);

    // Execute the statement
    int rc = sqlite3_step(insertStmt);
    if (rc != SQLITE_DONE) {
        //LOG_ERROR("Error executing insert statement: {}", sqlite3_errmsg(db));
    }
    // Reset the statement for reuse
    sqlite3_reset(insertStmt);
}
