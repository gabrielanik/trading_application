#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTextCursor>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>


namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LogInWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~LogInWindow() override;

signals:
    void loginSuccess(const int id);

private slots:
    void on_logInButton_clicked();

private:
    int authUser(const QString& uname, QString& pass);
    Ui::LogInWindow *ui;

};

#endif // LOGINWINDOW_H
