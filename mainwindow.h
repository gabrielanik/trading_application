#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QStandardItem>
#include <QStandardItemModel>
#include <memory>
#include <vector>
#include "main.h"

class Account;
class DBManager;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const int userId, DBManager* dbManager, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Account> m_account;
    DBManager* m_db;

    void loadAccountData(const int userId);
    void setLCD(const double balance, const QString currency);
    void setTableView(const std::map <QString, Holdings> portfolio);
};

#endif // MAINWINDOW_H
