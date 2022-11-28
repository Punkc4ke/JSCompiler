#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJSEngine>
#include <QScriptContext>
#include <QScriptValue>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>

#include "js_object.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->execPushButton, &QPushButton::clicked, this, &MainWindow::on_execPushButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_execPushButton_clicked()
{
    Factory *factory = new Factory;
    QJSValue jsFactory = engine.newQObject(factory);
    engine.globalObject().setProperty("operator", jsFactory);

// var t = operator.foo(); t.plus("/home/alexey/Рабочий стол/Результаты.txt");

    QString scriptCode = ui->javaScriptTextEdit->toPlainText();
    QJSValue result = engine.evaluate(scriptCode);
    ui->resultTextEdit->setPlainText(result.toString());

//       if (engine.hasUncaughtException()){
//           QString errPattern = "line %1: %2";
//           qDebug()<<errPattern.arg(QString::number(scriptEngine.uncaughtExceptionLineNumber()), scriptEngine.uncaughtException().toString());
//           return;
//       }
}


void MainWindow::on_openButton_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this, "Выберите скрипт", "/home/alexey/Рабочий стол" , "All Files (*.*);; JS Script (*.js)");
    ui->label->setText(str);
    if (str.isEmpty()){
        return;
    }
    else {
    QFile file(str);

    file.open(QIODevice::ReadWrite|QIODevice::Text);

    file.seek(0);
    QByteArray text = file.readAll();

    ui->javaScriptTextEdit->setPlainText(text);

    file.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
     QString  scriptCode = ui->javaScriptTextEdit->toPlainText();
     QString str;
     str = ui->label->text();

     QFile file(str);
     if(file.exists()==false){
         str = "";
         ui->label->setText(str);
         return;
     }
     if (scriptCode.isNull()){
         return;
     }
     if (str.isNull()){
         return;
     }

     file.open(QIODevice::ReadWrite|QIODevice::Text);

     file.seek(0);
     QString text = ui->javaScriptTextEdit->toPlainText();
     QByteArray text1 = text.toUtf8();
     file.write(text1);

     file.close();

}

void MainWindow::on_saveResultButton_clicked()
{
//    QString result = ui->resultTextEdit->toPlainText();
//    if (result.isNull() == true){
//        return;
//    }
//    else {
    QFile file("/home/alexey/Рабочий стол/Результаты.txt");

    file.open(QIODevice::WriteOnly);

    QString text = ui->resultTextEdit->toPlainText();
    QByteArray text1 = text.toUtf8();
    file.write(text1);

    file.close();

}


void MainWindow::on_saveHowButton_clicked()
{


    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить как", "/home/alexey/Рабочий стол", "All Files (*.*);; JS Script (*.js)");
    if (fileName.isEmpty()){
        return;
    }
    else {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);

       QString text = ui->javaScriptTextEdit->toPlainText();
       QByteArray text1 = text.toUtf8();
             file.write(text1);

       file.close();

       ui->label->setText(fileName);

    }
}
