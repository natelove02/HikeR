#include "database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

void displayMenu();
void addHikeMenu(sqlite3* db);
void addClimbMenu(sqlite3* db);
bool getValidChoice(int& choice);

int main() {
    sqlite3* db;
    if (!connectDatabase(db)) {
        return 1; 
    }

    createTables(db);

    int choice;
    while(true){
        displayMenu();

        if(!getValidChoice(choice)){
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }

        switch (choice){
            case 1:
                addHikeMenu(db);
                break;
            case 2:
                addClimbMenu(db);
                break;
            case 3:
                viewAllHikes(db);
                break;
            case 4:
                viewAllClimbs(db);
                break;
            case 5:
                closeDatabase(db);
                std::cout << "Exiting program." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    }

}


void displayMenu(){
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add Hike" << std::endl;
    std::cout << "2. Add Climb" << std::endl;
    std::cout << "3. View All Hikes" << std::endl;
    std::cout << "4. View All Climbs" << std::endl;
    std::cout << "5. Exit" << std::endl;

    std::cout << "Enter your choice: ";

}


void addHikeMenu(sqlite3* db){

    std::string trailName, location, date, notes;
    double distance;
    int duration;

    std::cin.ignore();

    std::cout << "Enter hike name: ";
    std::getline(std::cin, trailName);
    std::cout << "Enter hike location: ";
    std::getline(std::cin, location);
    std::cout << "Enter hike distance (in miles): ";
    std::cin >> distance;
    std::cout << "Enter hike duration (in minutes): ";
    std::cin >> duration;
    std::cout << "Enter hike date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter hike notes: ";
    std::cin >> notes;

    insertHike(db, trailName, location, distance, duration, date, notes);
}

void addClimbMenu(sqlite3* db){

    std::string routeName, location, style, date, notes, grade;
    int attempts;

    std::cout << "Enter climb route name: ";
    std::cin >> routeName;
    std::cout << "Enter climb location: ";
    std::cin >> location;
    std::cout << "Enter climb grade (5.10, 5.11, etc.): ";
    std::cin >> grade;
    std::cout << "Enter number of attempts: ";
    std::cin >> attempts;
    std::cout << "Enter climbing style (sport, trad, etc.): ";
    std::cin >> style;
    std::cout << "Enter climb date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter climb notes: ";
    std::cin >> notes;

    insertClimb(db, routeName, location, grade, attempts, style, date, notes);
}

bool getValidChoice(int& choice){
    if (std::cin >> choice) {
        return true;
    } else{
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
}





