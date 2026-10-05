#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "account.h"
#include "stockmanager.h"
#include "dbmanager.h"

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

    m_db->persistData(m_acc->getId(), ui->stockLineEdit->text(), ui->sharesLineEdit->text().toDouble(),
                    m_estimatedPrice, m_currency, m_order, m_acc);

    if(m_order == "Buy"){
      m_acc->buy(m_acc->getId(), ui->stockLineEdit->text(), ui->sharesLineEdit->text().toDouble(),
               ui->stockPriceLabel->text().toDouble());

      emit orderExecuted();
    } else if (m_order == "Sell"){
      m_acc->sell(m_acc->getId(), ui->stockLineEdit->text(), ui->sharesLineEdit->text().toDouble(),
                ui->stockPriceLabel->text().toDouble());

      emit orderExecuted();
    }

}

void OrderWindow::on_searchButton_clicked(){

    ui->estPricePlainTextEdit->clear();
    ui->messageTextEdit->clear();
    ui->sharesLineEdit->clear();

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

    ui->oSharesPlainTextEdit->clear();

    std::map<QString, Holdings> portfolio = m_acc->getPortfolio();
    double shares = 0.00;

    try {
        shares = portfolio.at(stock).shares;
    } catch(const std::out_of_range& e){
        qDebug() << e.what();
    }

    ui->oSharesPlainTextEdit->appendPlainText(QString::number(shares, 'f', 2));
    ui->stockNameLabel->setStyleSheet(
        "background-color: rgb(58, 58, 58); border: 1px solid rgb(75, 75, 75);"
        "border-radius: 8px; padding: 3px 3px;"
        );
    ui->stockNameLabel->setAlignment(Qt::AlignCenter);
    ui->stockNameLabel->setText(stock);

    ui->label_6->setStyleSheet("color: rgb(193, 196, 196); background: transparent");
    ui->sharesLineEdit->setAlignment(Qt::AlignCenter);

    m_stockManager->getPrice(stock);

}

void OrderWindow::updateStockPrice(const QString& stock, const double price, const QString& currency){


    QString symbol;

    if(currency == "USD"){
        symbol = "$";
    }else if(currency == "EUR"){
        symbol = "€";
    }

    ui->stockPriceLabel->setText(symbol + QString::number(price, 'f', 2));
    m_price = price;
    m_currency = currency;

}

void OrderWindow::on_sharesLineEdit_textChanged(const QString& text){

    ui->messageTextEdit->clear();
    ui->estPricePlainTextEdit->setStyleSheet("background:transparent;color:white;");

    double shares = text.toDouble();
    double total = shares * m_price;
    QString symbol;

    if(m_currency == "USD"){
        symbol = "$";
    }else if(m_currency == "EUR"){
        symbol = "€";
    }

    ui->estPricePlainTextEdit->clear();
    ui->messageTextEdit->clear();
    ui->estPricePlainTextEdit->appendPlainText(symbol + QString::number(total, 'f', 2));

    int order = ( m_order == "Buy") ? 1 : 2;

    switch(order){
    case 1:

        if(total > m_acc->getBalance()){

            ui->messageTextEdit->appendPlainText("Available balance exceeded.");
            ui->estPricePlainTextEdit->setStyleSheet("background:transparent;color:rgb(255, 156, 157);");
        }

        break;

    case 2:

        if(ui->sharesLineEdit->text().toDouble() > ui->oSharesPlainTextEdit->toPlainText().toDouble()){

            ui->messageTextEdit->appendPlainText("Not enough owned shares.");
            ui->estPricePlainTextEdit->setStyleSheet("background:transparent;color:rgb(255, 156, 157);");

        }
        break;

    }

    m_estimatedPrice = total;

}
