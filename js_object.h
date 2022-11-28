#include <QObject>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>


class Js_Object : public QObject
{
    Q_OBJECT
public:
    explicit Js_Object(QObject *parent = 0) : QObject(parent) {
        qDebug()<<"Js_Object::Js_Object(QObject *parent) : QObject(parent)";
    }
    Q_INVOKABLE QString plus(QString a) {
        qDebug() << "plus called";
            QCryptographicHash hash(QCryptographicHash::Md5);{

            QFile file(a);
            QByteArray data;
            if(!file.open(QIODevice::ReadOnly)){
                             a = "Ошибка чтения файла";
                             return a;
            }
            QByteArray ios = file.readAll();
            file.close();

            hash.addData(ios);
            data = hash.result().toHex().data();
            a = QString(data);
            qDebug()<<data;
            qDebug()<<0;
        }
            return a;
    }
};

class Factory : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QObject* foo() {
        return new Js_Object();
    }
};

