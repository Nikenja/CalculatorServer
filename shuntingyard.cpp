#include "shuntingyard.h"
#include <QStack>

ShuntingYard::ShuntingYard(){}

QStringList ShuntingYard::getReversePolishNotation(const QString &expression){
    bool previousIsOperation = false;
    QStringList expressionInPolish;
    QStack<QChar> operatorsFromExpression;
    int seek = 0;
    QString number("");
    if(expression[0] == '-'){
        number.append(expression[0]);
        seek+=1;
    }
    for(auto pToken = expression.begin() + seek; pToken != expression.end(); ++pToken){
        if(pToken->isDigit() || *pToken == '.'){
            number.append(*pToken);
            previousIsOperation = false;
        }
        else{
            if(previousIsOperation){
                number.append(*pToken);
                continue;
            }
            expressionInPolish.push_back(number);
            number = "";
            previousIsOperation = true;
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
