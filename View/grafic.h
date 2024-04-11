#ifndef GRAFIC_H
#define GRAFIC_H

#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QVector>

#include "../Logic/Controller.h"

/**
 *@brief Отрисовка графика функций
 */
namespace Ui {
class Grafic;
}

class Grafic : public QMainWindow {
  Q_OBJECT

 public:
  explicit Grafic(s21::Controller *c);
  ~Grafic();

 private slots:
  void on_Print_graf_clicked();
  void TakeStr(const QString &text);

 private:
  Ui::Grafic *ui;
  my::Controller *controller;
  double xBegin, xEnd, yBegin, yEnd, h, X, check;
  int N;

  QVector<double> x, y;
};

// public slots:
//     void mySlot(const QString &text);

#endif  // GRAFIC_H
