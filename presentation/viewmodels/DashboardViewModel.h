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
    OperationItem(const QString &name,
                  const QString &type,
                  const QString &sender,
                  const QString &date,
                  const QString &details,
                  const QString &amount)
        : m_name(name)
        , m_type(type)
        , m_sender(sender)
        , m_date(date)
        , m_details(details)
        , m_amount(amount)
    {}

    QString name() const { return m_name; }
    QString type() const { return m_type; }
    QString sender() const { return m_sender; }
    QString date() const { return m_date; }
    QString details() const { return m_details; }
    QString amount() const { return m_amount; }

private:
    QString m_name;
    QString m_type;
    QString m_sender;
    QString m_date;
    QString m_details;
    QString m_amount;
};

class OperationsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        SenderRole,
        DateRole,
        DetailsRole,
        AmountRole
    };

    explicit OperationsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setOperations(QList<OperationItem> operations);

private:
    QList<OperationItem> m_operations;
};

class DashboardViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName NOTIFY userNameChanged)
    Q_PROPERTY(QString revenue READ revenue NOTIFY revenueChanged)
    Q_PROPERTY(QString revenueChange READ revenueChange NOTIFY revenueChangeChanged)
    Q_PROPERTY(QString netProfit READ netProfit NOTIFY netProfitChanged)
    Q_PROPERTY(QString netProfitChange READ netProfitChange NOTIFY netProfitChangeChanged)
    Q_PROPERTY(QString salesCount READ salesCount NOTIFY salesCountChanged)
    Q_PROPERTY(QString salesCountChange READ salesCountChange NOTIFY salesCountChangeChanged)
    Q_PROPERTY(OperationsModel* operationsModel READ operationsModel CONSTANT)
    Q_PROPERTY(int currentPage READ currentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int totalPages READ totalPages NOTIFY totalPagesChanged)
    Q_PROPERTY(int filterIndex READ filterIndex WRITE setFilterIndex NOTIFY filterIndexChanged)

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
    int filterIndex() const { return m_filterIndex; }

    Q_INVOKABLE void setCurrentPage(int page);
    Q_INVOKABLE void setUserName(const QString& name);
    Q_INVOKABLE void reload();
    Q_INVOKABLE void setFilterIndex(int index);

    // Логирование пользовательских операций с текущим пользователем как отправителем.
    Q_INVOKABLE void logUiEvent(const QString& eventType,
                                const QString& title,
                                const QString& details = QString(),
                                double amountRubles = 0.0);

signals:
    void currentPageChanged();
    void totalPagesChanged();
    void userNameChanged();
    void revenueChanged();
    void revenueChangeChanged();
    void netProfitChanged();
    void netProfitChangeChanged();
    void salesCountChanged();
    void salesCountChangeChanged();
    void filterIndexChanged();

private:
    void reloadKpis();
    void reloadOperations();
    void updatePagination();

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
    int m_pageSize{10};
    int m_totalOperations{0};
    int m_filterIndex{0};
};

#endif // DASHBOARDVIEWMODEL_H
