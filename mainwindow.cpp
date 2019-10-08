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


#define PRINT(x) qDebug() << x

template <typename T>
void printVector(QVector<T> vec){
    PRINT("----------------");
    for (T i : vec)
    {
        PRINT(i);
    }
    PRINT("VECTOR PRINTED");
    PRINT("----------------");

}

template <typename V>
void printMatrix(QVector<V> mat){
    PRINT("==================");

    for (V i : mat)
    {
        printVector(i);
    }
    PRINT("MATRIX PRINTED");
    PRINT("==================");

}

QVector<int> matVecMul( QVector<int> vec,QVector<QVector<int> > mat)
{

    QVector<int> result;
    result.reserve(vec.size());
    QVector<QVector<int> > temp;

    for (int i = 0 ; i < vec.size() ; i++) //vec (1,2,3)
    {
        QVector<int> subTemp;

        for (int num : mat[i])
        {
            subTemp.push_back(num * vec[i]);
        }

        temp.push_back(subTemp);
    }


    for (int j = 0; j < temp[j].size() ; j++)
    {
        int total_j = 0;

        for (int x = 0 ; x < temp.size(); x++)
        {
            total_j += temp[x][j];
        }

        result.push_back(total_j);

    }
    return result;
}

QVector<QVector<int> > matMatMul (QVector<QVector<int> > mat1, QVector<QVector<int> > mat2)
{
    QVector<QVector<int> > res_mat;

    for (QVector<int> vec : mat1)
    {
        res_mat.push_back(matVecMul(vec,mat2));
    }
    return res_mat;
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

    QVector<QVector<int>> CroppedMat1;
    QVector<QVector<int>> CroppedMat2;


    for (int i = 0;i < ui->spinBoxMat1Cols->value(); i++)
    {
        QVector<int> temp;

        for (int j = 0; j < ui->spinBoxMat1Rows->value();j++)
        {

            temp.push_back(MatrixVector1[i][j]->value());
        }

        CroppedMat1.push_back(temp);
    }

    for (int i = 0;i < ui->spinBoxMat2Cols->value(); i++)
    {
        QVector<int> temp;

        for (int j = 0; j < ui->spinBoxMat2Rows->value();j++)
        {

            temp.push_back(MatrixVector2[j][i]->value());
        }

        CroppedMat2.push_back(temp);
    }


    //create mat3

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


    QVector<QVector<int>> resultMatMul = matMatMul(CroppedMat2,CroppedMat1);


    for (int i = 0 ; i < resultMatMul.size(); i++)
    {
        for (int j = 0; j < resultMatMul[i].size();j++)
        {
            MatrixVector3[i][j]->setValue(resultMatMul[i][j]);
        }
    }



    ui->frameMat3->show();
}
