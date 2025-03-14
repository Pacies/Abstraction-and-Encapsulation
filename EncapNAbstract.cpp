#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex> 
using namespace std;

bool whileTrue = true;
// Employee Class 
class Employee {
protected:
    int id;
    string name;
    double salary;

public:
    Employee(int id, string name, double salary) : id(id), name(name), salary(salary) {}
    virtual ~Employee() {}

    int getId() const { 
        return id; 
    }
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
};

// Full-Time Employee Class
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int id, string name, double salary) : Employee(id, name, salary) {}

    double calculateSalary() const override{
        return salary; 
    }

    void displayInfo() const override {
        cout << "\nEmployee: " << name << " (ID: " << id << ")" << endl;
        cout << "Fixed Monthly Salary: $" << salary << "\n" << endl;
    }
};

// Part-Time Employee Class
class PartTimeEmployee : public Employee {
private:
    int hoursWorked;

public:
    PartTimeEmployee(int id, string name, double salary, int hoursWorked)
        : Employee(id, name, salary), hoursWorked(hoursWorked) {}

    double calculateSalary() const override{
        return salary * hoursWorked; 
    }

    void displayInfo() const override {
        cout << "\nEmployee: " << name << " (ID: " << id << ")" << endl;
        cout << "Hourly Wage: $" << salary << endl;
        cout << "Hours Worked: " << hoursWorked << endl;
        cout << "Total Salary: $" << calculateSalary() << "\n" << endl;
    }
};

// Contractual Employee Class
class ContractualEmployee : public Employee {
private:
    int projects;

public:
    ContractualEmployee(int id, string name, double salary, int projects)
        : Employee(id, name, salary), projects(projects) {}

    double calculateSalary() const override{
        return salary * projects;
    }

    void displayInfo() const override {
        cout << "\nEmployee: " << name << " (ID: " << id << ")" << endl;
        cout << "Contract Payment Per Project: $" << salary << endl;
        cout << "Projects Completed: " << projects << endl;
        cout << "Total Salary: $" << calculateSalary() << "\n" << endl;
    }
};

// Function to Validate Integer Input (For IDs)
int getValidatedID(const string& prompt) {
    string input;
    regex validPattern("^[1-9]\\d*$"); // Only positive integers

    while (whileTrue) {
        cout << prompt;
        cin >> input;

        if (regex_match(input, validPattern)) {
            return stoi(input); // Valid integer ID
        }

        cout << "Invalid input. Please enter a valid positive integer for the ID." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Updated isDuplicateID Function
bool isDuplicateID(const vector<Employee*>& employees, int id) {
    for (Employee* emp : employees) {
        if (emp->getId() == id) {
            return true; 
        }
    }
    return false; 
}

// Input Validation for Salary (Numbers/Decimals, Max 2 Decimal Places)
double getValidatedDouble(string prompt) {
    string input;
    regex validPattern("^\\d+(\\.\\d{1,2})?$");
    double value;

    while (whileTrue) {
        cout << prompt;
        cin >> input;

        if (regex_match(input, validPattern)) {
            value = stod(input);
            break;
        }

        cout << "Invalid input. Please enter a valid number (up to 2 decimal places)." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    return value;
}

// Validate Menu Choice
int getValidatedChoice() {
    string input;
    while (whileTrue) {
        cout << "Enter your choice: ";
        cin >> input;

        bool valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            int choice = stoi(input);
            if (choice >= 1 && choice <= 6) return choice;
        }

        cout << "Invalid input. Please enter a number between 1 and 6." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Main Menu UI
int menuUI() {
    system("cls");
    cout << "\nMenu" << endl;
    cout << "1 - Full-time Employee" << endl;
    cout << "2 - Part-time Employee" << endl;
    cout << "3 - Contractual Employee" << endl;
    cout << "4 - Display Payroll Report" << endl;
    cout << "5 - Remove Employee" << endl;
    cout << "6 - Exit" << endl;
    return getValidatedChoice();
}

// Remove Employee Function
void removeEmployee(vector<Employee*>& employees) {
    int id;
    cout << "Enter Employee ID to remove: ";
    cin >> id;

    for (int i = 0; i < employees.size(); i++) {
        if (employees[i]->getId() == id) {
            delete employees[i];
            employees.erase(employees.begin() + i);
            cout << "Employee with ID " << id << " has been removed." << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

// Main Function
int main() {
    vector<Employee*> employees;
    int choice;

    do {
        choice = menuUI();

        if (choice == 1 || choice == 2 || choice == 3) {
            int id;
            do {
                id = getValidatedID("\nEnter Employee ID: ");
                if (isDuplicateID(employees, id)) {
                    cout << "Duplicate ID! Please enter a unique ID." << endl;
                }
            } while (isDuplicateID(employees, id));

            cin.ignore();
            string name;
            cout << "Enter Employee Name: ";
            getline(cin, name);

            double salary = getValidatedDouble("Enter Salary: ");

            if (choice == 1) {
                employees.push_back(new FullTimeEmployee(id, name, salary));
            } else if (choice == 2) {
                int hours = getValidatedDouble("Enter Hours Worked: ");
                employees.push_back(new PartTimeEmployee(id, name, salary, hours));
            } else if (choice == 3) {
                int projects = getValidatedDouble("Enter Number of Projects: ");
                employees.push_back(new ContractualEmployee(id, name, salary, projects));
            }

            cout << "Employee added successfully!" << endl;
        }
        else if (choice == 4) {
            cout << "\n------ Employee Payroll Report ------" << endl;
            for (Employee* emp : employees) {
                emp->displayInfo();
            }
            cout << "Total Employees: " << employees.size() << endl;
            cout << "-------------------------------------" << endl;
        }
        else if (choice == 5) {
            removeEmployee(employees);
        }
    } while (choice != 6);

    for (Employee* emp : employees) {
        delete emp;
    }

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}
