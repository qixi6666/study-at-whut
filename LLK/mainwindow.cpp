#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_basicgamebutton_clicked()
{
    this->hide();
    Game *g=new Game(this);
    g->show();


}


void MainWindow::on_rkbutton_clicked()
{
    QMessageBox::information(this,"","暂无排名");
}


void MainWindow::on_helpbutton_clicked()
{
    QMessageBox::information(
        this,
        "帮助",
        "如遇bug，请联系wjw"
        );
}


void MainWindow::on_freegamebutton_clicked()
{
    QMessageBox::information(this,"连连看","还没开发出来，如果想玩请联系wjw");
}


void MainWindow::on_gamebutton_clicked()
{
    QMessageBox::information(this,"连连看","还没开发出来，如果想玩请联系wjw");
}


void MainWindow::on_setbutton_clicked()
{
    QMessageBox::information(this,"设置","有什么想调的告诉我！");
}

