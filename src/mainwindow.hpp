#pragma once

#include <QMainWindow>

namespace Qtilities {
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadSettings();
    void saveSettings();

private:
    void about();

    Ui::MainWindow *ui;
};
} // namespace Qtilities
