#include "calculator.h"

#include <QChar>
#include <QVector>
#include <QStack>
#include <QStringList>
#include "shuntingyard.h"
#include "reversepolishnotationevaluator.h"

Calculator::Calculator(){}

QString Calculator::calculateExression(const QString &expression){
    if(expression.isEmpty())
        return QString("Пусто");
    try{
        ShuntingYard shuntingYard;
        ReversePolishNotationEvaluator rPolishEvaluator;
        return rPolishEvaluator.calculate(shuntingYard.getReversePolishNotation(expression));
    }
    catch(ReversePolishNotationEvaluatorDivByZero &exception){
        return QString(exception.what());
    }
    catch(ReversePolishNotationEvaluatorUnknowOperator &exception){
        return QString(exception.what());
    }
}
