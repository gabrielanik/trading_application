#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "account.h"
#include "stockmanager.h"

OrderWindow::OrderWindow(const QString &order, DBManager *dbManager,
                         Account *account, StockManager *stockManager, QWidget *parent): QDialog(parent),
    ui(new Ui::OrderWindow),
    m_db(dbManager),
    m_acc(account),
    m_stockManager(stockManager),
    m_order(order){

    ui->setupUi(this);
    ui->executeOrderButton->setText(order);

    connect(this,
            &OrderWindow::searchStock,
            this,
            &OrderWindow::loadStockData);

    connect(m_stockManager,
            &StockManager::priceReceived,
            this,
            &OrderWindow::updateStockPrice);

    loadBalance(m_acc->getBalance(), m_acc->getCurrency());

}

OrderWindow::~OrderWindow(){
    delete ui;
}

void OrderWindow::on_executeOrderButton_clicked(){

    // validations

    emit orderExecuted();
}

void OrderWindow::on_searchButton_clicked(){
    QString stock = ui->stockLineEdit->text();
    emit searchStock(stock);
}

void OrderWindow::on_backButton_clicked(){
    emit back();
}

void OrderWindow::loadBalance(const double balance, const QString currency){

    QString symbol;

    if(currency == "USD"){
        symbol = "$";
    }else if(currency == "EUR"){
        symbol = "€";
    }
    ui->balancePlainTextEdit->appendPlainText(symbol + QString::number(balance, 'f', 2));
}

void OrderWindow::loadStockData(const QString stock){

    std::map<QString, Holdings> portfolio = m_acc->getPortfolio();
    double shares = 0.00;

    try {
        shares = portfolio.at(stock).shares;
    } catch(const std::out_of_range& e){
        qDebug() << e.what();
    }

    ui->oSharesPlainTextEdit->appendPlainText(QString::number(shares, 'f', 2));
    ui->stockNameLabel->setText(stock);

    m_stockManager->getPrice(stock);

}

void OrderWindow::updateStockPrice(const QString& stock, const double price){

    ui->stockPriceLabel->setText(QString::number(price, 'f', 2));
    m_price = price;
}

void OrderWindow::on_sharesLineEdit_textChanged(const QString& text){

    double shares = text.toDouble();

    double total = shares * m_price;

    ui->estPricePlainTextEdit->clear();
    ui->estPricePlainTextEdit->appendPlainText(QString::number(total, 'f', 2));

}
