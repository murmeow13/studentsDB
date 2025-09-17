#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

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
    std::cout << "List of students:\n";
    for (const Student& student : database) {
        std::cout << "Name: " << student.name << "\n";
        std::cout << "Age: " << student.age << "\n";
        std::cout << "Major: " << student.major << "\n";
        std::cout << "GPA: " << student.gpa << "\n\n";
    }
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

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Display students\n";
        std::cout << "3. Sort by name (A-Z)\n";
        std::cout << "4. Sort by name (Z-A)\n";
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
                sortByName(database);
                break;
            case 4:
                sortByNameDesc(database);
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
