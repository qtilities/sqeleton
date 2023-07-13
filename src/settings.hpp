#pragma once

#include <QColor>
#include <QPoint>
#include <QSize>

namespace Qtilities {
class Settings
{
public:
    Settings();

    void load();
    void save();

    QColor backgroundColor() const { return bgColor_; }
    void setBackgroundColor(const QColor &bgColor) { bgColor_ = bgColor; }

    QColor foregroundColor() const { return fgColor_; }
    void setForegroundColor(const QColor &fgColor) { fgColor_ = fgColor; }

    QPoint position() const { return position_; }
    void setPosition(const QPoint &position) { position_ = position; }

    QSize size() const { return size_; }
    void setSize(const QSize &size) { size_ = size; }

private:
    QColor bgColor_;
    QColor fgColor_;
    QPoint position_;
    QSize size_;
};
} // namespace Qtilities
