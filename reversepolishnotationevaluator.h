#ifndef REVERSEPOLISHNOTATIONEVALUATOR_H
#define REVERSEPOLISHNOTATIONEVALUATOR_H

#include <QString>
#include <QStringList>

class ReversePolishNotationEvaluator{
public:
    ReversePolishNotationEvaluator();
    QString calculate(QStringList reversePolishNotation);
private:
    bool isOperator(const QString &op);
    QString calculateBinaryExpression(double operand1, double operand2, const QString &op);
};

class ReversePolishNotationEvaluatorDivByZero : public std::exception{
public:
    const char *what(){return "Div by zero";}
};

class ReversePolishNotationEvaluatorUnknowOperator : public std::exception{
public:
    const char *what(){return "Unknow operator";}
};

#endif // REVERSEPOLISHNOTATIONEVALUATOR_H
