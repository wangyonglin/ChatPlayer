#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QWidget>
class Settings : public QSettings
{
    Q_OBJECT
public:
    enum State{none=-1,off,on};
    explicit Settings(const QString & filename=nullptr,QObject *parent = nullptr);
    Settings::State loadedState(const QString &string);
signals:
};

#endif // SETTINGS_H
