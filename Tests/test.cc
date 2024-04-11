#include <gtest/gtest.h>

#include "../Logic/Controller.h"
#include "../Logic/model.h"

my::Model model;
my::Controller control(&model);

TEST(valid_error_1, test_1) {
  std::string str = "cos(sin(tan(asin(acos(atan)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_2, test_2) {
  std::string str = "32+12-(18.6-)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_3, test_3) {
  std::string str = "32/(12*(18.6-)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_4, test_4) {
  std::string str = "mod3ln";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_5, test_5) {
  std::string str = "127-a+cis(son(lg(laq(acus(2)))))";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_6, test_6) {
  std::string str = "x.123z*aspo(2)/sqrt(/)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_7, test_7) {
  std::string str = "ln(-3) * 3 mod 2 )";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_8, test_8) {
  std::string str = "25+$3-c0s(@-4)/";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_9, test_9) {
  std::string str = "13$(^mod5*!/(&+5)18";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_10, test_10) {
  std::string str = "37/";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_11, test_11) {
  std::string str = "37+";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_12, test_12) {
  std::string str = "(2+3)x";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_13, test_13) {
  std::string str = "80*+13";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_14, test_14) {
  std::string str = "sin(3) + * 4";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_15, test_15) {
  std::string str = "3sin(3)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_16, test_16) {
  std::string str = "18(4-89)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_17, test_17) {
  std::string str = "sin(3)+3mod";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_18, test_18) {
  std::string str = "123.123.123 + 1";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_19, test_19) {
  std::string str = "123.123.123 * 1";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_20, test_20) {
  std::string str = "(x+2.123.2)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_21, test_47) {
  std::string str = "sin(2mod3)+e-12";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_22, test_48) {
  std::string str = "sin(.1)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_23, test_49) {
  std::string str = "sqrt(cos(x + 2.)) * 3mod2.1223";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_24, test_50) {
  std::string str = "sqrt(cos(x + 2.0)) * 3mod2.1223";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_25, test_51) {
  std::string str = "(1/4e)*(4^3-2^5)+(1/2)^(-2)*(-2)";
  bool res = control.Valid(str);
  EXPECT_FALSE(res);
}

TEST(valid_error_26, test_52) {
  std::string str = "13e-1 * sin(2) - 1.87";
  bool res = control.Valid(str);
  EXPECT_TRUE(res);
}

TEST(valid_error_27, test_53) {
  std::string str = "-0.23-8";
  bool res = control.XValid(str);
  EXPECT_FALSE(res);
}

TEST(calc_1, test_21) {
  std::string str = "10+sin(cos(log(5+1)))";
  double count = 10.653510057399632;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_2, test_22) {
  std::string str = "((3^2 - 2^3)^2)";
  double count = 1;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_3, test_23) {
  std::string str = "((2^3 - 3^2)^77) / 7^(-1)";
  double count = -7;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_4, test_24) {
  std::string str = "0.8^0*(3^3+5^5)^0+(1/5)^(-1)";
  double count = 6;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_5, test_25) {
  std::string str = "(1/4)*(4^3-2^5)+(1/2)^(-2)*(-2)";
  double count = 0;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_6, test_26) {
  std::string str = "-5.8734/12+(0.000076*sqrt(0.99)-9mod3)";
  double count = -0.4893743809547799;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_7, test_27) {
  std::string str = "sin(cos(log(3^2 - 2^3)))";
  double count = 0.8414709848078965;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_8, test_28) {
  std::string str = "atan(0.678456)";
  double count = 0.59612010125075288;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_9, test_29) {
  std::string str = "asin(0.678456)";
  double count = 0.745658882754721;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_10, test_30) {
  std::string str = "acos(0.0331)";
  double count = 1.5376902796978882;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_11, test_31) {
  std::string str = "-tan(sqrt(9))";
  double count = 0.1425465430742778;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_12, test_32) {
  std::string str = "5mod2*ln(sqrt(2.9-0.13))+(-1.987)";
  double count = -1.4775763399003764;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_13, test_33) {
  std::string str = "-sqrt(9)/((1/4)*(4^3-2^5)+(1/2)^(-2)*(-2))";
  double res = control.Calculate(str, 0);
  EXPECT_TRUE(std::isnan(res));
}

TEST(calc_14, test_34) {
  std::string str = "sin(x)";
  double count = -0.8414709848078965;
  double res = control.Calculate(str, -1);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(calc_14, test_46) {
  std::string str = "18+(2e-1)";
  double count = 18.2;
  double res = control.Calculate(str, 0);
  EXPECT_DOUBLE_EQ(res, count);
}

TEST(credit_1, test_35) {
  double sum = 1000000;
  int year = 2;
  double procent = 13;
  my::CrCalc res =
      control.CreditCalculate(sum, year, procent, my::annuitet, my::year);
  double m_pay = 47541.82;
  double o_pay = 141003.68;
  double s_pay = 1141003.68;
  EXPECT_NEAR(res.month_pay_max, m_pay, 2);
  EXPECT_NEAR(res.over_pay, o_pay, 2);
  EXPECT_NEAR(res.sum_pay, s_pay, 2);
}

TEST(credit_2, test_36) {
  double sum = 150000;
  int year = 9;
  double procent = 13;
  my::CrCalc res =
      control.CreditCalculate(sum, year, procent, my::differnc, my::month);
  double m_pay = 16847.22;
  double o_pay = 8125.00;
  double s_pay = 158125.00;
  EXPECT_NEAR(res.month_pay_max, m_pay, 2);
  EXPECT_NEAR(res.over_pay, o_pay, 2);
  EXPECT_NEAR(res.sum_pay, s_pay, 2);
}

TEST(deposit_1, test_37) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::dayly;
  int capitalisation = 0;
  double r_procent = 200000;
  double r_tax = 6500;
  double r_sum = 1000000;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_2, test_38) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::dayly;
  int capitalisation = 1;
  double r_procent = 221369.301640;
  double r_tax = 9278.009213;
  double r_sum = 1221369.301640;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_3, test_39) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::weekly;
  int capitalisation = 1;
  double r_procent = 223516.596619;
  double r_tax = 9557.157560;
  double r_sum = 1223516.596619;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_4, test_40) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::monthly;
  int capitalisation = 1;
  double r_procent = 220390.961376;
  double r_tax = 9150.824979;
  double r_sum = 1220390.961376;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_5, test_41) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::quartery;
  int capitalisation = 1;
  double r_procent = 218402.897510;
  double r_tax = 8892.376676;
  double r_sum = 1218402.897510;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_6, test_42) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::half_yearly;
  int capitalisation = 1;
  double r_procent = 215506.250000;
  double r_tax = 8515.812500;
  double r_sum = 1215506.250000;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_7, test_43) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::yearly;
  int capitalisation = 1;
  double r_procent = 210000;
  double r_tax = 7800;
  double r_sum = 1210000;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_8, test_44) {
  double sum = 1000000;
  int month = 2;
  my::type_term type = my::year;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::at_the_end;
  int capitalisation = 1;
  double r_procent = 200000;
  double r_tax = 6500;
  double r_sum = 1200000;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

TEST(deposit_9, test_45) {
  double sum = 150000;
  int month = 4;
  my::type_term type = my::month;
  double pr_rate = 10;
  double tax_rate = 13;
  my::type_periodisity t_p = my::weekly;
  int capitalisation = 1;
  double r_procent = 5278.058770;
  double r_tax = 0;
  double r_sum = 155278.058770;
  my::DepCalc res = control.DepositCalculate(sum, month, type, pr_rate,
                                              tax_rate, t_p, capitalisation);
  EXPECT_NEAR(res.procent, r_procent, 2);
  EXPECT_NEAR(res.tax, r_tax, 2);
  EXPECT_NEAR(res.sum, r_sum, 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
