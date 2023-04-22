#ifndef GITGUI_H
#define GITGUI_H

#include <QWidget>
#include <QListWidgetItem>
#include <qgit2.h>
#include <QDialog>
#include <QLineEdit>
#include <clonedialog.h>
#include <commit.h>
#include <QVector>
#include <QFileSystemModel>

namespace Ui {
class GitGui;
}

class GitGui : public QWidget
{
    Q_OBJECT

public:
    explicit GitGui(QWidget *parent = nullptr);
    ~GitGui();

private slots:
    void on_addButton_clicked();

    void on_cloneButton_clicked();

    void on_deleteButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *it);

    void on_backButton_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_listWidget_currentRowChanged(int currentRow);

    void on_listWidget_4_itemClicked(QListWidgetItem *item);

    void TreeWidgetMenuSlot(const QPoint &pos);

    void MenuActionSlot(QAction *act);

//    void contextMenuEvent(QContextMenuEvent *event);

    void on_listWidget_3_itemClicked(QListWidgetItem *item);

    void on_acceptButtonClicked();

    void on_cancelButtonClicked();

    void TreeWidgetMenuSlot2(const QPoint &pos);

    void MenuActionSlot2(QAction *act);

    void on_treeView_clicked(const QModelIndex &index);

    void on_loadButton_clicked();

private:
    Ui::GitGui *ui;
    CloneDialog clonedialog;
    git_repository *repo;
    QMenu *menu;
    QMenu *menu_2;
    QDialog dialog;
    QLineEdit *lineEdit;
    QVector <Commit> commits;
    QFileSystemModel *model;
};

#endif // GITGUI_H
