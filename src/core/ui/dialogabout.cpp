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
