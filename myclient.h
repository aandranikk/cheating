#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QTcpSocket>
#include <QDataStream>
#include <QImage>

class MyClient {

private:
    QTcpSocket* pTcpSocket;
    quint32  nextBlockSize;    

public:

    MyClient(QString strHost, int nPort);

    void sendRequestToServer(QString req);
    QList<QString> getRequestResult();
    void sendImageToServer(QString req, QImage img);
    QImage getImageRequestResult();
    quint32 getCurrVers();

private:
    QImage getImage();
};

#endif // MYCLIENT_H

