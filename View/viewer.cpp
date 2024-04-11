#include "viewer.h"
#include "ui_viewer.h"


Viewer::Viewer(my::Controller *c)
    : QMainWindow(nullptr), ui(new Ui::Viewer), controller(c) {
    ui->setupUi(this);
    sWindow = new Grafic(c);

ui->lineEdit->installEventFilter(this);
ui->lineEdit->setFocus();

    connect(ui->pushButton_0, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_1, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_dot, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_acos, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_asin, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_atan, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_close_sk, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_div, SIGNAL(clicked()),this,SLOT(digit_numbers_div()));
    connect(ui->pushButton_ln, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_log, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_minus, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(ui->pushButton_mod, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_mult, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_open_sk, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_tan, SIGNAL(clicked()),this,SLOT(digit_numbers_func()));
    connect(ui->pushButton_x, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()),this,SLOT(digit_sqrt()));
    connect(ui->pushButton_step, SIGNAL(clicked()),this,SLOT(digit_numbers()));
    connect(ui->pushButton_e, SIGNAL(clicked()),this,SLOT(digit_numbers_x()));
    connect(this, SIGNAL(take_text(const QString &)), sWindow, SLOT(TakeStr(const QString &)));
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::digit_numbers()
{
    if (ui->lineEdit->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    ui->lineEdit->insert(button->text());
    ui->lineEdit->setFocus();
    }
}

void Viewer::digit_numbers_x()
{
    QPushButton *button = (QPushButton *)sender();

    if (ui->lineEdit_X->hasFocus())
    {
        ui->lineEdit_X->insert(button->text());
    }
    else
    {
    ui->lineEdit->insert(button->text());
    ui->lineEdit->setFocus();
    }
}

void Viewer::digit_numbers_func()
{
    if (ui->lineEdit->hasFocus()) {
   QPushButton *button = (QPushButton *)sender();

   QString str = button->text();

   ui->lineEdit->setText(ui->lineEdit->text() += str);
   ui->lineEdit->setText(ui->lineEdit->text() += '(');
    }
}

void Viewer::digit_sqrt()
{
if (ui->lineEdit->hasFocus()) {
   QString str =  "sqrt(";

   ui->lineEdit->setText(ui->lineEdit->text() += str);
}
}
void Viewer::digit_numbers_div()
{
    ui->lineEdit->insert("/");
    ui->lineEdit->setFocus();
}

void Viewer::on_pushButton_AC_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() = NULL);
    ui->lineEdit_X->clear();
}


void Viewer::on_pushButton_res_clicked()
{
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    std::string str = ba.data();
    double x_value = 0;
    int res = 1;
    if (sizeof(ui->lineEdit_X->text()) != 0) {
            QByteArray by = ui->lineEdit_X->text().toLocal8Bit();
            std::string str_x = by.data();
            if (controller->XValid(str_x)) {
            x_value = ui->lineEdit_X->text().toDouble();
            } else {
              res = 0;
            }
        }
        if (str.size() > 0) {
        if (controller->Valid(str) && res) {
            double check = controller->Calculate(str, x_value);
            QString res = "";
            res = QString::number(check, 'g', 15);
            ui->lineEdit->setText(res);
        } else {
             ui->lineEdit->setText("INCORRECT INPUT");
        }
        }
}


void Viewer::on_pushButton_grafic_clicked()
{
    emit take_text(ui->lineEdit->text());
    sWindow->show();

}


void Viewer::on_pushButton_credit_clicked()
{
    Credit window(controller);
    window.setModal(true);
    window.exec();
}


void Viewer::on_pushButton_deposit_clicked()
{
    Deposit window(controller);
    window.setModal(true);
    window.exec();

}

