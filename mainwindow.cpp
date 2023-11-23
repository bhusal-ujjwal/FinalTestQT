#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_start, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(&turtle, &Turtle::positionChanged, this, &MainWindow::onTurtlePositionChanged);
    connect(&hare, &Hare::positionChanged, this, &MainWindow::onHarePositionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Turtle::run() {
    for (int position = 0; position <= 1000; position += 1) {
        msleep(500);  // Sleep for 500ms
        emit positionChanged(position);
    }
}

void Hare::run() {
    for (int position = 0; position <= 1000; position += 1) {
        msleep(250);  // Sleep for 250ms
        emit positionChanged(position);
    }
}

void MainWindow::onStartButtonClicked() {
    maxDifference = ui->spinBox->value();

    ui->btn_start->setEnabled(false);

    // Reset the progress bars and winner label
    ui->turtleprogressBar->setValue(0);
    ui->hareprogressBar->setValue(0);
    ui->label_winner->setText("Unknown");

    turtle.start();
    hare.start();
}

void MainWindow::onTurtlePositionChanged(int newPosition) {
    ui->turtleprogressBar->setValue(newPosition);
    if (newPosition - ui->hareprogressBar->value() > maxDifference) {
        hare.quit();
        hare.wait();
        hare.start();
    }

    if (newPosition == 1000) {
        ui->label_winner->setText("Turtle");
        turtle.quit();
        turtle.wait();
        ui->btn_start->setEnabled(true);
    }
}

void MainWindow::onHarePositionChanged(int newPosition) {
    ui->hareprogressBar->setValue(newPosition);
    if (ui->turtleprogressBar->value() - newPosition > maxDifference) {
        turtle.quit();
        turtle.wait();
        turtle.start();
    }

    if (newPosition == 1000) {
        ui->label_winner->setText("Hare");
        hare.quit();
        hare.wait();
        ui->btn_start->setEnabled(true);
    }
}
