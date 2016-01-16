#include <myclient.h>

MyClient::MyClient(QString strHost,int nPort) : nextBlockSize(0) {

    pTcpSocket = new QTcpSocket(0);
    pTcpSocket->connectToHost(strHost, nPort);

}

void MyClient::sendRequestToServer(QString req){

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    out << quint32(0) << req;
    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));

    pTcpSocket->write(arrBlock);
}

void MyClient::sendImageToServer(QString req,QImage img){

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    out << quint32(0) << req << img;
    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));

    pTcpSocket->write(arrBlock);
}

QList<QString> MyClient::getRequestResult(){

    QList<QString> lst_str;

    if (pTcpSocket->waitForReadyRead()){
    QDataStream in(pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);

    for(;;){

        if(!nextBlockSize){
            if(pTcpSocket->bytesAvailable() < sizeof(quint32))
                break;

            in >> nextBlockSize;
        }

        if(pTcpSocket->bytesAvailable() < nextBlockSize)
            break;

        in >> lst_str;

        nextBlockSize = 0;
    }
}
  return lst_str;
}


QImage MyClient::getImage(){

    QImage img;

    pTcpSocket->waitForReadyRead(10);

    QDataStream in(pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);

    quint64 k = pTcpSocket->bytesAvailable();
    if(!nextBlockSize)
        in >> nextBlockSize;

    if(pTcpSocket->bytesAvailable()>=nextBlockSize)
        in >> img;


  return img;
}

QImage MyClient::getImageRequestResult(){
    QImage img;
    while(img.isNull())
        img = getImage();
    nextBlockSize = 0;
    return img;
}

quint32 MyClient::getCurrVers(){

    sendRequestToServer("GETCURRENTVERSION  ");

    quint32 vers;

    if (pTcpSocket->waitForReadyRead()){
    QDataStream in(pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);

    for(;;){

        if(!nextBlockSize){
            if(pTcpSocket->bytesAvailable() < sizeof(quint32))
                break;

            in >> nextBlockSize;
        }

        if(pTcpSocket->bytesAvailable() < nextBlockSize)
            break;

        in >> vers;

        nextBlockSize = 0;
    }
}
  return vers;
}
