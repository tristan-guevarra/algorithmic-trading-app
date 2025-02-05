#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QStyle>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Set default dark mode stylesheet
    this->setStyleSheet(R"(
        QWidget {
            background-color: #4F4F51; /* Dark grey background */
        }

        QPushButton {
            border: 2px solid #E8B1BD;
            border-radius: 5px;
            color: white;
            background-color: transparent;
        }

        QPushButton:hover {
            background-color: #F2C4CE;
            color: white;
        }

        QPushButton:pressed {
            background-color: #4B0082;
        }
    )");

    ui->stackedWidget->setCurrentIndex(0);

    setupReturnButtonConnections();

    QString filePath = "C:/Users/trist/OneDrive/Documents/376 sprint 1/code/Elec376_F24_group2/users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open users.txt for reading."));
    } else {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString name = in.readLine();
            QString email = in.readLine();
            QString password = in.readLine();
            QString role = in.readLine();
            in.readLine();

            if (role == "Student") {
                ui->studentComboBox->addItem(name);
            }
        }
        file.close();
    }

    ui->comboBox_2->addItem("English");
    ui->comboBox_2->addItem("Spanish");
    ui->comboBox_2->addItem("French");

    ui->comboBox_2->setCurrentIndex(0);

    connect(ui->darkMode, &QCheckBox::checkStateChanged, this, &Widget::on_darkMode_checkStateChanged);

    connect(ui->comboBox_2, &QComboBox::activated, this, &Widget::on_comboBox_2_activated);
}




Widget::~Widget()
{
    delete ui;
}

void Widget::setupReturnButtonConnections()
{
    // Find all QPushButtons whose object name starts with "RETURNBTN"
    QList<QPushButton*> returnButtons = findChildren<QPushButton*>();

    for (auto button : returnButtons) {
        if (button->objectName().startsWith("RETURNBTN")) {
            // Connect all buttons that start with "RETURNBTN" to the same slot
            connect(button, &QPushButton::clicked, this, [=]() {
                ui->moduleStack->setCurrentIndex(0);  // Return to the main module list (index 0 in moduleStack)
            });
        }
    }
}

void Widget::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->loginPage));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_backButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_regStuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentReg));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_regTeachButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->teacherReg));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}


void Widget::on_registerStudentBtn_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";

    QFile file(filePath);
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");

    QString email = ui->studentEmailTE->toPlainText();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!email.isEmpty() && line.contains(email)) {
                QMessageBox::critical(this, "Invalid email", "This email is already taken");
                file.close();
                return;
            }
        }
        file.close();
    } else {
        qDebug() << "Could not open file for reading.";
        qDebug() << filePath;
    }

    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        QString name = ui->studentNameTE->toPlainText();
        QString password = ui->studentPwTE->toPlainText();

        if (!name.isEmpty() && !email.isEmpty() && !password.isEmpty()) {
            out << name << Qt::endl << email << Qt::endl << password << Qt::endl << "Student" << Qt::endl;
            out << Qt::endl;
            QMessageBox::information(this, "Registration successful", "You have successfully registered your account!");
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
        } else {
            QMessageBox::critical(this, "Invalid details", "One or more fields have been left empty. Please ensure all fields are filled out.");
            file.close();
            return;
        }
        file.close();
    } else {
        qDebug() << "Could not open file for writing.";
    }

    QString studentIDInput = ui->studentIDinput->text().trimmed(); // Bottom input field
    if (studentIDInput.isEmpty()) {
        ui->confirmOutput->setPlainText("Student ID is empty. Please enter a valid Student ID.");
        return;
    }

    bool isNumeric;
    int studentID = studentIDInput.toInt(&isNumeric);

    if (!isNumeric || studentID <= 0) {
        ui->confirmOutput->setPlainText("Invalid Student ID. Please enter a positive numeric ID.");
        return;
    }

    // Automatically add the student to the dictionary if they don't exist
    if (dictionary.students.find(studentID) == dictionary.students.end()) {
        dictionary.students[studentID] = Student{studentID, {}};
        ui->confirmOutput->setPlainText("Student ID: " + QString::number(studentID) + " registered successfully.");
    } else {
        ui->confirmOutput->setPlainText("Student already exists.");
    }

    // Clear the Student ID input field
    ui->studentIDinput->clear();
}


void Widget::on_registerTeacherBtn_clicked()
{
    QString filePath = "C:\\Users\\benbe\\OneDrive\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");

    QString email = ui->teachEmailTE->toPlainText();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!email.isEmpty() && (QString::compare(line, email) == 0)) {
                QMessageBox::critical(this, "Invalid email", "This email is already taken");
                file.close();
                return;
            }
        }
        file.close();
    } else {
        qDebug() << "Could not open file for reading.";
    }

    if(file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        QString name = ui->teachNameTE->toPlainText();
        QString password = ui->teachPwTE->toPlainText();

        if (!name.isEmpty() && !email.isEmpty() && !password.isEmpty()) {
            out << name << Qt::endl << email << Qt::endl << password << Qt::endl << "Teacher" << Qt::endl;
            out << Qt::endl;
            QMessageBox::information(this, "Registration successful", "You have successfully registered your account!");
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
        } else {
            QMessageBox::critical(this, "Invalid details", "One or more fields have been left empty. Please ensure all fields are filled out.");
            file.close();
            return;
        }
        file.close();
    } else {
        qDebug() << "Could not open file for writing.";
    }
}

void Widget::on_helpButton_clicked()
{
    QString email = "mailto:tradelab@helpsupport.com";
    QUrl emailUrl(email);

    if (!QDesktopServices::openUrl(emailUrl)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open email client."));
    }
}


void Widget::on_loginScreenButton_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");

    QString email = ui->loginEmailTE->toPlainText();
    QString password = ui->loginPwTE->toPlainText();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Invalid input", "Email or password was left empty. Please ensure the fields are filled out.");
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        bool emailFound = false;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (QString::compare(line, email) == 0) {
                emailFound = true;
                line = in.readLine(); // Read the next line for the password

                if (QString::compare(line, password) == 0) {
                    QMessageBox::information(this, "Login success", "Successfully logged in!");
                    file.close();
                    // Switch to modules screen once implemented
                    if (QString::compare(in.readLine(), "Student") == 0) {
                        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentHome));
                        return;
                    } else {
                        // switch to teacher home page
                        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->teacherHome));
                        return;
                    }
                } else {
                    QMessageBox::critical(this, "Incorrect password", "Incorrect password. Please try again.");
                    file.close();
                    return;
                }
            }
        }

        // Check if email was found after the loop
        if (!emailFound) {
            QMessageBox::critical(this, "Invalid email", "The specified email could not be found. Please try again.");
        }

        file.close();
    } else {
        qDebug() << "Could not open file for reading.";
    }
}



void Widget::on_logoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_menu_clicked()
{
    ui->moduleStack->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentHome));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_modules_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->moduleWidget));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
    ui->moduleStack->setCurrentIndex(0);
}

void Widget::on_RETURNBTN_clicked()
{
    ui->moduleStack->setCurrentIndex(0);
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod1_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module1));
    ui->mod1stack->setCurrentIndex(ui->mod1stack->indexOf(ui->mod1content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod2_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module2));
    ui->mod2stack->setCurrentIndex(ui->mod2stack->indexOf(ui->mod2content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod3_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module3));
    ui->mod3stack->setCurrentIndex(ui->mod3stack->indexOf(ui->mod3content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod4_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module4));
    ui->mod4stack->setCurrentIndex(ui->mod4stack->indexOf(ui->mod4content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod5_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module5));
    ui->mod5stack->setCurrentIndex(ui->mod5stack->indexOf(ui->mod5content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod6_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module6));
    ui->mod6stack->setCurrentIndex(ui->mod6stack->indexOf(ui->mod6content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod7_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module7));
    ui->mod7stack->setCurrentIndex(ui->mod7stack->indexOf(ui->mod7content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod8_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module8));
    ui->mod8stack->setCurrentIndex(ui->mod8stack->indexOf(ui->mod8content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_mod9_clicked()
{
    ui->moduleStack->setCurrentIndex(ui->moduleStack->indexOf(ui->module9));
    ui->mod9stack->setCurrentIndex(ui->mod9stack->indexOf(ui->mod9content));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton1_clicked()
{
    ui->mod1stack->setCurrentIndex(ui->mod1stack->indexOf(ui->mod1quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton2_clicked()
{
    ui->mod2stack->setCurrentIndex(ui->mod2stack->indexOf(ui->mod2quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton3_clicked()
{
    ui->mod3stack->setCurrentIndex(ui->mod3stack->indexOf(ui->mod3quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton4_clicked()
{
    ui->mod4stack->setCurrentIndex(ui->mod4stack->indexOf(ui->mod4quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton5_clicked()
{
    ui->mod5stack->setCurrentIndex(ui->mod5stack->indexOf(ui->mod5quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton6_clicked()
{
    ui->mod6stack->setCurrentIndex(ui->mod6stack->indexOf(ui->mod6quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton7_clicked()
{
    ui->mod7stack->setCurrentIndex(ui->mod7stack->indexOf(ui->mod7quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton8_clicked()
{
    ui->mod8stack->setCurrentIndex(ui->mod8stack->indexOf(ui->mod8quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::on_quizButton9_clicked()
{
    ui->mod9stack->setCurrentIndex(ui->mod9stack->indexOf(ui->mod9quiz));
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::resetQuiz(QWidget *quizContainer)
{
    // find all QRadioButton elements that are children of the provided container
    QList<QRadioButton *> radioButtons = quizContainer->findChildren<QRadioButton *>();

    // iterate through the list and uncheck each QRadioButton
    for (QRadioButton *radioButton : radioButtons) {
        // disable auto-exclusivity, uncheck, and re-enable auto-exclusivity to reset properly
        radioButton->setAutoExclusive(false);
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);
    }
}

bool q1Complete = false;
void Widget::on_submitQuiz1_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("M1Q1A2_C");
    QRadioButton *q2 = findChild<QRadioButton *>("M1Q2A3_C");
    QRadioButton *q3 = findChild<QRadioButton *>("M1Q3A4_C");
    QRadioButton *q4 = findChild<QRadioButton *>("M1Q4A3_C");
    QRadioButton *q5 = findChild<QRadioButton *>("M1Q5A1_C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q1Complete == false) { ui->beginProgress->setValue(ui->beginProgress->value() + 33); }
        q1Complete = true;
        ui->mod1->setText("M1 - Basic Intuition - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod1quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q2Complete = false;
void Widget::on_submitQuiz2_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("M2Q1A4_C");
    QRadioButton *q2 = findChild<QRadioButton *>("M2Q2A2_C");
    QRadioButton *q3 = findChild<QRadioButton *>("M2Q3A1_C");
    QRadioButton *q4 = findChild<QRadioButton *>("M2Q4A3_C");
    QRadioButton *q5 = findChild<QRadioButton *>("M2Q5A3_C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q2Complete == false) { ui->beginProgress->setValue(ui->beginProgress->value() + 33); }
        q2Complete = true;
        ui->mod2->setText("M2 - Trading Basics - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod2quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q3Complete = false;
void Widget::on_submitQuiz3_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("M3Q1A4_C");
    QRadioButton *q2 = findChild<QRadioButton *>("M3Q2A4_C");
    QRadioButton *q3 = findChild<QRadioButton *>("M3Q3A1_C");
    QRadioButton *q4 = findChild<QRadioButton *>("M3Q4A2_C");
    QRadioButton *q5 = findChild<QRadioButton *>("M3Q5A3_C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q3Complete == false) { ui->beginProgress->setValue(ui->beginProgress->value() + 34); }
        q3Complete = true;
        ui->mod3->setText("M3 - Fundamental Analysis - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod3quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q4Complete = false;
void Widget::on_submitQuiz4_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A4_4C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A1_4C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A1_4C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A3_4C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A4_4C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q4Complete == false) { ui->interProgress->setValue(ui->interProgress->value() + 33); }
        q4Complete = true;
        ui->mod4->setText("M4 - Technical Analysis - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod4quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q5Complete = false;
void Widget::on_submitQuiz5_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A1_5C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A4_5C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A3_5C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A4_5C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A4_5C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q5Complete == false) { ui->interProgress->setValue(ui->interProgress->value() + 33); }
        q5Complete = true;
        ui->mod5->setText("M5 - Risk Management - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod5quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q6Complete = false;
void Widget::on_submitQuiz6_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A4_6C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A3_6C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A2_6C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A4_6C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A1_6C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q6Complete == false) { ui->interProgress->setValue(ui->interProgress->value() + 34); }
        q6Complete = true;
        ui->mod6->setText("M6 - Trading Strategies - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod6quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q7Complete = false;
void Widget::on_submitQuiz7_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A4_7C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A3_7C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A1_7C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A4_7C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A2_7C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q7Complete == false) { ui->advProgress->setValue(ui->advProgress->value() + 33); }
        q7Complete = true;
        ui->mod7->setText("M7 - Advanced Analysis - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod7quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q8Complete = false;
void Widget::on_submitQuiz8_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A4_8C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A1_8C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A4_8C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A2_8C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A3_8C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q8Complete == false) { ui->advProgress->setValue(ui->advProgress->value() + 33); }
        q8Complete = true;
        ui->mod8->setText("M8 - Derivatives && Options - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod8quiz);
    ui->moduleStack->setCurrentIndex(0);
}

bool q9Complete = false;
void Widget::on_submitQuiz9_clicked()
{
    int score = 0;

    QRadioButton *q1 = findChild<QRadioButton *>("Q1A4_9C");
    QRadioButton *q2 = findChild<QRadioButton *>("Q2A3_9C");
    QRadioButton *q3 = findChild<QRadioButton *>("Q3A1_9C");
    QRadioButton *q4 = findChild<QRadioButton *>("Q4A4_9C");
    QRadioButton *q5 = findChild<QRadioButton *>("Q5A3_9C");

    if (q1 && q1->isChecked()) { score+=20; }
    if (q2 && q2->isChecked()) { score+=20; }
    if (q3 && q3->isChecked()) { score+=20; }
    if (q4 && q4->isChecked()) { score+=20; }
    if (q5 && q5->isChecked()) { score+=20; }

    QString message;
    if (score >= 60) {
        message = QString("Congratulations! You passed the quiz!\nYou got a %1%.").arg(score);
        if(q9Complete == false) { ui->advProgress->setValue(ui->advProgress->value() + 34); }
        q9Complete = true;
        ui->mod9->setText("M9 - Portfolio Management - ✓");
    } else {
        message = QString("Unfortunately, you did not pass the quiz.\nYou got a %1%. Please try again.").arg(score);
    }
    QMessageBox::information(this, "Quiz Result", message);

    resetQuiz(ui->mod9quiz);
    ui->moduleStack->setCurrentIndex(0);
}

void Widget::on_adminInfo_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";

    bool ok;
    QString email = QInputDialog::getText(this, tr("Admin Login"), tr("Enter Teacher Email:"), QLineEdit::Normal, "", &ok);
    if (!ok || email.isEmpty()) {
        QMessageBox::warning(this, tr("Access Denied"), tr("Email input canceled."));
        return;
    }

    QString password = QInputDialog::getText(this, tr("Admin Login"), tr("Enter Teacher Password:"), QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) {
        QMessageBox::warning(this, tr("Access Denied"), tr("Password input canceled."));
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QTextStream in(&file);
    bool accessGranted = false;

    while (!in.atEnd()) {
        QString name = in.readLine();
        QString fileEmail = in.readLine();
        QString filePassword = in.readLine();
        QString role = in.readLine();
        in.readLine();

        if (fileEmail == email && filePassword == password && role == "Teacher") {
            accessGranted = true;
            break;
        }
    }

    file.close();

    if (accessGranted) {
        QMessageBox::information(this, tr("Access Granted"), tr("Welcome to the Admin Page."));
        updateStatistics();
        ui->stackedWidget->setCurrentWidget(ui->adminPage);
        QApplication::setPalette(QApplication::style()->standardPalette());
        qApp->setStyleSheet("");
    } else {
        QMessageBox::critical(this, tr("Access Denied"), tr("Invalid credentials or not a teacher. Access denied."));
    }
}


void Widget::on_adminInfoBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->studentHome);

    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet("");
}

void Widget::updateStatistics()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QTextStream in(&file);
    int studentCount = 0;
    int teacherCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line == "Student") {
            studentCount++;
        } else if (line == "Teacher") {
            teacherCount++;
        }
    }

    file.close();

    QString statistics = QString(
                             "Total Registered Users: %1\n"
                             "Students: %2\n"
                             "Teachers: %3\n"
                             ).arg(studentCount + teacherCount).arg(studentCount).arg(teacherCount);

    if (ui->statisticsLabel) { // Check if QLabel exists to avoid crashing
        ui->statisticsLabel->setText(statistics);
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Statistics label not found in the UI."));
    }
}


void Widget::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->settingPage));
}

void Widget::on_settingBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentHome));

}


void Widget::on_emailChange_clicked()
{
    if (ui->emailChange->isChecked()) {
        bool ok;
        QString newEmail = QInputDialog::getText(this, tr("Change Email"),
                                                 tr("Enter your new email:"), QLineEdit::Normal,
                                                 "", &ok);

        if (ok && !newEmail.isEmpty()) {
            QRegularExpression emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
            QRegularExpressionMatch match = emailRegex.match(newEmail);

            if (match.hasMatch()) {
                QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
                QFile file(filePath);

                if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
                    ui->emailChange->setChecked(false);
                    return;
                }

                QTextStream in(&file);
                QString currentEmail = ui->loginEmailTE->toPlainText();
                bool emailExists = false;
                QStringList lines;

                while (!in.atEnd()) {
                    QString line = in.readLine();
                    if (line == newEmail) {
                        emailExists = true;
                    }
                    lines.append(line);
                }

                file.close();

                if (emailExists) {
                    QMessageBox::warning(this, tr("Email Already Exists"), tr("The email you entered already exists. Please choose another email."));
                    ui->emailChange->setChecked(false);
                    return;
                }

                bool emailUpdated = false;
                for (int i = 0; i < lines.size(); ++i) {
                    if (lines[i] == currentEmail && !emailUpdated) {
                        lines[i] = newEmail;
                        emailUpdated = true;
                    }
                }

                if (!emailUpdated) {
                    QMessageBox::warning(this, tr("Email Not Found"), tr("The current email was not found in the file."));
                    ui->emailChange->setChecked(false);
                    return;
                }

                if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for writing."));
                    ui->emailChange->setChecked(false);
                    return;
                }

                QTextStream out(&file);
                for (const QString &line : lines) {
                    out << line << "\n";
                }

                file.close();

                QMessageBox::information(this, tr("Success"), tr("Your email has been successfully updated."));
            } else {
                QMessageBox::critical(this, tr("Invalid Email"), tr("The entered email is not valid. Please try again."));
            }
        } else if (ok && newEmail.isEmpty()) {
            QMessageBox::warning(this, tr("Empty Input"), tr("No email was entered. Please try again."));
        }

        ui->emailChange->setChecked(false);
    }
}

void Widget::on_dictionary_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->dictionaryPage));
}

void Widget::on_returnToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentHome));
}

void Widget::on_getDefinitionButton_clicked()
{
    QString studentIDInput = ui->getDefinitionStudentIDInput->text().trimmed(); // Top input field
    if (studentIDInput.isEmpty()) {
        ui->definitionResultOutput->setPlainText("Student ID is empty. Please enter a valid Student ID.");
        return;
    }

    bool isNumeric;
    int studentID = studentIDInput.toInt(&isNumeric);

    if (!isNumeric || studentID <= 0) {
        ui->definitionResultOutput->setPlainText("Invalid Student ID. Please enter a positive numeric ID.");
        return;
    }

    if (dictionary.students.find(studentID) == dictionary.students.end()) {
        ui->definitionResultOutput->setPlainText("Student not found.");
        return;
    }

    QString definitions;
    for (const auto &entry : dictionary.dict) {
        for (const auto &def : entry.second) {
            if (dictionary.students[studentID].completedModules.find(def.module) != dictionary.students[studentID].completedModules.end()) {
                definitions += QString::fromStdString(entry.first) + ": " + QString::fromStdString(def.meaning) + "\n";
            }
        }
    }

    ui->definitionResultOutput->setPlainText(definitions.isEmpty() ? "No definitions available." : definitions);
}

void Widget::on_showModulesButton_clicked()
{
    QString studentIDInput = ui->studentIDforModule->text().trimmed(); // Middle input field
    if (studentIDInput.isEmpty()) {
        ui->completedModulesList->setPlainText("Student ID is empty. Please enter a valid Student ID.");
        return;
    }

    bool isNumeric;
    int studentID = studentIDInput.toInt(&isNumeric);

    if (!isNumeric || studentID <= 0) {
        ui->completedModulesList->setPlainText("Invalid Student ID. Please enter a positive numeric ID.");
        return;
    }

    if (dictionary.students.find(studentID) == dictionary.students.end()) {
        ui->completedModulesList->setPlainText("Student not found.");
        return;
    }

    QString modules;
    for (const auto &module : dictionary.students[studentID].completedModules) {
        modules += QString::fromStdString(module) + "\n";
    }

    ui->completedModulesList->setPlainText(modules.isEmpty() ? "No modules completed yet." : modules);
}

void Widget::on_markCompletedButton_clicked()
{
    QString studentIDInput = ui->studentIDinput->text().trimmed(); // Bottom input field
    QString moduleInput = ui->lineEdit->text().trimmed();          // Module input field

    qDebug() << "Mark Completed Button clicked!";
    qDebug() << "Student ID Input:" << studentIDInput;
    qDebug() << "Module Input:" << moduleInput;

    if (studentIDInput.isEmpty()) {
        ui->confirmOutput->setPlainText("Student ID is empty. Please enter a valid Student ID.");
        return;
    }

    if (moduleInput.isEmpty()) {
        ui->confirmOutput->setPlainText("Module is empty. Please enter a module number.");
        return;
    }

    bool isNumeric;
    int studentID = studentIDInput.toInt(&isNumeric);

    if (!isNumeric || studentID <= 0) {
        ui->confirmOutput->setPlainText("Invalid Student ID. Please enter a positive numeric ID.");
        return;
    }

    if (dictionary.students.find(studentID) == dictionary.students.end()) {
        dictionary.students[studentID] = Student{studentID, {}}; // Automatically add the student
    }

    dictionary.completeModule(studentID, moduleInput.toStdString());
    ui->confirmOutput->setPlainText("Module '" + moduleInput + "' marked as completed for Student ID: " + QString::number(studentID));

    ui->lineEdit->clear();
}

void Widget::on_markUncompletedButton_clicked()
{
    QString studentIDInput = ui->studentIDinput->text().trimmed(); // Bottom input field for Student ID
    QString moduleInput = ui->lineEdit->text().trimmed();          // Input field for Module

    qDebug() << "Uncomplete Module Button clicked!";
    qDebug() << "Student ID Input:" << studentIDInput;
    qDebug() << "Module Input:" << moduleInput;

    if (studentIDInput.isEmpty()) {
        ui->confirmOutput->setPlainText("Student ID is empty. Please enter a valid Student ID.");
        return;
    }

    if (moduleInput.isEmpty()) {
        ui->confirmOutput->setPlainText("Module is empty. Please enter a module number.");
        return;
    }

    bool isNumeric;
    int studentID = studentIDInput.toInt(&isNumeric);

    if (!isNumeric || studentID <= 0) {
        ui->confirmOutput->setPlainText("Invalid Student ID. Please enter a positive numeric ID.");
        return;
    }

    if (dictionary.students.find(studentID) == dictionary.students.end()) {
        ui->confirmOutput->setPlainText("Student not found.");
        return;
    }

    if (dictionary.students[studentID].completedModules.erase(moduleInput.toStdString())) {
        ui->confirmOutput->setPlainText("Module '" + moduleInput + "' removed for Student ID: " + QString::number(studentID));
    } else {
        ui->confirmOutput->setPlainText("Module '" + moduleInput + "' not found for Student ID: " + QString::number(studentID));
    }

    ui->lineEdit->clear();
}


void Widget::on_passwordUp_clicked()
{
    if (ui->passwordUp->isChecked()) {
        bool ok;
        QString newPassword = QInputDialog::getText(this, tr("Update Password"),
                                                    tr("Enter your new password:"), QLineEdit::Password,
                                                    "", &ok);

        if (ok && !newPassword.isEmpty()) {
            QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
            QFile file(filePath);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
                ui->passwordUp->setChecked(false);
                return;
            }

            QTextStream in(&file);
            QString currentEmail = ui->loginEmailTE->toPlainText();
            QStringList lines;
            bool passwordUpdated = false;

            while (!in.atEnd()) {
                QString line = in.readLine();
                lines.append(line);

                // When the current email is found
                if (line == currentEmail) {
                    QString currentPassword = in.readLine(); // Read the current password
                    QString userType = in.readLine();        // Read the "Student" or "Teacher" placeholder

                    // Append updated password and placeholder
                    lines.append(newPassword); // Update the password
                    lines.append(userType);    // Append the user type
                    passwordUpdated = true;

                    // Skip the old password and user type
                }
            }

            file.close();

            if (!passwordUpdated) {
                QMessageBox::warning(this, tr("Password Update Failed"), tr("The current user was not found in the file."));
                ui->passwordUp->setChecked(false);
                return;
            }

            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for writing."));
                ui->passwordUp->setChecked(false);
                return;
            }

            QTextStream out(&file);
            for (const QString &line : lines) {
                out << line << "\n";
            }

            file.close();

            QMessageBox::information(this, tr("Success"), tr("Your password has been successfully updated."));
        } else if (ok && newPassword.isEmpty()) {
            QMessageBox::warning(this, tr("Empty Input"), tr("No password was entered. Please try again."));
        }

        ui->passwordUp->setChecked(false);
    }
}

void Widget::on_viewAllUsersButton_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QDialog usersDialog(this);
    usersDialog.setWindowTitle("All Registered Users");

    QTableWidget *table = new QTableWidget(&usersDialog);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Email", "Password", "Role"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTextStream in(&file);
    int row = 0;

    while (!in.atEnd()) {
        QString name = in.readLine();
        QString email = in.readLine();
        QString password = in.readLine();
        QString role = in.readLine();
        in.readLine();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(name));
        table->setItem(row, 1, new QTableWidgetItem(email));
        table->setItem(row, 2, new QTableWidgetItem(password));
        table->setItem(row, 3, new QTableWidgetItem(role));
        row++;
    }

    file.close();

    QVBoxLayout *layout = new QVBoxLayout(&usersDialog);
    layout->addWidget(table);
    usersDialog.setLayout(layout);

    usersDialog.exec();
}

void Widget::on_addUserButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Add User"), tr("Enter the user's name:"), QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString email = QInputDialog::getText(this, tr("Add User"), tr("Enter the user's email:"), QLineEdit::Normal, "", &ok);
    if (!ok || email.isEmpty()) return;

    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QTextStream in(&file);
    bool emailExists = false;
    while (!in.atEnd()) {
        QString existingName = in.readLine();
        QString existingEmail = in.readLine();
        in.readLine();
        in.readLine();
        in.readLine();

        if (existingEmail == email) {
            emailExists = true;
            break;
        }
    }
    file.close();

    if (emailExists) {
        QMessageBox::warning(this, tr("Error"), tr("This email already exists."));
        return;
    }

    QString password = QInputDialog::getText(this, tr("Add User"), tr("Enter the user's password:"), QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) return;

    QStringList roles = {"Student", "Teacher"};
    QString role = QInputDialog::getItem(this, tr("Add User"), tr("Select the user's role:"), roles, 0, false, &ok);
    if (!ok) return;

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for writing."));
        return;
    }

    QTextStream out(&file);
    out << name << "\n" << email << "\n" << password << "\n" << role << "\n\n";
    file.close();

    QMessageBox::information(this, tr("Success"), tr("User has been successfully added."));
    updateStatistics();
}

void Widget::on_editUserButton_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QDialog usersDialog(this);
    usersDialog.setWindowTitle("Select User to Edit");

    QTableWidget *table = new QTableWidget(&usersDialog);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Email", "Password", "Role"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTextStream in(&file);
    int row = 0;

    QStringList lines;
    while (!in.atEnd()) {
        QString name = in.readLine();
        QString email = in.readLine();
        QString password = in.readLine();
        QString role = in.readLine();
        in.readLine();

        lines << name << email << password << role << "";

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(name));
        table->setItem(row, 1, new QTableWidgetItem(email));
        table->setItem(row, 2, new QTableWidgetItem(password));
        table->setItem(row, 3, new QTableWidgetItem(role));
        row++;
    }
    file.close();

    QVBoxLayout *layout = new QVBoxLayout(&usersDialog);
    layout->addWidget(table);

    QPushButton *editButton = new QPushButton("Edit Selected User");
    layout->addWidget(editButton);

    usersDialog.setLayout(layout);

    connect(editButton, &QPushButton::clicked, &usersDialog, [&]() {
        int selectedRow = table->currentRow();
        if (selectedRow < 0) {
            QMessageBox::warning(&usersDialog, tr("Error"), tr("No user selected."));
            return;
        }

        QString name = table->item(selectedRow, 0)->text();
        QString email = table->item(selectedRow, 1)->text();
        QString password = table->item(selectedRow, 2)->text();
        QString role = table->item(selectedRow, 3)->text();

        bool ok;
        name = QInputDialog::getText(&usersDialog, tr("Edit User"), tr("Name:"), QLineEdit::Normal, name, &ok);
        if (!ok || name.isEmpty()) return;

        email = QInputDialog::getText(&usersDialog, tr("Edit User"), tr("Email:"), QLineEdit::Normal, email, &ok);
        if (!ok || email.isEmpty()) return;

        password = QInputDialog::getText(&usersDialog, tr("Edit User"), tr("Password:"), QLineEdit::Normal, password, &ok);
        if (!ok || password.isEmpty()) return;

        role = QInputDialog::getItem(&usersDialog, tr("Edit User"), tr("Role:"), {"Student", "Teacher"}, role == "Teacher" ? 1 : 0, false, &ok);
        if (!ok) return;

        table->setItem(selectedRow, 0, new QTableWidgetItem(name));
        table->setItem(selectedRow, 1, new QTableWidgetItem(email));
        table->setItem(selectedRow, 2, new QTableWidgetItem(password));
        table->setItem(selectedRow, 3, new QTableWidgetItem(role));

        int lineIndex = selectedRow * 5;
        lines[lineIndex] = name;
        lines[lineIndex + 1] = email;
        lines[lineIndex + 2] = password;
        lines[lineIndex + 3] = role;

        QMessageBox::information(&usersDialog, tr("Success"), tr("User details updated."));
    });

    usersDialog.exec();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for writing."));
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();

    QMessageBox::information(this, tr("Success"), tr("User data has been updated."));
    updateStatistics();
}

void Widget::on_deleteUserButton_clicked()
{
    QString filePath = "C:\\Users\\trist\\OneDrive\\Documents\\376 sprint 1\\code\\Elec376_F24_group2\\users.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for reading."));
        return;
    }

    QDialog usersDialog(this);
    usersDialog.setWindowTitle("Select User to Delete");

    QTableWidget *table = new QTableWidget(&usersDialog);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Email", "Password", "Role"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTextStream in(&file);
    int row = 0;

    QStringList lines;
    while (!in.atEnd()) {
        QString name = in.readLine();
        QString email = in.readLine();
        QString password = in.readLine();
        QString role = in.readLine();
        in.readLine();

        lines << name << email << password << role << "";

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(name));
        table->setItem(row, 1, new QTableWidgetItem(email));
        table->setItem(row, 2, new QTableWidgetItem(password));
        table->setItem(row, 3, new QTableWidgetItem(role));
        row++;
    }
    file.close();

    QVBoxLayout *layout = new QVBoxLayout(&usersDialog);
    layout->addWidget(table);

    QPushButton *deleteButton = new QPushButton("Delete Selected User");
    layout->addWidget(deleteButton);

    usersDialog.setLayout(layout);

    connect(deleteButton, &QPushButton::clicked, &usersDialog, [&]() {
        int selectedRow = table->currentRow();
        if (selectedRow < 0) {
            QMessageBox::warning(&usersDialog, tr("Error"), tr("No user selected."));
            return;
        }

        int ret = QMessageBox::warning(&usersDialog, tr("Delete User"),
                                       tr("Are you sure you want to delete this user?"),
                                       QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No) return;

        table->removeRow(selectedRow);
        int lineIndex = selectedRow * 5;
        for (int i = 0; i < 5; ++i) {
            lines.removeAt(lineIndex);
        }

        QMessageBox::information(&usersDialog, tr("Success"), tr("User deleted."));
    });

    usersDialog.exec();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open the file for writing."));
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();

    QMessageBox::information(this, tr("Success"), tr("User data has been updated."));
    updateStatistics();
}

void Widget::on_m1_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentPerformancePage));
}


void Widget::on_assignHwButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->assignPage));
}


void Widget::on_spBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->teacherHome));
}


void Widget::on_assignBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->teacherHome));
}


void Widget::on_backButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->welcomePage));
}

void Widget::on_darkMode_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked) {
        // Dark Mode
        this->setStyleSheet(R"(
        QWidget {
            background-color: #4F4F51; /* Dark grey background */
        }

        QPushButton {
            border: 2px solid #E8B1BD;
            border-radius: 5px;
            color: white;
            background-color: transparent;
        }

        QPushButton:hover {
            background-color: #F2C4CE;
            color: white;
        }

        QPushButton:pressed {
            background-color: #4B0082;
        }

            QLabel, QCheckBox {
                color: white; /* White text for labels and checkboxes */
            }
        )");
    } else if (arg1 == Qt::Unchecked) {
        // Light Mode
        this->setStyleSheet(R"(
            QWidget {
                background-color: #FFFFFF; /* White background */
                color: black; /* Default text color */
            }

            QPushButton {
                border: 2px solid blue;
                border-radius: 5px;
                color: black;
                background-color: transparent;
            }

            QPushButton:hover {
                background-color: lightblue;
                color: black;
            }

            QPushButton:pressed {
                background-color: #87CEEB;
            }

            QLabel, QCheckBox {
                color: black; /* Black text for labels and checkboxes */
            }
        )");
    }
}


void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->loginPage));
}


void Widget::on_comboBox_2_activated(int index)
{
    QString selectedLanguage = ui->comboBox_2->itemText(index);
    QMessageBox::information(this, tr("Language Selected"), tr("You selected: %1").arg(selectedLanguage));
}



void Widget::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->stockPage));

}


void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->studentHome));
}

