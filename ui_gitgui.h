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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
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
    QWidget *widget_2;
    QPushButton *backButton;
    QListWidget *listWidget_2;
    QLabel *label;
    QListWidget *listWidget_3;
    QLabel *label_2;
    QListWidget *listWidget_4;
    QTextBrowser *textBrowser;
    QTreeView *treeView;
    QTextBrowser *textBrowser_2;

    void setupUi(QWidget *GitGui)
    {
        if (GitGui->objectName().isEmpty())
            GitGui->setObjectName(QString::fromUtf8("GitGui"));
        GitGui->resize(792, 581);
        widget = new QWidget(GitGui);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        widget->setGeometry(QRect(0, 0, 792, 581));
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
        widget_2 = new QWidget(GitGui);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 792, 581));
        backButton = new QPushButton(widget_2);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(10, 10, 31, 25));
        listWidget_2 = new QListWidget(widget_2);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(10, 60, 161, 91));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 67, 17));
        listWidget_3 = new QListWidget(widget_2);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));
        listWidget_3->setGeometry(QRect(170, 60, 611, 221));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 150, 91, 17));
        listWidget_4 = new QListWidget(widget_2);
        listWidget_4->setObjectName(QString::fromUtf8("listWidget_4"));
        listWidget_4->setGeometry(QRect(10, 170, 161, 111));
        textBrowser = new QTextBrowser(widget_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(170, 280, 611, 81));
        treeView = new QTreeView(widget_2);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 360, 161, 211));
        textBrowser_2 = new QTextBrowser(widget_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(170, 360, 611, 211));
        listWidget_3->raise();
        backButton->raise();
        listWidget_2->raise();
        label->raise();
        label_2->raise();
        listWidget_4->raise();
        textBrowser->raise();
        treeView->raise();
        textBrowser_2->raise();

        retranslateUi(GitGui);
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), listWidget, SLOT(show()));

        QMetaObject::connectSlotsByName(GitGui);
    } // setupUi

    void retranslateUi(QWidget *GitGui)
    {
        GitGui->setWindowTitle(QCoreApplication::translate("GitGui", "\320\240\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\320\270", nullptr));
        cloneButton->setText(QCoreApplication::translate("GitGui", "\320\232\320\273\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        addButton->setText(QCoreApplication::translate("GitGui", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("GitGui", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        backButton->setText(QCoreApplication::translate("GitGui", "<", nullptr));
        label->setText(QCoreApplication::translate("GitGui", "\320\222\320\265\321\202\320\262\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("GitGui", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GitGui: public Ui_GitGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GITGUI_H
