#include "reversepolishnotationevaluator.h"

ReversePolishNotationEvaluator::ReversePolishNotationEvaluator(){}

QString ReversePolishNotationEvaluator::calculate(QStringList reversePolishNotation){
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

bool ReversePolishNotationEvaluator::isOperator(const QString &op){
    QString operators("+-*/");
    if(operators.contains(op))
        return true;
    return false;
}

QString ReversePolishNotationEvaluator::calculateBinaryExpression(double operand1, double operand2, const QString &op){
    if(op == "+")
        return QString().setNum(operand1 + operand2);
    if(op == "-")
        return QString().setNum(operand1 - operand2);
    if(op == "*")
        return QString().setNum(operand1 * operand2);
    if(op == "/"){
        if(operand2 == 0.0)
            throw ReversePolishNotationEvaluatorDivByZero();
        return QString().setNum(operand1/operand2);
    }
    throw ReversePolishNotationEvaluatorUnknowOperator();
}
