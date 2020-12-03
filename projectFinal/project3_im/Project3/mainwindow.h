#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEventTransition>
#include <QKeyEvent>
#include "admin_panel.h"
#include "user_panel.h"
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_handle_textChanged(const QString&);

    void on_lineEdit_password_textChanged(const QString&);

    void on_lineEdit_name_textChanged(const QString&);

    void on_lineEdit_usrname_textChanged(const QString&);

    void on_lineEdit_email_textChanged(const QString&);

    void on_lineEdit_password_2_textChanged(const QString&);

    void on_login_btn_clicked();

    void on_pushButton_sgn_clicked();

    void on_lineEdit_ref_textChanged(const QString &arg1);

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    Admin_Panel *admin;
    User_Panel *user;

    QStateMachine *machine;
    QStateMachine *about_machine;
    QState *s1;
    QState *s2;

    QPropertyAnimation *anim;
    QPropertyAnimation *anim2;
    QPropertyAnimation *anim3;

    QParallelAnimationGroup *animation_group;
    db mydb;

};
#endif // MAINWINDOW_H
