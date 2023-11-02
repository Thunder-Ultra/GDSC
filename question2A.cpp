#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student {
    string name;
    int rollNumber;
    double cgpa;

public:
    Student(const string& name, int rollNumber, double cgpa)
        : name(name), rollNumber(rollNumber), cgpa(cgpa) {}

    // Overload assignment operator
    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            rollNumber = other.rollNumber;
            cgpa = other.cgpa;
        }
        return *this;
    }

    // Overload << operator for printing student info
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "Name: " << student.name << ", Roll Number: " << student.rollNumber << ", CGPA: " << student.cgpa;
        return os;
    }

    // Define operator< for comparing students by CGPA
    bool operator<(const Student& other) const {
        return cgpa < other.cgpa;
    }
};

class Collection {
private:
    vector<Student> students;
    int maxSize;

public:
    Collection(int maxSize) : maxSize(maxSize) {}

    // Overload assignment operator
    Collection& operator=(const Collection& other) {
        if (this != &other) {
            students = other.students;
            maxSize = other.maxSize;
        }
        return *this;
    }

    // Overload << operator for printing the collection
    friend ostream& operator<<(ostream& os, const Collection& collection) {
        for (const Student& student : collection.students) {
            os << student << "\n";
        }
        return os;
    }

    // Add a student to the collection
    void addStudent(const Student& student) {
        if (students.size() < maxSize) {
            students.push_back(student);
            // Perform heapify up
            int currentIndex = students.size() - 1;
            while (currentIndex > 0) {
                int parentIndex = (currentIndex - 1) / 2;
                if (students[currentIndex] < students[parentIndex]) {
                    swap(students[currentIndex], students[parentIndex]);
                    currentIndex = parentIndex;
                } else {
                    break;
                }
            }
        } else {
            cerr << "Collection is full. Cannot add more students." << endl;
        }
    }

    // Perform heap sort on the collection
    void heapSort() {
        int n = students.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }

        for (int i = n - 1; i >= 0; i--) {
            swap(students[0], students[i]);
            heapify(i, 0);
        }
    }

private:
    void heapify(int n, int root) {
        int smallest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < n && students[left] < students[smallest]) {
            smallest = left;
        }

        if (right < n && students[right] < students[smallest]) {
            smallest = right;
        }

        if (smallest != root) {
            swap(students[root], students[smallest]);
            heapify(n, smallest);
        }
    }
};

int main() {
    int maxSize;
    int choice;
    cout << "Enter the maximum number of students in the collection: ";
    cin >> maxSize;
    Collection studentCollection(maxSize);

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Student\n";
        cout << "2. Sort Collection\n";
        cout << "3. Print Collection\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int rollNumber;
                double cgpa;
                cout << "Enter student's name: ";
                cin >> name;
                cout << "Enter student's roll number: ";
                cin >> rollNumber;
                cout << "Enter student's CGPA: ";
                cin >> cgpa;
                Student student(name, rollNumber, cgpa);
                studentCollection.addStudent(student);
                break;
            }
            case 2: {
                studentCollection.heapSort();
                cout << "Collection sorted in ascending order by CGPA." << endl;
                break;
            }
            case 3:
                cout << studentCollection;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

