#ifndef STUDENT_STATS_H
#define STUDENT_STATS_H

#include <QWidget>

namespace Ui {
class Student_Stats;
}

class Student_Stats : public QWidget
{
    Q_OBJECT

public:
    explicit Student_Stats(QWidget *parent = nullptr);
    ~Student_Stats();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_push_pic_2_clicked();

    void on_push_pic_3_clicked();

private:
    Ui::Student_Stats *ui;
};

#endif // STUDENT_STATS_H
