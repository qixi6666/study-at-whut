/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *basicgamebutton;
    QPushButton *freegamebutton;
    QPushButton *gamebutton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpbutton;
    QPushButton *setbutton;
    QPushButton *rkbutton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/llk/1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow{border-image: url(:/llk/1.jpg);}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 80, 91, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        basicgamebutton = new QPushButton(layoutWidget);
        basicgamebutton->setObjectName("basicgamebutton");
        basicgamebutton->setMinimumSize(QSize(20, 40));

        verticalLayout->addWidget(basicgamebutton);

        freegamebutton = new QPushButton(layoutWidget);
        freegamebutton->setObjectName("freegamebutton");
        freegamebutton->setMinimumSize(QSize(20, 40));

        verticalLayout->addWidget(freegamebutton);

        gamebutton = new QPushButton(layoutWidget);
        gamebutton->setObjectName("gamebutton");
        gamebutton->setMinimumSize(QSize(20, 40));

        verticalLayout->addWidget(gamebutton);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(560, 520, 178, 21));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        helpbutton = new QPushButton(layoutWidget1);
        helpbutton->setObjectName("helpbutton");

        horizontalLayout->addWidget(helpbutton);

        setbutton = new QPushButton(layoutWidget1);
        setbutton->setObjectName("setbutton");

        horizontalLayout->addWidget(setbutton);

        rkbutton = new QPushButton(layoutWidget1);
        rkbutton->setObjectName("rkbutton");

        horizontalLayout->addWidget(rkbutton);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\277\236\350\277\236\347\234\213", nullptr));
        basicgamebutton->setText(QCoreApplication::translate("MainWindow", "\345\237\272\346\234\254\346\250\241\345\274\217", nullptr));
        freegamebutton->setText(QCoreApplication::translate("MainWindow", "\344\274\221\351\227\262\346\250\241\345\274\217", nullptr));
        gamebutton->setText(QCoreApplication::translate("MainWindow", "\345\205\263\345\215\241\346\250\241\345\274\217", nullptr));
        helpbutton->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        setbutton->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        rkbutton->setText(QCoreApplication::translate("MainWindow", "\346\216\222\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
