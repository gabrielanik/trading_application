#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTextCursor>

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QDialog
{
    Q_OBJECT
public:
    explicit LogInWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~LogInWindow() override;

private slots:
    void on_logInButton_clicked();

private:
    Ui::LogInWindow *ui;

};

#endif // LOGINWINDOW_H
