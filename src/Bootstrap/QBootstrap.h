#ifndef QBOOTSTRAP_H
#define QBOOTSTRAP_H

#include <QObject>
#include <QSettings>
#include <QWidget>
class QBootstrap : public QSettings
{
    Q_OBJECT
public:
    enum State{none=-1,off,on};
    explicit QBootstrap(const QString & filename=nullptr,QObject *parent = nullptr);
    QBootstrap::State loadedState(const QString &string);
signals:
};

#endif // QBOOTSTRAP_H
