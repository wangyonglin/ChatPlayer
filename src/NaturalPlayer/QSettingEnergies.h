#ifndef QSETTINGENERGIES_H
#define QSETTINGENERGIES_H

#include <QObject>
#include <QSettings>

class QSettingEnergies : public QSettings
{
    Q_OBJECT
public:
    enum State{none=-1,off,on};
    explicit QSettingEnergies(const QString & filename=nullptr,QObject *parent = nullptr);

    QSettingEnergies::State loadedState(const QString &string);
signals:
};

#endif // QSETTINGENERGIES_H
