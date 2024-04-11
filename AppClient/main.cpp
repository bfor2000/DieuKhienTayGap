#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <backend.h>
#include<QQmlContext>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    //Backend *backend=new Backend(&app);
    QScopedPointer<Backend> example(new Backend);
    qmlRegisterSingletonInstance<Backend>("com.company.backend", 1, 0, "Backend", example.get());
    //qmlRegisterType<Backend>("com.company.backend", 1, 0, "Backend");
    const QUrl url(u"qrc:/Client/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
