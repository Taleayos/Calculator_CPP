#include "model.h"

bool my::Model::ValidCheck(std::string &str) {
  int res = 1;
  size_t n = str.length();
  int flag_bracket = 0;
  char ptr_ch = ' ';
  int flag_point = 0;
  for (size_t i = 0; i < n && res != 0; ++i) {
    if (IsNumber(str[i]) || str[i] == 'x') {
      if (ptr_ch == ' ' || IsNumber(ptr_ch) || IsOperator(ptr_ch) > 0 ||
          ptr_ch == '(' || ptr_ch == '.' || ptr_ch == 'e') {
        ptr_ch = str[i];
        if (str[++i] == '\0' && flag_point != 0) {
          --flag_point;
        }
        --i;
      } else {
        res = 0;
      }
    } else if (str[i] == '-' || str[i] == '+') {
      MPCheck(ptr_ch, str, res, flag_point, i);
    } else if (IsOperator(str[i]) > 0) {
      OperCheck(ptr_ch, str, res, flag_point, i);
    } else if (str[i] == '.') {
      DotCheck(ptr_ch, str, res, flag_point, i);
    } else if (IsFunction(str[i]) && !(IsMod(&str[i]))) {
      FunkCheck(ptr_ch, str, res, i, flag_bracket);
    } else if (IsFunction(str[i]) && (IsMod(&str[i]))) {
      ModCheck(ptr_ch, str, res, i, flag_point);
    } else if (str[i] == '(') {
      OpenBrackCheck(ptr_ch, str, res, i, flag_bracket);
    } else if (str[i] == ')') {
      CloseBrackCheck(ptr_ch, str, res, i, flag_bracket, flag_point);
    } else if (str[i] == 'e') {
      ECheck(ptr_ch, str, res, i);
    } else if (str[i] == ' ') {
    } else {
      res = 0;
    }
  }
  if (flag_bracket != 0) {
    res = 0;
  }
  if (flag_point != 0) {
    res = 0;
  }
  return res;
}

double my::Model::PolishNotation(std::string &str) {
  std::stringstream sstr{str};
  char ch;
  double value;
  bool flagUnar = true;
  while (!sstr.eof()) {
    ch = sstr.peek();
    if (ch == ' ') {
      sstr.ignore();
      continue;
    }
    if (IsNumber(ch)) {
      sstr >> value;
      numberStack_.push({value, number, CheckPriority(number)});
      flagUnar = false;
      continue;
    }
    if (ch == 'x') {
      numberStack_.push({x_value_, number, CheckPriority(number)});
      sstr.ignore();
      continue;
    }
    if ((ch == '-' && flagUnar) || (ch == '+' && flagUnar)) {
      numberStack_.push({0, number, CheckPriority(number)});
      operStack_.push(
          {0, (ch == '-' ? t_minus : t_plus), CheckPriority(t_minus)});
      flagUnar = false;
      sstr.ignore();
      continue;
    }
    if (IsOperator(ch) > 0 || ch == 'm') {
      PushOper(ch, sstr);
      continue;
    }
    if (IsFunction(ch) && (ch != 'm')) {
      PushFunc(ch, sstr);
      continue;
    }
    if (ch == '(') {
      operStack_.push({0, sk_open, CheckPriority(sk_open)});
      sstr.ignore();
      flagUnar = true;
      continue;
    }
    if (ch == ')') {
      while (operStack_.top().type != sk_open) {
        MathCount();
      }
      operStack_.pop();
      sstr.ignore();
      continue;
    }
  }
  while (operStack_.size() != 0) {
    MathCount();
  }
  return numberStack_.top().value;
}

void my::Model::MathCount() {
  double a = 0.0, b = 0.0;
  a = numberStack_.top().value;
  numberStack_.pop();
  oper_type ot = operStack_.top().type;
  if (ot < 9 || ot == 18) {
    b = numberStack_.top().value;
    numberStack_.pop();
    if (ot == t_plus)
      b += a;
    else if (ot == t_minus)
      b -= a;
    else if (ot == t_mult)
      b *= a;
    else if (ot == t_div) {
      if (a != 0)
        b /= a;
      else
        b = NAN;
    } else if (ot == t_mod)
      b = fmod(b, a);
    else if (ot == t_stepen)
      b = pow(b, a);
  } else {
    if (ot == t_sin)
      b = sin(a);
    else if (ot == t_cos)
      b = cos(a);
    else if (ot == t_tan)
      b = tan(a);
    else if (ot == t_acos)
      b = acos(a);
    else if (ot == t_asin)
      b = asin(a);
    else if (ot == t_atan)
      b = atan(a);
    else if (ot == t_sqrt)
      b = sqrt(a);
    else if (ot == t_ln)
      b = log(a);
    else if (ot == t_log)
      b = log10(a);
  }
  operStack_.pop();
  numberStack_.push({b, number, CheckPriority(number)});
}

double my::Model::ReturnValue(std::string &str) const {
  my::Model x(*this);
  return x.PolishNotation(str);
}

bool my::Model::IsNumber(char a) { return (a >= 48 && a <= 57); }
int my::Model::IsOperator(char a) {
  int res = 0;
  switch (a) {
    case '+':
      res = 3;
      break;
    case '-':
      res = 4;
      break;
    case '*':
      res = 5;
      break;
    case '/':
      res = 6;
      break;
    case '^':
      res = 8;
      break;
  }
  return res;
}
bool my::Model::IsFunction(char a) {
  return (a == 's' || a == 'c' || a == 'm' || a == 't' || a == 'a' || a == 'l');
}

bool my::Model::IsSin(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "sin(");
}

bool my::Model::IsCos(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "cos(");
}

bool my::Model::IsTan(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "tan(");
}

int my::Model::IsArc(char *str) {
  int res = 0;
  char Ch = str[0];
  if (Ch == 'a') {
    str++;
    if (IsSin(str)) {
      res = 13;
    } else if (IsCos(str)) {
      res = 12;
    } else if (IsTan(str)) {
      res = 14;
    }
  }
  return res;
}

bool my::Model::IsSqrt(char *str) {
  return (static_cast<std::string>(str).substr(0, 5) == "sqrt(");
}

bool my::Model::IsLog(char *str) {
  return (static_cast<std::string>(str).substr(0, 4) == "log(");
}

bool my::Model::IsLn(char *str) {
  return (static_cast<std::string>(str).substr(0, 3) == "ln(");
}

bool my::Model::IsMod(char *str) {
  return (static_cast<std::string>(str).substr(0, 3) == "mod");
}

int my::Model::CheckPriority(oper_type value) {
  int res = -2;
  if (value == 19) res = -1;
  if (value == 1 || value == 2) res = 0;
  if (value == 3 || value == 4) res = 1;
  if (value >= 5 && value <= 7) res = 2;
  if (value == 8) res = 3;
  if (value >= 9 && value <= 17) res = 4;
  if (value == 20) res = 5;
  return res;
}

void my::Model::SetX(double value) { x_value_ = value; }

void my::Model::MPCheck(char &ptr_ch, std::string &str, int &res,
                         int &flag_point, size_t &i) {
  if (ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == '(' || ptr_ch == 'x' ||
      ptr_ch == ')' || ptr_ch == 'e') {
    ++i;
    if (str[i] == '\0') {
      res = 0;
    } else {
      --i;
      ptr_ch = str[i];
      if (flag_point != 0) {
        flag_point--;
      }
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::OperCheck(char &ptr_ch, std::string &str, int &res,
                           int &flag_point, size_t &i) {
  if ((ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == 'x' || ptr_ch == ')') &&
      i > 0) {
    ++i;
    if (str[i] == '\0') {
      res = 0;
    } else {
      --i;
      ptr_ch = str[i];
      if (flag_point != 0) {
        flag_point--;
      }
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::DotCheck(char &ptr_ch, std::string &str, int &res,
                          int &flag_point, size_t &i) {
  if (IsNumber(ptr_ch)) {
    if (IsNumber(str[++i])) {
      ptr_ch = str[--i];
      flag_point++;
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::FunkCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                           int &flag_bracket) {
  if (ptr_ch == ' ' || IsOperator(ptr_ch) > 0 || ptr_ch == '(') {
    if (IsCos(&str[i]) || IsSin(&str[i]) || IsTan(&str[i]) || IsLog(&str[i])) {
      ptr_ch = '(';
      i += 3;
      flag_bracket++;
    } else if (IsSqrt(&str[i]) || IsArc(&str[i])) {
      ptr_ch = '(';
      i += 4;
      flag_bracket++;
    } else if (IsLn(&str[i])) {
      ptr_ch = '(';
      i += 2;
      flag_bracket++;
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::ModCheck(char &ptr_ch, std::string &str, int &res, size_t &i,
                          int &flag_point) {
  if (IsNumber(ptr_ch) || ptr_ch == 'x') {
    if (((IsNumber(str[i + 3]) && (str[i + 3] != '0')) ||
         (str[i + 3] == ' ' && IsNumber(str[i + 4]))) ||
        ((str[i + 3] == 'x') || (str[i + 3] == ' ' && str[i + 4] == 'x'))) {
      ptr_ch = ' ';
      i += 2;
      --flag_point;
      if (flag_point != 0) {
        res = 0;
      }
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::OpenBrackCheck(char &ptr_ch, std::string &str, int &res,
                                size_t &i, int &flag_bracket) {
  if (ptr_ch == ' ' || (IsOperator(ptr_ch) > 0) || ptr_ch == '(') {
    ptr_ch = str[i];
    flag_bracket++;
  } else {
    res = 0;
  }
}

void my::Model::CloseBrackCheck(char &ptr_ch, std::string &str, int &res,
                                 size_t &i, int &flag_bracket,
                                 int &flag_point) {
  if (ptr_ch == ' ' || IsNumber(ptr_ch) || ptr_ch == 'x' || ptr_ch == ')') {
    ptr_ch = str[i];
    flag_bracket--;
    if (flag_point != 0) {
      flag_point--;
    }
    if (flag_point != 0) {
      res = 0;
    }
  } else {
    res = 0;
  }
}

void my::Model::ECheck(char &ptr_ch, std::string &str, int &res, size_t &i) {
  if ((IsNumber(ptr_ch) && IsNumber(str[i + 1])) ||
      (IsNumber(ptr_ch) && str[i + 1] == '-' && IsNumber(str[i + 2]))) {
    ptr_ch = str[i];
  } else {
    res = 0;
  }
}

void my::Model::PushOper(char &ch, std::stringstream &sstr) {
  int res = IsOperator(ch);
  if (ch == 'm') {
    res = 7;
    for (int i = 0; i < 2; ++i) {
      sstr.ignore();
    }
  }
  if (operStack_.size() == 0) {
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  } else if (operStack_.size() != 0 &&
             (CheckPriority(static_cast<oper_type>(res)) >
              operStack_.top().priority)) {
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  } else if (operStack_.size() != 0 &&
             (CheckPriority(static_cast<oper_type>(res)) <=
              operStack_.top().priority)) {
    while (operStack_.size() != 0 && (CheckPriority(static_cast<oper_type>(
                                          res)) <= operStack_.top().priority)) {
      MathCount();
    }
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
    sstr.ignore();
  }
}

void my::Model::PushFunc(char &ch, std::stringstream &sstr) {
  int i = 0;
  char tmp[5] = {'\0'};
  for (i = 0; i < 5 && ch != '('; ++i) {
    ch = sstr.peek();
    tmp[i] = ch;
    if (ch != '(') sstr.ignore();
  }
  if (IsLn(tmp)) {
    operStack_.push({0, t_ln, CheckPriority(t_ln)});
  }
  if (IsSin(tmp)) {
    operStack_.push({0, t_sin, CheckPriority(t_sin)});
  }
  if (IsCos(tmp)) {
    operStack_.push({0, t_cos, CheckPriority(t_cos)});
  }
  if (IsTan(tmp)) {
    operStack_.push({0, t_tan, CheckPriority(t_tan)});
  }
  if (IsArc(tmp) > 0) {
    int res = IsArc(tmp);
    operStack_.push({0, static_cast<oper_type>(res),
                     CheckPriority(static_cast<oper_type>(res))});
  }
  if (IsSqrt(tmp)) {
    operStack_.push({0, t_sqrt, CheckPriority(t_sqrt)});
  }
  if (IsLog(tmp)) {
    operStack_.push({0, t_log, CheckPriority(t_log)});
  }
}

my::CrCalc my::Model::CreditCalc(double sum, int month_year, double procent,
                                   type_credit type, type_term t) {
  if (t == 1) {
    month_year *= 12;
  }
  CrCalc result = {0, 0, 0, 0};
  if (type == annuitet) {
    result.month_pay_min =
        sum *
        (((procent / 100 / 12) * pow((1 + (procent / 100 / 12)), month_year)) /
         (pow(1 + ((procent / 100 / 12)), month_year) - 1));
    result.over_pay = (month_year * result.month_pay_min) - sum;
    result.sum_pay = sum + result.over_pay;
    result.month_pay_max = result.month_pay_min;
  } else if (type == differnc) {
    double sum_tmp = sum;
    for (int i = month_year; i > 0; --i) {
      result.month_pay_max = (sum / i) + (sum * (procent / 100 / 12));
      if (i == month_year) {
        result.month_pay_min = result.month_pay_max;
      }
      result.sum_pay += result.month_pay_max;
      sum -= sum_tmp / (month_year);
    }
    result.over_pay = result.sum_pay - sum_tmp;
  }
  return result;
}

my::DepCalc my::Model::DepositCalc(double sum, int monthD, type_term type,
                                     double pr_rate, double tax_rate,
                                     type_periodisity t_p, int capitalisation) {
  DepCalc res = {0, 0, 0};
  double so = 1000000 * (7.50 / 100);
  double procent_tmp = 0;
  int d = 0;
  if (type == 1) {
    monthD *= 12;
  }
  double days = monthD * 30.41666666;
  if (capitalisation == 0) {
    res.procent = sum * ((pr_rate / 12 / 100) * monthD);
    res.sum = sum;
  }
  if (capitalisation == 1) {
    if (t_p == 0) {
      d = 365;
    } else if (t_p == 1) {
      days /= 7;
      d = 52;
    } else if (t_p == 2) {
      days = monthD;
      d = 12;
    } else if (t_p == 3) {
      days = monthD / 3;
      d = 4;
    } else if (t_p == 4) {
      days = monthD / 6;
      d = 2;
    } else if (t_p == 5 && monthD > 11) {
      days = monthD / 12;
      d = 1;
    } else if (t_p == 6 || monthD < 12) {
      res = DepositCalc(sum, monthD, month, pr_rate, tax_rate, t_p, 0);
      res.sum = res.procent + sum;
      return res;
    }
    for (int i = 0; i < days; i++) {
      procent_tmp = sum * (pr_rate / 100 / d);
      res.procent += procent_tmp;
      sum += procent_tmp;
    }
    res.sum = sum;
  }
  double tmp = res.procent;
  double s = (double)monthD / 12;
  double ex_tax = so * s;
  if (tmp > ex_tax) {
    res.tax = (res.procent - ex_tax) * (tax_rate / 100);
  } else {
    res.tax = 0;
  }
  return res;
}

bool my::Model::XValidation(std::string &str) {
  int res = 1;
  int flag_point = 0;
  int flag_oper = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '.') ++flag_point;
    if (IsOperator(str[i])) ++flag_oper;
  }
  if (flag_oper > 1 || flag_point > 1) res = 0;
  return res;
}
