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
#include "dialogabout.hpp"
#include "ui_dialogabout.h"
#include "application.hpp"
#include "settings.hpp"

#include <QAbstractButton>

Qtilities::DialogAbout::DialogAbout(QWidget *parent)
    : QDialog(parent)
    , ui(new Qtilities::Ui::DialogAbout)
{
    ui->setupUi(this);
    ui->tabInfo->setLayout(ui->layTabInfo);
    ui->tabAuthors->setLayout(ui->layTabAuthors);
    ui->tabLicense->setLayout(ui->layTabLicense);

    // TODO: Probably needed only on X11
    Application *theApp = static_cast<Application *>(qApp);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this,
            &Qtilities::DialogAbout::close);

    setWindowIcon(theApp->icon());
    setWindowTitle(tr("About"));
}

Qtilities::DialogAbout::~DialogAbout() { delete ui; }

void Qtilities::DialogAbout::setInfoText(const QString &text)
{
    QString translated = text;
    ui->txtInfo->setMarkdown(translated.replace("__AUTHOR__", tr("Author")));
}

void Qtilities::DialogAbout::setAuthorsText(const QString &text)
{
    ui->txtAuthors->setMarkdown(text);
}

void Qtilities::DialogAbout::setLicenseText(const QString &text)
{
    ui->txtLicense->setMarkdown(text);
}
