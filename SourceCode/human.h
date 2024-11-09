#pragma once
#include "date_time.h"
#include "flight.h"
#include "plane.h"
class Human {
	private:
		string name;
		Date date;
		string sex; // giới tính
		int age;
	public:
		Human();
		Human( string name, Date date, string sex );
		Human( const Human &human );
		friend void standarName( string &name );
		friend istream& operator >> ( istream& is, Human &human );
		friend ostream& operator << ( ostream& os, const Human &human );
		Human operator = ( const Human &human );
		string getName() const;
		Date getDate() const;
		string getSex() const;
		int getAge() const;
};
class humanInPlane : public Human {
	private:
	    string id;
		string position;  // chức vụ trên máy bay( cơ trưởng, tiếp viên, cơ phó )
		double salary;
	public:
		humanInPlane();
		humanInPlane( const Human &human, string id, string position, double salary );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
		void setId( string id );
		void setSalary( string position );
		string getPosition() const;
		double getSalary() const;
		string getId() const;
		bool operator<(const humanInPlane& other) const;
};
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Date {
public:
    int day, month, year;
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    friend ostream& operator << (ostream& os, const Date& date) {
        os << (date.day < 10 ? "0" : "") << date.day << "/"
           << (date.month < 10 ? "0" : "") << date.month << "/"
           << date.year;
        return os;
    }
};

void standarName(string &name) {
    for (char &ch : name) {
        ch = tolower(ch);
    }
    name[0] = toupper(name[0]);
}

class Human {
private:
    string name;
    Date date;
    string sex;
    int age;

public:
    Human() : name("Unknown"), date(), sex("Unknown"), age(0) {}

    Human(string name, Date date, string sex)
        : name(name), date(date), sex(sex), age(2023 - date.year) {}

    Human(const Human &human) 
        : name(human.name), date(human.date), sex(human.sex), age(human.age) {}

    friend void standarName(string &name);

    friend istream& operator >> (istream &is, Human &human) {
        cout << "Enter name: ";
        getline(is, human.name);
        standarName(human.name);

        cout << "Enter birth date (day month year): ";
        is >> human.date.day >> human.date.month >> human.date.year;
        human.age = 2023 - human.date.year;

        cout << "Enter sex (male/female): ";
        is >> human.sex;
        return is;
    }

    friend ostream& operator << (ostream &os, const Human &human) {
        os << "Name: " << human.name << ", Birth Date: " << human.date
           << ", Sex: " << human.sex << ", Age: " << human.age;
        return os;
    }

    Human& operator = (const Human &human) {
        if (this != &human) {
            name = human.name;
            date = human.date;
            sex = human.sex;
            age = human.age;
        }
        return *this;
    }

    string getName() const { return name; }
    Date getDate() const { return date; }
    string getSex() const { return sex; }
    int getAge() const { return age; }
};

class humanInPlane : public Human {
private:
    string id;
    string position;
    double salary;
    string nationality;
    int yearsOfExperience;
    vector<string> trainingCourses;

public:
    humanInPlane() : Human(), id("Unknown"), position("Unknown"), salary(0.0), nationality("Unknown"), yearsOfExperience(0) {}

    humanInPlane(const Human &human, string id, string position, double salary, string nationality, int yearsOfExperience)
        : Human(human), id(id), position(position), salary(salary), nationality(nationality), yearsOfExperience(yearsOfExperience) {}

    friend istream& operator >> (istream &is, humanInPlane &hip) {
        is >> static_cast<Human&>(hip);

        cout << "Enter ID: ";
        is >> hip.id;

        cout << "Enter position: ";
        is.ignore();
        getline(is, hip.position);

        cout << "Enter salary: ";
        is >> hip.salary;

        cout << "Enter nationality: ";
        is.ignore();
        getline(is, hip.nationality);

        cout << "Enter years of experience: ";
        is >> hip.yearsOfExperience;

        int numCourses;
        cout << "Enter the number of training courses: ";
        is >> numCourses;
        is.ignore(); // to discard the newline after the number
        for (int i = 0; i < numCourses; i++) {
            string course;
            cout << "Enter training course " << i + 1 << ": ";
            getline(is, course);
            hip.trainingCourses.push_back(course);
        }

        return is;
    }

    friend ostream& operator << (ostream &os, const humanInPlane &hip) {
        os << "ID: " << hip.id << ", Name: " << hip.getName() 
           << ", Position: " << hip.position 
           << ", Salary: " << hip.salary
           << ", Nationality: " << hip.nationality
           << ", Experience: " << hip.yearsOfExperience 
           << " years, Training: ";

        if (hip.trainingCourses.empty()) {
            os << "None";
        } else {
            for (const auto& course : hip.trainingCourses) {
                os << course << ", ";
            }
        }
        os << endl;
        return os;
    }

    void setId(string id) { this->id = id; }
    void setSalary(double salary) { this->salary = salary; }

    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    string getId() const { return id; }

    bool operator < (const humanInPlane &other) const {
        return this->salary < other.salary;
    }

    bool operator == (const string& searchId) const {
        return this->id == searchId;
    }

    vector<string> getTrainingCourses() const { return trainingCourses; }
    string getNationality() const { return nationality; }
    int getYearsOfExperience() const { return yearsOfExperience; }
};

void printMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Add a new human in plane\n";
    cout << "2. Display all human in plane\n";
    cout << "3. Sort by salary (ascending)\n";
    cout << "4. Sort by name (alphabetical)\n";
    cout << "5. Search by name\n";
    cout << "6. Search by ID\n";
    cout << "7. Update human information\n";
    cout << "8. Delete human by ID\n";
    cout << "9. Total salary of all employees\n";
    cout << "10. Find highest salary\n";
    cout << "11. Search by position\n";
    cout << "12. List employees by nationality\n";
    cout << "13. Average salary of all employees\n";
    cout << "14. Sort by years of experience\n";
    cout << "15. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<humanInPlane> people;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            humanInPlane hip;
            cin >> hip;
            people.push_back(hip);
        }
        else if (choice == 2) {
            cout << "\nList of human in plane:\n";
            for (const auto &hip : people) {
                cout << "---------------------------------------------------------------\n";
                cout << "ID: " << hip.getId() << " | Name: " << hip.getName() << "\n";
                cout << "Position: " << hip.getPosition() << "\n";
                cout << "Salary: " << hip.getSalary() << " | Nationality: " << hip.getNationality() << "\n";
                cout << "Experience: " << hip.getYearsOfExperience() << " years\n";
                cout << "Training Courses: ";
                if (hip.getTrainingCourses().empty()) {
                    cout << "None\n";
                } else {
                    for (const auto &course : hip.getTrainingCourses()) {
                        cout << course << ", ";
                    }
                    cout << endl;
                }
                cout << "---------------------------------------------------------------\n";
            }
        }
        else if (choice == 3) {
            sort(people.begin(), people.end());
            cout << "\nPeople sorted by salary (ascending):\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 4) {
            sort(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getName() < b.getName();
            });
            cout << "\nPeople sorted by name (alphabetical):\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 5) {
            string name;
            cout << "Enter name to search: ";
            getline(cin, name);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getName() == name) {
                    cout << hip << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with name: " << name << endl;
        }
        else if (choice == 6) {
            string id;
            cout << "Enter ID to search: ";
            getline(cin, id);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getId() == id) {
                    cout << hip << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with ID: " << id << endl;
        }
        else if (choice == 7) {
            string id;
            cout << "Enter ID to update: ";
            getline(cin, id);
            bool found = false;
            for (auto &hip : people) {
                if (hip.getId() == id) {
                    cout << "Enter new information for ID " << id << ":\n";
                    cin >> hip;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with ID: " << id << endl;
        }
        else if (choice == 8) {
            string id;
            cout << "Enter ID to delete: ";
            getline(cin, id);
            auto it = find_if(people.begin(), people.end(), [&id](const humanInPlane &hip) {
                return hip.getId() == id;
            });
            if (it != people.end()) {
                people.erase(it);
                cout << "Human with ID " << id << " has been deleted.\n";
            } else {
                cout << "No human found with ID: " << id << endl;
            }
        }
        else if (choice == 9) {
            double totalSalary = 0;
            for (const auto &hip : people) {
                totalSalary += hip.getSalary();
            }
            cout << "Total salary of all employees: " << totalSalary << endl;
        }
        else if (choice == 10) {
            if (people.empty()) {
                cout << "No employees to calculate.\n";
                continue;
            }
            auto maxSalaryIt = max_element(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getSalary() < b.getSalary();
            });
            cout << "Employee with highest salary:\n" << *maxSalaryIt << endl;
        }
        else if (choice == 11) {
            string position;
            cout << "Enter position to search: ";
            getline(cin, position);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getPosition() == position) {
                    cout << hip << endl;
                    found = true;
                }
            }
            if (!found) cout << "No employee found with position: " << position << endl;
        }
        else if (choice == 12) {
            string nationality;
            cout << "Enter nationality to filter: ";
            getline(cin, nationality);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getNationality() == nationality) {
                    cout << hip << endl;
                    found = true;
                }
            }
            if (!found) cout << "No employee found with nationality: " << nationality << endl;
        }
        else if (choice == 13) {
            double totalSalary = 0;
            for (const auto &hip : people) {
                totalSalary += hip.getSalary();
            }
            double avgSalary = totalSalary / people.size();
            cout << "Average salary of all employees: " << avgSalary << endl;
        }
        else if (choice == 14) {
            sort(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getYearsOfExperience() < b.getYearsOfExperience();
            });
            cout << "\nPeople sorted by years of experience:\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 15) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

class Date {
public:
    int day, month, year;

    Date() : day(1), month(1), year(2000) {}

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    static Date currentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return Date(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
    }

    int age(const Date &birthdate) const {
        Date current = currentDate();
        int age = current.year - birthdate.year;
        if (current.month < birthdate.month || (current.month == birthdate.month && current.day < birthdate.day)) {
            age--;
        }
        return age;
    }

    static int daysDifference(const Date &d1, const Date &d2) {
        tm a = {0};
        a.tm_year = d1.year - 1900;
        a.tm_mon = d1.month - 1;
        a.tm_mday = d1.day;
        time_t t1 = mktime(&a);

        tm b = {0};
        b.tm_year = d2.year - 1900;
        b.tm_mon = d2.month - 1;
        b.tm_mday = d2.day;
        time_t t2 = mktime(&b);

        return difftime(t2, t1) / (60 * 60 * 24);
    }

    friend ostream& operator << (ostream &os, const Date &date) {
        os << (date.day < 10 ? "0" : "") << date.day << "/"
           << (date.month < 10 ? "0" : "") << date.month << "/"
           << date.year;
        return os;
    }

    friend istream& operator >> (istream &is, Date &date) {
        is >> date.day >> date.month >> date.year;
        return is;
    }
};

class Human {
private:
    string name;
    Date date;
    string sex;
    int age;

public:
    Human() : name("Unknown"), date(), sex("Unknown"), age(0) {}

    Human(string name, Date date, string sex)
        : name(name), date(date), sex(sex), age(2023 - date.year) {}

    Human(const Human &human) 
        : name(human.name), date(human.date), sex(human.sex), age(human.age) {}

    friend istream& operator >> (istream &is, Human &human) {
        cout << "Enter name: ";
        getline(is, human.name);

        cout << "Enter birth date (day month year): ";
        is >> human.date;
        human.age = human.date.age(human.date);

        cout << "Enter sex (male/female): ";
        is >> human.sex;
        return is;
    }

    friend ostream& operator << (ostream &os, const Human &human) {
        os << "Name: " << human.name << ", Birth Date: " << human.date
           << ", Sex: " << human.sex << ", Age: " << human.age;
        return os;
    }

    Human& operator = (const Human &human) {
        if (this != &human) {
            name = human.name;
            date = human.date;
            sex = human.sex;
            age = human.age;
        }
        return *this;
    }

    string getName() const { return name; }
    Date getDate() const { return date; }
    string getSex() const { return sex; }
    int getAge() const { return age; }
};

class humanInPlane : public Human {
private:
    string id;
    string position;
    double salary;
    string nationality;
    int yearsOfExperience;
    vector<string> trainingCourses;

public:
    humanInPlane() : Human(), id("Unknown"), position("Unknown"), salary(0.0), nationality("Unknown"), yearsOfExperience(0) {}

    humanInPlane(const Human &human, string id, string position, double salary, string nationality, int yearsOfExperience)
        : Human(human), id(id), position(position), salary(salary), nationality(nationality), yearsOfExperience(yearsOfExperience) {}

    friend istream& operator >> (istream &is, humanInPlane &hip) {
        is >> static_cast<Human&>(hip);

        cout << "Enter ID: ";
        is >> hip.id;

        cout << "Enter position: ";
        is.ignore();
        getline(is, hip.position);

        cout << "Enter salary: ";
        is >> hip.salary;

        cout << "Enter nationality: ";
        is.ignore();
        getline(is, hip.nationality);

        cout << "Enter years of experience: ";
        is >> hip.yearsOfExperience;

        int numCourses;
        cout << "Enter the number of training courses: ";
        is >> numCourses;
        is.ignore();
        for (int i = 0; i < numCourses; i++) {
            string course;
            cout << "Enter training course " << i + 1 << ": ";
            getline(is, course);
            hip.trainingCourses.push_back(course);
        }

        return is;
    }

    friend ostream& operator << (ostream &os, const humanInPlane &hip) {
        os << "ID: " << hip.id << ", Name: " << hip.getName() 
           << ", Position: " << hip.position 
           << ", Salary: " << hip.salary
           << ", Nationality: " << hip.nationality
           << ", Experience: " << hip.yearsOfExperience 
           << " years, Training: ";

        if (hip.trainingCourses.empty()) {
            os << "None";
        } else {
            for (const auto& course : hip.trainingCourses) {
                os << course << ", ";
            }
        }
        os << endl;
        return os;
    }

    void setId(string id) { this->id = id; }
    void setSalary(double salary) { this->salary = salary; }

    string getPosition() const { return position; }
    double getSalary() const { return salary; }
    string getId() const { return id; }

    bool operator < (const humanInPlane &other) const {
        return this->salary < other.salary;
    }

    bool operator == (const string& searchId) const {
        return this->id == searchId;
    }

    vector<string> getTrainingCourses() const { return trainingCourses; }
    string getNationality() const { return nationality; }
    int getYearsOfExperience() const { return yearsOfExperience; }
};

void printMenu() {
    cout << "\n===== MENU =====\n";
    cout << "1. Add a new human in plane\n";
    cout << "2. Display all human in plane\n";
    cout << "3. Sort by salary (ascending)\n";
    cout << "4. Sort by name (alphabetical)\n";
    cout << "5. Search by name\n";
    cout << "6. Search by ID\n";
    cout << "7. Update human information\n";
    cout << "8. Delete human by ID\n";
    cout << "9. Total salary of all employees\n";
    cout << "10. Find highest salary\n";
    cout << "11. Search by position\n";
    cout << "12. List employees by nationality\n";
    cout << "13. Average salary of all employees\n";
    cout << "14. Sort by years of experience\n";
    cout << "15. Display current date and time\n";
    cout << "16. Display age of employee based on birthdate\n";
    cout << "17. Calculate days difference between two dates\n";
    cout << "18. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    vector<humanInPlane> people;
    int choice;

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            humanInPlane hip;
            cin >> hip;
            people.push_back(hip);
        }
        else if (choice == 2) {
            cout << "\nList of human in plane:\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 3) {
            sort(people.begin(), people.end());
            cout << "\nPeople sorted by salary (ascending):\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 4) {
            sort(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getName() < b.getName();
            });
            cout << "\nPeople sorted by name (alphabetical):\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 5) {
            string name;
            cout << "Enter name to search: ";
            getline(cin, name);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getName() == name) {
                    cout << hip << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with name: " << name << endl;
        }
        else if (choice == 6) {
            string id;
            cout << "Enter ID to search: ";
            getline(cin, id);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getId() == id) {
                    cout << hip << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with ID: " << id << endl;
        }
        else if (choice == 7) {
            string id;
            cout << "Enter ID to update: ";
            getline(cin, id);
            bool found = false;
            for (auto &hip : people) {
                if (hip.getId() == id) {
                    cout << "Enter new information for ID " << id << ":\n";
                    cin >> hip;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No human found with ID: " << id << endl;
        }
        else if (choice == 8) {
            string id;
            cout << "Enter ID to delete: ";
            getline(cin, id);
            auto it = find_if(people.begin(), people.end(), [&id](const humanInPlane &hip) {
                return hip.getId() == id;
            });
            if (it != people.end()) {
                people.erase(it);
                cout << "Human with ID " << id << " has been deleted.\n";
            } else {
                cout << "No human found with ID: " << id << endl;
            }
        }
        else if (choice == 9) {
            double totalSalary = 0;
            for (const auto &hip : people) {
                totalSalary += hip.getSalary();
            }
            cout << "Total salary of all employees: " << totalSalary << endl;
        }
        else if (choice == 10) {
            if (people.empty()) {
                cout << "No employees to calculate.\n";
                continue;
            }
            auto maxSalaryIt = max_element(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getSalary() < b.getSalary();
            });
            cout << "Employee with highest salary:\n" << *maxSalaryIt << endl;
        }
        else if (choice == 11) {
            string position;
            cout << "Enter position to search: ";
            getline(cin, position);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getPosition() == position) {
                    cout << hip << endl;
                    found = true;
                }
            }
            if (!found) cout << "No employee found with position: " << position << endl;
        }
        else if (choice == 12) {
            string nationality;
            cout << "Enter nationality to filter: ";
            getline(cin, nationality);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getNationality() == nationality) {
                    cout << hip << endl;
                    found = true;
                }
            }
            if (!found) cout << "No employee found with nationality: " << nationality << endl;
        }
        else if (choice == 13) {
            double totalSalary = 0;
            for (const auto &hip : people) {
                totalSalary += hip.getSalary();
            }
            double avgSalary = totalSalary / people.size();
            cout << "Average salary of all employees: " << avgSalary << endl;
        }
        else if (choice == 14) {
            sort(people.begin(), people.end(), [](const humanInPlane &a, const humanInPlane &b) {
                return a.getYearsOfExperience() < b.getYearsOfExperience();
            });
            cout << "\nPeople sorted by years of experience:\n";
            for (const auto &hip : people) {
                cout << hip << endl;
            }
        }
        else if (choice == 15) {
            Date current = Date::currentDate();
            cout << "Current date is: " << current << endl;
        }
        else if (choice == 16) {
            string name;
            cout << "Enter employee's name to calculate age: ";
            getline(cin, name);
            bool found = false;
            for (const auto &hip : people) {
                if (hip.getName() == name) {
                    int age = hip.getDate().age(hip.getDate());
                    cout << name << " is " << age << " years old.\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No employee found with name: " << name << endl;
        }
        else if (choice == 17) {
            Date start, end;
            cout << "Enter the first date (day month year): ";
            cin >> start;
            cout << "Enter the second date (day month year): ";
            cin >> end;
            int daysDiff = Date::daysDifference(start, end);
            cout << "The difference between the two dates is: " << daysDiff << " days.\n";
        }
        else if (choice == 18) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

