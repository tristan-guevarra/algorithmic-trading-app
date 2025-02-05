#include "student_stats.h"
#include "ui_student_stats.h"
#include <QMessageBox>
#include <QPixmap>
#include "homework.h"
#include <QFile>

Student_Stats::Student_Stats(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Student_Stats)
{
    ui->setupUi(this);

}

Student_Stats::~Student_Stats()
{
    delete ui;
}


void Student_Stats::on_pushButton_clicked()
{
    QMessageBox stats;
    stats.setWindowTitle("Module completion");
    QPixmap image("C:/allen/Photo/Completion_stats.png");
    stats.setIconPixmap(image);
    stats.exec();
}


void Student_Stats::on_pushButton_2_clicked()
{
    QMessageBox stats2;
    stats2.setWindowTitle("Module grades");
    QPixmap image("C:/allen/Photo/Grades_stats.jpg");
    stats2.setIconPixmap(image);
    stats2.exec();
}


void Student_Stats::on_push_pic_2_clicked()
{
    //Show the second window
    Homework *h = new Homework;
    //Disappear the previous window
    h->show();
    hide();

}


void Student_Stats::on_push_pic_3_clicked()
{
    QString completion = ui->lineEdit->text();
    QString grades = ui->lineEdit_2->text();
    QString comments = ui->lineEdit_3->text();

    QMessageBox::information(this, "Save File", "File has been saved");
    QFile file("Performance.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() <<file.errorString();
    }

    QTextStream stream(&file);
    stream <<"Module Completion Rate: " + completion + "\n";
    stream <<"Total Grade: " + grades + "\n";
    stream <<"Instructor Comments: " + comments + "\n";
}

