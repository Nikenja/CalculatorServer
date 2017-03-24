#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <QStringList>
#include <exception>

class Calculator{
public:
    Calculator();
    QString calculateExression(const QString &expression);
private:
    QStringList shuntingYard(const QString &expression);
    QString calculate(QStringList reversePolishNotation);
    bool isOperator(const QString &op);
    QString calculateBinaryExpression(double operand1, double operand2, const QString &operation);
};

class CalculatorDivByZero : public std::exception{
public:
    const char *what(){return "Деление на ноль";}
};

class CalculatorUnknowOperator : public std::exception{
public:
    const char *what(){return "Неизвестный оператор";}
};

#endif // CALCULATOR_H
