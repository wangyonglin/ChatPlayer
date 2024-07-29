#include "QSettingEnergies.h"

QSettingEnergies::QSettingEnergies(const QString & filename,QObject *parent)
    : QSettings(filename, QSettings::IniFormat,parent)
{}
QSettingEnergies::State QSettingEnergies::loadedState(const QString &string)
{
    if((string == QString::fromLocal8Bit("on")) || (string== QString::fromLocal8Bit("ON")) || (string== QString::fromLocal8Bit("On")))
    {
        return on;
    }else if ((string == QString::fromLocal8Bit("off")) || (string== QString::fromLocal8Bit("OFF")) || (string== QString::fromLocal8Bit("Off"))){
        return off;
    }
    return none;
}
