#ifndef FILEDATAMANAGER_H
#define FILEDATAMANAGER_H

#include <QDir>

#include "abstractdatamanager.h"

// данный класс предназначен только для тестирования

class FileDataManager : public AbstractDataManager
{
public:
    FileDataManager(const QString rootDir) : m_rootDir(rootDir)
    {
        auto dir = QDir(rootDir);
        if (dir.exists())
            dir.removeRecursively();
        dir.mkdir(rootDir);
    }

    virtual QStringList GetSubjectsList() const;
    virtual QStringList GetThemesList(const QString& subjectName) const;
    virtual QStringList GetImagesList(const QString& subjectName, const QString& themeName) const;
    virtual QImage GetImage(const QString& imageAddress) const;

    virtual bool AddSubject(const QString& subjectName);
    virtual bool AddTheme(const QString& subjectName, const QString& themeName);
    virtual  int AddImage(const QString& subjectName, const QString& themeName, const QString imageExt,
                          const QImage& image);

    virtual bool DeleteSubject(const QString& subjectName);
    virtual bool DeleteTheme(const QString& subjectName, const QString& themeName);
    virtual bool DeleteImage(const QString& subjectName, const QString& themeName, const QString& imageName);

private:
    QString m_rootDir;
    uint imagesCount = 0;
};

#endif // FILEDATAMANAGER_H
