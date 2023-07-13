#pragma once

#include "settings.hpp"

#include <QApplication>
#include <QIcon>
#include <QTranslator>

namespace Qtilities {
class MainWindow;
class DialogPrefs;
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int argc, char *argv[]);
    Settings &settings() { return settings_; }
    QIcon icon() const { return appIcon_; }
    void preferences();

private:
    void initLocale();
    void initUi();

    MainWindow *mainWindow_;
    DialogPrefs *dlgPrefs_;
    Settings settings_;

    QIcon appIcon_;
    QTranslator qtTranslator_;
    QTranslator translator_;
};
} // namespace Qtilities
