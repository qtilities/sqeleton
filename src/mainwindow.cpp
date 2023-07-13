#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "application.hpp"
#include "dialogabout.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Qtilities::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Qtilities::Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->layout);

    Application *theApp = static_cast<Application *>(qApp);

    setWindowIcon(QIcon(theApp->icon()));
    setWindowTitle(QCoreApplication::applicationName());
    loadSettings();

    connect(ui->actPrefs, &QAction::triggered, theApp,
            &Application::preferences);
    connect(ui->actAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actExit, &QAction::triggered, QCoreApplication::instance(),
            &QCoreApplication::quit);
}

Qtilities::MainWindow::~MainWindow() { delete ui; }

void Qtilities::MainWindow::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    setStyleSheet(QString("#MainWindow{background-color:rgb(%1,%2,%3);"
                          "color:rgb(%4,%5,%6)}")
                      .arg(settings.backgroundColor().red())
                      .arg(settings.backgroundColor().green())
                      .arg(settings.backgroundColor().blue())
                      .arg(settings.foregroundColor().red())
                      .arg(settings.foregroundColor().green())
                      .arg(settings.foregroundColor().blue()));
    resize(settings.size());
    move(settings.position());
    update();
}

void Qtilities::MainWindow::saveSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();
    settings.setPosition(pos());
    settings.setSize(size());
}

void Qtilities::MainWindow::about()
{
    QStringList list = {":/info", ":/authors", ":/license"};
    QStringList texts;

    for (const QString &item : list) {
        QFile f(item);
        if (!f.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Error loading about file" << '\n';
            return;
        }
        QTextStream in(&f);
        texts.append(in.readAll());
        f.close();
    }

    DialogAbout about;
    about.setInfoText(texts.at(0));
    about.setAuthorsText(texts.at(1));
    about.setLicenseText(texts.at(2));
    about.exec();
}
