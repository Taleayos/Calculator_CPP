#include "grafic.h"
#include "ui_grafic.h"


Grafic::Grafic(my::Controller *c) :
    QMainWindow(nullptr),
    ui(new Ui::Grafic),
    controller(c)
{
    ui->setupUi(this);

}

Grafic::~Grafic()
{
    delete ui;
}

void Grafic::TakeStr(const QString &text)
{
    QString str_take = text;
    ui->Text_from_calc->setText(str_take);
}

void Grafic::on_Print_graf_clicked() {

  double xBegin = ui->xBegin->text().toDouble();
  double yBegin = ui->yBegin->text().toDouble();
  double xEnd = ui->xEnd->text().toDouble();
  double yEnd = ui->yEnd->text().toDouble();

  QByteArray by = ui->Text_from_calc->text().toLocal8Bit();
  std::string str = by.data();
  if (str.rfind('x') == 0 || !controller->Valid(str)) {
      ui->Text_from_calc->setText("INCORRECT INPUT");
  } else
  {
    h = abs(xEnd - xBegin) / 1000.0;
    xEnd += h;
    x.clear();
    y.clear();
    double z = xBegin;
    while (z <= xEnd) {
        check = controller->Calculate(str, z);
        x.push_back(z);
        y.push_back(check);
        z += h;
    }
    ui->Qwt_Widget->xAxis->setRange(xBegin, xEnd);
    ui->Qwt_Widget->yAxis->setRange(yBegin, yEnd);
    ui->Qwt_Widget->addGraph();
    ui->Qwt_Widget->setNotAntialiasedElements(QCP::aeAll);
  ui->Qwt_Widget->graph(0)->setAdaptiveSampling(false);
  ui->Qwt_Widget->graph(0)->setData(x, y);
  ui->Qwt_Widget->replot();
  }
}

