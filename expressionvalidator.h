#ifndef EXPRESSIONVALIDATOR_H
#define EXPRESSIONVALIDATOR_H
#include <QString>
#include <QChar>
class ExpressionValidator{
public:
    ExpressionValidator();
    bool isCorrectExpression(const QString &expression);
private:
    bool isDot(const QChar &token);
    bool isOperator(const QChar &token);
    bool isMinus(const QChar &token);
    bool isValidDigitPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot);
    bool isValidMinusOperatorPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot);
    bool isValidOperatorPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot);
    bool isValidDotPosition(int tokenIndex, bool &isPreviousDigit, bool &isPreviousOperator, bool &isPreviousDot);
};

#endif // EXPRESSIONVALIDATOR_H
