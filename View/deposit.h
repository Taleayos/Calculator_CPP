#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>
#include <QMainWindow>
#include <QString>

#include "../Logic/Controller.h"

/**
 *@brief Депозитный калькулятор (расчет процентов по вкладу, расчет налога)
 */
namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(s21::Controller *c);
  ~Deposit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Deposit *ui;
  my::Controller *controller;
};

#endif  // DEPOSIT_H
