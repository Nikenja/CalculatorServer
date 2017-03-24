#include "calculator.h"

#include <QChar>
#include <QVector>
#include <QStack>
#include <QStringList>

#include <QDebug>

Calculator::Calculator(){}

//TODO проверка выражения, это можено в другом классе

QString Calculator::calculateExression(const QString &expression){
    if(expression.isEmpty())
        return QString("Пусто");
    try{
        return calculate(shuntingYard(expression));
    }
    catch(CalculatorDivByZero &exception){
        return QString(exception.what());
    }
    catch(CalculatorUnknowOperator &exception){
        return QString(exception.what());
    }
}

QStringList Calculator::shuntingYard(const QString &expression){
    bool previouslyIsOperation = false;
    QStringList expressionInPolish;
    QStack<QChar> operatorsFromExpression;
    int seek = 0;
    QString number("");
    if(expression[0] == '-'){
        number.append(expression[0]);
        seek+=1;
    }
    for(auto pToken = expression.begin() + seek; pToken != expression.end(); ++pToken){
        if(pToken->isDigit()){
            number.append(*pToken);
            previouslyIsOperation = false;
        }
        else{
            if(previouslyIsOperation){
                number.append(*pToken);
                continue;
            }
            expressionInPolish.push_back(number);
            number = "";
            previouslyIsOperation = true;
            if(*pToken == '+' || *pToken == '-'){
                if(!operatorsFromExpression.isEmpty() && (operatorsFromExpression.back() == '*' || operatorsFromExpression.back() == '/'))
                    while(!operatorsFromExpression.isEmpty())
                        expressionInPolish.push_back(operatorsFromExpression.pop());
                operatorsFromExpression.push(*pToken);
            }
            else
                operatorsFromExpression.push(*pToken);
        }

    }
    expressionInPolish.push_back(number);
    while(!operatorsFromExpression.isEmpty())
        expressionInPolish.push_back(operatorsFromExpression.pop());
    return expressionInPolish;
}

QString Calculator::calculate(QStringList reversePolishNotation){
    while(reversePolishNotation.size() != 1){
        QStringList::iterator pToken = reversePolishNotation.begin();
        while (pToken != reversePolishNotation.end()) {
            if(isOperator(*pToken)){
                (*(pToken - 2)) = calculateBinaryExpression((*(pToken - 2)).toDouble(),(*(pToken - 1)).toDouble(),*pToken);
                pToken = reversePolishNotation.erase(pToken-1);
                pToken = reversePolishNotation.erase(pToken);
                pToken = pToken - 1;
            }
            ++pToken;
        }
    }
    return reversePolishNotation.front();
}

bool Calculator::isOperator(const QString &op){
    QString operators("+-*/");
    if(operators.contains(op))
        return true;
    return false;
}

QString Calculator::calculateBinaryExpression(double operand1, double operand2, const QString &operation){
    if(operation == "+")
        return QString().setNum(operand1 + operand2);
    if(operation == "-")
        return QString().setNum(operand1 - operand2);
    if(operation == "*")
        return QString().setNum(operand1 * operand2);
    if(operation == "/"){
        if(operand2 == 0.0)
            throw CalculatorDivByZero();
        return QString().setNum(operand1/operand2);
    }
    throw CalculatorUnknowOperator();
}
