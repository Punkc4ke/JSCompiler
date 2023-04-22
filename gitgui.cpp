#include "gitgui.h"
#include "ui_gitgui.h"

#include <qgit2.h>
#include <libqgit2/qgit2.h>
#include <git2/branch.h>
#include <qgit2/libqgit2_export.h>

#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>
#include <QMenu>
#include <QVector>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFileSystemModel>
#include <QDir>
#include <mainwindow.h>

#include <commit.h>

GitGui::GitGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GitGui),
    menu(NULL),
    menu_2(NULL)
{
    ui->setupUi(this);

    ui->widget_2->hide();

    ui->listWidget_3->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->listWidget_3, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(TreeWidgetMenuSlot(const QPoint &)));
    connect(ui->listWidget_2, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(TreeWidgetMenuSlot2(const QPoint &)));

    ui->deleteButton->setEnabled(false);

    QPushButton *acceptButton = new QPushButton();
    QPushButton *cancelButton = new QPushButton();

    acceptButton->setText("Создать");
    cancelButton->setText("Отменить");

    connect(acceptButton, SIGNAL(clicked()), this, SLOT(on_acceptButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButtonClicked()));

    dialog.move(1200, 300);
    dialog.setModal(true);
    dialog.setWindowTitle("Создать ветку");

    QBoxLayout *layout1 = new QHBoxLayout;

    lineEdit = new QLineEdit;
    lineEdit->setFixedWidth(150);

    QLabel *label = new QLabel;
    label->setText("Название ветки:");

    layout1->addWidget(label);
    layout1->addWidget(lineEdit);
    layout1->addWidget(acceptButton);
    layout1->addWidget(cancelButton);

    dialog.setLayout(layout1);
}

//void GitGui::contextMenuEvent(QContextMenuEvent *)
//{
//    QMenu *menu = new QMenu(ui->listWidget_3);
//     menu-> addAction (tr ( "Elixir"));
//     menu-> addAction (tr ( "Homecoming"));
//    menu->exec(QCursor::pos());
//}

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

void GitGui::on_listWidget_itemDoubleClicked(QListWidgetItem *it)
{
    ui->listWidget_2->clear();

    QString txt = ui->listWidget->currentItem()->text();

    QString dir = txt.right(txt.size()-txt.lastIndexOf("в ")-1);

    dir = dir.remove(0,1);

    QByteArray dirb = dir.toLocal8Bit();

    git_libgit2_init();

    git_repository_open(&repo, dirb);

    const char *workdir = git_repository_workdir(repo);

    ui->widget->hide();
    ui->widget_2->show();

    const char *branch = NULL;
    git_reference *head = NULL;

    QString str;

    git_repository_head(&head, repo);

    git_branch_iterator *iterator;

    if (!git_branch_iterator_new(&iterator, repo, GIT_BRANCH_ALL)) {
      git_reference *ref;
      git_branch_t type;
      int i = 0;
      while (!git_branch_next(&ref, &type, iterator)) {

        // Do something with 'ref' and 'type'.
        branch = git_reference_shorthand(ref);
        str = branch ;
        if (str.contains("origin")){
            ui->listWidget_4->addItem(branch);
            git_reference_free(ref);
            if(ui->listWidget_4->item(i)->text().contains("HEAD")){
                    delete ui->listWidget_4->item(i);
            }
        }
        else{
            ui->listWidget_2->addItem(branch);
            git_reference_free(ref);
        }
      }
      git_branch_iterator_free(iterator);
    }
    git_libgit2_shutdown();
}

void GitGui::on_backButton_clicked()
{
    git_libgit2_init();
    git_repository_free(repo);
    git_libgit2_shutdown();

    setWindowTitle("Репозитории");

//    ui->listWidget_3->clear();
//    ui->listWidget_4->clear();
//    ui->textBrowser->clear();
//    ui->textBrowser_2->clear();
//    ui->treeView->setModel(NULL);

    ui->widget_2->hide();
    ui->widget->show();
}

void GitGui::on_listWidget_2_itemClicked(QListWidgetItem *it)
{
    commits.clear();

    ui->listWidget_3->clear();

    ui->listWidget_4->clearSelection();

    git_object *treeish = NULL;
    git_checkout_options opt = GIT_CHECKOUT_OPTIONS_INIT;
    opt.checkout_strategy = GIT_CHECKOUT_FORCE;

    QString  str = ui->listWidget_2->currentItem()->text();

    const char *branchToCheckOut = str.toUtf8();

    git_revparse_single(&treeish, repo, branchToCheckOut);

    git_checkout_tree(repo, treeish, &opt);

    git_object_free(treeish);

    ui->textBrowser_2->clear();

    QString branchName = ui->listWidget_2->currentItem()->text();

    git_libgit2_init();

    const char *workdir = git_repository_workdir(repo);

    QString path = ".git/refs/heads/"+branchName;

    const char *pathc = path.toUtf8();

        if(git_repository_open(&repo, workdir) != 0){
            return;
        }

        // Read HEAD on master
        char head_filepath[512];
        FILE *head_fileptr;
        char head_rev[41];

        strcpy(head_filepath, workdir);

        strcat(head_filepath, pathc);

        if((head_fileptr = fopen(head_filepath, "r")) == NULL){
            qDebug()<<head_filepath;
            return;
        }

        if(fread(head_rev, 40, 1, head_fileptr) != 1){
            qDebug()<<"Error reading from '%s'\n", head_filepath;
            fclose(head_fileptr);
            return;
        }

        fclose(head_fileptr);

        git_oid oid;
        git_revwalk *walker;
        git_commit *commit;

        if(git_oid_fromstr(&oid, head_rev) != 0){
            qDebug()<<"Invalid git object", head_rev;
            return;
        }

        git_revwalk_new(&walker, repo);
        git_revwalk_sorting(walker, GIT_SORT_TOPOLOGICAL);
        git_revwalk_push(walker, &oid);

        const char *commit_message;
        const git_signature *commit_author;

        while(git_revwalk_next(&oid, walker) == 0) {
            if(git_commit_lookup(&commit, repo, &oid)){
                qDebug()<<"Failed to lookup the next object";
                return;
            }

            commit_message = git_commit_message(commit);
            commit_author = git_commit_committer(commit);

            ui->listWidget_3->addItem(commit_message);

            Commit lol;

            lol.set_hash_commit(commit, commit_message);

            commits.push_back(lol);

            git_commit_free(commit);
        }


        branchName == NULL;
        path == NULL;
        pathc = NULL;
        head_filepath[512] = NULL;
        head_fileptr = NULL;
        head_rev[41] = NULL;

        git_revwalk_free(walker);

        return;

    git_libgit2_shutdown();
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

void GitGui::on_listWidget_4_itemClicked(QListWidgetItem *item)
{
    commits.clear();

    ui->listWidget_3->clear();

    ui->listWidget_2->clearSelection();

    QString branchName = ui->listWidget_4->currentItem()->text();

    git_libgit2_init();

    const char *workdir = git_repository_workdir(repo);

    QString path = ".git/refs/remotes/"+branchName;

    const char *pathc = path.toLocal8Bit();

        if(git_repository_open(&repo, workdir) != 0){
            return;
        }

        // Read HEAD on master
        char head_filepath[512];
        FILE *head_fileptr;
        char head_rev[41];

        strcpy(head_filepath, workdir);

            strcat(head_filepath, pathc);

        if((head_fileptr = fopen(head_filepath, "r")) == NULL){
            qDebug()<<head_filepath;
            return;
        }

        if(fread(head_rev, 40, 1, head_fileptr) != 1){
            qDebug()<<"Error reading from '%s'\n", head_filepath;
            fclose(head_fileptr);
            return;
        }

        fclose(head_fileptr);

        git_oid oid;
        git_revwalk *walker;
        git_commit *commit;
        QString str;

        if(git_oid_fromstr(&oid, head_rev) != 0){
            qDebug()<<"Invalid git object", head_rev;
            return;
        }

        git_revwalk_new(&walker, repo);
        git_revwalk_sorting(walker, GIT_SORT_TOPOLOGICAL);
        git_revwalk_push(walker, &oid);

        const char *commit_message;
        const git_signature *commit_author;
        const git_oid *commit_id;

        while(git_revwalk_next(&oid, walker) == 0) {
            if(git_commit_lookup(&commit, repo, &oid)){
                qDebug()<<"Failed to lookup the next object";
                return;
            }

            commit_message = git_commit_message(commit);
            commit_author = git_commit_committer(commit);
            commit_id = git_commit_id(commit);

            str = commit_message;

            ui->listWidget_3->addItem(str);

            Commit lol;

            lol.set_hash_commit(commit, commit_message);

            commits.push_back(lol);

            git_commit_free(commit);
        }

        git_revwalk_free(walker);

        return;

    git_libgit2_shutdown();
}

void GitGui::TreeWidgetMenuSlot(const QPoint &)
{
    if (menu == NULL)
    {
        menu = new QMenu(this);
        connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(MenuActionSlot(QAction *)));
    }
    menu->clear();
     QAction * act1 = new QAction (tr ( "Создать ветку"), menu);
    act1->setData(1);
    menu->addAction(act1);

     QAction * act2 = new QAction (tr ( "Создать патч"), menu);
    act2->setData(2);
    menu->addAction(act2);

    QAction * act3 = new QAction (tr ( "Выполнить cherry pick (перенос) в "), menu);
    act3->setData(3);
    menu->addAction(act3);

    menu->popup(QCursor::pos());
}

void GitGui::MenuActionSlot(QAction *act)
{
    if (act == NULL)
    {
        return;
    }
    int nData = act->data().toInt();
    switch (nData)
    {
    case 1:{
        dialog.show();
        break;
    }
    case 2:
         qDebug () << "HuaTang spring as very sweet";
        break;
    case 3:
         qDebug () << "red dress dancing Yan Fei busy";
        break;
    default:
        break;
    }
}

void GitGui::on_listWidget_3_itemClicked(QListWidgetItem *item)
{
    model = NULL;
    git_commit *commit =  commits[ui->listWidget_3->currentRow()].get_hash_commit();
    const git_signature *author = git_commit_author(commit);

    const char *workdir = git_repository_workdir(repo);

    git_time_t time =git_commit_time(commit);

    long long secs = time;
    QDateTime tmp = QDateTime::fromTime_t(secs);

    QString date = tmp.toString();

    QString commit_info = author->name;

    const git_oid *oid = git_commit_id(commit);

    QString sha = git_oid_tostr_s(oid);

    git_object *treeish = NULL;
    git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
    opts.checkout_strategy = GIT_CHECKOUT_FORCE;

    git_repository_set_head_detached(repo, oid);

    git_checkout_head(repo, &opts);

    commit_info = commit_info+" "+"<"+author->email+">"+"\n"+date+"\n"+"\n"+sha;

    ui->textBrowser->setText(commit_info);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QModelIndex index = model->setRootPath(workdir);
    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(index);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(1);
    ui->treeView->setHeaderHidden(true);

    ui->textBrowser_2->clear();
}

void GitGui::on_acceptButtonClicked()
{
    git_libgit2_init();

    const char *workdir = git_repository_workdir(repo);

    git_repository_open(&repo, workdir);

    git_reference *ref;

    QByteArray branchName = lineEdit->text().toUtf8();

    git_commit *commit =  commits[ui->listWidget_3->currentRow()].get_hash_commit();
    const git_oid *oid = git_commit_id(commit);

    git_repository_set_head_detached(repo, oid);

    git_object *head_commit;
    git_revparse_single(&head_commit, repo, "HEAD^{commit}");
    git_commit *head = (git_commit*)head_commit;

    git_branch_create(&ref, repo, branchName, head, 1);

    git_commit_free(commit);
    git_commit_free(head);
    git_object_free(head_commit);

    git_libgit2_shutdown();

    ui->listWidget_2->addItem(branchName);

    lineEdit->clear();

    dialog.close();

    dialog.destroyed();
}

void GitGui::on_cancelButtonClicked()
{
    dialog.close();
}

void GitGui::TreeWidgetMenuSlot2(const QPoint &)
{
    if (menu_2 == NULL)
    {
        menu_2 = new QMenu(this);
        connect(menu_2, SIGNAL(triggered(QAction *)), this, SLOT(MenuActionSlot2(QAction *)));
    }
    menu_2->clear();
     QAction * act1 = new QAction (tr ( "Checkout"), menu_2);
    act1->setData(1);
    menu_2->addAction(act1);

     QAction * act2 = new QAction (tr ( "Удалить ветку"), menu_2);
    act2->setData(2);
    menu_2->addAction(act2);

    QAction * act3 = new QAction (tr ( "Merge into"), menu_2);
    act3->setData(3);
    menu_2->addAction(act3);

    menu_2->popup(QCursor::pos());
}

void GitGui::MenuActionSlot2(QAction *act)
{
    if (act == NULL)
    {
        return;
    }
    int nData = act->data().toInt();
    switch (nData)
    {
    case 1:{
        qDebug () << "HuaTang spring as very sweet";
        git_libgit2_init();

        git_object *treeish = NULL;
        git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
        opts.checkout_strategy = GIT_CHECKOUT_FORCE;

        QString  str = ui->listWidget_2->currentItem()->text();

        const char *branchName = str.toUtf8();

        git_revparse_single(&treeish, repo, branchName);

        git_reference *ref;

        int error = git_checkout_tree(repo, treeish, &opts);

        git_object_free(treeish);

        git_libgit2_shutdown();

        break;
    }
    case 2:{
        git_libgit2_init();

        QString branchName = ui->listWidget_2->currentItem()->text();

        git_libgit2_init();

        const char *workdir = git_repository_workdir(repo);

        QString path = workdir;

        path = path+".git/refs/heads/"+branchName;

        const char *pathc = path.toLocal8Bit();

        QFile file(pathc);

        file.remove();

        QListWidgetItem *item = ui->listWidget_2->currentItem();

        delete item;

        ui->listWidget_3->clear();

        git_libgit2_shutdown();
        break;
    }
    case 3:
         qDebug () << "red dress dancing Yan Fei busy";
        break;
    default:
        break;
    }
}

void GitGui::on_treeView_clicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);
    if(fileInfo.isFile())
    {
        QString str = fileInfo.absoluteFilePath();

        QFile file(str);

        file.open(QIODevice::ReadWrite|QIODevice::Text);

        file.seek(0);
        QByteArray text = file.readAll();

        ui->textBrowser_2->setText(text);

        file.close();
    }
}

void GitGui::on_loadButton_clicked()
{
    QFileInfo fileInfo = model->fileInfo(ui->treeView->currentIndex());
    QString str = fileInfo.absoluteFilePath();
    if (str.isEmpty()){
        return;
    }
    else
    {
        QFile file(str);

        file.open(QIODevice::ReadWrite|QIODevice::Text);

        file.seek(0);
        QByteArray text = file.readAll();

        file.close();
    }
}
