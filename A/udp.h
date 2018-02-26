#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    void SayHello();

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
};

#endif // UDP_H
