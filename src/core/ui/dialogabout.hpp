#pragma once

#include <QDialog>

namespace Qtilities {
namespace Ui {
class DialogAbout;
}
class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr);
    ~DialogAbout();

    void setInfoText(const QString &);
    void setAuthorsText(const QString &);
    void setLicenseText(const QString &);

private:
    Ui::DialogAbout *ui;
};
} // namespace Qtilities
