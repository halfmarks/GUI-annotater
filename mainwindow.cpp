﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygonDraw.h"
#include <iostream>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QLabel>
#include <QVector>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{


    ui->setupUi(this);
    pmap=new pixelmap(this);
    //image = new QGraphicsPixmapItem();
    scene = new QGraphicsScene(this);
    ui -> graphicsView -> setScene(scene);


    QString sPath = "C:/";

    dirmodel = new QFileSystemModel(this);
    dirmodel -> setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirmodel -> setRootPath(sPath);


    filemodel = new QFileSystemModel(this);
    filemodel -> setFilter(QDir::NoDotAndDotDot | QDir::Files );
    filemodel-> setRootPath(sPath);

    ui -> ImgList -> setModel(filemodel);


}

MainWindow::~MainWindow()
{
    delete ui;
}


/* Load image button is clicked */
void MainWindow::on_actionLoad_triggered()
{
    //pmap -> loadImg(scene);

    //scene -> addItem(pmap);
}


/* Drawing Lines */
void MainWindow:: drawLines(const QPointF &firstP , const QPointF &secondP)
{
    QGraphicsLineItem *lines = scene -> addLine(firstP.x(), firstP.y(), secondP.x(), secondP.y(), pen);

    pmap -> lineV.push_back(lines);
}

/* Drawing Polygons */
void MainWindow:: drawPolygon(const QPolygonF &polygon)
{

    pointer = new polygonDraw(polygon, this);

    pointer -> setPen(pen);

    scene -> addItem(pointer);

    for (const QGraphicsLineItem* line: pmap -> lineV)
    {
        delete line;
    }
}

/* Remove polygon */
void MainWindow::removePolygon(polygonDraw *Dpoly)
{
    scene->removeItem(Dpoly);
}

/* Update class name */
void MainWindow::updateClassName(QGraphicsTextItem *CName)
{
    cout << "ClassName:" << CName <<endl;
    scene->addItem(CName);
}

/* Drawing with Polygon shape */
void MainWindow::on_polyShape_clicked()
{
    pmap -> PolygonOn = 1;
}

void MainWindow::on_pushButton_clicked()
{
    // browse dialog box to locate images folder, then load folder contents to QDir class
    QDir directory(QFileDialog::getExistingDirectory(this, "Open a Folder", QDir::homePath()));

    // only load filenames with acceptable image postfixes
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png" << "*.jpeg", QDir::Files);

    // populate listbox with acceptable files
    if (images.length() > 0) {
        // store path for later
        currentFolder = directory.path();
        qInfo() << currentFolder << endl;
        foreach(QString image, images) {
        ui -> WidgetImgList -> addItem(image);
        }
    } else
    {
        // show user error box if no images were found in folder
        //QMessageBox::information(this, "ERROR", "No images found in that directory");
    }

//    QString sPath = QFileDialog::getExistingDirectory(this, tr("Choose catalog"), ".", QFileDialog::ReadOnly);
//    QStringList filter;
//        filter << QLatin1String(".png");
//        filter << QLatin1String(".jpeg");
//        filter << QLatin1String(".jpg");
//        filter << QLatin1String(".gif");
//        filter << QLatin1String("*.raw");
//        filemodel -> setNameFilters(filter);

//    ui -> ImgList -> setRootIndex(filemodel -> setRootPath(sPath));

}



void MainWindow::on_WidgetImgList_currentItemChanged(QListWidgetItem *current)
{

    //scene->removeItem(pmap);
    // store filename ready for opening
    currentFile = current->text();
    fileName = currentFolder + '/' + currentFile;
    std::cout << fileName.toUtf8().constData() << std::endl;
    loadImage(fileName);

}

void MainWindow::on_ImgList_clicked(const QModelIndex &index)
{
    pmap -> filename = filemodel -> filePath(index);

    pmap -> loadImg(scene);
    scene -> addItem(pmap);
}

void MainWindow::on_loadClass_clicked()
{
//    QString sPath = QFileDialog::getOpenFileName(this, tr("Choose Class"), ".", tr("Text Files (*.txt))"));
//    QStringList filter2;
//    filter2<< QLatin1String("*.txt");
//    dirmodel -> setNameFilters(filter2);

//    ui -> classList -> setRootIndex(dirmodel -> setRootPath(sPath));



//    QString dPath = QFileDialog::getExistingDirectory(this, tr("Choose folder"), ".", QFileDialog::ReadOnly);
//    QStringList filter;
//    filter << QLatin1String("*.txt");;
//    dirmodel -> setNameFilters(filter);

//    ui -> classList ->setRootIndex(dirmodel -> setRootPath(dPath));

    classFile = QFileDialog::getOpenFileName(this, tr("Open Class File"), "", "Class file (*.names)");
    if(classFile.isEmpty())
        return;
    else{
        QFile classNameFile(classFile);
            if(!classNameFile.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, "Can not to open file", classNameFile.errorString());
                return;
        }
        QTextStream in(&classNameFile);
        ui->classList->clear();
        while (!in.atEnd()){
            QString line = in.readLine();

            ui->classList->addItem(line);

        }
        classNameFile.close();
    }
}

void MainWindow::on_addClass_clicked()
{
    QString file_name= QFileDialog::getSaveFileName(this,tr("Save Class File"),".",tr("*.names"));
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Error!","Could not open file for writing.");
        return;
    }
    QTextStream out(&file);
    QString text = ui->classNameField->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::loadImage(QString fileName)
{
    QImage image;
    if(image.load(fileName)){
        cout <<"hello";
        scene = new QGraphicsScene;
        pmap->setPixmap(QPixmap::fromImage(image));
        scene->addItem(pmap);
        ui->graphicsView->setScene(scene);

    }
}

QStringList sorting (QListWidget* fileList,int sort){

    QStringList images;
    int size = fileList->count();

    qDebug() << "size of image list "<< size;

    QString temp;
    int j;

    for (int k=0;k<size;k++){
        images.append(fileList->item(k)->text());
    }
    //when sort = 1 ascending sort
    if (sort == 1){
    for (int i = 1;i<size;i++){
        temp = images[i];
        j=i;
        while(j>0 && temp<images[j-1]){
            images[j]=images[j-1];
            images[j-1]=temp;

            j--;
        }
    }
    }
    //sort = 0 meaning descending sort
    else if(sort == 0){
        for (int i = 1;i<size;i++){
            temp = images[i];
            j=i;
            while(j>0 && temp>images[j-1]){
                images[j]=images[j-1];
                images[j-1]=temp;

                j--;
            }
        }
    }
    return images;
}

void MainWindow::on_imgListSortAsc_clicked()
{

    int size = ui->WidgetImgList->count();
    /*
    QStringList images;
    size = ui->WidgetImgList->count();

    qDebug() << "size of image list "<< size;

    QString temp;
    QString jitem;
    QString j1item;
    int j;
    for (int k=0;k<size;k++){
        images.append(ui->WidgetImgList->item(k)->text());
    }
    for (int i = 1;i<size;i++){
        temp = images[i];
        j=i;
        while(j>0 && temp<images[j-1]){
            images[j]=images[j-1];
            images[j-1]=temp;

            j--;
        }
    }*/
//    foreach(QString image,images){
//        ui->WidgetImgList->addItem(image);
//    }

    QStringList realList;
    realList = sorting(ui->WidgetImgList,1);
    ui->WidgetImgList->clear();
    for (int i =0;i<size;i++){
        ui->WidgetImgList->insertItem(i,realList[i]);
    }

}

void MainWindow::on_imgListSortDesc_clicked()
{
    /*int size;
    QStringList images;
    size = ui->WidgetImgList->count();

    qDebug() << "size of image list "<< size;

    QString temp;
    int j;

    for (int k=0;k<size;k++){
        images.append(ui->WidgetImgList->item(k)->text());
    }
    for (int i = 1;i<size;i++){
        temp = images[i];
        j=i;
        while(j>0 && temp>images[j-1]){
            images[j]=images[j-1];
            images[j-1]=temp;

            j--;
        }
    }
    foreach(QString image,images){
        ui->WidgetImgList->addItem(image);
   }
    ui->WidgetImgList->clear();
    for (int i =0;i<size;i++){
        ui->WidgetImgList->insertItem(i,images[i]);
    }
    */
    int size = ui->WidgetImgList->count();

    QStringList realList;
    realList = sorting(ui->WidgetImgList,0);
    ui->WidgetImgList->clear();
    for (int i =0;i<size;i++){
        ui->WidgetImgList->insertItem(i,realList[i]);
    }
}



void MainWindow::on_classSortAsc_clicked()
{
    int size = ui->classList->count();

    QStringList realList;
    realList = sorting(ui->classList,1);
    ui->classList->clear();
    for (int i =0;i<size;i++){
        ui->classList->insertItem(i,realList[i]);
    }

}

void MainWindow::on_classSortDesc_clicked()
{
    int size = ui->classList->count();

    QStringList realList;
    realList = sorting(ui->classList,0);
    ui->classList->clear();
    for (int i =0;i<size;i++){
        ui->classList->insertItem(i,realList[i]);
    }
}
