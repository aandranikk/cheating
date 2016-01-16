#ifndef SERVERDATAMANAGER_H
#define SERVERDATAMANAGER_H

#include <QUrl>
#include <QString>
#include "abstractdatamanager.h"
#include "myclient.h"

class ServerDataManager : public AbstractDataManager
{
public:
    ServerDataManager(QString strHost, int nPort){
        client = new MyClient(strHost,nPort);
    }

    virtual QStringList GetSubjectsList() const;
    virtual QStringList GetThemesList(const QString& subjectName) const;
    virtual QStringList GetImagesList(const QString& subjectName, const QString& themeName) const;
    virtual QImage GetImage(const QString& imageAddr) const;

    virtual bool AddSubject(const QString& subjectName);
    virtual bool AddTheme(const QString& subjectName, const QString& themeName);
    virtual  int AddImage(const QString& subjectName, const QString& themeName, const QString imageExt,
                          const QImage& image);

    virtual bool DeleteSubject(const QString& subjectName);
    virtual bool DeleteTheme(const QString& subjectName, const QString& themeName);
    virtual bool DeleteImage(const QString& subjectName, const QString& themeName, const QString& imageName);

    virtual bool SwapImage(const QImage& image,const QString& imageName);

private:
    MyClient* client;
};


#endif // SERVERDATAMANAGER_H

