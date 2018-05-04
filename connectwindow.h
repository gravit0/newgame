#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectWindow(QWidget *parent = 0);
    ~ConnectWindow();
    Ui::ConnectWindow *ui;
private slots:
    void on_pushButton_clicked();
};
extern ConnectWindow* connectwindow;
#endif // CONNECTWINDOW_H
