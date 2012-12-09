/********************************************************************************
** Form generated from reading UI file 'face.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_H
#define UI_FACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_face
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *face)
    {
        if (face->objectName().isEmpty())
            face->setObjectName(QString::fromUtf8("face"));
        face->resize(640, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(face->sizePolicy().hasHeightForWidth());
        face->setSizePolicy(sizePolicy);
        face->setMinimumSize(QSize(530, 400));
        face->setBaseSize(QSize(100, 100));
        face->setAutoFillBackground(true);
        centralwidget = new QWidget(face);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        face->setCentralWidget(centralwidget);
        menubar = new QMenuBar(face);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
        face->setMenuBar(menubar);
        statusbar = new QStatusBar(face);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        face->setStatusBar(statusbar);

        retranslateUi(face);

        QMetaObject::connectSlotsByName(face);
    } // setupUi

    void retranslateUi(QMainWindow *face)
    {
        face->setWindowTitle(QApplication::translate("face", "face", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class face: public Ui_face {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_H
