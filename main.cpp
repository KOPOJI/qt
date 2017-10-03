#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "database.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DataBase database;
    database.connectToDataBase();

    QVector<QStringList> moduleParts = database.getModuleData(1);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
