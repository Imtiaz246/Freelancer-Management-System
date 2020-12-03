#include "user_panel.h"
#include "ui_user_panel.h"
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QTimer>


User_Panel::User_Panel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_Panel)
{
    ui->setupUi(this);

    menu_clicked = false;

    ui->frame_7->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->frame_menu->setGeometry(QRect(1340,65,0,0));
    ui->label_4->setGeometry(0,0,1071,681);
    ui->label_6->setGeometry(0,0,1071,681);
    ui->frame_payment->setGeometry(350,180,401,341);
    ui->frame_payment_2->setGeometry(250,100,601,501);
    ui->frame_payment_3->setGeometry(250,100,601,501);

    ui->label_incorr->setVisible(false);
    ui->label_corr->hide();
    ui->label_password_inc->hide();
    ui->label_send_message->setVisible(false);

    ui->frame_payment->hide();
    ui->frame_payment_2->hide();
    ui->frame_payment_3->hide();
    ui->frame_3->hide();
    ui->frame_3->setGeometry(280,100,451,381);
    ui->label_4->hide();
    ui->label_6->hide();
    ui->frame_partial->hide();

    ui->listWidget_pro->setCurrentRow(0);

    loaded = false; // for message bos loading
    x = 0; y = 0; // for animating the profile in the message box
    scrollbar = ui->scrollArea_message->verticalScrollBar(); // for scrollbar set in the bottom

    //setting line validator
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("^[a-z0-9A-Z._@$]+"), this));
    ui->lineEdit_day->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1,2}"), this));
    ui->lineEdit_year->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1,4}"), this));

    //seting up data
    QString name, pass, sts, picPath,username,join, avail;
    QSqlQuery *qry;
    QSqlQueryModel *model;
    if(mydb.connOpen()){
        qDebug() << "admin hello open....";
        qry = new QSqlQuery;
        model = new QSqlQueryModel;
        if (qry->exec("select * from Retrive")) {
            qDebug() << "1st qry";
            model->setQuery(*qry);

            name = model->record(0).value(1).toString();
            pass = model->record(0).value(2).toString();
            qDebug() << name << sts;
            mydb.connClose();
            qry = nullptr;
            model = nullptr;
            mydb.connClose();
        }
    }
    if(mydb.connOpen()){
        qDebug() << "admin hello open....";
        qry = new QSqlQuery;
        model = new QSqlQueryModel;
        if (qry->exec("select * from AllMemberDetails where User_id = '"+name+"' and Password = '"+pass+"'")) {
            qDebug() << "2nd qry";
            model->setQuery(*qry);
            name = model->record(0).value(0).toString();
            username = model->record(0).value(1).toString();
            sts = model->record(0).value(4).toString();
            picPath = model->record(0).value(9).toString();
            join = model->record(0).value(12).toString();
            avail = model->record(0).value(5).toString();
            qDebug() << name << sts << picPath;
            ui->label_sname->setText(name);
            ui->label_name->setText(name);
            ui->label_username->setText(username);
            ui->label_stats_2->setText(sts);
            ui->label_join->setText(join);
            if(avail == "Available")
                ui->comboBox->setCurrentIndex(0);
            else if(avail == "Busy")
                ui->comboBox->setCurrentIndex(1);
            QPixmap pix(picPath);
            ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
            ui->label_pic_2->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_pic_2->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
            ui->label_menu->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_menu->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
            mydb.connClose();
        }
    }

    //setting up table in progress and running

    setting_table_data();

    //----------------------------------------------------------

    for(int i=0;i< ui->listWidget_pro->count(); i++)
        ui->listWidget_pro->item(i)->setSizeHint(QSize(90,31));

    // shawdow for message profile system
    border_frame_shadow(ui->frame_7);

    //shadow for payment system
    border_frame_shadow(ui->frame_payment);
    border_frame_shadow(ui->frame_payment_2);
    border_frame_shadow(ui->frame_payment_3);

    //shadow for submit system
    border_frame_shadow(ui->frame_3);

    load_earning_data();
}

User_Panel::~User_Panel()
{
    delete ui;
}

void User_Panel::load_tableview_data(QTableView *table, QString query)
{
    if(mydb.connOpen()){
        QSqlQuery *qry = new QSqlQuery;
        QSqlQueryModel *model = new QSqlQueryModel;

        if(qry->exec(query))
            model->setQuery(*qry);
        table->setModel(model);
    }
    mydb.connClose();
}

void User_Panel::setting_table_data()
{
    if(mydb.connOpen()){
        QSqlQuery *qry = new QSqlQuery;
        QString username = ui->label_username->text();

        if(qry->exec("select Name, Details, Deadline, Department, Amount from Projects where User_id = '"+username+"' and (Status <> 'Complete' or Status is null)")){
            if(qry->next()) {
                ui->label_rpro_name->setText(qry->value(0).toString());
                ui->label_rpro_name->setStyleSheet("border:none;color: #55ae27;background:none;");
                ui->label_rpro_details->setText(qry->value(1).toString());
                ui->label_rpro_deadline->setText(qry->value(2).toString());
                ui->label_rpro_dep->setText(qry->value(3).toString());
                ui->label_rpro_amount->setText(qry->value(4).toString());
            } else {
                ui->label_rpro_name->setText("No active job at the moment");
                ui->label_rpro_name->setStyleSheet("border:none;color: #888888;background:none;");
                ui->label_rpro_details->clear();
                ui->label_rpro_deadline->setText("N/A");
                ui->label_rpro_dep->setText("N/A");
                ui->label_rpro_amount->setText("N/A");
            }
            mydb.connClose();
        }
    }
    ui->label_rpro_2->setText(ui->label_rpro_name->text());
    ui->label_rpro_2->setStyleSheet(ui->label_rpro_name->styleSheet());

    if(mydb.connOpen()){
        QSqlQuery *qry = new QSqlQuery;
        QSqlQueryModel *model = new QSqlQueryModel;
        QString username = ui->label_username->text();
        if(qry->exec("select Name, Details, Amount, Submit_date from Projects where User_id = '"+username+"' and Assinged_to is not null and Status = 'Complete'")){
            model->setQuery(*qry);
            ui->tableView_2->setModel(model);
            ui->label_cpro_2->setNum(model->rowCount());
            mydb.connClose();
        }
    }

    //getting time remaining
    QString deadline = ui->label_rpro_deadline->text();
    if(deadline != "N/A"){
        deadline += " 23:59:59";


        beginDate = QDateTime::currentDateTime();
        expireDate = QDateTime::fromString(deadline, "MMM dd, yyyy hh:mm:ss");
        years = months = days = 0;
        if(beginDate.daysTo(expireDate) >= 0){
            s = beginDate.time().secsTo(expireDate.time());
            min = s/60;
            h = min/60;
            s %= 60;
            min %= 60;

            QTimer *timer = new QTimer;
            connect(timer, SIGNAL(timeout()), this, SLOT(update_time_left()));
            timer->start(1000);
        } else {
            ui->label_rpro_time_left->setText("LATE");
            ui->label_rpro_time_left->setStyleSheet("border:none;color:red;");
        }
    }
}

void User_Panel::border_frame_shadow(QFrame *obj)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 80));
    obj->setGraphicsEffect(bodyShadow);
}

void User_Panel::load_earning_data()
{
    total_earnings = total_withdraw = available_for_withdrawal = pending = 0;

    if(mydb.connOpen()){
        QSqlQuery *qry = new QSqlQuery;
        if(qry->exec("select Total_earning, Total_withdraw, Available_on_account from AllMemberDetails where User_id = '"+ui->label_username->text()+"'")){
            if(qry->next()){
                total_earnings = qry->value(0).toDouble();
                total_withdraw = qry->value(1).toDouble();
                available_for_withdrawal = qry->value(2).toDouble();
            }

            qry = new QSqlQuery;
            if(qry->exec("select Amount_requested from Withdraw_information where User_id = '"+ui->label_username->text()+"'")){
                while(qry->next())
                    pending += qry->value(0).toDouble();
            }
        }
        mydb.connClose();
    }
}

void User_Panel::update_time_left()
{
    years=expireDate.date().year()-beginDate.date().year();
    if((months=expireDate.date().month()-beginDate.date().month())<0) {
        years--;
        months+=12;
    }
    if((days=expireDate.date().day()-beginDate.date().day())<0) {
        if(--months < 0) {
            years--;
            months+=12;
        }
        days+=beginDate.date().daysInMonth();
    }

    if(--s < 0){
        --min;
        s+=60;
    }
    if(min < 0){
        --h;
        min+= 60;
    }

    QString days_left = "";

    if(years>1)
        days_left += QString::number(years) + "y ";
    else if(years>0)
        days_left += QString::number(years) + "y ";
    if(months>1)
        days_left += QString::number(months) + "m ";
    else if(months>0)
        days_left += QString::number(months) + "m ";
    if(days>1)
        days_left += QString::number(days) + " Days   ";
    else if(days>0)
        days_left += QString::number(days) + " Day   ";

    if(h>9)
        days_left += QString::number(h) + " : ";
    else if (h>=0)
        days_left += "0" + QString::number(h) + " : ";
    if(min>9)
        days_left += QString::number(min) +" : ";
    else if (min>=0)
        days_left += "0" + QString::number(min) +" : ";
    if(s>9)
        days_left += QString::number(s);
    else if (s>=0)
        days_left += "0" + QString::number(s);

    ui->label_rpro_time_left->setText(days_left);
}

void User_Panel::on_pushButton_logout_clicked()
{
    QApplication::exit(-123);
}

void User_Panel::on_pushButton_mdash_clicked()
{
    if(menu_clicked){
        on_pushButton_menu_clicked();
        menu_clicked = false;
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void User_Panel::on_pushButton_sett_clicked()
{
    if(menu_clicked){
        on_pushButton_menu_clicked();
        menu_clicked = false;
    }
    ui->stackedWidget->setCurrentIndex(1);
    QString username, name, pass, dept, address, email, dob, mbl, status;
    QSqlQuery *qry;
    QSqlQueryModel *model = new QSqlQueryModel;
    username = ui->label_username->text();
    status = ui->label_stats_2->text();

    if (status == "Admin") {
        ui->lineEdit_5->setFocusPolicy(Qt::NoFocus);
    }

    qDebug() << username;
    if(mydb.connOpen()){
        qry = new QSqlQuery;
        if(qry->exec("select * from AllMemberDetails where User_id = '"+username+"'")){
            model->setQuery(*qry);
            name = model->record(0).value(0).toString();
            pass = model->record(0).value(3).toString();
            dept = model->record(0).value(13).toString();
            address = model->record(0).value(14).toString();
            email = model->record(0).value(7).toString();
            dob = model->record(0).value(11).toString();
            mbl = model->record(0).value(15).toString();
            qDebug() << address;

            ui->lineEdit_1->setText(name);
            ui->lineEdit_2->setText(email);
            ui->lineEdit_3->setText(username);
            ui->lineEdit_4->setText(pass);
            ui->lineEdit_6->setText(pass);
            ui->lineEdit_5->setText(dept);
            ui->lineEdit_7->setText(address);
            ui->lineEdit_9->setText(mbl);
            mydb.connClose();

            QString month = dob.split(',').first().split(' ').last();
            ui->lineEdit_day->setText(dob.left(2));
            ui->lineEdit_year->setText(dob.right(4));
            ui->comboBox_month->setCurrentIndex(ui->comboBox_month->findText(month));
        }
    }
}

void User_Panel::on_pushButton_menu_clicked()
{
    QRect close = QRect(1340,65,0,0);
    QRect open = QRect(1200,65,171,171);

    menu_anim = new QPropertyAnimation(ui->frame_menu, "geometry");
//    menu_clicked = true;
    if(ui->frame_menu->geometry() == close){
        menu_anim->stop();
        menu_anim->setStartValue(close);
        menu_anim->setEndValue(open);
        menu_anim->setDuration(300);
        menu_anim->setEasingCurve(QEasingCurve::OutQuint);
        menu_anim->start();
        menu_clicked = true;
    }else if (ui->frame_menu->geometry() == open){
        menu_anim->stop();
        menu_anim->setStartValue(open);
        menu_anim->setEndValue(close);
        menu_anim->setDuration(150);
        menu_anim->setEasingCurve(QEasingCurve::OutQuint);
        menu_anim->start();
        menu_clicked = false;
    }
}

void User_Panel::on_pushButton_cpic_clicked()
{
    pic_path = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Images (*jpg *png *jpeg)"));
    QPixmap pix(pic_path);
    ui->label_pic_2->setPixmap(pix.scaled(ui->label_pic_2->width(), ui->label_pic_2->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}

void User_Panel::on_pushButton_update_clicked()
{
    QString name, email, picPath, user_id, pass, c_pass, dob, mob;


    if (ui->lineEdit_1->text() == "" || ui->lineEdit_2->text() == "" || ui->lineEdit_3->text() == "" || ui->lineEdit_4->text() == "" || ui->lineEdit_6->text() == "" || ui->lineEdit_7->text() == "" || ui->lineEdit_9->text() == "" || ui->lineEdit_day->text() == "" || ui->lineEdit_year->text() == "" ) {
        ui->label_incorr->setVisible(true);
    } else {
        ui->label_incorr->setVisible(false);
        QTimer::singleShot(5,ui->label_corr, SLOT(show()));
        QTimer::singleShot(2500,ui->label_corr, SLOT(hide()));
        QString username, name, pass, c_pass, dept, address, email, dob, mbl;
        QSqlQuery *qry;

        username = ui->label_username->text();

        if(mydb.connOpen()){
            qry = new QSqlQuery;
            name = ui->lineEdit_1->text();
            pass = ui->lineEdit_4->text();
            c_pass = ui->lineEdit_6->text();
            dept = ui->lineEdit_5->text();
            address = ui->lineEdit_7->text();
            email = ui->lineEdit_2->text();
            dob = ui->lineEdit_day->text() + " " + ui->comboBox_month->currentText() + ", " + ui->lineEdit_year->text();
            qDebug() << dob;
            mbl = ui->lineEdit_9->text();

            qDebug() << address;

            if (pass == c_pass) {
                if(qry->exec("update AllMemberDetails set Name = '"+name+"', Password = '"+pass+"', Department = '"+dept+"', Address = '"+address+"', Email = '"+email+"',DOB = '"+dob+"', Mobile = '"+mbl+"' where User_id = '"+username+"'")){
                    mydb.connClose();
                    qDebug() << pic_path;
                    if(pic_path != ""){
                        if(mydb.connOpen()){
                            qry = nullptr;
                            qry = new QSqlQuery;
                            if(qry->exec("update AllMemberDetails set Picture = '"+pic_path+"' where User_id = '"+username+"'")){
                                mydb.connClose();
                                QPixmap pix(pic_path);
                                ui->label_menu->setPixmap(pix.scaled(ui->label_menu->width(), ui->label_pic_2->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
                                ui->label_pic->setPixmap(pix.scaled(ui->label_pic->width(), ui->label_pic_2->height(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
                            }
                        }
                    }
                }
            } else ui->label_incorr->setVisible(true);
        }
    }
}

void User_Panel::on_comboBox_currentIndexChanged(int index)
{
    qDebug() << index;
    if(mydb.connOpen()){
        QSqlQuery *qry = new QSqlQuery;
        QString username = ui->label_username->text();
        QString combo_text = ui->comboBox->currentText();
        if(qry->exec("update AllMemberDetails set Availablity = '"+combo_text+"' where User_id = '"+username+"'"))
            mydb.connClose();
    }
}

void User_Panel::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)){
        if(ui->stackedWidget->currentIndex() == 2 && ui->lineEdit_massage->text().size() > 0)
            on_pushButton_send_message_clicked();
    }
}

void User_Panel::on_pushButton_message_clicked()
{
    if(menu_clicked){
        on_pushButton_menu_clicked();
        menu_clicked = false;
    }
    ui->stackedWidget->setCurrentIndex(2);

    QPushButton *button;
    QLabel * label_timeDate, *label_mess;
    QString mess, time, date, status;

    if (loaded == false) {
        loaded = true;
        if (mydb.connOpen()) {
            QSqlQuery * qry = new QSqlQuery;

            if (qry->exec("select Name, Message, Time, Date, Status from Message")) {
                qDebug() << "selected message";

                while (qry->next()) {
                    button = new QPushButton(qry->value(0).toString());
                    mess = qry->value(1).toString();
                    time = qry->value(2).toString();
                    date = qry->value(3).toString();
                    status = qry->value(4).toString();

                    label_timeDate= new QLabel;
                    label_mess = new QLabel;

                    label_timeDate->setText("   " + date + ", " + "at " + time);
                    label_timeDate->setStyleSheet("background: transparent; color: #bbbbbb; border: none; font-family: century gothic; font-size: 12px;");

                    label_mess->setText(mess);
                    label_mess->setStyleSheet("background: transparent; Text-align: left; font-family: century gothic; font-size: 15px; color: black; border: none;");


                    button->setObjectName("buttonNameObject");
                    button->setStyleSheet("QPushButton#buttonNameObject {background: transparent; Text-align: left; font-family:""Segoe UI Semibold""; font-size: 15px; color: #6fa000; border: none;}QPushButton#buttonNameObject:hover {border:none; font-size: bold; color: #2f8700;}");

                    QFrame *frame_line = new QFrame();
                    frame_line->setFrameShape(QFrame::HLine);
                    frame_line->setFrameShadow(QFrame::Sunken);
                    frame_line->setStyleSheet("background:gray");

                    lay->addRow(button, label_timeDate);
                    lay->addItem(new QSpacerItem(0, 7, QSizePolicy::Expanding, QSizePolicy::Expanding));
                    lay->addRow(label_mess);
                    //lay->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
                    lay->addRow(frame_line);
                    lay->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));

                    ui->scrollAreaMessage->setLayout(lay);

                    connect(button, SIGNAL(clicked()), this, SLOT(showProfileFromMessage_clicked()));
                    connect(scrollbar, SIGNAL(rangeChanged(int , int)), this, SLOT(moveScrollBarToBottom(int , int)));
                    RowCount++;
                }
            }
        }
    }
}

void User_Panel::on_pushButton_send_message_clicked()
{
    int timeModify;

    QDate *date = new QDate;
    QTime *time = new QTime;
    QString message, name, status, timeStr, dateStr, user_id;

    timeStr = time->currentTime().toString();
    timeStr = timeStr.left(5);
    dateStr = date->currentDate().toString();
    message = ui->lineEdit_massage->text();
    name = ui->label_sname->text();
    status = ui->label_stats_2->text();
    user_id = ui->label_username->text();

    timeModify = timeStr.left(2).toInt();
    qDebug() << timeModify;

    if (timeModify >= 12 || timeModify >= 24) {
            if (timeModify > 12) timeModify =  timeModify - 12;
            else if (timeModify >= 24) timeModify = timeModify - 24;
            timeStr = QString::number(timeModify) + timeStr.right(3) + " PM";
        } else timeStr = timeStr + " AM";

    qDebug() << timeStr;

    QPushButton *button = new QPushButton(name);
    QLabel * label_timeDate = new QLabel, *label_mess = new QLabel;

    label_timeDate->setText("   " + dateStr + ", " + "at " + timeStr);
    label_timeDate->setStyleSheet("background: transparent; color: #bbbbbb; border: none; font-family: century gothic; font-size: 12px;");

    label_mess->setText(message);
    label_mess->setStyleSheet("background: transparent; Text-align: left; font-family: century gothic; font-size: 15px; color: black; border: none;");

    button->setObjectName("buttonNameObject");
    button->setStyleSheet("QPushButton#buttonNameObject {background: transparent; Text-align: left; font-family:""Segoe UI Semibold""; font-size: 15px; color: #6fa000; border: none;}QPushButton#buttonNameObject:hover {border:none; font-size: bold; color: #2f8700;}");

    QFrame *frame_line = new QFrame();
    frame_line->setFrameShape(QFrame::HLine);
    frame_line->setFrameShadow(QFrame::Sunken);
    frame_line->setStyleSheet("background:gray");


    lay->addRow(button, label_timeDate);
    lay->addItem(new QSpacerItem(0, 7, QSizePolicy::Expanding, QSizePolicy::Expanding));
    lay->addRow(label_mess);
    //lay->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    lay->addRow(frame_line);
    lay->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(button, SIGNAL(clicked()), this, SLOT(showProfileFromMessage_clicked()));
    connect(scrollbar, SIGNAL(rangeChanged(int , int)), this, SLOT(moveScrollBarToBottom(int , int)));
    RowCount++;

    if (mydb.connOpen()) {
        QSqlQuery *qry = new QSqlQuery;
        if (qry->exec("insert into Message (Name, Message, Time, Date, Status, User_id) values ('"+name+"', '"+message+"', '"+timeStr+"', '"+dateStr+"', '"+status+"', '"+user_id+"')")){
            mydb.connClose();
        }
       ui->lineEdit_massage->clear();
    }
}

void User_Panel::on_lineEdit_massage_textChanged(const QString &arg1)
{
    if(arg1.size() > 0){
        ui->label_send_message->setVisible(true);
        ui->pushButton_send_message->setIcon(QIcon(":/imgs/send_active.png"));
    }
    else{
        ui->pushButton_send_message->setIcon(QIcon(":/imgs/send.png"));
        ui->label_send_message->setVisible(false);
    }
}

void User_Panel::on_lineEdit_day_editingFinished()
{
    if(ui->lineEdit_day->text().toInt() == 0)
        ui->lineEdit_day->setText("01");
    else if((ui->lineEdit_day->text().toInt() < 10) && (ui->lineEdit_day->text().size() < 2))
        ui->lineEdit_day->setText("0" + ui->lineEdit_day->text());
    if(ui->lineEdit_day->text().toInt() > 31){
        ui->lineEdit_day->setStyleSheet("*{border-radius:5px; border:1px solid red; color:red;}:hover{border: 1px solid red;}:focus{border: 1px solid red;}");
    } else
        ui->lineEdit_day->setStyleSheet("*{border-radius:5px;}:hover{border: 1px solid #34a671;}:focus{border: 1px solid #34a671;}");
}

void User_Panel::showProfileFromMessage_clicked()
{
    QPixmap pix;
    pushButton = new QPushButton;
    pushButton = qobject_cast<QPushButton*>(sender());
    QString name = pushButton->text();
    int xx = pushButton->x();
    int yy = pushButton->y();
    QString row,  user_id, picPath, specialist_details;
    if (yy/71 == 0) row = QString::number(1);
    else row = QString::number((yy-9)/71 + 1);

    qDebug() << yy << " -" << row;

    pushButton->setStyleSheet("QPushButton#buttonNameObject {background: transparent; Text-align: left; color:#2f8700; border: none;font-size:15px;font-family:""Segoe UI Semibold"";}");
    // retriving the data
    if (mydb.connOpen()) {
        QSqlQuery *qry = new QSqlQuery;

        if (qry->exec("select User_id from Message where ROWID is '"+row+"'")) {
            qDebug() << "searching  for message";

            while(qry->next()) {
                user_id = qry->value(0).toString();
            }

            if (qry->exec("select Picture, Specialist from AllMemberDetails where User_id = '"+user_id+"'")) {
                while(qry->next()) {
                    picPath = qry->value(0).toString();
                    specialist_details = qry->value(1).toString();
                }
            }
        }
        mydb.connClose();
    }
    if (y != yy and (QString::number(RowCount) == row)) {
        ui->frame_7->show();
        ui->frame_7->activateWindow();
        ui->frame_7->raise();
        ui->label_proName->setText(name);
        ui->label_proDetails->setText(specialist_details);
        pix.load(picPath);
        ui->label_profile_pic->setPixmap(pix);

        QPropertyAnimation *animation = new QPropertyAnimation(ui->frame_7, "geometry");
        animation->setDuration(200);
        animation->setEasingCurve(QEasingCurve::OutQuint);
        animation->setStartValue(QRect(xx+200, yy-40, 0, 0));
        animation->setEndValue(QRect(xx+300, yy-40, 421, 111));
        animation->start();
        x = xx;
        y = yy;
    }
    else if (y != yy and RowCount != 1) {
        ui->frame_7->show();
        ui->frame_7->activateWindow();
        ui->frame_7->raise();
        ui->label_proName->setText(name);
        ui->label_proDetails->setText(specialist_details);
        pix.load(picPath);
        ui->label_profile_pic->setPixmap(pix);

        QPropertyAnimation *animation = new QPropertyAnimation(ui->frame_7, "geometry");
        animation->setDuration(200);
        animation->setEasingCurve(QEasingCurve::OutQuint);
        animation->setStartValue(QRect(xx+200, yy, 0, 0));
        animation->setEndValue(QRect(xx+300, yy, 421, 111));
        animation->start();
        x = xx;
        y = yy;
    }

    else if (y == yy) {
        QPropertyAnimation *animation = new QPropertyAnimation(ui->frame_7, "geometry");
        pushButton = new QPushButton;
        pushButton = qobject_cast<QPushButton*>(sender());
        QString name = pushButton->text();
        x = ui->frame_7->x();
        y = ui->frame_7->y();
        animation->setDuration(200);
        animation->setEasingCurve(QEasingCurve::OutQuint);
        animation->setStartValue(QRect(ui->frame_7->geometry()));
        animation->setEndValue(QRect(x+400, y-10, 0, 0));
        animation->start();
        x = 0;
        y = 0;
    }

}

void User_Panel::moveScrollBarToBottom(int min, int max)
{
    Q_UNUSED(min)
    ui->scrollArea_message->verticalScrollBar()->setValue(max);
}

void User_Panel::on_pushButton_hide_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->frame_7, "geometry");
    pushButton = new QPushButton;
    pushButton = qobject_cast<QPushButton*>(sender());
    QString name = pushButton->text();
    x = ui->frame_7->x();
    y = ui->frame_7->y();
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuint);
    animation->setStartValue(QRect(ui->frame_7->geometry()));
    animation->setEndValue(QRect(x+400, y-10, 0, 0));
    animation->start();
    x = 0;
    y = 0;
}

void User_Panel::on_pushButton_payment_clicked()
{
    if(menu_clicked){
        on_pushButton_menu_clicked();
        menu_clicked = false;
    }
    ui->stackedWidget->setCurrentIndex(3);
    load_earning_data();
    load_tableview_data(ui->tableView_wallet, "select Date, Name, Amount from Payment_History where user_id = '"+ui->label_username->text()+"'");

    ui->tableView_wallet->setColumnWidth(0, 141);
    ui->tableView_wallet->setColumnWidth(1, 751);
    ui->tableView_wallet->setColumnWidth(2, 141);

    ui->label_wallet_net_income_amount->setText("$"+QString::number(total_earnings));
    ui->label_wallet_withdrawn_amount->setText("$"+QString::number(total_withdraw));
    ui->label_wallet_aw_amount->setText("$"+QString::number(available_for_withdrawal));
    ui->label_wallet_pending_amount->setText("$"+QString::number(pending));
}

void User_Panel::on_pushButton_bkash_clicked()
{
    method_clicked = "bKash Account";
    ui->label_4->show();
    ui->frame_payment->show();
    ui->label_wallet_payment_method_2->setText("bKash Account");
    ui->label_wallet_payment_method_4->setText("bKash Account");
    ui->label_wallet_number->setText("bKash Number");
    ui->radioButton_full->setText("Avaiable Balance $"+ QString::number(available_for_withdrawal));
    if(ui->radioButton_full->isChecked())
        ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(available_for_withdrawal-2)+" to your "+ method_clicked);
}

void User_Panel::on_pushButton_continue_clicked()
{
    QSqlQuery *qry;
    if(mydb.connOpen()){
        qry = new QSqlQuery;
        if(qry->exec("select * from AllMemberDetails where User_id = '"+ui->label_username->text()+"' and Password = '"+ui->lineEdit_password->text()+"'")){
            if(qry->next()){
                ui->label_password_inc->hide();
                ui->frame_payment_2->show();
                ui->frame_payment->hide();
                ui->lineEdit_password->setStyleSheet("*{\nborder-radius:5px;\npadding-left: 15px;\n}\n\n:hover{\n	border: 1px solid #34a671;\n}\n\n:focus{\nborder: 1px solid #34a671;\n}");
            } else {
                ui->lineEdit_password->setStyleSheet("*{\nborder-radius:5px;\npadding-left: 15px;border:1px solid red;\n}\n\n:hover{\n	border: 1px solid red;\n}\n\n:focus{\nborder: 1px solid red;\n}");
                ui->label_password_inc->show();
            }
        }
        mydb.connClose();
    }
}

void User_Panel::on_pushButton_cancel_clicked()
{
    ui->label_4->hide();
    ui->frame_payment->hide();
}

void User_Panel::on_pushButton_withcancel_clicked()
{
    ui->label_4->hide();
    ui->frame_payment_2->hide();
}

void User_Panel::on_pushButton_withdraw_clicked()
{
    double amount=0;
    QString dep;
    if(ui->radioButton_full->isChecked())
        amount = available_for_withdrawal;
    else if (ui->radioButton_partial->isChecked())
        amount = ui->lineEdit_amount->text().toDouble();

    if(available_for_withdrawal >= amount){
        ui->frame_payment_2->hide();
        ui->frame_payment_3->show();

        if(mydb.connOpen()){
            QSqlQuery *qry = new QSqlQuery;
            if(qry->exec("select Department from AllMemberDetails where User_id = '"+ui->label_username->text()+"'"))
                if(qry->next())
                    dep = qry->value(0).toString();
            qry = new QSqlQuery;
            if(qry->exec("insert into Withdraw_information values ('"+ui->label_name->text()+"', '"+ui->label_username->text()+"', '"+dep+"', '"+QString::number(amount)+"', '"+ui->label_wallet_payment_method_2->text()+"', '"+ui->lineEdit_wallet_number->text()+"')")){
                ui->label_wallet_pending_amount->setText("$"+ QString::number(pending+amount));
                qry = new QSqlQuery;
                qry->exec("update AllMemberDetails set Available_on_account = '"+QString::number(available_for_withdrawal-(pending+amount))+"' where User_id = '"+ui->label_username->text()+"'");
            }
            mydb.connClose();
        }
        ui->label_wallet_amount_4->setText("$"+QString::number(amount));
        if(amount-2 >0)
            ui->label_wallet_atbw_2->setText("$"+QString::number(amount-2));
        else
            ui->label_wallet_atbw_2->setText("$0");
        on_pushButton_payment_clicked();
    } else
        QMessageBox::critical(this, "Insufficient Amount", "You don't have enough balance.");
}

void User_Panel::on_pushButton_done_clicked()
{
    ui->label_4->hide();
    ui->frame_payment_3->hide();
}

void User_Panel::on_pushButton_rpro_submit_clicked()
{
    ui->frame_3->show();
    ui->label_6->show();
}

void User_Panel::on_radioButton_full_clicked()
{
    ui->frame_partial->hide();
    ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(available_for_withdrawal-2)+" to your "+ method_clicked);
}

void User_Panel::on_radioButton_partial_clicked()
{
        ui->frame_partial->show();
}

void User_Panel::on_pushButton_submit_clicked()
{
    if(ui->lineEdit_submit->text().size() > 0){
        QString submit_date = QDate::currentDate().toString();
        QString project_name;
        QStringList date = submit_date.split(' ');
        submit_date = date.at(1) + " " + date.at(2) + ", " + date.at(3);
        double amount = 0;
        int project_done =0;
        QSqlQuery *qry;
        if(mydb.connOpen()){
            qry = new QSqlQuery;
            if(qry->exec("select Project_done from AllMemberDetails where User_id = '"+ui->label_username->text()+"'")){
                if(qry->next())
                    project_done = qry->value(0).toInt();
                if(qry->exec("select Name,Amount from Projects where User_id = '"+ui->label_username->text()+"'")){
                    if(qry->next()){
                        project_name = qry->value(0).toString();
                        amount = qry->value(1).toDouble();
                        qDebug() << amount;
                    }
                }
            }
            qry = new QSqlQuery;
            if(qry->exec("select * from Projects where Status <> 'Complete' and User_id = '"+ui->label_username->text()+"'") && qry->next()){
                if(qry->exec("update Projects set Status = 'Complete', Submit_date = '"+submit_date+"' where Name = '"+ui->label_rpro_name->text()+"' and User_id = '"+ui->label_username->text()+"'")){
                    QMessageBox::information(this, "Successful", "Project submit successful");
                    project_done++;
                    qry = new QSqlQuery;
                    if(qry->exec("update AllMemberDetails set Project_done = "+QString::number(project_done)+", Total_earning = '"+QString::number(total_earnings+amount)+"', Available_on_account = '"+QString::number(available_for_withdrawal+amount)+"' where User_id = '"+ui->label_username->text()+"' and Status <> 'Complete'")){
                        qry = new QSqlQuery;
                        qry->exec("insert into Payment_History values('"+project_name+"', '"+ui->label_username->text()+"', '"+QString::number(amount)+"', '"+submit_date+"', null)");
                    }
                    setting_table_data();
                }
            } else
                QMessageBox::critical(this, "Failed", "Project submit failed. Make sure you currently have an active project");
            mydb.connClose();
            ui->frame_3->hide();
            ui->label_6->hide();
        }
    } else {
        QMessageBox::critical(this, "Failed", "Project submit failed. Make sure you have entered a valid link");
    }
}

void User_Panel::on_pushButton_subcancel_clicked()
{
    ui->frame_3->hide();
    ui->label_6->hide();
}

void User_Panel::on_lineEdit_amount_textChanged(const QString &arg1)
{
    if(ui->radioButton_partial->isChecked()){
        double amount = arg1.toDouble() - 2;
        if(amount > 0)
            ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(arg1.toDouble()-2)+" to your bKash Account");
        else
            ui->label_wallet_sent_info->setText("You are about to sent $0 to your bKash Account");
    }

    if(arg1.toDouble() > available_for_withdrawal)
        ui->lineEdit_amount->setStyleSheet("*{\n	border-radius:5px;\n}\n\n:hover{\n	border: 1px solid red;\n}\n\n:focus{\nborder: 1px solid red;\n}");
    else
        ui->lineEdit_amount->setStyleSheet("*{\n	border-radius:5px;\n}\n\n:hover{\n	border: 1px solid #34a671;\n}\n\n:focus{\n    border: 1px solid #34a671;\n}");
}

void User_Panel::on_pushButton_rocket_clicked()
{
    method_clicked = "Rocket Account";
    ui->label_4->show();
    ui->frame_payment->show();
    ui->label_wallet_payment_method_2->setText("Rocket Account");
    ui->label_wallet_payment_method_4->setText("Rocket Account");
    ui->label_wallet_number->setText("Rocket Number");
    ui->radioButton_full->setText("Avaiable Balance $"+ QString::number(available_for_withdrawal));
    if(ui->radioButton_full->isChecked())
        ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(available_for_withdrawal)+" to your "+ method_clicked);
}

void User_Panel::on_pushButton_paypal_clicked()
{
    method_clicked = "Paypal Account";
    ui->label_4->show();
    ui->frame_payment->show();
    ui->label_wallet_payment_method_2->setText("Paypal Account");
    ui->label_wallet_payment_method_4->setText("Paypal Account");
    ui->label_wallet_number->setText("Paypal Account Number");
    ui->radioButton_full->setText("Avaiable Balance $"+ QString::number(available_for_withdrawal));
    if(ui->radioButton_full->isChecked())
        ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(available_for_withdrawal)+" to your "+ method_clicked);
}

void User_Panel::on_pushButton_bank_clicked()
{
    method_clicked = "Bank Account";
    ui->label_4->show();
    ui->frame_payment->show();
    ui->label_wallet_payment_method_2->setText("Bank Account");
    ui->label_wallet_payment_method_4->setText("Bank Account");
    ui->label_wallet_number->setText("Bank Account Number");
    ui->radioButton_full->setText("Avaiable Balance $"+ QString::number(available_for_withdrawal));
    if(ui->radioButton_full->isChecked())
        ui->label_wallet_sent_info->setText("You are about to sent $"+QString::number(available_for_withdrawal)+" to your "+ method_clicked);
}

void User_Panel::on_pushButton_cpic_2_clicked()
{
    on_pushButton_cpic_clicked();
}
