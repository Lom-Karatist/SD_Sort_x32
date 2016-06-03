#include "widget.h"
#include "ui_widget.h"
#include "QDebug"


Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Window);
    setWindowTitle("SD_Sort");
    setGeometry(300,300,500,150);
    setAutoFillBackground(true);

    from_text = new QLabel(this);
    from_text->setText("&Importing folder:");
    to_text = new QLabel(this);
    to_text->setText("&Aim folder:");
    path_from_text = new QLineEdit(this);
    path_to_text = new QLineEdit(this);
    from_text->setBuddy(path_from_text);
    to_text->setBuddy(path_to_text);
    path_from_text->setEnabled(false);
    path_to_text->setEnabled(false);


    from_butt = new QPushButton("Brose");
    to_butt = new QPushButton("Brose");
    go_butt = new QPushButton("Go");
    go_butt->setEnabled(false);
    chkUseAimFolder = new QCheckBox("&Use as aim folder");
    chkDelBaseFolder = new QCheckBox("&Delete base folder");
    connect(from_butt, SIGNAL(clicked()), SLOT(slotFrom_buttClicked()));
    connect(to_butt, SIGNAL(clicked()), SLOT(slotTo_buttClicked()));
    connect(go_butt, SIGNAL(clicked()), SLOT(slotGo_buttClicked()));
    connect(chkUseAimFolder, SIGNAL(clicked()), SLOT(slotChkUseAimBClicked()));
    connect(chkDelBaseFolder, SIGNAL(clicked()), SLOT(slotChkDelBaseClicked()));

    radBox = new QGroupBox("Choose the way of importing files");
    radDownloadSingle = new QRadioButton("Download single file");
    radDownloadFolder = new QRadioButton("Download folder");
    radDownloadFolder->setChecked(true);
    connect(radDownloadSingle, SIGNAL(clicked()), SLOT(slotRadBClicked()));
    connect(radDownloadFolder, SIGNAL(clicked()), SLOT(slotRadBClicked()));

    // layout setup
    QVBoxLayout* vbxLayoutRad = new QVBoxLayout;
    QVBoxLayout* vbxLayoutGo = new QVBoxLayout;
    QGridLayout* grdlayout = new QGridLayout;

    grdlayout->setMargin(5);
    grdlayout->setSpacing(5);
    grdlayout->addWidget(from_text, 0,0);
    grdlayout->addWidget(to_text, 3,0);
    grdlayout->addWidget(path_from_text, 1,0);
    grdlayout->addWidget(path_to_text, 4,0);
    grdlayout->addWidget(from_butt, 1,1);
    grdlayout->addWidget(to_butt, 4,1);
    grdlayout->addWidget(chkUseAimFolder, 0,1);

    vbxLayoutGo->setMargin(5);
    vbxLayoutGo->setSpacing(5);
    vbxLayoutGo->addWidget(chkDelBaseFolder);
    vbxLayoutGo->addWidget(go_butt);
    grdlayout->addLayout(vbxLayoutGo, 5,1);

    vbxLayoutRad->setMargin(5);
    vbxLayoutRad->setSpacing(15);
    vbxLayoutRad->addWidget(radDownloadSingle);
    vbxLayoutRad->addWidget(radDownloadFolder);
    radBox->setLayout(vbxLayoutRad);
    grdlayout->addWidget(radBox, 5,0);

    setLayout(grdlayout);
}

Widget::~Widget()
{

}

void Widget::slotRadBClicked(){

}

void Widget::slotChkUseAimBClicked(){
    if (chkUseAimFolder->isChecked()){

        chkDelBaseFolder->setEnabled(false);
        chkDelBaseFolder->setChecked(false);
        chkUseAimFolder->setChecked(true);
        to_butt->setEnabled(false);

        if (!path_from_text->text().isEmpty()){

            path_to_text->setText(path_from_text->text());
            go_butt->setEnabled(true);

        }

    }
    else{

        chkDelBaseFolder->setEnabled(true);
        chkUseAimFolder->setChecked(false);
        to_butt->setEnabled(true);

    }
}

void Widget::slotChkDelBaseClicked(){

}

void Widget::slotFrom_buttClicked(){

    QString str = QFileDialog::getExistingDirectory(0, "Select Base Directory", path_from_text->text());

    if (!str.isEmpty()){
        path_from_text->setText(str);
    }

    if (chkUseAimFolder->isChecked()){

        path_to_text->setText(str);
    }

    if (!path_to_text->text().isEmpty()){
        go_butt->setEnabled(true);
    }
}

void Widget::slotTo_buttClicked(){

    QString str = QFileDialog::getExistingDirectory(0, "Select Aim Directory", path_to_text->text());

    if (!str.isEmpty()){
        path_to_text->setText(str);
    }
    if (!path_from_text->text().isEmpty()){
        go_butt->setEnabled(true);
    }
}

void Widget::slotGo_buttClicked(){

    chkDelBaseFolder->setEnabled(false);
    chkUseAimFolder->setEnabled(false);

    QDir inDir = QDir(path_from_text->text());
    inDir.setFilter(QDir::Files);
    QStringList listFiles = inDir.entryList();
    QList<QString>::iterator it = listFiles.begin();
    for (; it != listFiles.end(); ++it){
        QString fileName = path_from_text->text();
        fileName.append("/");
        fileName.append(*it);
        *it=fileName;
    }

    foreach (QString fileName, listFiles) {

        QGuiApplication::processEvents();

        QFile fileIn(fileName);
        QString strOwner = ("Owner:");
        QString strType = ("Type:");
        QString strClass = ("Class:");
        QString strSubclass = ("Subclass:");
        QString strName = ("Name:");
        Spectrum spctr;

        if (fileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&fileIn);
            QString str;
            while (!stream.atEnd()){
                str = stream.readLine();
                if (str.contains(strOwner)){
                    spctr.set_sOwner(findName(strOwner, str));
                }
                if (str.contains(strType)){
                    spctr.set_sType(findName(strType, str));
                }
                if (str.contains(strClass)){
                    spctr.set_sClass(findName(strClass, str));
                }
                if (str.contains(strSubclass)){
                    spctr.set_sSubclass(findName(strSubclass, str));
                }
                if (str.contains(strName)){
                    spctr.set_sName(findName(strName, str));
                }
            }
        }
        fileIn.close();

        saveFile(spctr, path_to_text->text(), fileName, 0);

    }
    chkDelBaseFolder->setEnabled(true);
    chkUseAimFolder->setEnabled(true);
}

QString Widget::findName(QString& nameType, QString& str){

    QString name("");
    QStringList nameList = str.split(" ");
    QList<QString>::iterator it = nameList.begin();
    for (; it != nameList.end(); ++it){
        QString str1 = *it;
        if (!str1.contains(nameType)){
            name.append(*it);
            name.append(" ");
        }
    }

    str = name;
    return str;
}

void Widget::saveFile(Spectrum spctr, QString fileOutPath, QString fileInName, int it){

    QString type = spctr.getParamAtIt(it);
    if (!type.isEmpty() && it < 4){
        //fileOutPath.append(QDir::separator());
        //fileOutPath.append(type);
        //QDir().mkdir(fileOutPath);
        ++it;
        //saveFile(typeList, fileOutPath, fileInName, it);
    }
    else{
        QFileInfo fileInfo(fileInName);
        QString destinationFile = fileOutPath + "/" + fileInfo.fileName();
        qDebug()<<destinationFile;
        qDebug()<<fileInName;

        /*QString name = typeList.at(4);
        if (name.isEmpty()){
            name = fileInfo.fileName();
        }
        QString destinationFile = fileOutPath + QDir::separator() + name + ".txt";*/
        QFile::copy(fileInName, destinationFile);
    }
}
