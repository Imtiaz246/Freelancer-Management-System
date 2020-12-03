#ifndef USER_PANEL_H
#define USER_PANEL_H

#include <QWidget>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEventTransition>
#include <QKeyEvent>
#include <QtSql>
#include <QScrollBar>
#include <QPushButton>
#include <QFormLayout>
#include <QTableView>
#include <QMessageBox>
#include "db.h"
#include "customshadoweffect.h"

namespace Ui {
class User_Panel;
}

class User_Panel : public QWidget
{
    Q_OBJECT

public:
    explicit User_Panel(QWidget *parent = nullptr);
    ~User_Panel();

private slots:
    void load_tableview_data(QTableView *table, QString query);

    void setting_table_data();

    void border_frame_shadow(QFrame *obj);

    void load_earning_data();

    void update_time_left();

    void on_pushButton_logout_clicked();

    void on_pushButton_mdash_clicked();

    void on_pushButton_sett_clicked();

    void on_pushButton_menu_clicked();

    void on_pushButton_cpic_clicked();

    void on_pushButton_update_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void keyPressEvent(QKeyEvent *event);

    void on_pushButton_message_clicked();

    void on_pushButton_send_message_clicked();

    void on_lineEdit_massage_textChanged(const QString &arg1);

    void on_lineEdit_day_editingFinished();

    void showProfileFromMessage_clicked();

    void  moveScrollBarToBottom(int , int);

    void on_pushButton_hide_clicked();

    void on_pushButton_payment_clicked();

    void on_pushButton_bkash_clicked();

    void on_pushButton_continue_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_withcancel_clicked();

    void on_pushButton_withdraw_clicked();

    void on_pushButton_done_clicked();

    void on_pushButton_rpro_submit_clicked();

    void on_radioButton_full_clicked();

    void on_radioButton_partial_clicked();

    void on_pushButton_submit_clicked();

    void on_pushButton_subcancel_clicked();

    void on_lineEdit_amount_textChanged(const QString &arg1);

    void on_pushButton_rocket_clicked();

    void on_pushButton_paypal_clicked();

    void on_pushButton_bank_clicked();

    void on_pushButton_cpic_2_clicked();

private:
    Ui::User_Panel *ui;

    QString pic_path;
    QString method_clicked;

    //time-left-variables
    QTime time_left;
    int h, min, s, years, months, days;
    QDateTime beginDate, expireDate;
    //----------------

    QPropertyAnimation *anim;
    QPropertyAnimation *menu_anim;
    db mydb;

    QFormLayout *lay = new QFormLayout(this);

    //variables for accessing datas
    //int admin, dep, free, des, running_project, complete_project, pending_project;

    QPushButton *pushButton;

    bool menu_clicked;
    double total_earnings, total_withdraw, available_for_withdrawal, pending;

    //for message box loading
    bool loaded;
    // for profile loading in message box
    bool animationDoneForProfileView;
    int x, y;
    // for scroll area attached in the bottom
    QScrollBar *scrollbar;
    int RowCount = 0; // for settele the last element of the message box
};

#endif // USER_PANEL_H
