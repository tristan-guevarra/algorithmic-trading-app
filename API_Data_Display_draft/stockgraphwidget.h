#ifndef STOCKGRAPHWIDGET_H
#define STOCKGRAPHWIDGET_H

#include <QMainWindow>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class StockGraphWidget;
}
QT_END_NAMESPACE

class StockGraphWidget : public QMainWindow
{
    Q_OBJECT

public:
    StockGraphWidget(QWidget *parent = nullptr);
    ~StockGraphWidget();

    void loadDataFromFile(const QString &filePath);

private:
    Ui::StockGraphWidget *ui;
};

#endif // STOCKGRAPHWIDGET_H
