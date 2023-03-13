#include "gitgui.h"
#include "ui_gitgui.h"

#include <qgit2.h>
#include <git2/branch.h>
#include <qgit2/libqgit2_export.h>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>

GitGui::GitGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GitGui)
{
    ui->setupUi(this);
    ui->listWidget->addItem("Line1");
    ui->listWidget->addItem("Line1\nLine2");
}

GitGui::~GitGui()
{
    delete ui;
}

void GitGui::on_addButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString path = dialog.getExistingDirectory(this, "Добавить репозиторий", "/home/");

    QString dir = path.right(path.size()-path.lastIndexOf("/")-1);

    QByteArray pathb = path.toLocal8Bit();

    git_libgit2_init();

    git_repository *repo;

    int error = git_repository_open(&repo, pathb);

    git_object *head_commit;
    error = git_revparse_single(&head_commit, repo, "HEAD^{commit}");
    git_commit *commit = (git_commit*)head_commit;

    const char *header = git_commit_raw_header(commit);

    const git_signature *author = git_commit_author(commit);

//    const char *message = git_commit_message(commit);
//    const char *repo_path = git_repository_path(repo);
//    const char *summmary = git_commit_summary(commit);
//    const char *encoding = git_commit_message_encoding(commit);


    ui->listWidget->addItem(dir+"\n"+path+"lol");

    git_libgit2_shutdown();
}


void GitGui::on_cloneButton_clicked()
{
    clonedialog.setFixedSize(630, 130);
    clonedialog.move(1100, 300);
    clonedialog.setModal(true);
    clonedialog.exec();
}

void GitGui::on_deleteButton_clicked()
{

    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());

    QMessageBox msgBox;
    msgBox.move(1200, 300);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText("Удалить репозиторий из списка?");
    QPushButton *cancelButton = msgBox.addButton(tr("Отмена"), QMessageBox::ActionRole);
    QPushButton *acceptButton = msgBox.addButton(tr("Ок"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(acceptButton);
    msgBox.exec();

    if (msgBox.clickedButton() == acceptButton) {
       delete it;
    } else if (msgBox.clickedButton() == cancelButton) {
        msgBox.close();
    }
}

