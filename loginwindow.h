#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

class DBManager;

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LogInWindow(DBManager* dbManager, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~LogInWindow() override;

signals:
    void loginSuccess(const int id, DBManager* dbManager);

private slots:
    void on_logInButton_clicked();

private:
    int authUser(const QString& uname, const QString& pass);
    Ui::LogInWindow *ui;
    DBManager* m_db;

};

#endif // LOGINWINDOW_H
