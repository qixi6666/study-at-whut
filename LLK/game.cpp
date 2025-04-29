#include "game.h"
#include "ui_game.h"
#include<QString>
#include<QMessageBox>
#include<QCloseEvent>
Game::Game(QWidget *parent): QMainWindow(parent), ui(new Ui::Game),gameMap(10,12)
{
    ui->setupUi(this);
    ui->scoreEdit->setReadOnly(true);

    timeoutTimer.setSingleShot(true);
    connect(&timeoutTimer, &QTimer::timeout, this, [this]() {
        QMessageBox::information(this, "超时", "游戏结束，请重新开始");
        this->on_restartButton_clicked();
    });

    timeLeft=60;
    ui->timeprogressBar->setRange(0, 60); // 最大值120秒
    ui->timeprogressBar->setValue(60);    // 初始值
    ui->timeprogressBar->setFormat("剩余时间: %v秒"); // 显示格式

    connect(&countdownTimer, &QTimer::timeout, this, [this]() {
        if(timeLeft>=0){
        timeLeft--;
        ui->timeprogressBar->setValue(timeLeft);
        }
    });
    timeoutTimer.start(TIMEOUT); // 60秒后触发
    countdownTimer.start(1000);     // 每秒触发
}

Game::~Game()
{
    delete ui;

}

void Game::closeEvent(QCloseEvent *event) {
   parentWidget()->show(); // 关闭时显示父窗口（即主界面）
    event->accept();        // 接受关闭事件
}


void Game::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event); // 基类处理其他绘制
    QPainter painter(this);

    // 强制背景颜色（调试）
    //painter.fillRect(rect(), QColor(200, 200, 200)); // 灰色背景

    int mapWidth = gameMap.cols * blockSize;
    int mapHeight = gameMap.rows * blockSize;

    // 确保地图可以居中显示
    int startX = (width() - mapWidth) / 2;
    int startY = (height() - mapHeight) / 2;


    // 遍历绘制地图
    for (int row = 0; row < gameMap.rows; ++row) {
        for (int col = 0; col < gameMap.cols; ++col) {
            int imageIndex = gameMap.map[row][col];
            if (imageIndex == -1) continue;

            QPixmap pixmap = gameMap.blockImages.value(imageIndex); // 避免越界
            if (pixmap.isNull())qDebug()<<"nothing";

            int x = startX + col * blockSize;
            int y = startY + row * blockSize;

            painter.drawPixmap(x, y, blockSize, blockSize, pixmap);
        }
    }
    //绘制选中区域
    if (!selectedBlock.isNull()) {
        int x = selectedBlock.y() * blockSize+startX;
        int y = selectedBlock.x() * blockSize+startY;
        painter.setPen(QPen(Qt::red, 3));
        painter.drawRect(x, y, blockSize, blockSize);
    }
    //显示提示
    if (!hintBlock1.isNull()||!hintBlock2.isNull()) {
        painter.setPen(QPen(Qt::blue, 3)); // 黄色边框
        painter.drawRect(hintBlock1.y() * blockSize+startX, hintBlock1.x() * blockSize+startY, blockSize, blockSize);
        painter.drawRect(hintBlock2.y() * blockSize+startX, hintBlock2.x() * blockSize+startY, blockSize, blockSize);
        hintBlock1=QPoint();
        hintBlock2=QPoint();

    }


    // 绘制测试矩形（验证位置）
   //painter.setPen(Qt::red);
    //painter.drawRect(startX, startY, mapWidth, mapHeight); // 标出地图边框
    ui->scoreEdit->setText(QString::number(score));
 }

void Game::mousePressEvent(QMouseEvent*event){

    int mapWidth = gameMap.cols * blockSize;
    int mapHeight = gameMap.rows * blockSize;
    int startX = (width() - mapWidth) / 2;
    int startY = (height() - mapHeight) / 2;
    QPoint pos=event->pos();
    int row=(pos.y()-startY)/blockSize;
    int col=(pos.x()-startX)/blockSize;

    if(row>=0&&row<gameMap.rows&&col>=0&&col<gameMap.cols){
    handleBlockClick(row,col);
    }

}
void Game::handleBlockClick(int row,int col){
    if(gameMap.map[row][col]==-1)return;
    if(selectedBlock.isNull()){
        selectedBlock=QPoint(row,col);
        update();

    }else{
        QPoint p1= selectedBlock;
        QPoint p2=QPoint(row,col);
        if(gameMap.canEliminate(p1,p2)){
            gameMap.map[p1.x()][p1.y()]=-1;
            gameMap.map[p2.x()][p2.y()]=-1;

            score=score+10;

             update();
        }
        selectedBlock=QPoint();

    }
}




void Game::on_restartButton_clicked()
{

    timeoutTimer.stop();
    countdownTimer.stop();

    // 重置时间和游戏状态
    timeLeft = 60;
    ui->timeprogressBar->setValue(timeLeft);
    score = 0;
    gameMap.generateRandomMap();

    // 重启计时器
    timeoutTimer.start(TIMEOUT);
    countdownTimer.start(1000);

    update();
}




void Game::on_pauseButton_clicked()
{
    int t=timeoutTimer.remainingTime();
    timeoutTimer.stop();
    countdownTimer.stop();

    QMessageBox::information(this,"暂停","继续游戏");
    timeoutTimer.start(t);
    countdownTimer.start(1000);

}


void Game::on_promptButton_clicked()
{

    if (gameMap.findHintPair(hintBlock1, hintBlock2)) {
        //qDebug()<<hintBlock1;
        update(); // 触发重绘

    } else {
        QMessageBox::information(this, "提示", "当前没有可消除的方块对");
    }
}

