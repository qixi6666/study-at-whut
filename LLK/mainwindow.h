#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<game.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_basicgamebutton_clicked();

    void on_rkbutton_clicked();

    void on_helpbutton_clicked();

    void on_freegamebutton_clicked();

    void on_gamebutton_clicked();

    void on_setbutton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
