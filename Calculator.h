#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
//#include <QString>
#include <QDateTime>////
#include <QTimer>

class Calculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
    Q_PROPERTY(bool checkingCode READ checkingCode NOTIFY secretStateChanged)

public:
    explicit Calculator(QObject *parent = nullptr);
    ~Calculator();

    QString expression() const;
    QString result() const;
    bool checkingCode() const;////

public slots:
    void digitPressed(int digit);
    void operatorPressed(const QString &op);
    void decimalPressed();
    void clearPressed();
    void equalsPressed();
    void percentagePressed();
    void negationPressed();

    void handleEqualsPressed(bool isLongPress);

signals:
    void expressionChanged();
    void resultChanged();
    void secretStateChanged();////

    void secretCodeActivated();////
    void secretPageRequested();////

private:
    void calculate();
    void reset();
    void updateExpression();
    void resetSecretState();////

    QString m_expression;
    QString m_result;
    QString m_currentInput;

    QString m_lastOperation;
    double m_firstOperand;
    bool m_waitingForOperand;
    bool m_hasDecimal;

    QString m_enteredCode;
    bool m_checkingCode;
    QTimer* m_codeTimer;
};

#endif // CALCULATOR_H
