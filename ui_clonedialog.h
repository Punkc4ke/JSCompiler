/********************************************************************************
** Form generated from reading UI file 'clonedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLONEDIALOG_H
#define UI_CLONEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CloneDialog
{
public:
    QPushButton *cloneButton;
    QLineEdit *urlEdit;
    QLineEdit *localDirEdit;
    QLabel *label;
    QLabel *label_2;
    QPushButton *browseButton;

    void setupUi(QDialog *CloneDialog)
    {
        if (CloneDialog->objectName().isEmpty())
            CloneDialog->setObjectName(QString::fromUtf8("CloneDialog"));
        CloneDialog->setWindowModality(Qt::NonModal);
        CloneDialog->resize(630, 130);
        CloneDialog->setAutoFillBackground(false);
        CloneDialog->setSizeGripEnabled(false);
        CloneDialog->setModal(false);
        cloneButton = new QPushButton(CloneDialog);
        cloneButton->setObjectName(QString::fromUtf8("cloneButton"));
        cloneButton->setGeometry(QRect(500, 100, 121, 25));
        urlEdit = new QLineEdit(CloneDialog);
        urlEdit->setObjectName(QString::fromUtf8("urlEdit"));
        urlEdit->setGeometry(QRect(250, 10, 291, 25));
        localDirEdit = new QLineEdit(CloneDialog);
        localDirEdit->setObjectName(QString::fromUtf8("localDirEdit"));
        localDirEdit->setGeometry(QRect(250, 40, 291, 25));
        label = new QLabel(CloneDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 221, 21));
        label_2 = new QLabel(CloneDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 40, 131, 21));
        browseButton = new QPushButton(CloneDialog);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(550, 40, 71, 25));

        retranslateUi(CloneDialog);

        QMetaObject::connectSlotsByName(CloneDialog);
    } // setupUi

    void retranslateUi(QDialog *CloneDialog)
    {
        CloneDialog->setWindowTitle(QCoreApplication::translate("CloneDialog", "\320\232\320\273\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\200\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\320\271", nullptr));
        cloneButton->setText(QCoreApplication::translate("CloneDialog", "\320\232\320\273\320\276\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("CloneDialog", "URL \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\200\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\321\217:", nullptr));
        label_2->setText(QCoreApplication::translate("CloneDialog", "\320\233\320\276\320\272\320\260\320\273\321\214\320\275\320\260\321\217 \320\277\320\260\320\277\320\272\320\260:", nullptr));
        browseButton->setText(QCoreApplication::translate("CloneDialog", "\320\236\320\261\320\267\320\276\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CloneDialog: public Ui_CloneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLONEDIALOG_H
