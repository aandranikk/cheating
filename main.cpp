#include <QApplication>
#include <QQmlApplicationEngine>

#include <QStringListModel>
#include <QQmlContext>

#include "filedatamanager.h"
#include "datamodel.h"
#include "imageprovider.h"
#include "backend.h"

#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BackEnd backEnd;
    backEnd.run();

    return app.exec();
}

