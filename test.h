#include <QObject>
#include <QDebug>

class Js_Test : public QObject
{
    Q_OBJECT
public:
    explicit Js_Test(QObject *parent = 0) : QObject(parent) {
        qDebug()<<"Js_Object::Js_Object(QObject *parent) : QObject(parent)";
    }
    Q_INVOKABLE int minus(int a,  int b) {
        qDebug() << "minus called";
        return a-b; }

};


