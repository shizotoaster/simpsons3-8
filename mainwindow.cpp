#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsonparser.h"
#include "integrationcounter.h"
#include "graphdrawer.h"
#include <QMessageBox>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Установка лимитов для вводимых чисел */
    ui->spinBox_a->setMaximum(2147483647);
    ui->spinBox_a->setMinimum(-2147483648);
    ui->spinBox_b->setMaximum(2147483647);
    ui->spinBox_b->setMinimum(-2147483648);
    ui->spinBox_c->setMaximum(2147483647);
    ui->spinBox_c->setMinimum(-2147483648);

    ui->spinBox_x0->setMaximum(1000);
    ui->spinBox_x0->setMinimum(-1000);
    ui->spinBox_x1->setMaximum(1000);
    ui->spinBox_x1->setMinimum(-1000);

    ui->spinBox_n->setMaximum(498);
    ui->spinBox_n->setMinimum(3);
    ui->spinBox_n->setSingleStep(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseButton_clicked()
{
    JsonParser parser;
    parser.parse(*ui);
}


void MainWindow::on_countButton_clicked()
{
    if (ui->spinBox_n->value() % 3) {
        QMessageBox errMessageBox;

        errMessageBox.setText("Число разбиений должно быть кратно 3!");
        errMessageBox.setStandardButtons(QMessageBox::Ok);

        errMessageBox.exec();

        return;
    }

    if (ui->spinBox_x0->value() >= ui->spinBox_x1->value()) {
        QMessageBox errMessageBox;

        errMessageBox.setText("Нижняя граница должна быть меньше верхней!");
        errMessageBox.setStandardButtons(QMessageBox::Ok);

        errMessageBox.exec();

        return;
    }

    IntegrationCounter counter;
    counter.count(*ui);
}

