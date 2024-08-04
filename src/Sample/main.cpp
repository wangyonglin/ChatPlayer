#include "UserWidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ChatPlayer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    UserWidget w;
    // 设置窗口的最小大小为800x600像素
    w.setMinimumSize(QSize(480, 854));
    //w.setMinimumSize(QSize(720, 1080));
    // 设置窗口的最大大小为800x600像素
    w.setMaximumSize(QSize(480, 854));
    //w.setMaximumSize(QSize(1080, 1960));
    w.show();
    return a.exec();
}
