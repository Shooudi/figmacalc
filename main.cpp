#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calculator.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("Shoudi");
    QCoreApplication::setApplicationName("figmacalc");


    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Calculator calculator;
    engine.rootContext()->setContextProperty("calc", &calculator);


    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    //engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    engine.loadFromModule("figmacalc", "Main");

    return app.exec();
}
