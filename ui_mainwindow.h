/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "Qsci/qsciscintilla.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *execPushButton;
    QPlainTextEdit *resultTextEdit;
    QPushButton *openButton;
    QPushButton *saveButton;
    QLabel *label;
    QPushButton *saveResultButton;
    QLabel *label_2;
    QPushButton *saveHowButton;
    QsciScintilla *textEdit1;
    QPushButton *repoButton;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(792, 581);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        execPushButton = new QPushButton(centralwidget);
        execPushButton->setObjectName(QString::fromUtf8("execPushButton"));
        execPushButton->setGeometry(QRect(10, 520, 771, 25));
        resultTextEdit = new QPlainTextEdit(centralwidget);
        resultTextEdit->setObjectName(QString::fromUtf8("resultTextEdit"));
        resultTextEdit->setGeometry(QRect(10, 380, 771, 131));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(10, 10, 89, 25));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(240, 10, 171, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 771, 20));
        saveResultButton = new QPushButton(centralwidget);
        saveResultButton->setObjectName(QString::fromUtf8("saveResultButton"));
        saveResultButton->setGeometry(QRect(420, 10, 161, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 360, 81, 17));
        saveHowButton = new QPushButton(centralwidget);
        saveHowButton->setObjectName(QString::fromUtf8("saveHowButton"));
        saveHowButton->setGeometry(QRect(110, 10, 121, 25));
        textEdit1 = new QsciScintilla(centralwidget);
        textEdit1->setObjectName(QString::fromUtf8("textEdit1"));
        textEdit1->setEnabled(true);
        textEdit1->setGeometry(QRect(10, 60, 771, 281));
        textEdit1->setFrameShadow(QFrame::Sunken);
        repoButton = new QPushButton(centralwidget);
        repoButton->setObjectName(QString::fromUtf8("repoButton"));
        repoButton->setGeometry(QRect(590, 10, 111, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 792, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        execPushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        label->setText(QString());
        saveResultButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202:", nullptr));
        saveHowButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
#if QT_CONFIG(tooltip)
        textEdit1->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        textEdit1->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        repoButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
