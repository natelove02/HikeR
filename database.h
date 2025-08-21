#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

bool connectDatabase(sqlite3*& db);
void createTables(sqlite3 *db);
void insertHike(sqlite3 *db, const std::string& trailName, const std::string& location, double distance, int duration, const std::string& date, const std::string& notes);
void insertClimb(sqlite3 *db, const std::string& routeName, const std::string& location, std::string& grade, int attempts, const std::string& style, const std::string& date, const std::string& notes);
void viewAllHikes(sqlite3 *db);
void viewAllClimbs(sqlite3 *db);
void closeDatabase(sqlite3 *db);
void displayDuration(int minutes);


#endif