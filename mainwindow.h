#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScriptEngine>
#include <QJSEngine>
#include <QDir>
#include <QFileSystemModel>
#include <QFileDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_execPushButton_clicked();

    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_saveResultButton_clicked();

private:
    Ui::MainWindow *ui;
    QJSEngine engine;
    QFileSystemModel *model;
};

#endif // MAINWINDOW_H
