#include "gamemap.h"
#include<qpoint.h>
#include<algorithm>
#include <QDebug>

GameMap::GameMap(int rows,int cols):rows(rows),cols(cols) {
     map.resize(rows, QVector<int>(cols, -1));

    // 加载所有图片并缩放（假设图片大小为 64x64）
    QStringList imagePaths = {
        ":/llk/game1.jpg",
        ":/llk/game2.jpg",
        ":/llk/game3.jpg",
        ":/llk/game4.jpg",
        ":/llk/game5.jpg",
        ":/llk/game6.jpg"
    };

    for (const QString &path : imagePaths) {
        QPixmap pixmap(path);
        pixmap = pixmap.scaled(64, 64, Qt::KeepAspectRatio);
        blockImages.append(pixmap);
    }
    generateRandomMap();

}
void GameMap::generateRandomMap() {
    // 确保行数和列数为偶数
    if ((rows * cols) % 2 != 0) {
        qDebug() << "行数×列数必须是偶数！";
        return;
    }

   // qDebug()<<"地图";
    // 填充到地图
    int index = 0;
     QVector<int> allElements;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = index%blockImages.size();
            allElements.append(map[i][j]);
        }
        index++;
    }
    //打乱顺序
    std::random_shuffle(allElements.begin(), allElements.end());
    index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            map[i][j] = allElements[index++];
        }
    }

}

bool GameMap::checkLine(QPoint p1,QPoint p2){
    if (p1.x() == p2.x()) {
        int minY = std::min(p1.y(), p2.y());
        int maxY = std::max(p1.y(), p2.y());
        for (int y = minY + 1; y < maxY; ++y) {
            if (map[p1.x()][y] != -1) return false; // 路径有障碍
        }
        return true;
    }
    // 同一列
    if (p1.y() == p2.y()) {
        int minX = std::min(p1.x(), p2.x());
        int maxX = std::max(p1.x(), p2.x());
        for (int x = minX + 1; x < maxX; ++x) {
            if (map[x][p1.y()] != -1) return false;
        }
        return true;
    }
    return false;
}
bool GameMap:: checkconner(QPoint p1,QPoint p2){
    QPoint conner1=QPoint(p1.x(),p2.y());
    QPoint conner2=QPoint(p2.x(),p1.y());
    if(map[conner1.x()][conner1.y()]==-1&&checkLine(conner1,p1)&&checkLine(conner1,p2)){
        return true;
    }
    if(map[conner2.x()][conner2.y()]==-1&&checkLine(conner2,p1)&&checkLine(conner2,p2)){
        return true;
    }
    return false;
}
bool GameMap::canEliminate(QPoint p1, QPoint p2){
    if(map[p1.x()][p1.y()]!=map[p2.x()][p2.y()]){
        return false;
    }
    if(p1==p2){
        return false;
    }
    //同一直线消子
    if(checkLine(p1,p2))return true;

    //一条折线消子
    if(checkconner(p1,p2))return true;

    //两条折线消子
    // 扫描横向边界（左右两侧）
    for (int x = 0; x < rows; x++) {
        QPoint c1(x, p1.y());
        QPoint c2(x, p2.y());
        if (map[x][p1.y()] == -1 && map[x][p2.y()] == -1) {
            if (checkLine(p1, c1) && checkLine(c1, c2) && checkLine(c2, p2)) {
                return true;
            }
        }
    }

    // 扫描纵向边界（上下两侧）
    for (int y = 0; y < cols; y++) {
        QPoint c1(p1.x(), y);
        QPoint c2(p2.x(), y);
        if (map[p1.x()][y] == -1 && map[p2.x()][y] == -1) {
            if (checkLine(p1, c1) && checkLine(c1, c2) && checkLine(c2, p2)) {
                return true;
            }
        }
    }

    return false;


 }
bool GameMap:: findHintPair(QPoint &p1, QPoint &p2){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == -1) continue;

            // 1. 同一行，右侧的方块
            for (int y = j + 1; y < cols; ++y) {
                if (map[i][y] == -1) continue;
                if (map[i][j] == map[i][y] && canEliminate(QPoint(i, j), QPoint(i, y))) {
                    p1 = QPoint(i, j);
                    p2 = QPoint(i, y);
                    return true;
                }
            }

            // 2. 后续所有行，所有列
            for (int x = i + 1; x < rows; ++x) {
                for (int y = 0; y < cols; ++y) {
                    if (map[x][y] == -1) continue;
                    if (map[i][j] == map[x][y] && canEliminate(QPoint(i, j), QPoint(x, y))) {
                        p1 = QPoint(i, j);
                        p2 = QPoint(x, y);
                        return true;
                    }
                }
            }
        }
    }
    return false;

}



