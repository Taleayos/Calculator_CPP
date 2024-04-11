#include "credit.h"
#include "ui_credit.h"

Credit::Credit(my::Controller *c) :
    QDialog(nullptr),
    ui(new Ui::Credit),
    controller(c)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_pushButton_clicked()
{
    my::type_term t = my::year;
    int time_t = ui->time_2->currentIndex();
    if (time_t == 0) {
       t = my::year;
    } else if (time_t == 1) {
       t = my::month;
    }

    my::type_credit type = my::annuitet;

    double sum = ui->sum_1->text().toDouble();

    int year = ui->time_1->text().toInt();

    double procent = ui->proc_2->text().toDouble();

    if (ui->type_a->isChecked()) {
        type = my::annuitet;
    }
    if (ui->type_d->isChecked()) {
        type = my::differnc;
    }
    if (sum > 0 && (t == my::year ? year <= 50 : year <= 600) && year > 0 && procent >= 0.01 && procent <= 999) {
    my::CrCalc result;
    result = controller->CreditCalculate(sum, year, procent, type, t);

    ui->min->setText(QString().setNum(result.month_pay_min, 'f', 2));
    ui->tochki->setText(" ...");
    ui->max->setText(QString().setNum(result.month_pay_max, 'f', 2));
    ui->proc_nachisl->setText(QString().setNum(result.over_pay, 'f', 2));
    ui->proc_dolg->setText(QString().setNum(result.sum_pay, 'f', 2));
    } else {
        ui->min->setText("INCORRECT INPUT");
        ui->max->clear();
        ui->tochki->clear();
        ui->proc_nachisl->clear();
        ui->proc_dolg->clear();
    }
}



