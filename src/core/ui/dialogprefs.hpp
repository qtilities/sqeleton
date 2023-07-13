#pragma once

#include <QDialog>

class QLabel;

namespace Qtilities {
namespace Ui {
class DialogPrefs;
}
class DialogPrefs : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrefs(QWidget *parent = nullptr);
    ~DialogPrefs();

    void loadSettings();

private:
    void accept() override;

    void setColorForLabel(QLabel *);

    Ui::DialogPrefs *ui;
};
} // namespace Qtilities
