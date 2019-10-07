#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <array>
#include <iostream>
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <vector>
#include <QSpinBox>
#include <QVector>


void printVector(QVector<QSpinBox*> vect)
{
    for (QSpinBox* i : vect)
    {
        qDebug() << i;

    }
}


QVector<int> mulVectors(QVector<QSpinBox*> firstVec,QVector<QVector<QSpinBox*>> matrixVec)
{
    QVector<QVector<int>> mulMatrix;
    mulMatrix.reserve(firstVec.size());

    for (int i = 0; i < firstVec.size(); i++) //(1,2,3)
    {
        QVector<int> temp;

        for (QVector<QSpinBox*> vec : matrixVec ) //matrixVec : ((1,2),(3,4),(5,6))
        {

            for (QSpinBox* spinbox : vec) // vec : (1,2)
            {
                temp.push_back(firstVec[i]->value() * spinbox->value());
                mulMatrix.push_back(temp); // i* 1, i* 2
            }

        } // for
    }

    QVector<int> resultVec;

    for (int i = 0; i < mulMatrix.size(); i++)
    {
        int sum = 0;

        for (int j = 0; j < mulMatrix.size(); j++)
        {
            sum += mulMatrix[j][i];
        }

        resultVec.push_back(sum);
    }
    return resultVec;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (ui-> spinBoxMat1Rows->value() == 0 || ui ->spinBoxMat1Cols->value() == 0){
        ui-> frameMat1->hide();
        ui-> frameMat3->hide();
        MainWindow::resize(200,200);
    }
    if (ui-> spinBoxMat2Rows->value() == 0 || ui ->spinBoxMat2Cols->value() == 0){
            ui-> frameMat2->hide();
            ui-> frameMat3->hide();
            MainWindow::resize(200,200);
    }
    else{
        ui-> frameMat2->show();
        ui-> frameMat1->show();
    }





    connect(ui->pushButtonSetDim,SIGNAL(released()),this,SLOT(dimensionButtonPressed()));
    connect(ui->pushButton_calculate,SIGNAL(released()),this,SLOT(calculateButtonPressed()));

}


MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::dimensionButtonPressed(){

    if (ui->spinBoxMat1Cols->value() == 0 && ui->spinBoxMat1Rows->value() == 0)
    {
        ui->pushButtonSetDim->setText("fill out Matrix 1");
        return;
    }

    if (ui->spinBoxMat2Cols->value() == 0 && ui->spinBoxMat2Rows->value() == 0)
    {
        ui->pushButtonSetDim->setText("fill out Matrix 2");
        return;
    }

    if (ui->spinBoxMat1Cols->value() != ui->spinBoxMat2Rows->value())
    {
        ui->pushButtonSetDim->setText("Invalid entry");
        return;
    }


    //put mat1 into vector

    QVector<QSpinBox*> mat1VecRow1;
    mat1VecRow1.reserve(4);
    mat1VecRow1.push_back(ui->mat1_0_0);
    mat1VecRow1.push_back(ui->mat1_0_1);
    mat1VecRow1.push_back(ui->mat1_0_2);
    mat1VecRow1.push_back(ui->mat1_0_3);

    QVector<QSpinBox*> mat1VecRow2;
    mat1VecRow2.reserve(4);
    mat1VecRow2.push_back(ui->mat1_1_0);
    mat1VecRow2.push_back(ui->mat1_1_1);
    mat1VecRow2.push_back(ui->mat1_1_2);
    mat1VecRow2.push_back(ui->mat1_1_3);

    QVector<QSpinBox*> mat1VecRow3;
    mat1VecRow3.reserve(4);
    mat1VecRow3.push_back(ui->mat1_2_0);
    mat1VecRow3.push_back(ui->mat1_2_1);
    mat1VecRow3.push_back(ui->mat1_2_2);
    mat1VecRow3.push_back(ui->mat1_2_3);

    QVector<QSpinBox*> mat1VecRow4;
    mat1VecRow4.reserve(4);
    mat1VecRow4.push_back(ui->mat1_3_0);
    mat1VecRow4.push_back(ui->mat1_3_1);
    mat1VecRow4.push_back(ui->mat1_3_2);
    mat1VecRow4.push_back(ui->mat1_3_3);

    //put mat2 into vector

    QVector<QSpinBox*> mat2VecRow1;
    mat2VecRow1.reserve(4);
    mat2VecRow1.push_back(ui->mat2_0_0);
    mat2VecRow1.push_back(ui->mat2_0_1);
    mat2VecRow1.push_back(ui->mat2_0_2);
    mat2VecRow1.push_back(ui->mat2_0_3);

    QVector<QSpinBox*> mat2VecRow2;
    mat2VecRow2.reserve(4);
    mat2VecRow2.push_back(ui->mat2_1_0);
    mat2VecRow2.push_back(ui->mat2_1_1);
    mat2VecRow2.push_back(ui->mat2_1_2);
    mat2VecRow2.push_back(ui->mat2_1_3);

    QVector<QSpinBox*> mat2VecRow3;
    mat2VecRow3.reserve(4);
    mat2VecRow3.push_back(ui->mat2_2_0);
    mat2VecRow3.push_back(ui->mat2_2_1);
    mat2VecRow3.push_back(ui->mat2_2_2);
    mat2VecRow3.push_back(ui->mat2_2_3);

    QVector<QSpinBox*> mat2VecRow4;
    mat2VecRow4.reserve(4);
    mat2VecRow4.push_back(ui->mat2_3_0);
    mat2VecRow4.push_back(ui->mat2_3_1);
    mat2VecRow4.push_back(ui->mat2_3_2);
    mat2VecRow4.push_back(ui->mat2_3_3);

    //put mats into vector higher dim vector


    QVector<QVector<QSpinBox*>> MatrixVector1;
    QVector<QVector<QSpinBox*>> MatrixVector2;

    MatrixVector1.push_back(mat1VecRow1);
    MatrixVector1.push_back(mat1VecRow2);
    MatrixVector1.push_back(mat1VecRow3);
    MatrixVector1.push_back(mat1VecRow4);

    MatrixVector2.push_back(mat2VecRow1);
    MatrixVector2.push_back(mat2VecRow2);
    MatrixVector2.push_back(mat2VecRow3);
    MatrixVector2.push_back(mat2VecRow4);



    for (int i = 0 ; i < MatrixVector1.size(); i++)
    {
        for(int j = 0 ; j < MatrixVector1.size(); j++)
        {
            MatrixVector1[i][j]->hide();
        }
    }


    for (int i = 0; i < ui->spinBoxMat1Rows->value(); i++)
    {

        for(int j = 0 ;j < ui->spinBoxMat1Cols->value(); j++)
        {
            MatrixVector1[i][j]->show();
        }

    }

    for (int i = 0 ; i < MatrixVector2.size(); i++)
    {
        for(int j = 0 ; j < MatrixVector2.size(); j++)
        {
            MatrixVector2[i][j]->hide();
        }
    }


    for (int i = 0; i < ui->spinBoxMat2Rows->value(); i++)
    {

        for(int j = 0 ;j < ui->spinBoxMat2Cols->value(); j++)
        {
            MatrixVector2[i][j]->show();
        }

    }


    ui->frameMat1->show();
    ui->frameMat2->show();
}




void MainWindow::calculateButtonPressed()

{
    if (ui->spinBoxMat1Cols->value() == 0 && ui->spinBoxMat1Rows->value() == 0)
    {
        ui->pushButtonSetDim->setText("fill out Matrix 1");
        return;
    }

    if (ui->spinBoxMat2Cols->value() == 0 && ui->spinBoxMat2Rows->value() == 0)
    {
        ui->pushButtonSetDim->setText("fill out Matrix 2");
        return;
    }

    //put mat1 into vector

    QVector<QSpinBox*> mat1VecRow1;
    mat1VecRow1.reserve(4);
    mat1VecRow1.push_back(ui->mat1_0_0);
    mat1VecRow1.push_back(ui->mat1_1_0);
    mat1VecRow1.push_back(ui->mat1_2_0);
    mat1VecRow1.push_back(ui->mat1_3_0);

    QVector<QSpinBox*> mat1VecRow2;
    mat1VecRow2.reserve(4);
    mat1VecRow2.push_back(ui->mat1_0_1);
    mat1VecRow2.push_back(ui->mat1_1_1);
    mat1VecRow2.push_back(ui->mat1_2_1);
    mat1VecRow2.push_back(ui->mat1_3_1);

    QVector<QSpinBox*> mat1VecRow3;
    mat1VecRow3.reserve(4);
    mat1VecRow3.push_back(ui->mat1_0_2);
    mat1VecRow3.push_back(ui->mat1_1_2);
    mat1VecRow3.push_back(ui->mat1_2_2);
    mat1VecRow3.push_back(ui->mat1_3_2);

    QVector<QSpinBox*> mat1VecRow4;
    mat1VecRow4.reserve(4);
    mat1VecRow4.push_back(ui->mat1_0_3);
    mat1VecRow4.push_back(ui->mat1_1_3);
    mat1VecRow4.push_back(ui->mat1_2_3);
    mat1VecRow4.push_back(ui->mat1_3_3);

    //put mat2 into vector

    QVector<QSpinBox*> mat2VecRow1;
    mat2VecRow1.reserve(4);
    mat2VecRow1.push_back(ui->mat2_0_0);
    mat2VecRow1.push_back(ui->mat2_0_1);
    mat2VecRow1.push_back(ui->mat2_0_2);
    mat2VecRow1.push_back(ui->mat2_0_3);

    QVector<QSpinBox*> mat2VecRow2;
    mat2VecRow2.reserve(4);
    mat2VecRow2.push_back(ui->mat2_1_0);
    mat2VecRow2.push_back(ui->mat2_1_1);
    mat2VecRow2.push_back(ui->mat2_1_2);
    mat2VecRow2.push_back(ui->mat2_1_3);

    QVector<QSpinBox*> mat2VecRow3;
    mat2VecRow3.reserve(4);
    mat2VecRow3.push_back(ui->mat2_2_0);
    mat2VecRow3.push_back(ui->mat2_2_1);
    mat2VecRow3.push_back(ui->mat2_2_2);
    mat2VecRow3.push_back(ui->mat2_2_3);

    QVector<QSpinBox*> mat2VecRow4;
    mat2VecRow4.reserve(4);
    mat2VecRow4.push_back(ui->mat2_3_0);
    mat2VecRow4.push_back(ui->mat2_3_1);
    mat2VecRow4.push_back(ui->mat2_3_2);
    mat2VecRow4.push_back(ui->mat2_3_3);

    //put mats into vector higher dim vector


    QVector<QVector<QSpinBox*>> MatrixVector1;
    QVector<QVector<QSpinBox*>> MatrixVector2;

    MatrixVector1.push_back(mat1VecRow1);
    MatrixVector1.push_back(mat1VecRow2);
    MatrixVector1.push_back(mat1VecRow3);
    MatrixVector1.push_back(mat1VecRow4);

    MatrixVector2.push_back(mat2VecRow1);
    MatrixVector2.push_back(mat2VecRow2);
    MatrixVector2.push_back(mat2VecRow3);
    MatrixVector2.push_back(mat2VecRow4);

    QVector<QSpinBox*> mat3VecRow1;
    mat3VecRow1.reserve(4);
    mat3VecRow1.push_back(ui->mat3_0_0);
    mat3VecRow1.push_back(ui->mat3_0_1);
    mat3VecRow1.push_back(ui->mat3_0_2);
    mat3VecRow1.push_back(ui->mat3_0_3);

    QVector<QSpinBox*> mat3VecRow2;
    mat3VecRow2.reserve(4);
    mat3VecRow2.push_back(ui->mat3_1_0);
    mat3VecRow2.push_back(ui->mat3_1_1);
    mat3VecRow2.push_back(ui->mat3_1_2);
    mat3VecRow2.push_back(ui->mat3_1_3);

    QVector<QSpinBox*> mat3VecRow3;
    mat3VecRow3.reserve(4);
    mat3VecRow3.push_back(ui->mat3_2_0);
    mat3VecRow3.push_back(ui->mat3_2_1);
    mat3VecRow3.push_back(ui->mat3_2_2);
    mat3VecRow3.push_back(ui->mat3_2_3);

    QVector<QSpinBox*> mat3VecRow4;
    mat3VecRow4.reserve(4);
    mat3VecRow4.push_back(ui->mat3_3_0);
    mat3VecRow4.push_back(ui->mat3_3_1);
    mat3VecRow4.push_back(ui->mat3_3_2);
    mat3VecRow4.push_back(ui->mat3_3_3);

    QVector<QVector<QSpinBox*>> MatrixVector3;

    MatrixVector3.push_back(mat3VecRow1);
    MatrixVector3.push_back(mat3VecRow2);
    MatrixVector3.push_back(mat3VecRow3);
    MatrixVector3.push_back(mat3VecRow4);



    for (int i = 0 ; i < MatrixVector3.size(); i++)
    {
        for(int j = 0 ; j < MatrixVector3.size(); j++)
        {
            MatrixVector3[i][j]->hide();
        }
    }


    for (int i = 0; i < ui->spinBoxMat1Rows->value(); i++)
    {

        for(int j = 0 ;j < ui->spinBoxMat2Cols->value(); j++)
        {
            MatrixVector3[i][j]->show();
        }

    }


    for (int i = 0 ; i < ui->spinBoxMat2Rows->value() ; i++)
    {

        for (int j = 0; j < ui->spinBoxMat2Cols->value(); j++)
        {
            qDebug() << MatrixVector2[i][j]->value() * MatrixVector1[i][j]->value();
        }
    }

    for (int i = 0 ; i < ui->spinBoxMat1Rows->value() ; i++) // output : 1 4 7 2 5 8 3 6 9
    {
        for (int j = 0 ; j < ui->spinBoxMat1Cols->value(); j++)
        {
            qDebug() << MatrixVector1[j][i]->value();
        }
    }


    for (int i = 0 ; i < ui->spinBoxMat2Rows->value(); i++)
    {
        mulVectors(MatrixVector2[i],MatrixVector1);
    }

    ui->frameMat3->show();
}
