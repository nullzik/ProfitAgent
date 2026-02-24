#include "FinanceViewModel.h"
#include "application/services/FinanceService.h"

#include <QLocale>
#include <QDebug>

FinanceViewModel::FinanceViewModel(QObject *parent)
    : QObject(parent)
{
    reload();
}

void FinanceViewModel::reload()
{
    m_transactions = application::FinanceService::getAllTransactions();
    m_incomeTransactions = application::FinanceService::getTransactionsByType(application::FinanceService::Income);
    m_expenseTransactions = application::FinanceService::getTransactionsByType(application::FinanceService::Expense);
    updateTotals();
    emit transactionsChanged();
    emit totalsChanged();
}

bool FinanceViewModel::addIncome(double amountRubles, const QString& category, const QString& description)
{
    if (amountRubles <= 0) {
        setLastError(QStringLiteral("Сумма должна быть больше нуля"));
        return false;
    }
    if (!application::FinanceService::addTransaction(application::FinanceService::Income, amountRubles, category, description)) {
        setLastError(QStringLiteral("Не удалось добавить доход"));
        return false;
    }
    setLastError(QString{});
    reload();
    return true;
}

bool FinanceViewModel::addExpense(double amountRubles, const QString& category, const QString& description)
{
    if (amountRubles <= 0) {
        setLastError(QStringLiteral("Сумма должна быть больше нуля"));
        return false;
    }
    if (!application::FinanceService::addTransaction(application::FinanceService::Expense, amountRubles, category, description)) {
        setLastError(QStringLiteral("Не удалось добавить расход"));
        return false;
    }
    setLastError(QString{});
    reload();
    return true;
}

bool FinanceViewModel::updateTransaction(int id, int type, double amountRubles, const QString& category, const QString& description)
{
    if (amountRubles <= 0) {
        setLastError(QStringLiteral("Сумма должна быть больше нуля"));
        return false;
    }
    if (!application::FinanceService::updateTransaction(id, type, amountRubles, category, description)) {
        setLastError(QStringLiteral("Не удалось обновить операцию"));
        return false;
    }
    setLastError(QString{});
    reload();
    return true;
}

bool FinanceViewModel::deleteTransaction(int id)
{
    if (!application::FinanceService::deleteTransaction(id)) {
        setLastError(QStringLiteral("Не удалось удалить операцию"));
        return false;
    }
    setLastError(QString{});
    reload();
    return true;
}

QString FinanceViewModel::formatMoney(double rubles) const
{
    return QLocale(QLocale::Russian).toCurrencyString(rubles, QStringLiteral("₽"));
}

void FinanceViewModel::setLastError(const QString& message)
{
    if (m_lastError != message) {
        m_lastError = message;
        emit lastErrorChanged();
    }
}

void FinanceViewModel::updateTotals()
{
    m_totalIncome = application::FinanceService::getTotalIncome();
    m_totalExpenses = application::FinanceService::getTotalExpenses();
    m_profit = application::FinanceService::getProfit();
}
