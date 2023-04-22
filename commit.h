#ifndef COMMIT_H
#define COMMIT_H

#include <QString>
#include <QDebug>
#include <qgit2.h>

class Commit
{
    private:
        QString commit_message;
        git_commit *hash_commit;
    public:
        void set_hash_commit(git_commit *commit, QString message) {
            hash_commit = commit;
            commit_message = message;
        }

        git_commit *get_hash_commit() {
            return hash_commit;
        }

        QString get_commit_message(){
            return commit_message;
        }
};

#endif // COMMIT_H
