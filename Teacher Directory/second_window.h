#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include <QWidget>

namespace Ui {
class Second_Window;
}

class Second_Window : public QWidget
{
    Q_OBJECT

public:
    explicit Second_Window(QWidget *parent = nullptr);
    ~Second_Window();

private slots:
    void on_push_pic_clicked();

private:
    Ui::Second_Window *ui;
};

#endif // SECOND_WINDOW_H
