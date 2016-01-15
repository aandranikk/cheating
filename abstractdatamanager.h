#ifndef ABSTRACTDATAMANAGER_H
#define ABSTRACTDATAMANAGER_H

#include <QString>
#include <QList>
#include <QImage>
#include <QSharedPointer>

class AbstractDataManager
{
public:
    AbstractDataManager(){}
    virtual ~AbstractDataManager(){}

    virtual QStringList GetSubjectsList() const = 0;
    virtual QStringList GetThemesList(const QString& subjectName) const = 0;
    virtual QStringList GetImagesList(const QString& subjectName, const QString& themeName) const = 0;
    virtual QImage GetImage(const QString& imageAddress) const = 0;

    virtual bool AddSubject(const QString& subjectName) = 0;
    virtual bool AddTheme(const QString& subjectName, const QString& themeName) = 0;
    virtual  int AddImage(const QString& subjectName, const QString& themeName, const QString imageExt,
                          const QImage& image) = 0;
    // AddImage возвращает номер (>= 0), присвоенный изображению, или -1, если произошла ошибка
    // imageExt - расширение файла

    virtual bool DeleteSubject(const QString& subjectName) = 0;
    virtual bool DeleteTheme(const QString& subjectName, const QString& themeName) = 0;
    virtual bool DeleteImage(const QString& subjectName, const QString& themeName, const QString& imageName) = 0;
};

typedef QSharedPointer<AbstractDataManager> pAbstractDataManager;

#endif // ABSTRACTDATAMANAGER_H
