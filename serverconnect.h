#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H

#include <QObject>
#include <QTcpSocket>
#include "libns.h"
class ServerConnect : public QObject
{
    Q_OBJECT
protected:
    QTcpSocket sock;
    char* readBuffer;
    int nextBlockSize;
public:
    explicit ServerConnect(QObject *parent = nullptr);
    bool connect(QString host, int port);
    bool cmd(cmds cmd, unsigned int cmdflags = 0);
    bool cmd(cmds cmd,QString param, unsigned int cmdflags = 0);
    void result_handler(message_result *head, size_t size);
    ~ServerConnect();
signals:

public slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
};
extern ServerConnect* sock;
#endif // SERVERCONNECT_H
