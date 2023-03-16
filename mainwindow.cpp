#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJSEngine>
#include <QScriptContext>
#include <QScriptValue>
#include <QFile>
#include <QtGui>
#include <QColor>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerjavascript.h>

#include <js_object.h>

#include <qgit2.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->execPushButton, &QPushButton::clicked, this, &MainWindow::on_execPushButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);

    ui->textEdit1->setUtf8(true);// мы же хотим читать кириллицу
    QsciLexerJavaScript * lexJS = new QsciLexerJavaScript(this);// создаем лексер (схему подсветки)
    ui->textEdit1->setLexer(lexJS); // задаем С++ лексер нашему редактору

    //! Текущая строка кода и ее подсветка
    ui->textEdit1->setCaretLineVisible(true);
    ui->textEdit1->setCaretLineBackgroundColor(QColor("gainsboro"));

    //! Выравнивание
    ui->textEdit1->setAutoIndent(true);
    ui->textEdit1->setIndentationGuides(false);
    ui->textEdit1->setIndentationsUseTabs(true);
    ui->textEdit1->setIndentationWidth(4);

    //! margin это полоска слева, на которой обычно распологаются breakpoints
    ui->textEdit1->setMarginsBackgroundColor(QColor("gainsboro"));
    ui->textEdit1->setMarginLineNumbers(1, true);
    ui->textEdit1->setMarginWidth(1, 25);

    //! Авто-дополнение кода в зависимости от источника
    ui->textEdit1->setAutoCompletionSource(QsciScintilla::AcsAll);
    ui->textEdit1->setAutoCompletionCaseSensitivity(true);
    ui->textEdit1->setAutoCompletionReplaceWord(true);
    ui->textEdit1->setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
    ui->textEdit1->setAutoCompletionThreshold(0);

    //! Подсветка соответствий скобок
    ui->textEdit1->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    ui->textEdit1->setMatchedBraceBackgroundColor(Qt::green);
    ui->textEdit1->setUnmatchedBraceForegroundColor(Qt::blue);

//    git_libgit2_init();
//    git_repository *repo;

//    int error_code = git_repository_init(&repo, "/home/alexey/TestRepo", false);
//    qDebug()<<error_code;

//    git_libgit2_shutdown();
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

    QString scriptCode = ui->textEdit1->text();
    QJSValue result = engine.evaluate(scriptCode);
    ui->resultTextEdit->setPlainText(result.toString());
}

void MainWindow::on_openButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, "Выберите скрипт", "/home/alexey/Рабочий стол" , "All Files (*.*);; JS Script (*.js)");
    ui->label->setText(str);
    if (str.isEmpty()){
        return;
    }
    else{
        QFile file(str);

        file.open(QIODevice::ReadWrite|QIODevice::Text);

        file.seek(0);
        QByteArray text = file.readAll();

        ui->textEdit1->setText(text);

        file.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString  scriptCode = ui->textEdit1->text();
    QString str = ui->label->text();

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
    QString text = ui->textEdit1->text();
    QByteArray text1 = text.toUtf8();
    file.write(text1);

    file.close();
}

void MainWindow::on_saveResultButton_clicked()
{
    QFile file("/home/alexey/Desktop/Результаты.txt");

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

        QString text = ui->textEdit1->text();
        QByteArray text1 = text.toUtf8();

        file.write(text1);

        file.close();

        ui->label->setText(fileName);
    }
}

QString QsciLexerJavaScript::description(int style) const
{
    switch(style) {
        case Default:
            return "Default";
        case Comment:
            return "Comment";
        case Keyword:
            return "Keyword";
        case Number:
            return "Number";
    }
    return QString(style);
}

QColor QsciLexerJavaScript::defaultColor(int style) const
{
    switch(style) {
        case Comment:
            return Qt::green;
        case Keyword:
            return QColor(128, 166, 255);
        case Number:
            return QColor(128, 0, 128);
        case Operator:
            return QColor(224, 207, 177);
        case DoubleQuotedString:
           return QColor(119, 221, 119);
    }
    return Qt::black;
}

void MainWindow::on_repoButton_clicked()
{
    gitgui.move(950, 80);
    gitgui.show();
}
