#include "database.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

bool connectDatabase(sqlite3*& db) {
    int rc = sqlite3_open("hiketracker.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    std::cout << "Opened database successfully" << std::endl;
    return true;
}

void createTables(sqlite3 *db){
    
    const char* create_hikes = "CREATE TABLE IF NOT EXISTS hikes("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "trail_name TEXT NOT NULL,"
                        "location TEXT NOT NULL,"
                        "distance REAL NOT NULL,"
                        "duration INTEGER NOT NULL,"
                        "date TEXT,"
                        "notes TEXT"
                        ");";
    
    const char* create_climbs = "CREATE TABLE IF NOT EXISTS climbs("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "route_name TEXT NOT NULL,"
                        "location TEXT NOT NULL,"
                        "grade TEXT NOT NULL,"
                        "attempts INTEGER NOT NULL,"
                        "style TEXT,"
                        "date TEXT,"
                        "notes TEXT"
                        ");";

    char* errMsg = 0;
    int rc = sqlite3_exec(db, create_hikes, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Hikes table created successfully" << std::endl;
    }

    rc = sqlite3_exec(db, create_climbs, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Climbs table created successfully" << std::endl;
    }

}

void insertHike(sqlite3 *db, const std::string& trailName, const std::string& location, double distance, int duration,
     const std::string& date, const std::string& notes){
    //use parameter binding concept

    const char* sql = "INSERT INTO hikes (trail_name, location, distance, duration, date, notes) VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    //Parameter Binding
    sqlite3_bind_text(stmt, 1, trailName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, location.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, distance);
    sqlite3_bind_int(stmt, 4, duration);
    sqlite3_bind_text(stmt, 5, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, notes.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to insert hike: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Hike inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void insertClimb(sqlite3 *db, const std::string& routeName, const std::string& location, std::string& grade, int attempts, 
    const std::string& style, const std::string& date, const std::string& notes){

    const char* sql = "INSERT INTO climbs (route_name, location, grade, attempts, style, date, notes) VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    //Parameter Binding
    sqlite3_bind_text(stmt, 1, routeName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, location.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, grade.c_str(), -1 , SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, attempts);
    sqlite3_bind_text(stmt, 5, style.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, notes.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to insert climb: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Climb inserted successfully" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void viewAllHikes(sqlite3 *db){
    const char* sql = "SELECT * FROM hikes;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    bool found_any = false;


    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found_any = true;
        int id = sqlite3_column_int(stmt, 0);
        const char* trailName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        double distance = sqlite3_column_double(stmt, 3);
        int duration = sqlite3_column_int(stmt, 4);
        const char* date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        const char* notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        std::cout << "Hike ID: " << id << ", Trail Name: " << trailName 
                  << ", Location: " << location << ", Distance: " << distance 
                  << ", Duration: ";
                  displayDuration(duration);
                  std::cout << ", Date: " << date << ", Notes: " << notes << std::endl;
    }
    if (!found_any){
        std::cout << "No hikes found." << std::endl;

    }
    sqlite3_finalize(stmt);
}

void viewAllClimbs(sqlite3 *db){
    const char* sql = "SELECT * FROM climbs;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    bool found_any = false;
    
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }    


    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        found_any = true;
        int id = sqlite3_column_int(stmt, 0);
        const char* routeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* grade = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int attempts = sqlite3_column_int(stmt, 4);
        const char* style = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        const char* date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        const char* notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

        std::cout << "Climb ID: " << id << ", Route Name: " << routeName 
                  << ", Location: " << location << ", Grade: " << grade 
                  << ", Attempts: " << attempts << ", Style: " << style 
                  << ", Date: " << date << ", Notes: " << notes << std::endl;
    }
    
    if (!found_any){
        std::cout << "No climbs found." << std::endl;

    }
    
    sqlite3_finalize(stmt);

}


void closeDatabase(sqlite3 *db){
    if (db) {
        sqlite3_close(db);
    }
}

void displayDuration(int minutes){
    int hours = minutes / 60;
    int mins = minutes % 60;
    if (hours > 0){
        std::cout << hours << "h " << mins << "m";
    } else {
        std::cout << mins << "m";
    }
}