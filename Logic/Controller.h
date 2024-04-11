#ifndef LOGIC_CONTROLLER_H
#define LOGIC_CONTROLLER_H

#include "model.h"

/**
 *@brief Пространство имен s21::
 */
namespace my {
/**
 *@brief Класс контроллер, осуществляющий модификацию модели по действию
 *пользователя.
 */
class Controller {
 public:
  /**
   *@brief Конструкор, инициализирующий private поле класса Контроллер
   *@param m указатель на объект класса Model
   */
  Controller(Model *m) : model_(m){};
  /**
   *@brief Функция для проверки введенного выражения на валидность
   *@param str указатель на строку, хранящую введенное выражение
   */
  bool Valid(std::string &str) { return model_->ValidCheck(str); };
  /**
   *@brief Функция возвращает вещественное число - результат вычисления
   *арифметического выражения
   *@param str указатель на строку, хранящую введенное выражение
   */
  double Calculate(std::string &str, double x_value) {
    model_->SetX(x_value);
    return model_->ReturnValue(str);
  };
  /**
   *@brief Функция для проведения расчетов в режиме Credit (Кредитный
   *калькулятор)
   *@param sum сумма кредита
   *@param month_year срок кредита
   *@param procent рамер процентной ставки по кредиту
   *@param type тип начсления процентов по кредиту. Аннуитетный платеж  - тип
   *выплат, при котором заемщик каждый месяц перечисляете банку одну и ту же
   *сумму, дифференцированный платеж  - заемщик каждый месяц вносит
   *фиксированную сумму в счет погашения основного долга плюс сверх нее
   *оплачивает проценты.
   * @param t определение срока кредита в месяцах или в годах
   */
  CrCalc CreditCalculate(double sum, int month_year, double procent,
                         type_credit type, type_term t) {
    return model_->CreditCalc(sum, month_year, procent, type, t);
  };
  /**
   *@brief Функция для проведения расчетов в режиме Deposit (Депозитный
   *калькулятор)
   *@param sum сумма депозита
   *@param month срок размещения депозита
   *@param pr_rate рамер процентной ставки по депозиту
   *@param tax_rate ставка налога
   *@param type определение срока кредита в месяцах или в годах
   *@param t_p периодичность выплат процентов по вкладу
   *@param capitalisation наличие капитализации процентов
   */
  DepCalc DepositCalculate(double sum, int month, type_term type,
                           double pr_rate, double tax_rate,
                           type_periodisity t_p, int capitalisation) {
    return model_->DepositCalc(sum, month, type, pr_rate, tax_rate, t_p,
                               capitalisation);
  }
  /**
   *@brief Функция проверяет корректность значения Х
   *@param str указатель на строку, хранящую введенное выражение
   */
  bool XValid(std::string &str) { return model_->XValidation(str); };

 private:
  Model *model_;

};  // class Controller;
}  // namespace my

#endif /* LOGIC_CONTROLLER_H */
