# 🏔️ HikeTracker

An application for tracking hiking and climbing activities with persistent SQLite database storage.

## ✨ Features

- **Complete CLI Interface** - Menu-driven experience
- **SQLite Database Integration** - Persistent data storage with parameter binding
- **Dual Activity Support** - Track both hikes and climbing routes
- **Smart Data Validation** - Input validation and error handling
- **Duration Formatting** - Automatic conversion to hours/minutes display

## 🚀 Technologies Used

- **C++17** - Modern C++ with professional coding standards
- **SQLite3** - Lightweight, embedded database

## 📁 Project Structure

```
hiketracker/
├── main.cpp              # CLI interface and menu system
├── database.h            # Database function declarations
├── database.cpp          # SQLite implementation
├── .gitignore           # Git ignore rules
└── README.md            # Project documentation
```

## 🛠️ Build Instructions

### Prerequisites
- C++ compiler (g++ or clang++)
- SQLite3 development libraries

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential sqlite3 libsqlite3-dev
```

### Compile:
```bash
g++ -o hiketracker main.cpp database.cpp -lsqlite3
```

### Run:
```bash
./hiketracker
```

## 📊 Database Schema

### Hikes Table
- `id` (INTEGER PRIMARY KEY)
- `trail_name` (TEXT)
- `location` (TEXT)
- `distance` (REAL) - in miles
- `duration` (INTEGER) - in minutes
- `date` (TEXT) - YYYY-MM-DD format
- `notes` (TEXT)

### Climbs Table
- `id` (INTEGER PRIMARY KEY)
- `route_name` (TEXT)
- `location` (TEXT)
- `grade` (TEXT) - climbing grade (5.10a, V4, etc.)
- `attempts` (INTEGER)
- `style` (TEXT) - sport, trad, boulder, etc.
- `date` (TEXT)
- `notes` (TEXT)

## 🎯 Usage Examples

```
=== Hike Tracker ===
1. Add Hike
2. Add Climb
3. View All Hikes
4. View All Climbs
5. Exit

Enter your choice: 1
Enter hike name: Mount Belford
Enter hike location: San Isabel National Forest, Colorado
Enter hike distance (in miles): 6.6
Enter hike duration (in minutes): 237
Enter hike date (YYYY-MM-DD): 2025-07-06
Enter hike notes: 14er summit!

Hike inserted successfully!
```

## 🔮 Future Enhancements

- Search and filter functionality
- Data export (CSV/JSON)
- Statistical analysis
- Tableau dashboard integration
- GPS coordinate support

## 👨‍💻 Nate Love
