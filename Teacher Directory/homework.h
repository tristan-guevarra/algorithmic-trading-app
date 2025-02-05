#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <QWidget>

namespace Ui {
class Homework;
}

class Homework : public QWidget
{
    Q_OBJECT

public:
    explicit Homework(QWidget *parent = nullptr);
    ~Homework();

private slots:
    void on_push_pic_2_clicked();

    void on_push_pic_3_clicked();

private:
    Ui::Homework *ui;
};

#endif // HOMEWORK_H
