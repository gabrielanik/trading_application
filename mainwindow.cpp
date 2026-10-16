#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"
#include "dbmanager.h"
#include "stockmanager.h"

MainWindow::MainWindow(const int userId, DBManager* dbManager, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db(dbManager),
    m_stockManager(new StockManager(this)),
    m_model(new QStandardItemModel(this))
{
    ui->setupUi(this);

    connect(m_stockManager,
            &StockManager::priceReceived,
            this,
            &MainWindow::updateStockPrice);

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

    setBalance(m_account->getPortfolio(), m_account->getBalance(),
               m_account->getCurrency());

    setTableView(portfolio);
}

void MainWindow::setBalance(const std::map <QString, Holdings>& portfolio,
                            const double balance, const QString currency){


    double sum = 0;
    QString symbol;
    for (const auto& [stock, holding] : portfolio)
    {
        sum += holding.investment;
    }

    double accountValue = sum + balance;

    if(currency == "USD"){
        symbol = "$";
    }else if(currency == "EUR"){
        symbol = "€";
    }

    ui->accValueTextEdit->appendPlainText(symbol + QString::number(accountValue, 'f', 2));
    ui->sumTextEdit->appendPlainText(symbol + QString::number(sum, 'f', 2));
    ui->balanceTextEdit->appendPlainText(symbol + QString::number(balance, 'f', 2));

}

void MainWindow::setTableView(const std::map <QString, Holdings>& portfolio){

    m_model->setHorizontalHeaderLabels({
        "Stock",
        "Shares",
        "Investment",
        "Current price",
        "Return"
    });

    ui->tableView->setModel(m_model);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableView->horizontalHeader()
        ->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    ui->tableView->horizontalHeader()
        ->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    ui->tableView->horizontalHeader()
        ->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    int rowIndex = 0;

    for (const auto& [stock, holding] : portfolio)
    {
        QList<QStandardItem*> row;

        row.append(
            new QStandardItem(stock)
            );

        row.append(
            new QStandardItem(
                QString::number(holding.shares)
                )
            );

        row.append(
            new QStandardItem(
                QString::number(holding.investment, 'f', 2)
                + " "
                + holding.currency
                )
            );

        row.append(
            new QStandardItem("Loading...")
            );

        row.append(
            new QStandardItem("Loading...")
            );

        m_model->appendRow(row);

        m_stockRows.insert(stock, rowIndex);

        m_stockManager->getPrice(stock);

        ++rowIndex;
    }

}

void MainWindow::updateStockPrice(const QString& stock, const double price, const QString& currency){

    if (!m_model) {
        qDebug() << "m_model is null";
        return;
    }

    if (!m_stockRows.contains(stock)) {
        qDebug() << "No row found for stock:" << stock;
        return;
    }

    int row = m_stockRows.value(stock);

    QStandardItem* priceItem =
        m_model->item(row, 3);

    if (!priceItem) {
        qDebug() << "Price item is null for row:" << row;
        return;
    }

    priceItem->setText(
        QString::number(price, 'f', 2)
        + " "
        + currency);


    QStandardItem* returnItem =
        m_model->item(row, 4);

    const auto& portfolio = m_account->getPortfolio();
    double investment = portfolio.at(stock).investment;
    double shares     = portfolio.at(stock).shares;

    double unrealizedReturn =
        price*shares - investment;

    QString returnText;

    if (unrealizedReturn > 0) {
        returnText = "+" + QString::number(unrealizedReturn, 'f', 2);
    } else {
        returnText = QString::number(unrealizedReturn, 'f', 2);
    }

    returnItem->setText(returnText
                        + " "
                        + currency);

    if (unrealizedReturn < 0) {
        returnItem->setForeground(QColor(220, 80, 80));
    }
    else if (unrealizedReturn > 0) {
        returnItem->setForeground(QColor(80, 180, 100));
    }

}

void MainWindow::on_buyPushButton_clicked(){

    emit orderRequest("Buy", m_db, m_account.get(), m_stockManager );
}
void MainWindow::on_sellPushButton_clicked(){

    emit orderRequest("Sell", m_db, m_account.get(), m_stockManager );
}