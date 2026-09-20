#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <map>

class DBManager;
class Account;
class StockManager;

namespace Ui {
class OrderWindow;
}

class OrderWindow: public QDialog
{
    Q_OBJECT
public:
    explicit OrderWindow(const QString &order, DBManager *dbManager,
                         Account *account, StockManager *stockManager, QWidget *parent = nullptr);
    ~OrderWindow() override;

signals:
    void searchStock(QString stock);
    void orderExecuted();
    void back();

private slots:
    void on_searchButton_clicked();
    void on_executeOrderButton_clicked();
    void on_backButton_clicked();
    void on_sharesLineEdit_textChanged(const QString& text);

private:
    QString m_order;
    Ui::OrderWindow *ui = nullptr;
    DBManager *m_db = nullptr;
    Account *m_acc = nullptr;
    StockManager *m_stockManager = nullptr;
    double m_price;

    void loadBalance(const double balance, const QString currency);
    void loadStockData(const QString stock);
    void updateStockPrice(const QString& stock, const double price);

};

#endif // ORDERWINDOW_H
