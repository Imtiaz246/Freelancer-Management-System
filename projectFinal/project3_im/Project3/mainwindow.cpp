#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

#include <QGraphicsDropShadowEffect>
#include "customshadoweffect.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_incorr->setVisible(false);
    ui->label_incorr_2->setVisible(false);
    ui->label_username_taken->setVisible(false);
    ui->label_email_taken->setVisible(false);

    ui->lineEdit_handle->setValidator(new QRegExpValidator(QRegExp("^[a-z0-9A-Z._@$]+"), this));
    ui->lineEdit_usrname->setValidator(new QRegExpValidator(QRegExp("^[a-z0-9A-Z._@$]+"), this));
    ui->lineEdit_email->setValidator(new QRegExpValidator(QRegExp("^[a-z0-9A-Z._@]+"), this));

    this->setCentralWidget(ui->stackedWidget);
    setWindowTitle("Freelancer Management System");
    setWindowIcon(QIcon(":/imgs/project-management.png"));

    //shadow
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(20.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 80));
    ui->frame_bg->setGraphicsEffect(bodyShadow);


    ui->label_handle->setVisible(false);
    ui->label_password->setVisible(false);
    ui->label_name->setVisible(false);
    ui->label_email->setVisible(false);
    ui->label_regpass->setVisible(false);
    ui->label_regusrname->setVisible(false);
    ui->label_ref->setVisible(false);

    //animation part
    machine = new QStateMachine(this);

    s1 = new QState();
    s1->assignProperty(ui->frame_wel, "geometry", QRect(660,140,471,511));
    s1->assignProperty(ui->frame_wel, "styleSheet", "background-color: qlineargradient(spread:pad, x1:0.159, y1:0, x2:0.773, y2:1, stop:0 rgba(63, 193, 152, 255), stop:1 rgba(53, 167, 115, 255));"
                                                    "border-top-right-radius: 30px;"
                                                    "border-bottom-right-radius: 30px;");
    s1->assignProperty(ui->label_wel, "text", "<html><head/><body><p align=""center""><span style=" "font-size:20pt; color:#ffffff;"">Hello, Friend!</span></p></body></html>");
    s1->assignProperty(ui->label_com_2, "text", "<html><head/><body><p align=""center""><span style=" "font-size:14pt; color:#ffffff;"">Enter Your Personal Details And</span></p></body></html>");
    s1->assignProperty(ui->label_com_3, "text", "<html><head/><body><p align=""center""><span style=" "font-size:14pt; color:#ffffff;"">Start Your Journey With Us</span></p></body></html>");
    s1->assignProperty(ui->pushButton_reg, "text", "Sign Up");
    s1->assignProperty(ui->frame_signin, "geometry", QRect(190,140,471,511));
    s1->assignProperty(ui->frame_signup, "geometry", QRect(660,140,0,511));
    s1->assignProperty(ui->pushButton_sgn, "geometry", QRect(150,420,191,0));
    s1->assignProperty(ui->login_btn, "geometry", QRect(150,360,191,41));

    s2 = new QState();
    s2->assignProperty(ui->frame_wel, "geometry", QRect(190,140,471,511));
    s2->assignProperty(ui->frame_wel, "styleSheet", "background-color: qlineargradient(spread:pad, x1:0.159, y1:0, x2:0.773, y2:1, stop:0 rgba(63, 193, 152, 255), stop:1 rgba(53, 167, 115, 255));"
                                                    "border-top-left-radius: 30px;"
                                                    "border-bottom-left-radius: 30px;");
    s2->assignProperty(ui->label_wel, "text", "<html><head/><body><p align=""center""><span style=" "font-size:20pt; color:#ffffff;"">Welcome Back!</span></p></body></html>");
    s2->assignProperty(ui->label_com_2, "text", "<html><head/><body><p align=""center""><span style=" "font-size:14pt; color:#ffffff;"">To keep connected with us please login</span></p></body></html>");
    s2->assignProperty(ui->label_com_3, "text", "<html><head/><body><p align=""center""><span style=" "font-size:14pt; color:#ffffff;"">with your personal info</span></p></body></html>");
    s2->assignProperty(ui->pushButton_reg, "text", "Sign In");
    s2->assignProperty(ui->frame_signin, "geometry", QRect(660,140,0,511));
    s2->assignProperty(ui->frame_signup, "geometry", QRect(660,140,471,511));
    s2->assignProperty(ui->pushButton_sgn, "geometry", QRect(150,420,191,41));
    s2->assignProperty(ui->login_btn, "geometry", QRect(150,360,191,0));

    anim = new QPropertyAnimation(ui->frame_wel, "geometry");
    anim->setDuration(500);
    anim->setEasingCurve(QEasingCurve::OutQuint);

    anim2 = new QPropertyAnimation(ui->frame_signin, "geometry");
    anim2->setDuration(500);
    anim2->setEasingCurve(QEasingCurve::OutQuint);

    anim3 = new QPropertyAnimation(ui->frame_signup, "geometry");
    anim3->setDuration(500);
    anim3->setEasingCurve(QEasingCurve::OutQuint);

    animation_group = new QParallelAnimationGroup;
    animation_group->addAnimation(anim);
    animation_group->addAnimation(anim2);
    animation_group->addAnimation(anim3);

    QEventTransition *t1 = new QEventTransition(ui->pushButton_reg, QEvent::MouseButtonPress);
    t1->setTargetState(s2);
    t1->addAnimation(animation_group);
    s1->addTransition(t1);

    QEventTransition *t2 = new QEventTransition(ui->pushButton_reg, QEvent::MouseButtonPress);
    t2->setTargetState(s1);
    t2->addAnimation(animation_group);
    s2->addTransition(t2);

    machine->addState(s1);
    machine->addState(s2);
    machine->setInitialState(s1);
    machine->start();


    about_machine = new QStateMachine(this);

    QState *s3 = new QState();
    s3->assignProperty(ui->frame_about, "geometry", QRect(0,510,471,0));
    s3->assignProperty(ui->label_wel, "geometry", QRect(10,130,451,41));
    s3->assignProperty(ui->label_com_2, "geometry", QRect(10,200,451,31));
    s3->assignProperty(ui->label_com_3, "geometry", QRect(10,230,451,31));
    s3->assignProperty(ui->pushButton_reg, "geometry", QRect(160,310,161,41));
    s3->assignProperty(ui->pushButton_about, "geometry", QRect(140,420,201,31));

    QState *s4 = new QState();
    s4->assignProperty(ui->frame_about, "geometry", QRect(0,0,471,511));
    s4->assignProperty(ui->label_wel, "geometry", QRect(10,130,451,0));
    s4->assignProperty(ui->label_com_2, "geometry", QRect(10,200,451,0));
    s4->assignProperty(ui->label_com_3, "geometry", QRect(10,230,451,0));
    s4->assignProperty(ui->pushButton_reg, "geometry", QRect(160,310,161,0));
    s4->assignProperty(ui->pushButton_about, "geometry", QRect(140,420,201,0));

    QPropertyAnimation *anim4 = new QPropertyAnimation(ui->frame_about, "geometry");
    anim4->setEasingCurve(QEasingCurve::Linear);

    QEventTransition *t3 = new QEventTransition(ui->pushButton_about, QEvent::MouseButtonPress);
    t3->setTargetState(s4);
    t3->addAnimation(anim4);
    s3->addTransition(t3);

    QEventTransition *t4 = new QEventTransition(ui->pushButton_habout, QEvent::MouseButtonPress);
    t4->setTargetState(s3);
    t4->addAnimation(anim4);
    s4->addTransition(t4);

    about_machine->addState(s3);
    about_machine->addState(s4);
    about_machine->setInitialState(s3);
    about_machine->start();
    //---------------------------------------------------------------------------------------------------------

    //password show hide
    QStateMachine *pass_show_hid_machine = new QStateMachine(this);

    QState *pass_show = new QState;
    pass_show->assignProperty(ui->lineEdit_password, "echoMode", "Normal");
    pass_show->assignProperty(ui->lineEdit_password_2, "echoMode", "Normal");
    pass_show->assignProperty(ui->pushButton_pass_show, "icon", QIcon(":/imgs/icons8-eye-90.png"));
    pass_show->assignProperty(ui->pushButton_pass_show_2, "icon", QIcon(":/imgs/icons8-eye-90.png"));

    QState *pass_hide = new QState;
    pass_hide->assignProperty(ui->lineEdit_password, "echoMode", "Password");
    pass_hide->assignProperty(ui->lineEdit_password_2, "echoMode", "Password");
    pass_hide->assignProperty(ui->pushButton_pass_show, "icon", QIcon(":/imgs/icons8-hide-90.png"));
    pass_hide->assignProperty(ui->pushButton_pass_show_2, "icon", QIcon(":/imgs/icons8-hide-90.png"));

    QEventTransition *event_pass_show = new QEventTransition(ui->pushButton_pass_show, QEvent::MouseButtonPress);
    event_pass_show->setTargetState(pass_hide);
    pass_show->addTransition(event_pass_show);

    QEventTransition *event_pass_show_2 = new QEventTransition(ui->pushButton_pass_show_2, QEvent::MouseButtonPress);
    event_pass_show_2->setTargetState(pass_hide);
    pass_show->addTransition(event_pass_show_2);

    QEventTransition *event_pass_hide = new QEventTransition(ui->pushButton_pass_show, QEvent::MouseButtonPress);
    event_pass_hide->setTargetState(pass_show);
    pass_hide->addTransition(event_pass_hide);

    QEventTransition *event_pass_hide_2 = new QEventTransition(ui->pushButton_pass_show_2, QEvent::MouseButtonPress);
    event_pass_hide_2->setTargetState(pass_show);
    pass_hide->addTransition(event_pass_hide_2);

    pass_show_hid_machine->addState(pass_show);
    pass_show_hid_machine->addState(pass_hide);
    pass_show_hid_machine->setInitialState(pass_hide);
    pass_show_hid_machine->start();
    //----------------------------------------------------------------------------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_handle_textChanged(const QString &handle_txt)
{
    if(handle_txt.size() > 0){
        ui->label_handle->setVisible(true);
        ui->lineEdit_handle->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
        ui->label_handle->setStyleSheet("color:#34a670;");
    } else {
        ui->label_handle->setVisible(false);
        ui->lineEdit_handle->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
}

void MainWindow::on_lineEdit_password_textChanged(const QString &pass_txt)
{
    if(pass_txt.size() > 0){
        ui->label_password->setVisible(true);
        ui->lineEdit_password->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
        ui->label_password->setStyleSheet("color:#34a670;");
    } else {
        ui->label_password->setVisible(false);
        ui->lineEdit_password->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
}

void MainWindow::on_lineEdit_name_textChanged(const QString &name_txt)
{
    if(name_txt.size() > 0){
        ui->label_name->setVisible(true);
        ui->lineEdit_name->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    } else {
        ui->label_name->setVisible(false);
        ui->lineEdit_name->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
}

void MainWindow::on_lineEdit_usrname_textChanged(const QString &usrname_txt)
{
    if(usrname_txt.size() > 0){
        ui->label_regusrname->setVisible(true);
        ui->lineEdit_usrname->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    } else {
        ui->label_regusrname->setVisible(false);
        ui->lineEdit_usrname->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }

    //searching for if username is taken
    QSqlQuery *qry;
    if(mydb.connOpen()){
        qry = new QSqlQuery;
        if(qry->exec("select * from AllMemberDetails where User_id = '"+usrname_txt+"'")){
            if(qry->next()){
                ui->lineEdit_usrname->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
                ui->label_regusrname->setStyleSheet("color:red;");
                ui->label_username_taken->setVisible(true);
            }
            else{
                ui->label_regusrname->setStyleSheet("color:#34a670;");
                ui->label_username_taken->setVisible(false);
            }
            mydb.connClose();
        }
    }
    //---------------------------------------------------------------

}

void MainWindow::on_lineEdit_email_textChanged(const QString &email_txt)
{
    if(email_txt.size() > 0){
        ui->label_email->setVisible(true);
        ui->lineEdit_email->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    } else {
        ui->label_email->setVisible(false);
        ui->lineEdit_email->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
    if(email_txt == " "){
        ui->label_email_taken->setVisible(true);
        ui->label_email_taken->setText("No spaces allowed only alphabets, digits and [. _] is allowed");
    }


    //searching for if email is taken
    QSqlQuery *qry;
    if(mydb.connOpen()){
        qry = new QSqlQuery;
        if(qry->exec("select * from AllMemberDetails where Email = '"+email_txt+"'")){
            if(qry->next()){
                ui->lineEdit_email->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
                ui->label_email->setStyleSheet("color:red;");
                ui->label_email_taken->setVisible(true);
            }
            else{
                ui->label_email->setStyleSheet("color:#34a670;");
                ui->label_email_taken->setVisible(false);
            }
            mydb.connClose();
        }
    }
    //---------------------------------------------------------------
}

void MainWindow::on_lineEdit_password_2_textChanged(const QString &pass_txt)
{
    if(pass_txt.size() > 0){
        ui->label_regpass->setVisible(true);
        ui->lineEdit_password_2->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    } else {
        ui->label_regpass->setVisible(false);
        ui->lineEdit_password_2->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
}

void MainWindow::on_lineEdit_ref_textChanged(const QString &ref_txt)
{
    if(ref_txt.size() > 0){
        ui->label_ref->setVisible(true);
        ui->lineEdit_ref->setStyleSheet("*{\nborder:1px solid #34a670;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    } else {
        ui->label_ref->setVisible(false);
        ui->lineEdit_ref->setStyleSheet("*{\nborder:1px solid #e7ecf1;;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid #34a670;\n}\n\n:focus{\nborder: 2px solid #34a670;\n}");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)){
        if(ui->login_btn->geometry() == QRect(150,360,191,41))
            on_login_btn_clicked();
        else if(ui->pushButton_sgn->geometry() == QRect(150,420,191,41))
            on_pushButton_sgn_clicked();
    }
}

void MainWindow::on_login_btn_clicked()
{
    QString userId, pass;
    userId = ui->lineEdit_handle->text();
    pass = ui->lineEdit_password->text();

    qDebug() << "connection openning.....";
    if (mydb.connOpen()) {
        qDebug() << "hello open....";
        QSqlQuery qry;
        qry.prepare("select * from AllMemberDetails where User_id = '"+userId+"' and Password = '"+pass+"'");
        if (qry.exec()) {
            if (!qry.next()) {
                ui->label_incorr->setVisible(true);
                ui->label_handle->setStyleSheet("color:red");
                ui->label_password->setStyleSheet("color:red");
                ui->lineEdit_handle->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
                ui->lineEdit_password->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
            }
            QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery(qry);
            if (model->record(0).value(4).toString() == "Admin") {
                qry.exec("update Retrive set user_id= '"+userId+"', Password = '"+pass+"' where no = '1';");

                admin = new Admin_Panel(this);
                ui->stackedWidget->addWidget(admin);
                mydb.connClose();
                ui->stackedWidget->setCurrentIndex(1);
                ui->login_btn->setGeometry(QRect(150,360,191,0));
                ui->pushButton_sgn->setGeometry(QRect(150,420,191,0));
                ui->lineEdit_handle->clear();
                ui->lineEdit_password->clear();

            }else if(model->record(0).value(4).toString() == "Freelancer"){
                qry.exec("update Retrive set user_id= '"+userId+"', Password = '"+pass+"' where no = '1';");

                user = new User_Panel(this);
                ui->stackedWidget->addWidget(user);
                mydb.connClose();
                ui->stackedWidget->setCurrentIndex(1);
                ui->login_btn->setGeometry(QRect(150,360,191,0));
                ui->pushButton_sgn->setGeometry(QRect(150,420,191,0));
                ui->lineEdit_handle->clear();
                ui->lineEdit_password->clear();
            }
        }
    }
}

void MainWindow::on_pushButton_sgn_clicked()
{
    if (ui->lineEdit_name->text() == "" || ui->lineEdit_ref->text() == "" || ui->lineEdit_email->text() == "" || ui->lineEdit_usrname->text() == "" || ui->lineEdit_password_2->text() == "") {
        ui->label_incorr_2->setVisible(true);
        ui->label_incorr_2->setText("Please fill up all query correctly");
        if(ui->lineEdit_name->text() == "" )
            ui->lineEdit_name->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
        if(ui->lineEdit_ref->text() == "" )
            ui->lineEdit_ref->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
        if(ui->lineEdit_email->text() == "")
            ui->lineEdit_email->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
        if(ui->lineEdit_usrname->text() == "")
            ui->lineEdit_usrname->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
        if(ui->lineEdit_password_2->text() == "")
            ui->lineEdit_password_2->setStyleSheet("*{\nborder:1px solid red;\npadding-left:20px;\n}\n\n:hover{\nborder:1px solid red;\n}\n\n:focus{\nborder: 2px solid red;\n}");
    }
    else {
        QStringList datel = QDate::currentDate().toString().split(' ');
        QString date;
        date = datel[1] + " " + datel[2] + ", " + datel[3];
        date = "Joined on " + date;
        QString name, user_name, pass, ref, email;
        name = ui->lineEdit_name->text();
        user_name = ui->lineEdit_usrname->text();
        pass = ui->lineEdit_password_2->text();
        email = ui->lineEdit_email->text();
        ref = ui->lineEdit_ref->text();

        if(mydb.connOpen()) {
            QSqlQuery qry;
            if(qry.exec("select * from AllMemberDetails where Reference_code = '"+ref+"'")){
                if(qry.next()){
                    qDebug() << "Success";
                    if (qry.exec("insert into AllMemberDetails (Name, User_id, Password, Status, Email, Joined_date) values('"+name+"','"+user_name+"', '"+pass+"', 'Freelancer', '"+email+"', '"+date+"')")) {
                        ui->label_incorr_2->setText("Singed up successfully. Please login.");
                        ui->label_incorr_2->setText("color:#34a670;");
                        ui->label_incorr_2->setVisible(true);
                    }
                    else {
                        ui->label_incorr_2->setText("Account already exist with this email.Please login");
                        ui->label_incorr_2->setVisible(true);
                    }

                    mydb.connClose();
                }else {
                    ui->label_incorr_2->setText("Please enter a valid Reference code");
                }
            }
        }
    }

}
