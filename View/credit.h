#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QMainWindow>
#include <QString>

#include "../Logic/Controller.h"
/**
 *@brief Кредитный калькулятор (расчет выплат по основному долгу и процентов)
 */
namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(s21::Controller *c);
  ~Credit();

 private slots:

  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
  my::Controller *controller;
};

#endif  // CREDIT_H
