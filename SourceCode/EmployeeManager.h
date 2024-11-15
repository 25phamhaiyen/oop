#include <vector>

class EmployeeManager {
private:
    vector<Employee> employees;

public:
    // Thêm nhân viên mới
    void addEmployee(const Employee& employee);

    // Xóa nhân viên theo ID
    void removeEmployee(const string& employeeID);

    // Cập nhật thông tin nhân viên
    void updateEmployee(const string& employeeID, const string& newName, int newAge,
                        const string& newPosition, double newSalary);

    // Tìm kiếm nhân viên theo ID
    Employee* findEmployeeByID(const string& employeeID);

    // Hiển thị tất cả nhân viên
    void displayAllEmployees() const;

    void EmployeeManager::exportToFile(const string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        cout << "Unable to open file." << endl;
        return;
    }

    //Xuất nhân viên vào một tệp
    file << "Employee List:" << endl;
    for (const auto& employee : employees) {
        file << "ID: " << employee.getEmployeeID() << ", "
             << "Name: " << employee.getName() << ", "
             << "Age: " << employee.getAge() << ", "
             << "Position: " << employee.getPosition() << ", "
             << "Salary: " << employee.getSalary() << endl;
    }
    
    file.close();
    cout << "Employee data exported to " << filename << " successfully!" << endl;
}

    // Hiển thị menu
    void printMenu();
};
void EmployeeManager::addEmployee(const Employee& employee) {
    employees.push_back(employee);
    cout << "Employee added successfully!" << endl;
}

void EmployeeManager::removeEmployee(const string& employeeID) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getEmployeeID() == employeeID) {
            employees.erase(it);
            cout << "Employee removed successfully!" << endl;
            return;
        }
    }
    cout << "Employee not found!" << endl;
}

void EmployeeManager::updateEmployee(const string& employeeID, const string& newName, int newAge,
                                     const string& newPosition, double newSalary) {
    for (auto& employee : employees) {
        if (employee.getEmployeeID() == employeeID) {
            employee.setName(newName);
            employee.setAge(newAge);
            employee.setPosition(newPosition);
            employee.setSalary(newSalary);
            cout << "Employee updated successfully!" << endl;
            return;
        }
    }
    cout << "Employee not found!" << endl;
}

Employee* EmployeeManager::findEmployeeByID(const string& employeeID) {
    for (auto& employee : employees) {
        if (employee.getEmployeeID() == employeeID) {
            return &employee;
        }
    }
    cout << "Employee not found!" << endl;
    return nullptr;
}

void EmployeeManager::displayAllEmployees() const {
    if (employees.empty()) {
        cout << "No employees available." << endl;
    } else {
        cout << "List of Employees:" << endl;
        for (const auto& employee : employees) {
            employee.displayInfo();
        }
    }
}

void EmployeeManager::printMenu() {
    cout << "====== Employee Manager Menu ======" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Remove Employee" << endl;
    cout << "3. Update Employee" << endl;
    cout << "4. Find Employee by ID" << endl;
    cout << "5. Display All Employees" << endl;
    cout << "6. Export Employee Data to File" << endl;
    cout << "7. Exit" << endl;   
    cout << "Select an option: ";
}
