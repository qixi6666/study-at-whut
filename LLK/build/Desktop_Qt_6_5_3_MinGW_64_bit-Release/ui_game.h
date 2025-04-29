/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pauseButton;
    QPushButton *restartButton;
    QPushButton *promptButton;
    QLabel *label;
    QLineEdit *scoreEdit;
    QProgressBar *timeprogressBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName("Game");
        Game->resize(800, 800);
        Game->setMinimumSize(QSize(800, 800));
        Game->setMaximumSize(QSize(800, 800));
        Game->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/llk/1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Game->setWindowIcon(icon);
        Game->setAnimated(true);
        centralwidget = new QWidget(Game);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 10, 178, 20));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pauseButton = new QPushButton(layoutWidget);
        pauseButton->setObjectName("pauseButton");

        horizontalLayout->addWidget(pauseButton);

        restartButton = new QPushButton(layoutWidget);
        restartButton->setObjectName("restartButton");

        horizontalLayout->addWidget(restartButton);

        promptButton = new QPushButton(layoutWidget);
        promptButton->setObjectName("promptButton");

        horizontalLayout->addWidget(promptButton);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 10, 31, 21));
        scoreEdit = new QLineEdit(centralwidget);
        scoreEdit->setObjectName("scoreEdit");
        scoreEdit->setGeometry(QRect(450, 10, 51, 20));
        timeprogressBar = new QProgressBar(centralwidget);
        timeprogressBar->setObjectName("timeprogressBar");
        timeprogressBar->setGeometry(QRect(220, 10, 171, 20));
        timeprogressBar->setMinimum(100);
        timeprogressBar->setValue(99);
        Game->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Game);
        statusbar->setObjectName("statusbar");
        Game->setStatusBar(statusbar);

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QMainWindow *Game)
    {
        Game->setWindowTitle(QCoreApplication::translate("Game", "\345\237\272\346\234\254\346\250\241\345\274\217", nullptr));
        pauseButton->setText(QCoreApplication::translate("Game", "\346\232\202\345\201\234", nullptr));
        restartButton->setText(QCoreApplication::translate("Game", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
        promptButton->setText(QCoreApplication::translate("Game", "\346\217\220\347\244\272", nullptr));
        label->setText(QCoreApplication::translate("Game", "\345\210\206\346\225\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
