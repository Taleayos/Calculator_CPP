#ifndef LOGIC_MODEL_H
#define LOGIC_MODEL_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

namespace my {
/**
 *@brief Определие типа для хранения переменных вводимой строки
 *@param number - целое или вещественное число
 *@param x - переменная х
 *@param t_plus - сложение
 *@param t_minus - вычитание
 *@param t_mult - умножение
 *@param t_div - деление
 *@param t_mod - остаток от деления
 *@param t_stepen - возведение в степень
 *@param t_sin - функция синус
 *@param t_cos - функция косинус
 *@param t_tan - функция тангенс
 *@param t_acos - функция арккосинус
 *@param t_asin - функция арксинус
 *@param t_atan - функция арктангенс
 *@param t_sqrt - извленеие квадратного корня числа
 *@param t_ln - расчет натурального логорифма
 *@param t_log - расчет десятичного логорифма
 *@param sk_open - открывающаяся скобка
 *@param sk_close - закрывающаяся скобка
 */
enum oper_type {
  // priority = 0;
  number = 1,
  x = 2,
  // priority = 1;
  t_plus = 3,
  t_minus = 4,
  // priority = 2;
  t_mult = 5,
  t_div = 6,
  t_mod = 7,
  // priority = 3;
  t_stepen = 8,
  // priority = 4;
  t_sin = 9,
  t_cos = 10,
  t_tan = 11,
  t_acos = 12,
  t_asin = 13,
  t_atan = 14,
  t_sqrt = 15,
  t_ln = 16,
  t_log = 17,
  // priority = -1;
  sk_open = 19,
  // priority = 5;
  sk_close = 20
};

/**
 *@brief Структура, хранящая переменные входящей строки
 *@param value - вещественное число - значение поступившего числа (или 0 для
 *арифметических операций и функций)
 *@param type - пит переменной
 *@param priority - приоретет при проведении расчетов в инфиксной нотации
 */

struct ParcVal {
  double value;
  oper_type type;
  int priority;
};

/**
 *@brief Структура, оределяющая тип выплат по кредиту. Используется для
 *произведения расчетов в режиме Credit
 *@param annuitet - аннуитетный платеж по кредиту (тип выплат, при котором
 *заемщик каждый месяц перечисляете банку одну и ту же сумму)
 *@param differnc - дифференцированный платеж по кредиту (заемщик каждый месяц
 *вносит фиксированную сумму в счет погашения основного долга плюс сверх нее
 *оплачивает проценты_
 */

enum type_credit { annuitet, differnc };

/**
 *@brief Структура, оределяющая единицы измерения срока кредита
 *@param month - в месяцах
 *@param year - в годах
 */

enum type_term { month, year };

/**
 *@brief Структура, оределяющая периодичность выплат процентов по вкладу
 *@param dayly - ежедневная выплата процентов по вкладу
 *@param weekly - еженедельная выплата процентов по вкладу
 *@param monthly - ежемесячная выплата процентов по вкладу
 *@param quartery - ежеквартальная выплата процентов по вкладу
 *@param half_yearly - выплата процентов раз в пол-года
 *@param yearly - ежегодная выплата процентов по вкладу
 *@param at_the_end -  выплата процентов производится в конце срока кредита
 */

enum type_periodisity {
  dayly,
  weekly,
  monthly,
  quartery,
  half_yearly,
  yearly,
  at_the_end
};

/**
 *@brief Структура, возвращающая данные о платежах по кредиту
 *@param month_pay_max - максимальное значение платежа по кредиту
 *@param month_pay_min - минимальное значение платежа по кредиту
 *@param over_pay - сумма переплаты по кредиту
 *@param sum_pay - сумма уплаченного кредита с учетом процентов
 */

struct CrCalc {
  double month_pay_max;
  double month_pay_min;
  double over_pay;
  double sum_pay;
};

/**
 *@brief Структура, возвращающая данные о начислении процентов, уплате налога
 *@param procent - начисленные проценты по вкладу
 *@param tax -  сумма уплаченного налога
 *@param sum - сумма на вкладе к концу срока
 */

struct DepCalc {
  double procent;
  double tax;
  double sum;
};

/**
 *@brief Класс модель, содержащую в себе бизнес-логику, представление - форму
 *пользовательского интерфейса для осуществления взаимодействия с программой
 */

class Model {
 public:
  /**
   *@brief Функция для проверки введенного выражения на валидность
   *@param str строка, хранящая введенное выражение
   */
  bool ValidCheck(std::string &str);
  /**
   *@brief Функция, производящая расчет арифметического выражения в инфиксной
   *нотации
   *@param str строка, хранящая введенное выражение
   */
  double PolishNotation(std::string &str);
  /**
   *@brief Функция производит арифметические выражения
   */
  void MathCount();
  /**
   *@brief Функция возвращает вещественное число - результат вычисления
   *арифметического выражения
   *@param str строка, хранящая введенное выражение
   */
  double ReturnValue(std::string &str) const;
  /**
   *@brief Функция проверяет явлениется ли элемент сроки целым числом
   *@param а элемент строки
   */
  bool IsNumber(char a);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки арифметическим
   *операндом
   *@param а элемент строки
   */
  int IsOperator(char a);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией
   *@param а элемент строки
   */
  bool IsFunction(char a);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией синус
   *@param str элементы строки
   */
  bool IsSin(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией косинус
   *@param str элементы строки
   */
  bool IsCos(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией тангенс
   *@param str элементы строки
   */
  bool IsTan(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией арксинус,
   *арккосинус или арктангенс
   *@param str элементы строки
   */
  int IsArc(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией извленечия
   *квадратного корня числа
   *@param str элементы строки
   */
  bool IsSqrt(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией десятичного
   *логорифма
   *@param str элементы строки
   */
  bool IsLog(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией натурального
   *логорияма
   *@param str элементы строки
   */
  bool IsLn(char *str);
  /**
   *@brief Функция проверяет явлениется ли элемент сроки функцией нахождения
   *остатка от деления
   *@param str элементы строки
   */
  bool IsMod(char *str);
  /**
   *@brief Функция проверяет приоритет арифметической операции или функции
   *@param value тип переменной
   */
  int CheckPriority(oper_type value);
  /**
   *@brief Функция устанавливает значение приватного поля x_value_
   *@param value вещественное число - значение поля х
   */
  void SetX(const double value);
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
  CrCalc CreditCalc(double sum, int month_year, double procent,
                    type_credit type, type_term t);
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
  DepCalc DepositCalc(double sum, int month, type_term type, double pr_rate,
                      double tax_rate, type_periodisity t_p,
                      int capitalisation);
  /**
   *@brief Функция для валидации знаяений "+" и "-"
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_point указатель на флаг для отслеживания количества введенных
   *"."
   *@param i указатель на счетчик символа строки
   */
  void MPCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
               size_t &i);
  /**
   *@brief Функция для валидации арифметических операций
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_point указатель на флаг для отслеживания количества введенных
   *"."
   *@param i указатель на счетчик символа строки
   */
  void OperCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
                 size_t &i);
  /**
   *@brief Функция для валидации количества  "."  в вещественном числе
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_point указатель на флаг для отслеживания количества введенных
   *"."
   *@param i указатель на счетчик символа строки
   */
  void DotCheck(char &ptr_ch, std::string &str, int &res, int &flag_point,
                size_t &i);
  /**
   *@brief Функция для валидации арифметических функций
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_bracket указатель на флаг для отслеживания количества введенных
   *"()"
   *@param i указатель на счетчик символа строки
   */
  void FunkCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                 int &flag_bracket);
  /**
   *@brief Функция для валидации  функци mod (остаток от деления)
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param i указатель на счетчик символа строки
   */
  void ModCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                int &flag_point);
  /**
   *@brief Функция для валидации открывающихся скобок
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_bracket указатель на флаг для отслеживания количества введенных
   *"()"
   *@param i указатель на счетчик символа строки
   */
  void OpenBrackCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                      int &flag_bracket);
  /**
   *@brief Функция для валидации закрывающихся скобок
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param flag_bracket указатель на флаг для отслеживания количества введенных
   *"()"
   *@param i указатель на счетчик символа строки
   */
  void CloseBrackCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                       int &flag_bracket, int &flag_point);
  /**
   *@brief Функция для валидации чисел, записанных в экспоненциальной записи
   *@param ptr_ch указатель на предыдущую строку
   *@param str указатель на строку для валидации
   *@param res указатель на переменную, возвращаюую результат валидации
   *@param i указатель на счетчик символа строки
   */
  void ECheck(char &ptr_ch, std::string &str, int &res, size_t &i);
  /**
   *@brief Функция для добавления в стэк функций
   *@param ch указатель на текущий символ
   *@param str указатель на строку для для парсинга
   */
  void PushFunc(char &ch, std::stringstream &sstr);
  /**
   *@brief Функция для добавления в стэк арифлетических операций
   *@param ch указатель на текущий символ
   *@param str указатель на строку для для парсинга
   */
  void PushOper(char &ch, std::stringstream &sstr);
  /**
   *@brief Функция для проверки поступающего значения Х
   *@param str указатель на строку для для парсинга
   */
  bool XValidation(std::string &str);

 private:
  std::stack<ParcVal> operStack_;
  std::stack<ParcVal> numberStack_;
  double x_value_;

};  // class Model;
}  // namespace my

#endif /* LOGIC_MODEL_H */
