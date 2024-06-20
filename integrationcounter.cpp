using namespace std;

#include <cmath>
#include <functional>
#include <QVector>
#include <QPen>
#include <QGraphicsScene>
#include "integrationcounter.h"
#include "ui_mainwindow.h"

IntegrationCounter::IntegrationCounter() {}

int a,        /* коэфф. a                      */
    b,        /* коэфф. b                      */
    c,        /* коэфф. c                      */
    upper,    /* верхний предел интегрирования */
    lower,    /* нижний предел интегрирования  */
    interval, /* число разбиений               */
    type;     /* тип уравнения                 */

float stepSize, exactStepSize;

QVector<double> xValues;
QVector<double> yValues;

QVector<double> xExactValues;
QVector<double> yExactValues;

/*
 * Расчет 1 типа уравнения
 * @param x - число x
 * */
double f1(double x) { return (a * pow(x, 3)) + (b * x) + c; }
/*
 * Расчет 2 типа уравнения
 * @param x - число x
 * */
double f2(double x) { return a * sin(x + b) + c; }
/*
 * Расчет 3 типа уравнения
 * @param x - число x
 * */
double f3(double x) { return (a / (x+b)) + c; }

/*
 * Первообразная 1 типа уравнения
 * @param x - число x
 * */
double F1(double x) { return (a * pow(x, 4) / 4) + (b * pow(x, 2) / 2) + (c * x); }
/*
 * Первообразная 2 типа уравнения
 * @param x - число x
 * */
double F2(double x) { return (-a * cos(x + b)) + (c * x); }
/*
 * Первообразная 3 типа уравнения
 * @param x - число x
 * */
double F3(double x) { return (a * log(abs(x + b))) + (c * x); }

/*
 * Вычисление интеграла методом Симпсона 3/8
 * */
double countFunc(function<double(double)> f) {
    double res = f(lower) + f(upper);

    for (int i = 1; i < interval; i++) {
        double k = lower + i * stepSize;
        xValues.push_back(k);
        if (i % 3 == 0) {
            res += 2 * f(k);
            yValues.push_back(2 * f(k));
        } else {
            res += 3 * f(k);
            yValues.push_back(3 * f(k));
        }
    }

    return (3 * stepSize / 8) * res;
}

/*
 * Вычисление точного значения интеграла
 * */
double exactCountFunc(function<double(double)> F) {
    for (int i = lower; i <= upper; i++) {
        xExactValues.push_back(i);
        yExactValues.push_back(F(i));
    }
    return F(upper) - F(lower);
}

void IntegrationCounter::count(Ui::MainWindow ui) {
    a        = ui.spinBox_a->value(),
        b        = ui.spinBox_b->value(),
        c        = ui.spinBox_c->value(),
        upper    = ui.spinBox_x1->value(),
        lower    = ui.spinBox_x0->value(),
        interval = ui.spinBox_n->value(),
        type     = ui.equationPicker->currentIndex();

    stepSize = abs(((float)upper - (float)lower) / (float)interval);

    double res;
    double exactRes;

    switch (type) {
    case 0:
        res = countFunc(&f1);
        exactRes = exactCountFunc(&F1);
        break;
    case 1:
        res = countFunc(&f2);
        exactRes = exactCountFunc(&F2);
        break;
    default:
        res = countFunc(&f3);
        exactRes = exactCountFunc(&F3);
    }

    QString ret = "Метод Симпсона 3/8: \n  ";
    ret.append(QString::number(res));
    ret.append("\nТочный результат: \n  ");
    ret.append(QString::number(exactRes));
    ret.append("\nОтносительная погрешность в %: ");
    ret.append(QString::number(100 * abs((exactRes - res) / exactRes)));
    ret.append("\nАбсолютная погрешность: ");
    ret.append(QString::number(abs(exactRes - res)));

    ui.label->setText(ret);

    ui.plot->addGraph();
    ui.plot->graph(0)->setData(xValues, yValues);
    ui.plot->addGraph();
    ui.plot->graph(1)->setData(xExactValues, yExactValues);
    ui.plot->graph(1)->setPen(QPen(Qt::red));

    ui.plot->xAxis->setLabel("x");
    ui.plot->yAxis->setLabel("y");

    ui.plot->xAxis->setRange(*min_element(xValues.begin(), xValues.end()), *max_element(xValues.begin(), xValues.end()));
    ui.plot->yAxis->setRange(*min_element(yValues.begin(), yValues.end()), *max_element(yValues.begin(), yValues.end()));

    ui.plot->replot();

    xValues.clear();
    yValues.clear();
    xExactValues.clear();
    yExactValues.clear();
}
