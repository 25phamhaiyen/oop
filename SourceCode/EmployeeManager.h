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

    // Hiển thị menu
    void printMenu();
};
