#include <QObject>
#include <QDebug>


class Js_Object : public QObject
{
    Q_OBJECT
public:
    explicit Js_Object(QObject *parent = 0) : QObject(parent) {
        qDebug()<<"Js_Object::Js_Object(QObject *parent) : QObject(parent)";
    }
    Q_INVOKABLE int plus(int a,  int b) {
        qDebug() << "plus called";
        return a+b; }

};

class Factory : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QObject* foo() {
        return new Js_Object();
    }
};

