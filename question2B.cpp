#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
    int acc_no;
    float balance;
    string name;

public:
    Account(const int& acc_no, float balance, string name)
        : acc_no(acc_no), balance(balance), name(name) {}

    // Overload assignment operator
    Account& operator=(const Account& other) {
        if (this != &other) {
            acc_no = other.acc_no;
            balance = other.balance;
            name = other.name;
        }
        return *this;
    }

    // Overload << operator for printing acccount info
    friend ostream& operator<<(ostream& os, const Account& acccount) {
        os << "Account No : " << acccount.acc_no << ", Balance: " << acccount.balance << ", Name: " << acccount.name;
        return os;
    }

    // Define operator< for comparing acccounts by CGPA
    bool operator<(const Account& other) const {
        return name < other.name;
    }
};

class Collection {
private:
    vector<Account> acccounts;
    int maxSize;

public:
    Collection(int maxSize) : maxSize(maxSize) {}

    // Overload assignment operator
    Collection& operator=(const Collection& other) {
        if (this != &other) {
            acccounts = other.acccounts;
            maxSize = other.maxSize;
        }
        return *this;
    }

    // Overload << operator for printing the collection
    friend ostream& operator<<(ostream& os, const Collection& collection) {
        for (const Account& acccount : collection.acccounts) {
            os << acccount << "\n";
        }
        return os;
    }

    // Add a acccount to the collection
    void addAccount(const Account& acccount) {
        if (acccounts.size() < maxSize) {
            acccounts.push_back(acccount);
            // Perform heapify up
            int currentIndex = acccounts.size() - 1;
            while (currentIndex > 0) {
                int parentIndex = (currentIndex - 1) / 2;
                if (acccounts[currentIndex] < acccounts[parentIndex]) {
                    swap(acccounts[currentIndex], acccounts[parentIndex]);
                    currentIndex = parentIndex;
                } else {
                    break;
                }
            }
        } else {
            cerr << "Collection is full. Cannot add more acccounts." << endl;
        }
    }

    // Perform heap sort on the collection
    void heapSort() {
        int n = acccounts.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }

        for (int i = n - 1; i >= 0; i--) {
            swap(acccounts[0], acccounts[i]);
            heapify(i, 0);
        }
    }

private:
    void heapify(int n, int root) {
        int smallest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < n && acccounts[left] < acccounts[smallest]) {
            smallest = left;
        }

        if (right < n && acccounts[right] < acccounts[smallest]) {
            smallest = right;
        }

        if (smallest != root) {
            swap(acccounts[root], acccounts[smallest]);
            heapify(n, smallest);
        }
    }
};

int main() {
    int maxSize;
    int choice;
    cout << "Enter the maximum number of acccounts in the collection: ";
    cin >> maxSize;
    Collection acccountCollection(maxSize);

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Account\n";
        cout << "2. Sort Accounts\n";
        cout << "3. Print Accounts\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int acc_no;
                float balance;
                string name;
                cout << "Enter acccount No: ";
                cin >> acc_no;
                cout << "Enter acccount's Balance: ";
                cin >> balance;
                cout << "Enter acccount holder's name: ";
                cin >> name;
                Account acccount(acc_no, balance, name);
                acccountCollection.addAccount(acccount);
                break;
            }
            case 2: {
                acccountCollection.heapSort();
                cout << "Collection sorted in ascending order by Balance." << endl;
                break;
            }
            case 3:
                cout << acccountCollection;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

