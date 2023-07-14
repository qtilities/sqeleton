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
#pragma once

#include "settings.hpp"

#include <QApplication>
#include <QIcon>
#include <QTranslator>

namespace Qtilities {
class MainWindow;
class DialogPrefs;
class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int argc, char *argv[]);
    Settings &settings() { return settings_; }
    QIcon icon() const { return appIcon_; }
    void preferences();

private:
    void initLocale();
    void initUi();

    MainWindow *mainWindow_;
    DialogPrefs *dlgPrefs_;
    Settings settings_;

    QIcon appIcon_;
    QTranslator qtTranslator_;
    QTranslator translator_;
};
} // namespace Qtilities
