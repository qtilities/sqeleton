#include "application.hpp"
#include "mainwindow.hpp"
#include "dialogprefs.hpp"

#include <QLibraryInfo>
#include <QLocale>

Qtilities::Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{
    setApplicationName(APPLICATION_NAME);
    setOrganizationName(ORGANIZATION_NAME);
    setOrganizationDomain(ORGANIZATION_DOMAIN);

    initLocale();

    QString icoCurPath = QCoreApplication::applicationDirPath() + '/'
                         + QStringLiteral(PROJECT_ICON_NAME);
    QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH);

    // Try first to find the app icon in the current directory
    appIcon_ = QIcon(icoCurPath);
    if (appIcon_.isNull())
        appIcon_ = QIcon(icoSysPath);

        // UseHighDpiPixmaps is default from Qt6
#if QT_VERSION < 0x060000
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
    initUi();
}

void Qtilities::Application::initLocale()
{
#if 0
    QLocale locale = QLocale::system();
#else
    QLocale locale(QLocale("it"));
    QLocale::setDefault(locale);
#endif
    // Qt translations (buttons and the like)
    QString translationsPath
#if QT_VERSION < 0x060000
        = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#else
        = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
#endif
    QString translationsFileName = QStringLiteral("qt_") + locale.name();

    if (qtTranslator_.load(translationsFileName, translationsPath))
        installTranslator(&qtTranslator_);

    // E.g. "<appname>_en"
    translationsFileName
        = QCoreApplication::applicationName().toLower() + '_' + locale.name();

    // Try first in the same binary directory, in case we are building,
    // otherwise read from system data
    translationsPath = QCoreApplication::applicationDirPath();

    bool isLoaded = translator_.load(translationsFileName, translationsPath);
    if (!isLoaded) {
        // "/usr/share/<appname>/translations
        isLoaded = translator_.load(translationsFileName,
                                    QStringLiteral(PROJECT_DATA_DIR)
                                        + QStringLiteral("/translations"));
    }
    if (isLoaded)
        installTranslator(&translator_);
}

void Qtilities::Application::initUi()
{
    settings_.load();

    mainWindow_ = new Qtilities::MainWindow;
    dlgPrefs_ = new Qtilities::DialogPrefs(mainWindow_);

    mainWindow_->move(settings_.position());
    mainWindow_->resize(settings_.size());
    mainWindow_->show();

    connect(dlgPrefs_, &QDialog::accepted, mainWindow_,
            &MainWindow::loadSettings);

    connect(this, &QApplication::aboutToQuit, dlgPrefs_, &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, mainWindow_,
            &QObject::deleteLater);
    connect(this, &QApplication::aboutToQuit, this, [this]() {
        mainWindow_->saveSettings();
        settings_.save();
    });
}

void Qtilities::Application::preferences()
{
    dlgPrefs_->loadSettings();
    dlgPrefs_->show();
}

int main(int argc, char *argv[])
{
    Qtilities::Application app(argc, argv);
    return app.exec();
}
