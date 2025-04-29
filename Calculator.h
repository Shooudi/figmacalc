#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QStack>
#include <QMap>
#include <QRegularExpression>
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
    bool checkingCode() const;

public slots:
    void digitPressed(int digit);
    void operatorPressed(const QString &op);
    void decimalPressed();
    void clearPressed();
    void equalsPressed();
    void percentagePressed();
    void negationPressed();
    void openParenthesis();
    void closeParenthesis();

    void handleEqualsPressed(bool isLongPress);

signals:
    void expressionChanged();
    void resultChanged();
    void secretStateChanged();
    void secretCodeActivated();
    void secretPageRequested();
    void parenthesisPressed(const QString &paren);

private:
    void calculate();
    void reset();
    void updateExpression();
    void resetSecretState();
    bool validateExpression(const QString &expression) const;

    // Методы для алгоритма сортировочной станции
    QMap<QString, int> m_operatorPrecedence;
    bool isOperator(const QString &token) const;
    bool isNumber(const QString &token) const;
    QStringList tokenize(const QString &expression) const;
    QStringList shuntingYard(const QStringList &tokens) const;
    double evaluateRPN(const QStringList &rpnTokens) const;
    double evaluateExpression(const QString &expression) const;

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
