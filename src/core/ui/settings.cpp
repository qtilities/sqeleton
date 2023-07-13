#include "settings.hpp"

#include <QApplication>
#include <QSettings>

namespace Default {
static const QColor backgroundColor = QColor(0x92, 0xd7, 0xff);
static const QColor foregroundColor = QColor(0x94, 0x00, 0x80);
static const QPoint position = QPoint(200, 200);
static const QSize size = QSize(240, 120);
} // namespace Default

Qtilities::Settings::Settings()
    : bgColor_(Default::backgroundColor)
    , fgColor_(Default::foregroundColor)
    , position_(Default::position)
    , size_(Default::size)
{
}

void Qtilities::Settings::load()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("Options");
    bgColor_ = settings
                   .value(QStringLiteral("BackgroundColor"),
                          Default::backgroundColor)
                   .value<QColor>();
    fgColor_ = settings
                   .value(QStringLiteral("ForegroundColor"),
                          Default::foregroundColor)
                   .value<QColor>();
    position_ = settings.value(QStringLiteral("Position"), Default::position)
                    .toPoint();
    size_ = settings.value(QStringLiteral("Size"), Default::size).toSize();
    settings.endGroup();
}

void Qtilities::Settings::save()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationDisplayName());

    settings.beginGroup("Options");
    settings.setValue(QStringLiteral("BackgroundColor"), bgColor_);
    settings.setValue(QStringLiteral("ForegroundColor"), fgColor_);
    settings.setValue(QStringLiteral("Position"), position_);
    settings.setValue(QStringLiteral("Size"), size_);
    settings.endGroup();
}
