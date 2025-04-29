#include "calculator.h"
#include <QDebug>
#include <cmath>

Calculator::Calculator(QObject *parent) : QObject(parent), m_codeTimer(new QTimer(this))
{
    reset();

    m_operatorPrecedence["+"] = 1;
    m_operatorPrecedence["-"] = 1;
    m_operatorPrecedence["×"] = 2;
    m_operatorPrecedence["÷"] = 2;

    m_codeTimer->setSingleShot(true);
    m_codeTimer->setInterval(5000);
    connect(m_codeTimer, &QTimer::timeout, this, &Calculator::resetSecretState);

    resetSecretState();
}

Calculator::~Calculator()
{
    delete m_codeTimer;
}

void Calculator::resetSecretState()
{
    m_checkingCode = false;
    m_enteredCode.clear();
    emit secretStateChanged();
}

bool Calculator::checkingCode() const
{
    return m_checkingCode;
}

QString Calculator::expression() const {
    return m_expression;
}

QString Calculator::result() const {
    return m_result.isEmpty() ? "0" : m_result;
}

void Calculator::digitPressed(int digit) {
    if (m_checkingCode) {
        m_enteredCode.append(QString::number(digit));

        if (m_enteredCode == "123") {
            m_codeTimer->stop();
            emit secretPageRequested();
            resetSecretState();
        }
        return;
    }

    if (m_waitingForOperand) {
        m_currentInput.clear();
        m_waitingForOperand = false;
    }

    if (digit == 0 && m_currentInput == "0")
        return;
    if (digit != 0 && m_currentInput == "0")
        m_currentInput.clear();

    m_currentInput.append(QString::number(digit));
    updateExpression();
}

void Calculator::operatorPressed(const QString &op) {
    if (m_checkingCode) {
        m_codeTimer->stop();
        resetSecretState();
        return;
    }

    if (!m_currentInput.isEmpty()) {
        if (!m_lastOperation.isEmpty() && !m_waitingForOperand) {
            calculate();
        } else {
            m_firstOperand = m_currentInput.toDouble();
        }
    }

    m_lastOperation = op;
    m_waitingForOperand = true;
    m_hasDecimal = false;

    m_expression.append(op);
    emit expressionChanged();
}

void Calculator::decimalPressed() {
    if (m_waitingForOperand) {
        m_currentInput = "0";
        m_waitingForOperand = false;
    }

    if (!m_currentInput.contains(".")) {
        m_currentInput.append(".");
        m_hasDecimal = true;
        updateExpression();
    }
}

void Calculator::equalsPressed() {
    if (!m_lastOperation.isEmpty() && !m_waitingForOperand) {
        calculate();
        m_lastOperation.clear();
        emit expressionChanged();
    }
    m_waitingForOperand = true;
    m_hasDecimal = false;
}

void Calculator::handleEqualsPressed(bool isLongPress)
{
    if (isLongPress) {
        m_checkingCode = true;
        m_enteredCode.clear();
        m_codeTimer->start();
        emit secretCodeActivated();
        return;
    }

    equalsPressed();
}

void Calculator::percentagePressed()
{
    if (m_waitingForOperand || m_lastOperation.isEmpty()) {
        double value = m_currentInput.toDouble() / 100.0;
        m_currentInput = QString::number(value);
    } else {
        double percentage = m_currentInput.toDouble() / 100.0 * m_firstOperand;
        m_currentInput = QString::number(percentage);
    }

    updateExpression();
    emit expressionChanged();
}

void Calculator::negationPressed() {
    if (m_currentInput.isEmpty() && !m_expression.isEmpty()) {
        m_expression.prepend("-(");
        m_expression.append(")");
        emit expressionChanged();
    } else {
        double value = m_currentInput.toDouble();
        m_currentInput = QString::number(-value);
        updateExpression();
    }
}

void Calculator::clearPressed() {
    reset();
    emit expressionChanged();
    emit resultChanged();
}

void Calculator::openParenthesis() {
    if (m_checkingCode) {
        m_codeTimer->stop();
        resetSecretState();
        return;
    }

    if (m_expression.isEmpty() ||
        isOperator(m_expression.right(1)) ||
        m_expression.right(1) == "(") {
        m_expression.append("(");
        emit expressionChanged();
        emit parenthesisPressed("(");
    }
}

void Calculator::closeParenthesis() {
    if (m_checkingCode) {
        m_codeTimer->stop();
        resetSecretState();
        return;
    }

    int openCount = m_expression.count("(");
    int closeCount = m_expression.count(")");

    if (openCount > closeCount &&
        (!m_currentInput.isEmpty() || m_expression.right(1) == ")")) {
        m_expression.append(")");
        emit expressionChanged();
        emit parenthesisPressed(")");
    }
}

void Calculator::calculate() {
    if (!validateExpression(m_expression)) {
        m_result = "0";
        emit resultChanged();
        return;
    }

    try {
        double result = evaluateExpression(m_expression);

        if (qIsInf(result) || qIsNaN(result)) {
            m_result = "0";
        } else {
            m_result = QString::number(result, 'g', 12);
        }

        m_firstOperand = result;
        m_currentInput = m_result;
        emit resultChanged();
    } catch (...) {
        emit resultChanged();
    }
}

void Calculator::reset() {
    m_expression.clear();
    m_result = "0";
    m_currentInput = "0";
    m_lastOperation.clear();
    m_firstOperand = 0.0;
    m_waitingForOperand = true;
    m_hasDecimal = false;
}

void Calculator::updateExpression() {
    if (m_waitingForOperand) {
        m_expression = m_currentInput;
    } else {
        int lastPos = -1;
        for (int i = m_expression.length()-1; i >= 0; --i) {
            QChar c = m_expression.at(i);
            if (c == "+" || c == "-" || c == "×" || c == "÷" || c == "(") {
                lastPos = i;
                break;
            }
        }

        if (lastPos >= 0) {
            m_expression = m_expression.left(lastPos+1) + m_currentInput;
        } else {
            m_expression = m_currentInput;
        }
    }
    emit expressionChanged();
}

bool Calculator::isOperator(const QString &token) const {
    return m_operatorPrecedence.contains(token);
}

bool Calculator::isNumber(const QString &token) const {
    bool ok;
    token.toDouble(&ok);
    return ok;
}

QStringList Calculator::tokenize(const QString &expression) const {
    QStringList tokens;
    QString number;

    for (const QChar &c : expression) {
        if (c.isDigit() || c == ".") {
            number.append(c);
        } else {
            if (!number.isEmpty()) {
                tokens.append(number);
                number.clear();
            }

            if (c == "+" || c == "-" || c == "×" || c == "÷" ||
                c == "(" || c == ")") {
                tokens.append(QString(c));
            }
        }
    }

    if (!number.isEmpty()) {
        tokens.append(number);
    }

    return tokens;
}

QStringList Calculator::shuntingYard(const QStringList &tokens) const {
    QStringList output;
    QStack<QString> stack;

    for (const QString &token : tokens) {
        if (isNumber(token)) {
            output.append(token);
        } else if (isOperator(token)) {
            while (!stack.isEmpty() && isOperator(stack.top()) &&
                   m_operatorPrecedence[stack.top()] >= m_operatorPrecedence[token]) {
                output.append(stack.pop());
            }
            stack.push(token);
        } else if (token == "(") {
            stack.push(token);
        } else if (token == ")") {
            while (!stack.isEmpty() && stack.top() != "(") {
                output.append(stack.pop());
            }

            if (stack.isEmpty()) {
                return QStringList();
            }

            stack.pop();
        }
    }

    while (!stack.isEmpty()) {
        if (stack.top() == "(") {
            return QStringList();
        }
        output.append(stack.pop());
    }

    return output;
}

double Calculator::evaluateRPN(const QStringList &rpnTokens) const {
    QStack<double> stack;

    for (const QString &token : rpnTokens) {
        if (isNumber(token)) {
            stack.push(token.toDouble());
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                return 0.0;
            }

            double b = stack.pop();
            double a = stack.pop();
            double result = 0.0;

            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "×") result = a * b;
            else if (token == "÷") {
                if (b == 0.0) {
                    throw std::runtime_error("Деление на ноль");
                }
                result = a / b;
            }

            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        return 0.0;
    }

    return stack.pop();
}

double Calculator::evaluateExpression(const QString &expression) const {
    if (expression.isEmpty()) return 0.0;

    QStringList tokens = tokenize(expression);
    if (tokens.isEmpty()) return 0.0;

    QStringList rpn = shuntingYard(tokens);
    if (rpn.isEmpty()) return 0.0;

    return evaluateRPN(rpn);
}

bool Calculator::validateExpression(const QString &expression) const {
    int balance = 0;
    for (const QChar &c : expression) {
        if (c == "(") balance++;
        else if (c == ")") balance--;

        if (balance < 0) return false;
    }
    return balance == 0;
}
