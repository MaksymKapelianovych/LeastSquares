#include "mainwindow.h"
#include <cmath>
#include "sqrt.h"
#include <QDebug>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), customPlot(new QCustomPlot(this)), layout(new QGridLayout), label(new QLabel("Введіть степінь: ", this)),
    spinBox(new QSpinBox(this)), btn(new QPushButton("Намалювати", this))
{
    ui->setupUi(this);

    connect(btn, &QPushButton::clicked, this, &MainWindow::btn_clicked);



    points.insert(0.2, 1.16);
    points.insert(0.4, 1.3);
    points.insert(0.6, 1.2);
    points.insert(0.8, 1.2);
    points.insert(1.0, 0.6);
    points.insert(1.2, -1.6);
    points.insert(1.4, 0.4);
    points.insert(1.6, 0.0);
    points.insert(1.8, -0.5);
    points.insert(2.0, -1.0);

    spinBox->setMinimum(0);
    spinBox->setMaximum(points.size()-1);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(A, B);
    customPlot->yAxis->setRange(-2, 2);

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QColor(50, 50, 50, 255));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    customPlot->graph(0)->setData(points.keys().toVector(), points.values().toVector());

    layout->addWidget(label, 0, 0);
    layout->addWidget(spinBox, 0, 1);
    layout->addWidget(btn, 0, 2);
    layout->addWidget(customPlot, 1, 0, 5, 5);

    QWidget * w = new QWidget(this);
    w->setLayout(layout);
    setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calcCoef()
{
    QVector<QVector<double>> A(N);
    QVector<double> B(N);
    for(int i = 0; i< N; i++){
        A[i] = QVector<double>(N);

        for(int j = 0; j < N; j++){

            double temp = 0;
            for(int k = 0; k < points.size(); k++){
                temp += pow(points.keys()[k], i+j);
            }
            A[i][j] = temp;


        }
        double y = 0;
        for(int k = 0; k < points.size(); k++){
            y += points.values()[k]*pow(points.keys()[k], i);
        }
        B[i] = y;
    }

    coef = QVector<double>(N);
    SqrtMt::solve(A, B, coef);
}

double MainWindow::getY(double x)
{
    double res = 0;
    for(int i = 0; i < coef.size(); i++){
        res += coef[i]*pow(x, i);
    }
    return res;
}

void MainWindow::draw()
{
    customPlot->clearGraphs();
    QVector<double> x(101), y(101);
    for (int i=0; i<101; ++i)
    {
      x[i] = A+(B-A)*i/100.0;
      y[i] = getY(x[i]);  // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    customPlot->graph(0)->setPen(QPen(Qt::red));


    customPlot->addGraph();
    customPlot->graph(1)->setPen(QColor(50, 50, 50, 255));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    customPlot->graph(1)->setData(points.keys().toVector(), points.values().toVector());

    customPlot->replot();
}

void MainWindow::btn_clicked()
{
    N = spinBox->value()+1;
    calcCoef();
    draw();
}



























