#pragma once

#include <QString>
#include <QVariantList>

namespace application {

class FinanceService {
public:
    enum Type { Income = 1, Expense = 2 };

    // Returns all transactions as QVariantList of maps (id, type, amountRubles, category, description, createdAt)
    static QVariantList getAllTransactions();

    // Returns transactions filtered by type (1=income, 2=expense), or all if type=0
    static QVariantList getTransactionsByType(int type);

    // Adds transaction. type: 1=income, 2=expense. amountRubles: amount in rubles.
    static bool addTransaction(int type, double amountRubles, const QString& category);

    // Adds transaction with optional description
    static bool addTransaction(int type, double amountRubles, const QString& category, const QString& description);

    // Updates transaction by id
    static bool updateTransaction(int id, int type, double amountRubles, const QString& category, const QString& description);

    // Deletes transaction by id
    static bool deleteTransaction(int id);

    // Returns total income (sum of type=1 transactions).
    static double getTotalIncome();

    // Returns total expenses (sum of type=2 transactions).
    static double getTotalExpenses();

    // Returns profit (income - expenses).
    static double getProfit();

    // Revenue from sales transactions (category starts with "Продажи стол") in the last `days` days.
    // offsetDays=0 => latest window; offsetDays=days => previous window.
    static double getSalesRevenueForDays(int days, int offsetDays = 0);

    // Count of sales transactions (category starts with "Продажи стол") in the last `days` days.
    static int getSalesCountForDays(int days, int offsetDays = 0);

    // Net profit (income - expenses) in the last `days` days.
    static double getNetProfitForDays(int days, int offsetDays = 0);

    // Returns aggregates for waiters (role=0): id, fullName, workedHours, salaryRubles.
    static QVariantList getWaiterAggregates();
};

} // namespace application
