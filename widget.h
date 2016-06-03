#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <QFile>
#include "spectrum.h"

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QLabel* from_text;
    QLabel* to_text;
    QLineEdit* path_from_text;
    QLineEdit* path_to_text;
    QPushButton* from_butt;
    QPushButton* to_butt;
    QPushButton* go_butt;
    QCheckBox* chkUseAimFolder;
    QCheckBox* chkDelBaseFolder;
    QGroupBox* radBox;
    QRadioButton* radDownloadSingle;
    QRadioButton* radDownloadFolder;

public slots:
    void slotRadBClicked();
    void slotChkUseAimBClicked();
    void slotChkDelBaseClicked();
    void slotFrom_buttClicked();
    void slotTo_buttClicked();
    void slotGo_buttClicked();
    QString findName(QString& , QString& );
    void saveFile(Spectrum , QString , QString , int );
};

#endif // WIDGET_H
