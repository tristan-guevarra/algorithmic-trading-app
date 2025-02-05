#include "homework.h"
#include "ui_homework.h"
#include <QMessageBox>
#include <QFile>

Homework::Homework(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Homework)
{
    ui->setupUi(this);
    ui->comboBox->addItem("M1 - Basic Intuition");
    ui->comboBox->addItem("M2 - Trading Basics");
    ui->comboBox->addItem("M3 - Fundamental Analysis");
    ui->comboBox->addItem("M4 - Technical Analysis");
    ui->comboBox->addItem("M5 - Risk Management");
    ui->comboBox->addItem("M6 - Trading Strategies");
    ui->comboBox->addItem("M7 - Advanced Tech. Analysis");
    ui->comboBox->addItem("M8 - Derivatives & Options");
    ui->comboBox->addItem("M9 - Portfolio Management");

}

Homework::~Homework()
{
    delete ui;
}

void Homework::on_push_pic_2_clicked()
{
    QMessageBox::information(this, "Homework", "Homework Assigned!");

}


void Homework::on_push_pic_3_clicked()
{
    QString date = ui->lineEdit->text();
    QString targetGrade = ui->lineEdit_2->text();
    QString course = ui->comboBox->currentText();


    QMessageBox::information(this, "Save File", "File has been saved");
    QFile file("Homework.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        qCritical() <<file.errorString();
    }

    QTextStream stream(&file);
    stream <<"Assigned Course: " + course + "\n";
    stream <<"Homework Deadline Date: " + date + "\n";
    stream <<"Student Target Grade: " + targetGrade + "\n";

}

