#include "gitgui.h"
#include "ui_gitgui.h"

#include <qgit2.h>
#include <git2/branch.h>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>

GitGui::GitGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GitGui)
{
    ui->setupUi(this);
    ui->deleteButton->setEnabled(false);
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

    if (path ==NULL){
        return;
    }

    QString dir = path.right(path.size()-path.lastIndexOf("/")-1);

    QByteArray pathb = path.toLocal8Bit();

    QDir git(path + "/.git");
    if(!git.exists()){

        QMessageBox msgBox;
        msgBox.move(1050, 300);
        msgBox.setWindowTitle("Создание нового репозитория");
        msgBox.setText(path + " не явялется git репозиторием. Хотите инициализировать новый git репозиторий в этой папке?");
        QPushButton *cancelButton = msgBox.addButton(tr("Отменить"), QMessageBox::ActionRole);
        QPushButton *acceptButton = msgBox.addButton(tr("Создать репозиторий"), QMessageBox::ActionRole);
        msgBox.setDefaultButton(acceptButton);
        msgBox.exec();

        if (msgBox.clickedButton() == acceptButton) {

            git_libgit2_init();

            git_signature *sig;
            git_index *index;
            git_oid tree_id, commit_id;
            git_tree *tree;

            git_repository *repo;

            int error_code = git_repository_init(&repo, pathb, false);

            git_signature_default(&sig, repo);
            git_repository_index(&index, repo);
            git_index_write_tree(&tree_id, index);
            git_tree_lookup(&tree, repo, &tree_id);
            git_commit_create_v(&commit_id, repo, "HEAD", sig, sig, NULL, "Initial commit", tree, 0);

            git_repository_open(&repo, pathb);

            const char *branch = NULL;
            git_reference *head = NULL;

            git_repository_head(&head, repo);

            branch = git_reference_shorthand(head);

            ui->listWidget->addItem(dir+"\n"+branch+" в "+path);

            git_libgit2_shutdown();
        } else if (msgBox.clickedButton() == cancelButton) {
            msgBox.close();
        }
    }
    else{

        git_libgit2_init();

        git_repository *repo;

        int error = git_repository_open(&repo, pathb);

        git_object *head_commit;
        error = git_revparse_single(&head_commit, repo, "HEAD^{commit}");
        git_commit *commit = (git_commit*)head_commit;

        const char *header = git_commit_raw_header(commit);

        const git_signature *author = git_commit_author(commit);

        int error_br = 0;
        const char *branch = NULL;
        git_reference *head = NULL;

        error_br = git_repository_head(&head, repo);

        branch = git_reference_shorthand(head);

    //    const char *message = git_commit_message(commit);
    //    const char *repo_path = git_repository_path(repo);
    //    const char *summmary = git_commit_summary(commit);
    //    const char *encoding = git_commit_message_encoding(commit);

        ui->listWidget->addItem(dir+"\n"+branch+" в "+path);

        git_libgit2_shutdown();
    }
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
    QPushButton *cancelButton = msgBox.addButton(tr("Отменить"), QMessageBox::ActionRole);
    QPushButton *acceptButton = msgBox.addButton(tr("Ок"), QMessageBox::ActionRole);
    msgBox.setDefaultButton(acceptButton);
    msgBox.exec();

    if (msgBox.clickedButton() == acceptButton) {
       delete it;
    } else if (msgBox.clickedButton() == cancelButton) {
        msgBox.close();
    }
}


void GitGui::on_searchButton_clicked()
{
    QListWidgetItem *item;
    QList<QListWidgetItem *> found = ui->listWidget->findItems(ui->searchLineEdit->text(), Qt::MatchContains);//возвращает пустой лист
    for (int i=0;i<found.count();i++){
        ui->listWidget->setItemSelected(item,true);
    }
}

void GitGui::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0){
        ui->deleteButton->setEnabled(true);
    }
    else{
        ui->deleteButton->setEnabled(false);
    }
}
