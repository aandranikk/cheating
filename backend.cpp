#include <QDebug>
#include <QPainter>
#include <QRegExp>
#include <QPersistentModelIndex>
#include <QFileInfo>

#include "backend.h"

void BackEnd::run()
{
    if (!m_model.init())
    {/* обработка */}
    m_proxyModel.setSourceModel(&m_model);
    m_imagesSelection.setModel(&m_model);

    m_engine.addImageProvider("ImageProvider", new ImageProvider(m_dataManager));
    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto rc = m_engine.rootContext();

    rc->setContextProperty("backEnd", this);
    rc->setContextProperty("dataModelBE", &m_model);
    rc->setContextProperty("currPicDir",QCoreApplication::applicationDirPath()+"/pictures/"); // for linux(windows)
    //rc->setContextProperty("currPicDir",
    //                       QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/"); //for android
}

void BackEnd::subjectClicked(const QModelIndex& subjectIndex)
{
    m_model.subjectClicked(subjectIndex);
}

void BackEnd::themeClicked(const QModelIndex& themeIndex)
{
    m_model.themeClicked(themeIndex);
}

QString BackEnd::addSubject(const QString& subjectName)
{
    for (int i = 0; i < m_model.rowCount(m_model.invisibleRootItem()->index()); ++i)
    {
        if (m_model.item(i)->data(Qt::DisplayRole) == subjectName)
            return subjectAlreadyExistMsg;
    }

    if (!m_dataManager->AddSubject(subjectName))
        if (!m_dataManager->AddSubject(subjectName))
            return failedMsg;

    m_model.addSubject(subjectName);

    return "";
}

QString BackEnd::addTheme(const QModelIndex& subjectIndex, const QString& themeName)
{
    for (int i = 0; i < m_model.rowCount(subjectIndex); ++i)
    {
        if (subjectIndex.child(i, 0).data(Qt::DisplayRole).toString() == themeName)
            return themeAlreadyExistMsg;
    }

    if (!m_dataManager->AddTheme(subjectIndex.data(Qt::DisplayRole).toString(), themeName))
        if (!m_dataManager->AddTheme(subjectIndex.data(Qt::DisplayRole).toString(), themeName))
            return failedMsg;

    m_model.addTheme(subjectIndex, themeName);

    return "";
}

QString BackEnd::addImage(const QModelIndex& themeIndex, const QString& imagePath)
{
    auto subjectName = themeIndex.parent().data(Qt::DisplayRole).toString();
    auto themeName = themeIndex.data(Qt::DisplayRole).toString();
    auto imageLocalPath = QUrl(imagePath).toLocalFile();
    auto imageExt = QFileInfo(imageLocalPath).completeSuffix();
    QImage image(imageLocalPath);

    qDebug() << imageExt;

    int imageNumber = m_dataManager->AddImage(subjectName, themeName, imageExt, image);
    if (imageNumber == -1)
    {
        imageNumber = m_dataManager->AddImage(subjectName, themeName, imageExt, image);
        if (imageNumber == -1)
            return failedMsg;
    }

    m_model.addImage(themeIndex, QString::number(imageNumber));

    return "";
}

QString BackEnd::deleteSubject(const QModelIndex& subjectIndex)
{
    auto subjectName = subjectIndex.data(Qt::DisplayRole).toString();
    if (!m_dataManager->DeleteSubject(subjectName))
        if (!m_dataManager->DeleteSubject(subjectName))
            return failedMsg;

    m_model.deleteSubject(subjectIndex);

    return "";
}

QString BackEnd::deleteTheme(const QModelIndex& themeIndex)
{
    auto subjectName = themeIndex.parent().data(Qt::DisplayRole).toString();
    auto themeName = themeIndex.data(Qt::DisplayRole).toString();
    if (!m_dataManager->DeleteTheme(subjectName, themeName))
        if (!m_dataManager->DeleteTheme(subjectName, themeName))
            return failedMsg;

    m_model.deleteTheme(themeIndex);

    return "";
}

QString BackEnd::deleteImage(const QModelIndex& imageIndex)
{
    auto subjectName = imageIndex.parent().parent().data(Qt::DisplayRole).toString();
    auto themeName = imageIndex.parent().data(Qt::DisplayRole).toString();
    auto imageName = imageIndex.data(Qt::DisplayRole).toString();

    if (!m_dataManager->DeleteImage(subjectName, themeName, imageName))
        if (!m_dataManager->DeleteImage(subjectName, themeName, imageName))
            return failedMsg;

    m_model.deleteImage(imageIndex);

    return "";
}

void BackEnd::selectImage(const QModelIndex& index)
{
    //qDebug() << "toggled: " << index.data().toString();
    m_imagesSelection.select(index, QItemSelectionModel::Toggle);
}

QString BackEnd::deleteSelectedImages()
{
    auto selectedImagesIndexes = m_imagesSelection.selectedIndexes();

    if (!selectedImagesIndexes.empty())
    {
        QList<QPersistentModelIndex> selectedImagesPersistentIndexes;
        for (auto index : selectedImagesIndexes)
            selectedImagesPersistentIndexes.append(QPersistentModelIndex(index));

        for (auto index : selectedImagesPersistentIndexes)
        {
            auto msg = deleteImage(index);
            if (msg != "")
                return failedMsg + " (удалена часть изображений)";
        }
    }

    return "";
}











