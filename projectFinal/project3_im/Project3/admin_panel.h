#ifndef ADMIN_PANEL_H
#define ADMIN_PANEL_H

#include <QWidget>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEventTransition>
#include <QtSql>
#include <QPushButton>
#include <QMessageBox>
#include "db.h"
#include "qcustomplot.h"
#include <QScrollBar>

namespace Ui {
class Admin_Panel;
}

class Admin_Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Panel(QWidget *parent = nullptr);
    ~Admin_Panel();

private:
    struct information {
        QString name, user_id, dep, amount, payment_method, account_no, row_id;
    }info[100];

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_mdash_clicked();

    void on_pushButton_sett_clicked();

    void on_pushButton_manage_clicked();

    void on_pushButton_menu_clicked();

    void on_pushButton_cpic_clicked();

    void on_pushButton_update_clicked();

    void on_scroll_button_name_clicked();

    void on_pushButton_abort_clicked();

    void on_pushButton_assign_clicked();

    void on_tableView_3_clicked(const QModelIndex index);

    void makePlot(int, int, int, int,int, int, int); // for custom plot

    void on_pushButton_message_clicked();

    void on_lineEdit_massage_textChanged(const QString &arg1);

    void keyPressEvent(QKeyEvent *event);

    void on_lineEdit_search_textChanged(const QString &arg1);

    void load_tableview_data(QTableView *table, QString qry);

    void on_pushButton_manage_user_clicked();

    void on_lineEdit_search_2_textChanged(const QString &arg1);

    void on_tableView_user_clicked(const QModelIndex &index);

    void on_pushButton_back_clicked();

    void on_pushButton_user_remove_clicked();

    void on_pushButton_send_message_clicked();

    void showProfileFromMessage_clicked();

    void  moveScrollBarToBottom(int , int);

    void on_pushButton_hide_clicked();

    void on_lineEdit_day_editingFinished();

    void on_pushButton_add_newP_clicked();

    void on_pushButton_back_2_clicked();

    void on_pushButton_add_pro_clicked();

    void on_pushButton_clear_clicked();

    void on_lineEdit_deadline_day_editingFinished();

    void on_pushButton_clicked();

    void on_tableView_paid_request_clicked(const QModelIndex index);

    void on_left_clicked();

    void on_right_clicked();

    void fill_up_withdraw_info(int, int, int);

    void on_pushButton_continue_clicked();

    void on_pushButton_cancel_clicked();

    void on_money_send_btn_main_2_clicked();

    void on_money_send_btn_main_clicked();

    void load_struct_for_withdraw_info();

    void load_table_payment_info();

    void on_money_send_btn_left_clicked();

    void on_money_send_btn_right_clicked();

    void shadow_on_payment_gateway();

    void load_details();

    void load_pending_project_list();

    void eraseLayout(QLayout * layout);

private:
    Ui::Admin_Panel *ui;

    QString pic_path;
    QString user_username;
    QString status;

    QPropertyAnimation *anim;
    QPropertyAnimation *assign_anim, *add_new_anim;
    QPropertyAnimation *menu_anim;
    QPropertyAnimation *user_anim;
    db mydb;

    bool menu_clicked;

    //variables for accessing datas
    int admin, dep, free, des, running_project, complete_project, pending_project;
    // for scroll area

    int trackforScroll = 0;
    QPushButton *pushButton;
    QString getDataFromScrollArea, scrollAreaToAssign, getDurationData;
    QSqlQueryModel *modelForAssign;
    QSqlQuery *qryForAssign;
    int indexForAssign;

    QFormLayout * layout = new QFormLayout(this); // for assiging job
    QFormLayout *lay = new QFormLayout(this); // for messeging

    //for message box loading
    bool loaded;
    // for profile loading in message box
    bool animationDoneForProfileView;
    int x, y;
    // for scroll area attached in the bottom
    QScrollBar *scrollbar;
    int RowCount = 0; // for settele the last element of the message box

    //for fullfill the withdraw animation
    int current_pos, left_pos, right_pos, total_row;
    QString MidPos = "mid", RightPos = "right", LeftPos = "left";
    QRect mid = QRect(343, 130, 401, 401), left = QRect(55, 210, 251, 241), right = QRect(778, 210, 251, 241);
    QRect posOfRightSpacer, posOfLeftSpacer, posOfMidSpacer;
};


#endif // ADMIN_PANEL_H
