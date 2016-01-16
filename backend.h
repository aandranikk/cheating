#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QQmlContext>
#include <QQuickItem>
#include <QItemSelectionModel>
#include <QDir>

#include "filedatamanager.h"
#include "datamodel.h"
#include "imageprovider.h"
#include "serverdatamanager.h"

class BackEnd : QObject
{
    Q_OBJECT

public:
    BackEnd()
        : m_dataManager(new ServerDataManager("localhost",2323))
        , m_model(m_dataManager)
    {}

    void run();

    /* в функциях ниже возвращается сообщение с ошибками, если есть;
     * стоит перейти к enum для улучшения производительности и добавить новые ошибки
     */
    Q_INVOKABLE QString addSubject(const QString& subjectName);
    Q_INVOKABLE QString addTheme(const QModelIndex& subjectIndex, const QString& themeName);
    Q_INVOKABLE QString addImage(const QModelIndex& themeIndex, const QString& imagePath);

    Q_INVOKABLE QString deleteSubject(const QModelIndex& subjectIndex);
    Q_INVOKABLE QString deleteTheme(const QModelIndex& themeIndex);
                QString deleteImage(const QModelIndex& imageIndex);

    Q_INVOKABLE void selectImage(const QModelIndex& index);
    Q_INVOKABLE QString deleteSelectedImages();

public slots:
    void subjectClicked(const QModelIndex& subjectIndex);
    void themeClicked(const QModelIndex& themeIndex);

private:
    pAbstractDataManager m_dataManager;
    DataModel m_model;
    QSortFilterProxyModel m_proxyModel;
    QItemSelectionModel m_imagesSelection;
    QQmlApplicationEngine m_engine;

    const QString subjectAlreadyExistMsg = "Предмет с таким названием уже сущесвует.";
    const QString themeAlreadyExistMsg = "Тема с таким названием уже сущесвует.";
    const QString failedMsg = "Не удалось выполнить операцию. Возможно, нет подключения к серверу.";
};

#endif // BACKEND_H
