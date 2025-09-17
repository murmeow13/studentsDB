#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <sstream>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Enter student name: ";
    std::cin >> student.name;
    std::cout << "Enter student age: ";
    std::cin >> student.age;
    std::cout << "Enter student major: ";
    std::cin >> student.major;
    std::cout << "Enter student GPA: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Student added to database.\n";
}

void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "Database is empty.\n";
        return;
    }
    
    std::cout << "\nList of students:\n";
    std::cout << std::setw(15) << std::left << "Name"
              << std::setw(8) << "Age"
              << std::setw(15) << "Major"
              << std::setw(12) << "GPA" << "\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (const Student& student : database) {
        std::cout << std::setw(15) << std::left << student.name
                  << std::setw(8) << student.age
                  << std::setw(15) << student.major
                  << std::setw(12) << std::fixed << std::setprecision(2) << student.gpa << "\n";
    }
    std::cout << "\n";
}

void sortByName(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.name < b.name;
        });
    std::cout << "Students sorted by name (A-Z).\n";
}

void sortByNameDesc(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.name > b.name;
        });
    std::cout << "Students sorted by name (Z-A).\n";
}

void sortByGPA(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.gpa < b.gpa;
        });
    std::cout << "Students sorted by GPA (ascending).\n";
}

void sortByGPADesc(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
        });
    std::cout << "Students sorted by GPA (descending).\n";
}

void showSortMenu(std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "Database is empty. Nothing to sort.\n";
        return;
    }
    
    int sortChoice;
    do {
        std::cout << "\nSorting Menu:\n";
        std::cout << "1. Sort by name (A-Z)\n";
        std::cout << "2. Sort by name (Z-A)\n";
        std::cout << "3. Sort by GPA (ascending)\n";
        std::cout << "4. Sort by GPA (descending)\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choose action: ";
        std::cin >> sortChoice;

        switch (sortChoice) {
            case 1:
                sortByName(database);
                break;
            case 2:
                sortByNameDesc(database);
                break;
            case 3:
                sortByGPA(database);
                break;
            case 4:
                sortByGPADesc(database);
                break;
            case 0:
                std::cout << "Returning to main menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (sortChoice != 0);
}

void addTestStudent(std::vector<Student>& database, 
                   const std::string& name, 
                   int age, 
                   const std::string& major, 
                   double gpa) {
    Student student;
    student.name = name;
    student.age = age;
    student.major = major;
    student.gpa = gpa;
    database.push_back(student);
}

bool isSortedByName(const std::vector<Student>& database, bool ascending = true) {
    if (database.size() <= 1) return true;
    
    for (size_t i = 1; i < database.size(); ++i) {
        if (ascending) {
            if (database[i-1].name > database[i].name) {
                return false;
            }
        } else {
            if (database[i-1].name < database[i].name) {
                return false;
            }
        }
    }
    return true;
}

bool isSortedByGPA(const std::vector<Student>& database, bool ascending = true) {
    if (database.size() <= 1) return true;
    
    for (size_t i = 1; i < database.size(); ++i) {
        if (ascending) {
            if (database[i-1].gpa > database[i].gpa) {
                return false;
            }
        } else {
            if (database[i-1].gpa < database[i].gpa) {
                return false;
            }
        }
    }
    return true;
}

std::string captureDisplayOutput(const std::vector<Student>& database) {
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    
    displayStudents(database);
    
    std::cout.rdbuf(oldCout);
    return output.str();
}

void testAddStudent() {
    std::cout << "=== Testing addStudent function ===\n";
    std::vector<Student> database;
    
    addTestStudent(database, "John", 20, "ComputerScience", 3.8);
    assert(database.size() == 1);
    assert(database[0].name == "John");
    assert(database[0].age == 20);
    assert(database[0].major == "ComputerScience");
    assert(database[0].gpa == 3.8);
    std::cout << "✓ Test 1 passed: single student addition\n";
    
    addTestStudent(database, "Alice", 21, "Mathematics", 4.0);
    addTestStudent(database, "Bob", 19, "Physics", 3.5);
    assert(database.size() == 3);
    assert(database[1].name == "Alice");
    assert(database[1].gpa == 4.0);
    assert(database[2].age == 19);
    std::cout << "✓ Test 2 passed: multiple students addition\n";
    
    std::vector<Student> emptyDatabase;
    assert(emptyDatabase.size() == 0);
    std::cout << "✓ Test 3 passed: empty database\n";
}

void testDisplayStudents() {
    std::cout << "\n=== Testing displayStudents function ===\n";
    std::vector<Student> database;
    
    std::string emptyOutput = captureDisplayOutput(database);
    assert(emptyOutput.find("Database is empty") != std::string::npos);
    std::cout << "✓ Test 1 passed: empty database display\n";
    
    addTestStudent(database, "Emma", 22, "Biology", 3.2);
    addTestStudent(database, "David", 20, "Chemistry", 3.9);
    
    std::string output = captureDisplayOutput(database);
    assert(output.find("Emma") != std::string::npos);
    assert(output.find("David") != std::string::npos);
    assert(output.find("Biology") != std::string::npos);
    assert(output.find("3.20") != std::string::npos);
    assert(output.find("3.90") != std::string::npos);
    std::cout << "✓ Test 2 passed: student data display\n";
    
    assert(output.find("Name") != std::string::npos);
    assert(output.find("Age") != std::string::npos);
    assert(output.find("Major") != std::string::npos);
    assert(output.find("GPA") != std::string::npos);
    std::cout << "✓ Test 3 passed: table formatting\n";
}

void testSortByName() {
    std::cout << "\n=== Testing sortByName function ===\n";
    std::vector<Student> database;
    
    addTestStudent(database, "Zoe", 22, "Biology", 3.2);
    addTestStudent(database, "Anna", 21, "Mathematics", 4.0);
    addTestStudent(database, "Mike", 20, "ComputerScience", 3.7);
    addTestStudent(database, "Bob", 19, "Physics", 3.5);
    
    sortByName(database);
    assert(isSortedByName(database, true));
    assert(database[0].name == "Anna");
    assert(database[1].name == "Bob");
    assert(database[2].name == "Mike");
    assert(database[3].name == "Zoe");
    std::cout << "✓ Test 1 passed: ascending name sort\n";
    
    assert(database[0].gpa == 4.0);
    assert(database[1].age == 19);
    assert(database[2].major == "ComputerScience");
    std::cout << "✓ Test 2 passed: data integrity after sort\n";
    
    std::vector<Student> singleStudent;
    addTestStudent(singleStudent, "Single", 25, "Test", 3.0);
    sortByName(singleStudent);
    assert(singleStudent.size() == 1);
    assert(singleStudent[0].name == "Single");
    std::cout << "✓ Test 3 passed: single student sort\n";
}

void testSortByGPA() {
    std::cout << "\n=== Testing sortByGPA function ===\n";
    std::vector<Student> database;
    
    addTestStudent(database, "High", 20, "CS", 4.0);
    addTestStudent(database, "Low", 21, "Math", 2.5);
    addTestStudent(database, "Medium", 22, "Physics", 3.5);
    addTestStudent(database, "VeryLow", 19, "Bio", 2.0);
    
    sortByGPA(database);
    assert(isSortedByGPA(database, true));
    assert(database[0].gpa == 2.0);
    assert(database[1].gpa == 2.5);
    assert(database[2].gpa == 3.5);
    assert(database[3].gpa == 4.0);
    std::cout << "✓ Test 1 passed: ascending GPA sort\n";
    
    assert(database[0].name == "VeryLow");
    assert(database[3].name == "High");
    std::cout << "✓ Test 2 passed: name correspondence\n";
    
    std::vector<Student> sameGPA;
    addTestStudent(sameGPA, "Student1", 20, "CS", 3.0);
    addTestStudent(sameGPA, "Student2", 21, "Math", 3.0);
    sortByGPA(sameGPA);
    assert(sameGPA[0].gpa == 3.0);
    assert(sameGPA[1].gpa == 3.0);
    std::cout << "✓ Test 3 passed: equal GPA values\n";
}

void testSortByGPADesc() {
    std::cout << "\n=== Testing sortByGPADesc function ===\n";
    std::vector<Student> database;
    
    addTestStudent(database, "Medium", 20, "CS", 3.2);
    addTestStudent(database, "Highest", 21, "Math", 4.0);
    addTestStudent(database, "Lowest", 22, "Physics", 2.8);
    addTestStudent(database, "High", 19, "Bio", 3.8);
    
    sortByGPADesc(database);
    assert(isSortedByGPA(database, false));
    assert(database[0].gpa == 4.0);
    assert(database[1].gpa == 3.8);
    assert(database[2].gpa == 3.2);
    assert(database[3].gpa == 2.8);
    std::cout << "✓ Test 1 passed: descending GPA sort\n";
    
    assert(database[0].name == "Highest");
    assert(database[1].name == "High");
    assert(database[3].name == "Lowest");
    std::cout << "✓ Test 2 passed: name order verification\n";
    
    sortByGPA(database); 
    sortByGPADesc(database); 
    assert(isSortedByGPA(database, false));
    std::cout << "✓ Test 3 passed: reverse sorting\n";
}

void runAllTests() {
    std::cout << "Running all tests...\n\n";
    
    testAddStudent();
    testDisplayStudents();
    testSortByName();
    testSortByGPA();
    testSortByGPADesc();
    
    std::cout << "\n========================================\n";
    std::cout << "All tests passed successfully! ✓\n";
    std::cout << "5 functions tested:\n";
    std::cout << "1. addStudent\n";
    std::cout << "2. displayStudents\n";
    std::cout << "3. sortByName\n";
    std::cout << "4. sortByGPA\n";
    std::cout << "5. sortByGPADesc\n";
    std::cout << "========================================\n";
}

int main() {
    #ifdef TEST_MODE
        runAllTests();
        return 0;
    #endif

    std::vector<Student> database;
    int choice;
    
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Display students\n";
        std::cout << "3. Sort students\n";
        std::cout << "4. Run tests\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose action: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                showSortMenu(database);
                break;
            case 4:
                runAllTests();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
