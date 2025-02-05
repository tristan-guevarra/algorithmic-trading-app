#include "second_window.h"
#include "ui_second_window.h"
#include <QPixmap>
#include "student_stats.h"

Second_Window::Second_Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Second_Window)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Joel");
    ui->comboBox->addItem("Ben");
    ui->comboBox->addItem("Connor");


}

Second_Window::~Second_Window()
{
    delete ui;
}

void Second_Window::on_push_pic_clicked()
{
    //Show the second window
    Student_Stats *ss = new Student_Stats;
    //Disappear the previous window
    ss->show();
    hide();

}

