#ifndef DASHBOARDVIEWMODEL_H
#define DASHBOARDVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QVariant>
#include <QHash>
#include <QList>
#include <QModelIndex>

class OperationItem
{
public:
    OperationItem(const QString &name, const QString &type, const QString &sender, const QString &date)
        : m_name(name), m_type(type), m_sender(sender), m_date(date) {}

    QString name() const { return m_name; }
    QString type() const { return m_type; }
    QString sender() const { return m_sender; }
    QString date() const { return m_date; }

private:
    QString m_name;
    QString m_type;
    QString m_sender;
    QString m_date;
};

class OperationsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        SenderRole,
        DateRole
    };

    explicit OperationsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<OperationItem> m_operations;
};

class DashboardViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    Q_PROPERTY(QString revenue READ revenue CONSTANT)
    Q_PROPERTY(QString revenueChange READ revenueChange CONSTANT)
    Q_PROPERTY(QString netProfit READ netProfit CONSTANT)
    Q_PROPERTY(QString netProfitChange READ netProfitChange CONSTANT)
    Q_PROPERTY(QString salesCount READ salesCount CONSTANT)
    Q_PROPERTY(QString salesCountChange READ salesCountChange CONSTANT)
    Q_PROPERTY(OperationsModel* operationsModel READ operationsModel CONSTANT)
    Q_PROPERTY(int currentPage READ currentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int totalPages READ totalPages CONSTANT)

public:
    explicit DashboardViewModel(QObject *parent = nullptr);

    QString userName() const { return m_userName; }
    QString revenue() const { return m_revenue; }
    QString revenueChange() const { return m_revenueChange; }
    QString netProfit() const { return m_netProfit; }
    QString netProfitChange() const { return m_netProfitChange; }
    QString salesCount() const { return m_salesCount; }
    QString salesCountChange() const { return m_salesCountChange; }
    OperationsModel* operationsModel() const { return m_operationsModel; }
    int currentPage() const { return m_currentPage; }
    int totalPages() const { return m_totalPages; }

    Q_INVOKABLE void setCurrentPage(int page);
    Q_INVOKABLE void setUserName(const QString& name);

signals:
    void currentPageChanged();
    void userNameChanged();

private:
    QString m_userName;
    QString m_revenue;
    QString m_revenueChange;
    QString m_netProfit;
    QString m_netProfitChange;
    QString m_salesCount;
    QString m_salesCountChange;
    OperationsModel* m_operationsModel;
    int m_currentPage;
    int m_totalPages;
};

#endif // DASHBOARDVIEWMODEL_H
