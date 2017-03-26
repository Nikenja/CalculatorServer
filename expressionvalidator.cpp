#include "expressionvalidator.h"

ExpressionValidator::ExpressionValidator(){}

bool ExpressionValidator::isCorrectExpression(const QString &expression){
    bool isPreviousOperator = false;
    bool isPreviousDigit = false;
    bool isPreviousDot = false;
    int tokenIndex = 0;

    if(expression.isEmpty())
        return false;
    if(isOperator(expression[0])){
        if(isMinus(expression[0])){
            isPreviousOperator = true;
            tokenIndex = 1;
        }
        else
            return false;
    }
    for(; tokenIndex < expression.size(); ++tokenIndex){
        if(expression[tokenIndex].isDigit())
            if(isValidDigitPosition(tokenIndex, isPreviousDigit, isPreviousOperator, isPreviousDot))
                continue;
        if(isOperator(expression[tokenIndex])){
            if(isMinus(expression[tokenIndex])){
                if(isValidMinusOperatorPosition(tokenIndex, isPreviousDigit, isPreviousOperator, isPreviousDot))
                    continue;
            }
            else
                if(isValidOperatorPosition(tokenIndex, isPreviousDigit, isPreviousOperator, isPreviousDot))
                    continue;
        }
        if(isDot(expression[tokenIndex]))
            if(isValidDotPosition(tokenIndex, isPreviousDigit, isPreviousOperator, isPreviousDot))
                continue;
        return false;
    }
    return isPreviousDigit;
}

bool ExpressionValidator::isDot(const QChar &token){
    return token == '.';
}

bool ExpressionValidator::isOperator(const QChar &token){
    QString operators("+-*/");
    return operators.contains(token);
}

bool ExpressionValidator::isMinus(const QChar &token){
    return token == '-';
}

bool ExpressionValidator::isValidDigitPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot){
    if(!bool(tokenIndex) || isPreviousDigit || isPreviousOperator || isPreviousDot){
        isPreviousDigit = true;
        isPreviousDot = false;
        isPreviousOperator = false;
        return true;
    }
    return false;
}

bool ExpressionValidator::isValidMinusOperatorPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot){
    if(!bool(tokenIndex) || isPreviousDigit || isPreviousOperator){
        isPreviousOperator = true;
        isPreviousDigit = false;
        isPreviousDot = false;
        return true;
    }
    return false;
}

bool ExpressionValidator::isValidOperatorPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot){
    if(bool(tokenIndex) && isPreviousDigit){
        isPreviousOperator = true;
        isPreviousDigit = false;
        isPreviousDot = false;
        return true;
    }
    return false;
}

bool ExpressionValidator::isValidDotPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot){
    if(bool(tokenIndex) && isPreviousDigit){
        isPreviousDot = true;
        isPreviousOperator = false;
        isPreviousDigit = false;
        return true;
    }
    return false;
}
