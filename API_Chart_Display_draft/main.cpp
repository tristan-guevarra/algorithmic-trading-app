#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMainWindow>
#include <QMap>
#include <QPen>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <limits>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create a chart
    QChart *chart = new QChart();

    // Create a series to hold the data
    QLineSeries *series = new QLineSeries();
    series->setName("AMZN Close Price");

    // Open the AMZNdata.txt file
    QFile file("AMZNdata.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file: " << file.errorString();
        return -1;
    }

    QByteArray data = file.readAll(); // Read the file content
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        qDebug() << "Failed to parse JSON";
        return -1;
    }

    QJsonObject jsonObject = doc.object();
    QJsonObject timeSeries = jsonObject["Time Series (Daily)"].toObject();

    // Use QMap to sort dates
    QMap<QDateTime, float> sortedData;

    // Parse the JSON and populate sortedData
    for (auto it = timeSeries.begin(); it != timeSeries.end(); ++it) {
        QString dateString = it.key();
        QDateTime date = QDateTime::fromString(dateString, "yyyy-MM-dd");

        QJsonObject dayData = it.value().toObject();
        float closePrice = dayData["4. close"].toString().toFloat();

        sortedData.insert(date, closePrice);
    }

    // Store the beginning of the 30-day window (first date of the data)
    QDateTime currentStartDate = sortedData.firstKey();

    // Get the last available date in the dataset
    QDateTime lastDate = sortedData.lastKey();

    // Create axes for the chart
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("MMM dd, yyyy");
    axisX->setTitleText("Date");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Price (USD)");

    // Store the last known price to hold if we encounter missing data
    float lastValidPrice = 0.0f;

    auto updateGraph = [&]() {
        series->clear();

        float minY = std::numeric_limits<float>::max();
        float maxY = std::numeric_limits<float>::lowest();

        QDateTime windowEnd = currentStartDate.addDays(30);
        if (windowEnd > lastDate) {
            windowEnd = lastDate;
        }

        for (QDateTime currentDate = currentStartDate; currentDate <= windowEnd; currentDate = currentDate.addDays(1)) {
            if (sortedData.contains(currentDate)) {
                float price = sortedData.value(currentDate);
                series->append(currentDate.toMSecsSinceEpoch(), price);
                minY = std::min(minY, price);
                maxY = std::max(maxY, price);
                lastValidPrice = price;
            } else if (lastValidPrice != 0.0f) {
                series->append(currentDate.toMSecsSinceEpoch(), lastValidPrice);
                minY = std::min(minY, lastValidPrice);
                maxY = std::max(maxY, lastValidPrice);
            }
        }

        axisX->setRange(currentStartDate, windowEnd);
        axisY->setRange(minY - (minY * 0.05), maxY + (maxY * 0.05));
    };

    updateGraph();

    chart->addSeries(series);
    chart->setAxisX(axisX, series);
    chart->setAxisY(axisY, series);
    chart->setTitle("AMZN Stock Price");

    series->setPen(QPen(Qt::blue));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(0, 0, 800, 500);

    QPushButton *shiftButton = new QPushButton("Next 30 Days");
    shiftButton->setGeometry(25, 520, 200, 40);

    QPushButton *incrementButton = new QPushButton("Buy");
    incrementButton->setGeometry(550, 520, 100, 40);

    QPushButton *decrementButton = new QPushButton("Sell");
    decrementButton->setGeometry(660, 520, 100, 40);

    QLabel *counterLabel = new QLabel("0", nullptr);
    counterLabel->setGeometry(450, 493, 50, 30);
    counterLabel->setAlignment(Qt::AlignCenter);

    QLabel *staticCounterLabel = new QLabel("0", nullptr);
    staticCounterLabel->setGeometry(450, 513, 50, 30);
    staticCounterLabel->setAlignment(Qt::AlignCenter);

    QLabel *thirdStaticCounterLabel = new QLabel("0", nullptr);
    thirdStaticCounterLabel->setGeometry(450, 533, 50, 30);
    thirdStaticCounterLabel->setAlignment(Qt::AlignCenter);

    QLabel *fourthStaticCounterLabel = new QLabel("0", nullptr);
    fourthStaticCounterLabel->setGeometry(450, 553, 50, 30);
    fourthStaticCounterLabel->setAlignment(Qt::AlignCenter);

    QLabel *todaysInvestmentTextLabel = new QLabel("Today's Investment (Shares): ", nullptr);
    todaysInvestmentTextLabel->setGeometry(300, 500, 150, 30);
    todaysInvestmentTextLabel->setAlignment(Qt::AlignRight);

    QLabel *totalInvestmentTextLabel = new QLabel("Total Investment ($): ", nullptr);
    totalInvestmentTextLabel->setGeometry(300, 520, 150, 30);
    totalInvestmentTextLabel->setAlignment(Qt::AlignRight);

    QLabel *totalSharesTextLabel = new QLabel("Total (Shares): ", nullptr);
    totalSharesTextLabel->setGeometry(300, 540, 150, 30);
    totalSharesTextLabel->setAlignment(Qt::AlignRight);
    \
    QLabel *totalProfitTextLabel = new QLabel("Total Profit ($): ", nullptr);
    totalProfitTextLabel->setGeometry(300, 560, 150, 30);
    totalProfitTextLabel->setAlignment(Qt::AlignRight);

    int counter = 0;
    int staticCounter = 0;
    int thirdStaticCounter = 0;
    float latestStockPrice = 0.0f;

    QObject::connect(shiftButton, &QPushButton::clicked, [&]() {
        currentStartDate = currentStartDate.addDays(1);
        if (currentStartDate.addDays(30) > lastDate) {
            currentStartDate = lastDate.addDays(-30);
        }
        updateGraph();

        QDateTime windowEnd = currentStartDate.addDays(30);
        if (windowEnd > lastDate) {
            windowEnd = lastDate;
        }

        // Determine the most recent stock price in the window
        latestStockPrice = 0.0f;
        for (QDateTime currentDate = windowEnd; currentDate >= currentStartDate; currentDate = currentDate.addDays(-1)) {
            if (sortedData.contains(currentDate)) {
                latestStockPrice = sortedData.value(currentDate);
                break;
            }
        }

        // Use the last valid price if no stock price is found in the window
        if (latestStockPrice == 0.0f) {
            latestStockPrice = lastValidPrice;
        }

        // Update static counters and labels
        staticCounter += counter * latestStockPrice;
        staticCounterLabel->setText(QString::number(staticCounter));

        thirdStaticCounter += counter;
        thirdStaticCounterLabel->setText(QString::number(thirdStaticCounter));

        float secondLabelValue = thirdStaticCounter * latestStockPrice;
        staticCounterLabel->setText(QString::number(secondLabelValue));

        // Add to the fourthStaticCounterLabel if counter is negative
        if (counter < 0) {
            float penalty = (-counter) * latestStockPrice;
            float fourthLabelValue = fourthStaticCounterLabel->text().toFloat() + penalty;
            fourthStaticCounterLabel->setText(QString::number(fourthLabelValue));
        }

        // Reset counter
        counter = 0;
        counterLabel->setText(QString::number(counter));
    });


    QObject::connect(incrementButton, &QPushButton::clicked, [&]() {
        counter++;
        counterLabel->setText(QString::number(counter));
    });

    QObject::connect(decrementButton, &QPushButton::clicked, [&]() {
        counter--;
        counterLabel->setText(QString::number(counter));
    });

    QWidget *mainWidget = new QWidget;
    mainWidget->setWindowTitle("AMZN Stock Price Viewer");
    mainWidget->setFixedSize(800, 600);
    mainWidget->setGeometry(100, 100, 800, 600);
    mainWidget->show();
    chartView->setParent(mainWidget);
    chartView->show();
    shiftButton->setParent(mainWidget);
    shiftButton->show();
    incrementButton->setParent(mainWidget);
    incrementButton->show();
    decrementButton->setParent(mainWidget);
    decrementButton->show();
    counterLabel->setParent(mainWidget);
    counterLabel->show();
    staticCounterLabel->setParent(mainWidget);
    staticCounterLabel->show();
    thirdStaticCounterLabel->setParent(mainWidget);
    thirdStaticCounterLabel->show();
    fourthStaticCounterLabel->setParent(mainWidget);
    fourthStaticCounterLabel->show();
    todaysInvestmentTextLabel->setParent(mainWidget);
    todaysInvestmentTextLabel->show();
    totalInvestmentTextLabel->setParent(mainWidget);
    totalInvestmentTextLabel->show();
    totalSharesTextLabel->setParent(mainWidget);
    totalSharesTextLabel->show();
    totalProfitTextLabel->setParent(mainWidget);
    totalProfitTextLabel->show();

    return a.exec();
}
