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

    std::map<QString, Holdings> portfolio = m_db->getHoldings(userId);
    m_account->setPortfolio(portfolio);

    setLCD(m_account->getBalance(), m_account->getCurrency());

    setTableView(portfolio);
}

void MainWindow::setLCD(const double balance, const QString currency){
    ui->lcdBalance->display(balance);
    ui->currencyTextEdit->appendPlainText(currency);
}

void MainWindow::setTableView(const std::map <QString, Holdings> portfolio){

    auto *model = new QStandardItemModel(this);

    model->setHorizontalHeaderLabels({
        "Stock",
        "Shares",
        "Investment"
    });

    for (const auto& [stock, holding] : portfolio) {

        QList<QStandardItem*> row;

        row.append(
            new QStandardItem(stock)
            );

        row.append(
            new QStandardItem(
                QString::number(holding.shares)
                )
            );

        QString investment =
            QString::number(
                holding.investment,
                'f',
                2
                )
            + " "
            + holding.currency;

        row.append(
            new QStandardItem(investment)
            );

        model->appendRow(row);
    }

    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();
}