#include "serverdatamanager.h"

QStringList ServerDataManager::GetSubjectsList() const {

     QList<QString> list;
     client->sendRequestToServer("GETSUBJECTS   ");
     list = client->getRequestResult();
     QStringList str_lst(list);
     return str_lst;
}

QStringList ServerDataManager::GetThemesList(const QString& subjectName) const {

    QList<QString> list;
    client->sendRequestToServer(QString("GETTHEMES %1  ").arg(subjectName));
    list = client->getRequestResult();
    QStringList str_lst(list);
    return str_lst;
}

QStringList ServerDataManager::GetImagesList(const QString& subjectName, const QString& themeName) const {

    QList<QString> list;
    client->sendRequestToServer(QString("GETPICTURES %1 %2 ").arg(subjectName).arg(themeName));
    list = client->getRequestResult();
    QStringList str_lst(list);
    return str_lst;
}

QImage ServerDataManager::GetImage(const QString& imageAddr) const {

    QImage img;
    QUrl adr(imageAddr);
    QString filename = adr.fileName();
    client->sendRequestToServer(QString("GETIMAGE %1  ").arg(filename));
    img = client->getImageRequestResult();
    return img;
}

bool ServerDataManager::AddSubject(const QString& subjectName){
    client->sendRequestToServer(QString("PUTSUBJECT %1  ").arg(subjectName));
    return true;
}

bool ServerDataManager::AddTheme(const QString& subjectName, const QString& themeName){
    client->sendRequestToServer(QString("PUTTHEME %1 %2 ").arg(subjectName).arg(themeName));
    return true;
}

int ServerDataManager::AddImage(const QString& subjectName, const QString& themeName, const QString imageExt,
                                const QImage& image){
    client->sendImageToServer(QString("PUTIMAGE %1 %2 %3").arg(subjectName).arg(themeName).arg(imageExt),image);
    QList<QString> res = client->getRequestResult();

    return res.at(0).toInt();
}


bool ServerDataManager::DeleteSubject(const QString& subjectName){
    client->sendRequestToServer(QString("DELETESUBJECT %1").arg(subjectName));
    return true;
}

bool ServerDataManager::DeleteTheme(const QString& subjectName, const QString& themeName){
    client->sendRequestToServer(QString("DELETETHEME %1 %2").arg(subjectName).arg(themeName));
    return true;
}

bool ServerDataManager::DeleteImage(const QString& subjectName, const QString& themeName, const QString& imageName){
    client->sendRequestToServer(QString("DELETEIMAGE %1").arg(imageName));
    return true;
}

bool ServerDataManager::SwapImage(const QImage& image,const QString& imageName){
    client->sendImageToServer(QString("SWAPIMAGE %1").arg(imageName),image);
    return true;
}
