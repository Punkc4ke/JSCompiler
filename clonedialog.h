#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include <QDialog>

namespace Ui {
class CloneDialog;
}

class CloneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloneDialog(QWidget *parent = nullptr);
    ~CloneDialog();

private slots:

    void on_browseButton_clicked();

    void on_cloneButton_clicked();

private:
    Ui::CloneDialog *ui;
};

#endif // CLONEDIALOG_H
