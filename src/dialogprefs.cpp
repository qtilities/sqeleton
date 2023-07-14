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
#include "dialogprefs.hpp"
#include "ui_dialogprefs.h"
#include "application.hpp"
#include "settings.hpp"

#include <QColorDialog>
#include <QPushButton>

Qtilities::DialogPrefs::DialogPrefs(QWidget *parent)
    : QDialog(parent)
    , ui(new Qtilities::Ui::DialogPrefs)
{
    ui->setupUi(this);
    ui->lblColorBg->setAutoFillBackground(true);
    ui->lblColorFg->setAutoFillBackground(true);

    loadSettings();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
            &DialogPrefs::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
            &DialogPrefs::reject);

    connect(ui->pbnBg, &QAbstractButton::clicked, this,
            [this]() { setColorForLabel(ui->lblColorBg); });
    connect(ui->pbnFg, &QAbstractButton::clicked, this,
            [this]() { setColorForLabel(ui->lblColorFg); });

    Application *theApp = static_cast<Application *>(qApp);

    setWindowIcon(theApp->icon());
    setWindowTitle(tr("Preferences"));
}

Qtilities::DialogPrefs::~DialogPrefs() { delete ui; }

void Qtilities::DialogPrefs::loadSettings()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();

    QColor bgColor = settings.backgroundColor();
    QColor fgColor = settings.foregroundColor();

    ui->lblColorBg->setPalette(QPalette(bgColor));
    ui->lblColorFg->setPalette(QPalette(fgColor));

    ui->lblColorBg->setText(bgColor.name());
    ui->lblColorFg->setText(fgColor.name());
}

void Qtilities::DialogPrefs::accept()
{
    Settings &settings = static_cast<Application *>(qApp)->settings();

    settings.setBackgroundColor(
        ui->lblColorBg->palette().color(QPalette::Window));
    settings.setForegroundColor(
        ui->lblColorFg->palette().color(QPalette::Window));

    QDialog::accept();

    hide();
}

void Qtilities::DialogPrefs::setColorForLabel(QLabel *label)
{
    const QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        label->setText(color.name());
        label->setPalette(QPalette(color));
    }
}
