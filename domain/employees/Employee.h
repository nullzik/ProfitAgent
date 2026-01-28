#pragma once

#include <string>

#include "domain/value_objects/Money.h"
#include "domain/value_objects/Quantity.h"

namespace domain {

enum class EmployeeRole {
    Waiter,
    Chef,
    Manager,
    Director,
    Cashier,
    Other
};

class Employee final {
public:
    Employee(std::string id,
             std::string fullName,
             int age,
             std::string phone,
             std::string address,
             EmployeeRole role,
             Money hourlyRate,
             Quantity workedHours,
             Money salaryBalance)
        : id_(std::move(id)),
          fullName_(std::move(fullName)),
          age_(age),
          phone_(std::move(phone)),
          address_(std::move(address)),
          role_(role),
          hourlyRate_(std::move(hourlyRate)),
          workedHours_(workedHours),
          salaryBalance_(std::move(salaryBalance)) {}

    const std::string& id() const noexcept { return id_; }
    const std::string& fullName() const noexcept { return fullName_; }
    int age() const noexcept { return age_; }
    const std::string& phone() const noexcept { return phone_; }
    const std::string& address() const noexcept { return address_; }
    EmployeeRole role() const noexcept { return role_; }
    const Money& hourlyRate() const noexcept { return hourlyRate_; }
    const Quantity& workedHours() const noexcept { return workedHours_; }
    const Money& salaryBalance() const noexcept { return salaryBalance_; }

    void setFullName(std::string v) { fullName_ = std::move(v); }
    void setAge(int v) { age_ = v; }
    void setPhone(std::string v) { phone_ = std::move(v); }
    void setAddress(std::string v) { address_ = std::move(v); }
    void setRole(EmployeeRole v) { role_ = v; }
    void setHourlyRate(Money v) { hourlyRate_ = std::move(v); }
    void setWorkedHours(Quantity v) { workedHours_ = v; }
    void setSalaryBalance(Money v) { salaryBalance_ = std::move(v); }

private:
    std::string id_;
    std::string fullName_;
    int age_{0};
    std::string phone_;
    std::string address_;
    EmployeeRole role_{EmployeeRole::Other};

    Money hourlyRate_{Money::zero("RUB")};
    Quantity workedHours_{Quantity::zero()};
    Money salaryBalance_{Money::zero("RUB")};
};

} // namespace domain



