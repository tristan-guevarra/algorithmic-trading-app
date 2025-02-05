#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dict.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();
    void on_backButton_2_clicked();
    void on_backButton_3_clicked();
    void on_regStuButton_clicked();
    void on_regTeachButton_clicked();
    void on_registerStudentBtn_clicked();
    void on_registerTeacherBtn_clicked();
    void on_loginScreenButton_clicked();
    void on_logoutButton_clicked();
    void on_modules_clicked();
    void on_mod1_clicked();
    void on_mod2_clicked();
    void on_mod3_clicked();
    void on_mod4_clicked();
    void on_mod5_clicked();
    void on_RETURNBTN_clicked();
    void on_menu_clicked();
    void on_mod6_clicked();
    void on_mod7_clicked();
    void on_mod8_clicked();
    void on_mod9_clicked();
    void on_quizButton1_clicked();
    void on_quizButton2_clicked();
    void on_quizButton3_clicked();
    void on_quizButton4_clicked();
    void on_quizButton5_clicked();
    void on_quizButton6_clicked();
    void on_quizButton7_clicked();
    void on_quizButton8_clicked();
    void on_quizButton9_clicked();
    void resetQuiz(QWidget *quizContainer);
    void on_submitQuiz1_clicked();
    void on_submitQuiz2_clicked();
    void on_submitQuiz3_clicked();
    void on_submitQuiz4_clicked();
    void on_submitQuiz5_clicked();
    void on_submitQuiz6_clicked();
    void on_submitQuiz7_clicked();
    void on_submitQuiz8_clicked();
    void on_submitQuiz9_clicked();

    // New slots for Admin Information
    // void on_adminInfoButton_clicked();
    void on_adminInfoBackButton_clicked();

    void on_adminInfo_clicked();

    void on_settings_clicked();

    void on_settingBackButton_clicked();

    void on_darkMode_checkStateChanged(const Qt::CheckState &arg1);

    // void on_passUpdate_clicked();

    void on_emailChange_clicked();

    void on_passwordUp_clicked();

    void on_viewAllUsersButton_clicked();
    void on_addUserButton_clicked();
    void on_editUserButton_clicked();
    void on_deleteUserButton_clicked();

    void on_m1_button_clicked();

    void on_assignHwButton_clicked();

    void on_spBackButton_clicked();

    void on_assignBackButton_clicked();

    void on_getDefinitionButton_clicked();

    void on_dictionary_clicked();

    void on_returnToMenu_clicked();

    void on_showModulesButton_clicked();

    void on_markCompletedButton_clicked();

    void on_markUncompletedButton_clicked();

    void on_backButton_4_clicked();

    void on_darkMode_clicked();

    void on_studentComboBox_activated(int index);

    void on_accSettings_clicked();

    void on_helpButton_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_activated(int index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Dict dictionary;

private:
    Ui::Widget *ui;
    void setupReturnButtonConnections();
    void updateStatistics();
    QString generateRandomAdminInfo();
};





#endif // WIDGET_H
