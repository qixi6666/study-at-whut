#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include <QPixmap>

class GameMap {
public:
    GameMap(int rows, int cols);

    // 生成随机地图
    void generateRandomMap();
    //寻找两个能消除的点
    bool findHintPair(QPoint &p1, QPoint &p2);




    // 判断两个方块是否可以消除
    bool canEliminate(QPoint p1, QPoint p2);
    bool checkLine(QPoint p1,QPoint p2);
    bool checkconner(QPoint p1,QPoint p2);


    // 获取预加载的图片列表
    const QVector<QPixmap>& getBlockImages() const;

    int rows, cols;
    QVector<QVector<int>> map; // 存储图片索引（-1 表示已消除）
    QVector<QPixmap> blockImages; // 存储所有预加载的图片
};

#endif // GAMEMAP_H
