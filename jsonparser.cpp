#include "jsonparser.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

JsonParser::JsonParser() {}

void JsonParser::parse(Ui::MainWindow ui) {
    QFileDialog dialog;
    QString jsonFileName = dialog.getOpenFileName();

    QFile file;
    file.setFileName(jsonFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QString contents;
    contents = file.readAll();
    file.close();

    QJsonObject obj = QJsonDocument::fromJson(contents.toUtf8()).object();

    QString errStr = "Не удалось считать переменные [";
    bool errHappened = 0;

    bool ok = 0;

    QJsonValue a = obj.value(QString("a"));
    int a_int = a.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append("a");
    } else
        ui.spinBox_a->setValue(a_int);

    QJsonValue b = obj.value(QString("b"));
    int b_int = b.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append(" b");
    } else
        ui.spinBox_b->setValue(b_int);

    QJsonValue c = obj.value(QString("c"));
    int c_int = c.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append(" c");
    } else
        ui.spinBox_c->setValue(c_int);

    QJsonValue x0 = obj.value(QString("x0"));
    int x0_int = x0.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append(" x0");
    } else
        ui.spinBox_x0->setValue(x0_int);

    QJsonValue x1 = obj.value(QString("x1"));
    int x1_int = x1.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append(" x1");
    } else
        ui.spinBox_x1->setValue(x1_int);

    QJsonValue n = obj.value(QString("n"));
    int n_int = n.toVariant().toInt(&ok);
    if (!ok) {
        errHappened = true;
        errStr.append(" n");
    } else
        ui.spinBox_n->setValue(n_int);

    errStr.append(" ]. Пожалуйста, проверьте правильность составления файла!");

    if (errHappened) {
        QMessageBox errMessageBox;

        errMessageBox.setText(errStr);
        errMessageBox.setStandardButtons(QMessageBox::Ok);

        errMessageBox.exec();
    }
}
