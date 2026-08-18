#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

struct Employee {
    std::string name;
    double salary = 0.0;
};

std::vector<Employee> readEmployeesFromConsole(std::size_t count) {
    std::vector<Employee> employees;
    employees.reserve(count);

    for (std::size_t i = 0; i < count; ++i) {
        Employee employee;
        std::cout << "Employee " << i + 1 << " name: ";
        std::getline(std::cin, employee.name);

        std::cout << "Employee " << i + 1 << " salary: ";
        while (!(std::cin >> employee.salary)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid salary. Enter a numeric value: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        employees.push_back(employee);
    }
    return employees;
}

void writeEmployees(const std::vector<Employee>& employees, const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
        throw std::runtime_error("Could not open output file: " + filename);
    }

    output << std::fixed << std::setprecision(2);
    for (const Employee& employee : employees) {
        output << std::quoted(employee.name) << ' ' << employee.salary << '\n';
    }
}

std::vector<Employee> readEmployees(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) {
        throw std::runtime_error("Could not open input file: " + filename);
    }

    std::vector<Employee> employees;
    Employee employee;
    while (input >> std::quoted(employee.name) >> employee.salary) {
        employees.push_back(employee);
    }
    return employees;
}

double maxSalary(const std::vector<Employee>& employees) {
    if (employees.empty()) {
        return 0.0;
    }

    return std::max_element(employees.begin(), employees.end(),
        [](const Employee& first, const Employee& second) {
            return first.salary < second.salary;
        })->salary;
}

double averageSalary(const std::vector<Employee>& employees) {
    if (employees.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const Employee& employee : employees) {
        total += employee.salary;
    }
    return total / static_cast<double>(employees.size());
}

void sortBySalary(std::vector<Employee>& employees) {
    std::sort(employees.begin(), employees.end(),
        [](const Employee& first, const Employee& second) {
            return first.salary < second.salary;
        });
}

void displayEmployees(const std::vector<Employee>& employees) {
    std::cout << std::left << std::setw(24) << "Name" << "Salary\n";
    std::cout << std::string(36, '-') << '\n';

    for (const Employee& employee : employees) {
        std::cout << std::left << std::setw(24) << employee.name
                  << std::fixed << std::setprecision(2) << employee.salary << '\n';
    }
}

int main() {
    constexpr const char* kFilename = "employee.txt";
    std::size_t count = 0;

    std::cout << "How many employees would you like to enter? ";
    if (!(std::cin >> count)) {
        std::cerr << "Invalid employee count.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        auto employees = readEmployeesFromConsole(count);
        writeEmployees(employees, kFilename);

        employees = readEmployees(kFilename);
        std::cout << "\nMaximum salary: " << maxSalary(employees) << '\n';
        std::cout << "Average salary: " << averageSalary(employees) << '\n';

        sortBySalary(employees);
        writeEmployees(employees, kFilename);

        std::cout << "\nEmployees sorted by salary:\n";
        displayEmployees(employees);
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
