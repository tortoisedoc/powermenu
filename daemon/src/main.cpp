#include <QtQuick>
#include <QGuiApplication>

#include <sailfishapp.h>

#include "dbuslistener.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

const char* msgTypeToString(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg:
        return "D";
    case QtWarningMsg:
        return "W";
    case QtCriticalMsg:
        return "C";
    case QtFatalMsg:
        return "F";
        //abort();
    default:
        return "D";
    }
}

void printLog(const QString &message)
{
    QTextStream(stdout) << message;
}

QString simpleLog(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    Q_UNUSED(context);
    return QString("[%1 %2] %3\n").arg(msgTypeToString(type))
                                     .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                     .arg(message);
}

void stdoutHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    printLog(simpleLog(type, context, msg));
    if (type == QtFatalMsg)
        abort();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(stdoutHandler);
    setuid(0);

    QScopedPointer<QGuiApplication> app(new QGuiApplication(argc, argv));
    new DBusListener(app.data());

    return app->exec();
}

