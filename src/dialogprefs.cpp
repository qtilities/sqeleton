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
