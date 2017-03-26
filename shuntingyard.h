#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <QString>
#include <QStringList>

class ShuntingYard{
public:
    ShuntingYard();
    QStringList getReversePolishNotation(const QString &expression);
};

#endif // SHUNTINGYARD_H
