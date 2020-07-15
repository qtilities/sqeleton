#include "mainwindow.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centerWidget(new QWidget(this))
    , layout(new QVBoxLayout(centerWidget))
    , button(new QPushButton("Click me!", centerWidget))
{
    layout->setContentsMargins(6, 6, 6, 6);
    layout->addWidget(button);

    centerWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
}
