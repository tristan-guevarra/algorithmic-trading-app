#include "stockgraphwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StockGraphWidget w;
    w.show();
    return a.exec();
}
