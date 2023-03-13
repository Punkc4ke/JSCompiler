/********************************************************************************
** Form generated from reading UI file 'gitgui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GITGUI_H
#define UI_GITGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GitGui
{
public:
    QWidget *widget;
    QPushButton *cloneButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QListWidget *listWidget;

    void setupUi(QWidget *GitGui)
    {
        if (GitGui->objectName().isEmpty())
            GitGui->setObjectName(QString::fromUtf8("GitGui"));
        GitGui->resize(792, 581);
        widget = new QWidget(GitGui);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 871, 611));
        cloneButton = new QPushButton(widget);
        cloneButton->setObjectName(QString::fromUtf8("cloneButton"));
        cloneButton->setGeometry(QRect(10, 10, 111, 25));
        addButton = new QPushButton(widget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(130, 10, 89, 25));
        deleteButton = new QPushButton(widget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(230, 10, 89, 25));
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(170, 50, 461, 511));

        retranslateUi(GitGui);

        QMetaObject::connectSlotsByName(GitGui);
    } // setupUi

    void retranslateUi(QWidget *GitGui)
    {
        GitGui->setWindowTitle(QCoreApplication::translate("GitGui", "\320\240\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\320\270", nullptr));
        cloneButton->setText(QCoreApplication::translate("GitGui", "\320\232\320\273\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        addButton->setText(QCoreApplication::translate("GitGui", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("GitGui", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GitGui: public Ui_GitGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GITGUI_H
