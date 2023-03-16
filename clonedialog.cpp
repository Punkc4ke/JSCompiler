#include "clonedialog.h"
#include "ui_clonedialog.h"

#include <qgit2.h>
#include <QMessageBox>
#include <QFileDialog>

CloneDialog::CloneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloneDialog)
{
    ui->setupUi(this);
}

CloneDialog::~CloneDialog()
{
    delete ui;
}

void CloneDialog::on_browseButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString dir = dialog.getExistingDirectory(this, "Выберите локальную папку", "/home/");
    ui->localDirEdit->setText(dir);
}

void CloneDialog::on_cloneButton_clicked()
{
    QString url = ui->urlEdit->text();
    if ((url == NULL) && (url == "") && (ui->urlEdit->text() == NULL)){
        QMessageBox urlBox;
        urlBox.setText("Введите URL удаленного репозитория.");
        urlBox.exec();
        return;
    }

    QByteArray urlb = url.toLocal8Bit();

    QString local_path = ui->localDirEdit->text();

    if ((local_path == NULL) && (local_path == "") && (ui->localDirEdit->text() == NULL)){
        QMessageBox local_pathBox;
        local_pathBox.setText("Укажите локальную папку.");
        local_pathBox.exec();
        return;
    }

    QByteArray local_pathb = local_path.toLocal8Bit();

    git_libgit2_init();

    git_repository *repo;

    QDir dir(local_path);
    dir.removeRecursively();

    int error_code = git_clone(&repo, urlb, local_pathb, NULL);

    git_libgit2_shutdown();

    if (error_code != 0) {
        QMessageBox errorBox;
        errorBox.setText("Ошибка клонирования репозитория.");
        errorBox.exec();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText("Репозиторий успешно клонирован.");
        messageBox.exec();
        ui->localDirEdit->setText(NULL);
        ui->urlEdit->setText(NULL);
        close();
    }
}
