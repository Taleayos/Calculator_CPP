#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(my::Controller *c) :
    QDialog(nullptr),
    ui(new Ui::Deposit),
    controller(c)
{
    ui->setupUi(this);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::on_pushButton_clicked()
{
    my::DepCalc res = {0, 0, 0};
    my::type_term t = my::month;
    int time_t = ui->time_2->currentIndex();

    if (time_t == 0) {
       t = my::year;
    } else if (time_t == 1) {
       t = my::month;
    }

    double sum = ui->sum_1->text().toDouble();

    int year = ui->time_1->text().toInt();

    double pr_rate = ui->proc_2->text().toDouble();

    double tax_rate = ui->proc_nalog_2->text().toDouble();

    my::type_periodisity t_p = my::at_the_end;
    int period = ui->comboBox->currentIndex();
    switch (period) {
    case 0 : t_p = my::dayly; break;
    case 1 : t_p = my::weekly; break;
    case 2 : t_p = my::monthly; break;
    case 3 : t_p = my::quartery; break;
    case 4 : t_p = my::half_yearly; break;
    case 5 : t_p = my::yearly; break;
    default : t_p = my::at_the_end;
    }

    int capitalisation = 0;
    if (ui->capital->isChecked()) {
        capitalisation = 1;
    }

    res = controller->DepositCalculate(sum, year, t, pr_rate, tax_rate, t_p,capitalisation);

    ui->res_proc_1->setText(QString().setNum(res.procent, 'f', 2));
    ui->sum_nalog_1->setText(QString().setNum(res.tax, 'f', 2));
    ui->sum_itog->setText(QString().setNum(res.sum, 'f', 2));
}

