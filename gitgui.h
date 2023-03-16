#ifndef GITGUI_H
#define GITGUI_H

#include <QWidget>
#include <clonedialog.h>

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

    void on_searchButton_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::GitGui *ui;
    CloneDialog clonedialog;
};

#endif // GITGUI_H
