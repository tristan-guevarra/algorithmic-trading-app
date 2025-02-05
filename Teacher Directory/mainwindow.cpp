#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "second_window.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/allen/Photo/images (1).jpg");
    ui->label_pic->setPixmap(pix);
    ui->label_pic_2->setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Login_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if(username == "test" && password == "test") {
        QMessageBox::information(this, "Login", "User Authenticated");
        //Show the second window
        Second_Window *sec = new Second_Window;
        //Disappear the previous window
        sec->show();
        hide();
    }else{
        QMessageBox::warning(this, "Login", "Incorrect combination of username and password");
    }
}

