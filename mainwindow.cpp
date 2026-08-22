#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"
#include "dbmanager.h"

MainWindow::MainWindow(const int userId, DBManager* dbManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_db(dbManager)
{
    ui->setupUi(this);
    loadAccountData(userId);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadAccountData(const int userId){

    m_account = m_db->getAccount(userId);

    setLCD(m_account->getBalance(), m_account->getCurrency());
   // set table
}

void MainWindow::setLCD(const double balance, const QString currency){
    ui->lcdBalance->display(balance);
    ui->currencyTextEdit->appendPlainText(currency);
}