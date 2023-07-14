/*
    MIT License

    Copyright (c) 2021-2023 Andrea Zanellato <redtid3@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/
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
