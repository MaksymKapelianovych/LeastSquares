#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include "G:/QtProjects/QCustomPlot/qcustomplot/qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCustomPlot* customPlot;

    void calcCoef();
    double getY(double x);

    void draw();


    int f;
    const double A = 0;
    const double B = 2;
    int N;
    QVector<double> coef;
    //QVector<double> arr;
    QMap<double, double> points;

    QGridLayout *layout;

    QSpinBox *spinBox;
    QPushButton *btn;
    QLabel *label;


public slots:
    void btn_clicked();
};

#endif // MAINWINDOW_H
