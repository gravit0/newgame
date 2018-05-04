#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <serverconnect.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    sock->cmd(cmds::su);
}

void MainWindow::on_action_2_triggered()
{
    sock->cmd(cmds::stop);
}
