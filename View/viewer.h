#ifndef VIEWER_H
#define VIEWER_H

#include <credit.h>
#include <grafic.h>
#include <deposit.h>

#include <QDialog>
#include <QMainWindow>
#include <QString>

#include "../Logic/Controller.h"

QT_BEGIN_NAMESPACE
/**
 *@brief Пространство имен Ui::
 */
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
    Viewer(my::Controller *c);
  ~Viewer();

 private:
  Ui::Viewer *ui;
  Grafic *sWindow;
  my::Controller *controller;

 private slots:
  void digit_numbers();
  void digit_numbers_x();
  void digit_numbers_div();

 private slots:
  void digit_numbers_func();

 private slots:
  void digit_sqrt();
  void on_pushButton_AC_clicked();
  void on_pushButton_res_clicked();
  void on_pushButton_grafic_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();



signals:
  void take_text(const QString &text);
  void sig_set_text(QString);
};
#endif  // VIEWER_H
