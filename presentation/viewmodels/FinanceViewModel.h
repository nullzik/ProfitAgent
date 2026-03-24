#pragma once

#include <QObject>
#include <QVariantList>
#include <QString>

class FinanceViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double totalIncome READ totalIncome NOTIFY totalsChanged)
    Q_PROPERTY(double totalExpenses READ totalExpenses NOTIFY totalsChanged)
    Q_PROPERTY(double profit READ profit NOTIFY totalsChanged)
    Q_PROPERTY(QVariantList transactions READ transactions NOTIFY transactionsChanged)
    Q_PROPERTY(QVariantList incomeTransactions READ incomeTransactions NOTIFY transactionsChanged)
    Q_PROPERTY(QVariantList expenseTransactions READ expenseTransactions NOTIFY transactionsChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QVariantList waiterAggregates READ waiterAggregates NOTIFY waiterAggregatesChanged)

public:
    explicit FinanceViewModel(QObject *parent = nullptr);

    double totalIncome() const { return m_totalIncome; }
    double totalExpenses() const { return m_totalExpenses; }
    double profit() const { return m_profit; }
    QVariantList transactions() const { return m_transactions; }
    QVariantList incomeTransactions() const { return m_incomeTransactions; }
    QVariantList expenseTransactions() const { return m_expenseTransactions; }
    QString lastError() const { return m_lastError; }
    QVariantList waiterAggregates() const { return m_waiterAggregates; }

    Q_INVOKABLE void reload();
    Q_INVOKABLE bool addIncome(double amountRubles, const QString& category, const QString& description = QString());
    Q_INVOKABLE bool addExpense(double amountRubles, const QString& category, const QString& description = QString());
    Q_INVOKABLE bool updateTransaction(int id, int type, double amountRubles, const QString& category, const QString& description);
    Q_INVOKABLE bool deleteTransaction(int id);
    Q_INVOKABLE QString formatMoney(double rubles) const;

signals:
    void totalsChanged();
    void transactionsChanged();
    void lastErrorChanged();
    void waiterAggregatesChanged();

private:
    void setLastError(const QString& message);
    void updateTotals();

    double m_totalIncome{0};
    double m_totalExpenses{0};
    double m_profit{0};
    QVariantList m_transactions;
    QVariantList m_incomeTransactions;
    QVariantList m_expenseTransactions;
    QVariantList m_waiterAggregates;
    QString m_lastError;
};
