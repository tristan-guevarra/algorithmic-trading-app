#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChartWindow;
}
QT_END_NAMESPACE

class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();

private:
    Ui::ChartWindow *ui;
};
#endif // CHARTWINDOW_H
