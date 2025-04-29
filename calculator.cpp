#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
    , m_codeTimer(new QTimer(this))
{
    reset();

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

QString Calculator::expression() const
{
    return m_expression;
}

QString Calculator::result() const
{
    return m_result.isEmpty() ? "0" : m_result;
}

void Calculator::digitPressed(int digit)
{
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

void Calculator::operatorPressed(const QString &op)
{
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

void Calculator::decimalPressed()
{
    if (m_waitingForOperand) {
        m_currentInput = "0";
        m_waitingForOperand = false;
    }

    if (!m_currentInput.contains('.')) {
        m_currentInput.append('.');
        m_hasDecimal = true;
        updateExpression();
    }
}

void Calculator::equalsPressed()
{
    if (!m_lastOperation.isEmpty() && !m_waitingForOperand) {
        calculate();
        //m_expression = m_result; // после нажатия "=" будет отображаться результат в верхней и нижней строке
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

void Calculator::negationPressed()
{
    double value = m_currentInput.toDouble();
    m_currentInput = QString::number(-value);
    updateExpression();
}

void Calculator::clearPressed()
{
    reset();
    emit expressionChanged();
    emit resultChanged();
}

void Calculator::calculate()
{
    double secondOperand = m_currentInput.toDouble();
    double result = 0.0;

    if (m_lastOperation == "+") {
        result = m_firstOperand + secondOperand;
    } else if (m_lastOperation == "-") {
        result = m_firstOperand - secondOperand;
    } else if (m_lastOperation == "×") {
        result = m_firstOperand * secondOperand;
    } else if (m_lastOperation == "÷") {
        if (secondOperand == 0.0) {
            m_result = "Error";
            reset();
            emit resultChanged();
            return;
        }
        result = m_firstOperand / secondOperand;
    }

    m_result = QString::number(result);
    m_firstOperand = result;
    m_currentInput = m_result;
    emit resultChanged();
}

void Calculator::reset()
{
    m_expression.clear();
    //m_result.clear();
    m_result = "0";
    m_currentInput = "0";
    m_lastOperation.clear();
    m_firstOperand = 0.0;
    m_waitingForOperand = true;
    m_hasDecimal = false;
}

void Calculator::updateExpression()
{
    if (m_waitingForOperand) {
        m_expression = m_currentInput;
    } else {
        int lastOpPos = -1;
        for (int i = m_expression.length() - 1; i >= 0; --i) {
            if (m_expression.at(i) == "+" || m_expression.at(i) == "-" || m_expression.at(i) == "×"
                || m_expression.at(i) == "÷") {
                lastOpPos = i;
                break;
            }
        }

        if (lastOpPos >= 0) {
            m_expression = m_expression.left(lastOpPos + 1) + m_currentInput;
        } else {
            m_expression = m_currentInput;
        }
    }
    emit expressionChanged();
}
