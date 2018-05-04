#include "serverconnect.h"
#include "mainwindow.h"
#include "connectwindow.h"
#include "libns.h"
#include <string>
#include <QDataStream>
#include <QTime>
#include <QDebug>
ServerConnect* sock;
ServerConnect::ServerConnect(QObject *parent) : QObject(parent)
{
    QObject::connect(&sock, &QTcpSocket::connected, this, &ServerConnect::slotConnected);
    QObject::connect(&sock, &QTcpSocket::readyRead,this, &ServerConnect::slotReadyRead);
    readBuffer = new char[1024];
}
bool ServerConnect::connect(QString host, int port)
{
    sock.connectToHost(host,port);
    if(sock.isOpen()) return true;
    return false;
}

bool ServerConnect::cmd(cmds cmd, unsigned int cmdflags)
{
    message_head head;
    head.cmd = (unsigned int)cmd;
    head.cmdflags = cmdflags;
    head.flag = 0;
    head.size = 0;
    head.version = 1;
    sock.write((const char*) &head,sizeof(head));
    sock.waitForBytesWritten();
    return true;
}

bool ServerConnect::cmd(cmds cmd, QString param, unsigned int cmdflags)
{
    std::string str = param.toStdString();
    const char* c_str = str.c_str();
    int strlen = str.size();
    message_head* head = (message_head*) new char[sizeof(message_head) + strlen];
    head->cmd = (unsigned int)cmd;
    head->cmdflags = cmdflags;
    head->flag = 0;
    head->size = 0;
    head->version = 1;
    memcpy((char*)head + sizeof(struct message_head),c_str,strlen);
    sock.write((const char*) &head,sizeof(message_head) + strlen);
    sock.waitForBytesWritten();
    delete[] (char*)head;
    return true;
}

void ServerConnect::result_handler(message_result *result, size_t size)
{
    if((result->flag & message_result::FLAG_EVENT) != 0)
        qDebug() << "EVENT:" << result->code;
    else
        qDebug() << "CODE:" << result->code;
}

ServerConnect::~ServerConnect()
{
    sock.close();
    delete[] readBuffer;
}

void ServerConnect::slotReadyRead()
{
    int b = sock.bytesAvailable();
    sock.read(readBuffer,b);
    QByteArray str(readBuffer,b);
    qDebug() << str.toHex();
    if(b < sizeof(message_result)) {
        qDebug() << "ERROR Parsing data";
    }
    else if(b == sizeof(message_result))
    {
        result_handler((message_result*)readBuffer,b);
    }
    else
    {
        message_result* result = (message_result*)readBuffer;
        char* it = readBuffer;
        while(it < readBuffer + b)
        {
            result_handler((message_result*)it,sizeof(message_result) + result->size);
            it += sizeof(message_result) + result->size;
        }

    }
    nextBlockSize = 0;
}

void ServerConnect::slotError(QAbstractSocket::SocketError)
{

}

void ServerConnect::slotSendToServer()
{

}
void ServerConnect::slotConnected()
{
    connectwindow->hide();
    mainwindow->show();
    cmd(cmds::listen);
}
