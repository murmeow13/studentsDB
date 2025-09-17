#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> 

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

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Display students\n";
        std::cout << "3. Sort students\n";
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
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
