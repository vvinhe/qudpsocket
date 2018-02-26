#include "udp.h"

UDP::UDP(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 5557);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UDP::SayHello()
{
    QByteArray Data;
    Data.append("Hello");
    socket->writeDatagram(Data, QHostAddress("127.0.0.1"), 1234);
}

void UDP::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << Buffer;
}
