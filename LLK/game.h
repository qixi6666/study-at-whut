#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include<gamemap.h>
#include <QPainter>
#include <QPaintEvent>
#include<QTimer>
#define TIMEOUT 60*1000
namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:

    explicit Game(QWidget *parent = nullptr);

    ~Game();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void drawBlock(QPainter &painter, int row, int col);
    void handleBlockClick(int row, int col);

protected:
    void closeEvent(QCloseEvent *event) override;




private slots:
    void on_restartButton_clicked();
    void on_pauseButton_clicked();
    void on_promptButton_clicked();

private:
    Ui::Game *ui;
    GameMap gameMap;
    QPoint selectedBlock;// 当前选中的方块坐标
    QPoint hintBlock1, hintBlock2;//提示方块
    const int blockSize = 64; // 方块大小（与图片大小一致）
    int score=0;
    QTimer timeoutTimer;    // 单次计时器
    QTimer countdownTimer;  // 重复计时器
    int timeLeft;


};

#endif // GAME_H
