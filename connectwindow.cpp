#include "connectwindow.h"
#include "ui_connectwindow.h"
#include "serverconnect.h"
ConnectWindow::ConnectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    sock = new ServerConnect(this);
}

ConnectWindow::~ConnectWindow()
{
    delete sock;
    delete ui;
}

void ConnectWindow::on_pushButton_clicked()
{
    sock->connect(ui->lineEdit_3->text(),ui->lineEdit_4->text().toInt());
}
