#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Turtle : public QThread {
    Q_OBJECT

signals:
    void positionChanged(int newPosition);

public:
    void run() override;
};

class Hare : public QThread {
    Q_OBJECT

signals:
    void positionChanged(int newPosition);

public:
    void run() override;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartButtonClicked();
    void onTurtlePositionChanged(int newPosition);
    void onHarePositionChanged(int newPosition);

private:
    Ui::MainWindow *ui;
    Turtle turtle;
    Hare hare;
    int maxDifference;
};

#endif // MAINWINDOW_H
