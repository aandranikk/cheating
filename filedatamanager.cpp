#include <QDir>
#include <QDebug>

#include "filedatamanager.h"

QStringList FileDataManager::GetSubjectsList() const
{
    QStringList subjectsList;
    QDir dir(m_rootDir);

    auto entryList = dir.entryInfoList();
    for (const auto& f : entryList)
    {
        if (f.isDir() && f.baseName() != "")
            subjectsList += f.baseName();
    }

    return subjectsList;
}

QStringList FileDataManager::GetThemesList(const QString& subjectName) const
{
    QStringList themesList;
    QDir dir(m_rootDir + "/" + subjectName);

    auto entryList = dir.entryInfoList();
    for (const auto& f : entryList)
    {
        if (f.isDir() && f.baseName() != "")
            themesList += f.baseName();
    }

    return themesList;
}

QStringList FileDataManager::GetImagesList(const QString& subjectName, const QString& themeName) const
{
    QStringList imagesList;
    QDir dir(m_rootDir + "/" + subjectName + "/" + themeName);

    auto entryList = dir.entryInfoList();
    for (const auto& f : entryList)
    {
        if (f.isFile() && f.baseName() != "")
            imagesList += f.baseName();
    }

    return imagesList;
}

QImage FileDataManager::GetImage(const QString& imageAddress) const
{
    return QImage(m_rootDir + "/" + imageAddress);
}

bool FileDataManager::AddSubject(const QString& subjectName)
{
    return QDir().mkpath(m_rootDir + "/" + subjectName);
}

bool FileDataManager::AddTheme(const QString& subjectName, const QString& themeName)
{
    return QDir().mkpath(m_rootDir + "/" + subjectName + "/" + themeName);
}

int FileDataManager::AddImage(const QString& subjectName, const QString& themeName, const QString imageExt,
                              const QImage& image)
{
    QString imageName = QString::number(imagesCount);

    return image.save(m_rootDir + "/" + subjectName + "/" +
                      themeName + "/" + imageName, imageExt.toStdString().c_str()) \
           ? imagesCount ++ : -1;
}

bool FileDataManager::DeleteSubject(const QString& subjectName)
{
    return QDir(m_rootDir + "/" + subjectName).removeRecursively();
}

bool FileDataManager::DeleteTheme(const QString& subjectName, const QString& themeName)
{
    return QDir(m_rootDir + "/" + subjectName + "/" + themeName).removeRecursively();
}

bool FileDataManager::DeleteImage(const QString& subjectName, const QString& themeName, const QString& imageName)
{
    //qDebug() << "remove " + m_rootDir + "/" + subjectName + "/" + themeName + "/" + imageName;
    return QDir().remove(m_rootDir + "/" + subjectName + "/" + themeName + "/" + imageName);
}






