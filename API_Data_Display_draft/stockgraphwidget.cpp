#include "stockgraphwidget.h"
#include "ui_stockgraphwidget.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

StockGraphWidget::StockGraphWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StockGraphWidget)
{
    ui->setupUi(this);

    // Load the data from AMZNdata.txt
    loadDataFromFile("AMZNdata.txt");  // Path to your JSON file
}

StockGraphWidget::~StockGraphWidget()
{
    delete ui;
}

void StockGraphWidget::loadDataFromFile(const QString &filePath)
{
    // Print the current working directory to check where the application is running
    qDebug() << "Current working directory: " << QDir::currentPath();

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file: " << filePath;
        return;
    }

    // Read the contents of the file
    QByteArray data = file.readAll();

    // Parse the JSON data
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON data.";
        return;
    }

    QJsonObject jsonObj = doc.object();
    QJsonObject timeSeries = jsonObj.value("Time Series (Daily)").toObject();

    // Set up the table
    ui->tableWidget->setRowCount(timeSeries.size());
    ui->tableWidget->setColumnCount(5); // Date, Open, High, Low, Close

    int row = 0;
    for (auto it = timeSeries.begin(); it != timeSeries.end(); ++it) {
        QString date = it.key();
        QJsonObject dayData = it.value().toObject();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(date));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(dayData.value("1. open").toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(dayData.value("2. high").toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(dayData.value("3. low").toString()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dayData.value("4. close").toString()));

        row++;
    }
}
