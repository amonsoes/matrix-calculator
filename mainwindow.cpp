#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QSpinBox>
#include <QComboBox>
#include <QVector>

// debugging tools to print to the console

#define PRINT(x) qDebug() << x

template <typename T>
void printVector(const QVector<T>& vec){
    PRINT("----------------");
    for (T i : vec)
    {
        PRINT(i);
    }
    PRINT("VECTOR PRINTED");
    PRINT("----------------");

}

template <typename V>
void printMatrix(const QVector<V>& mat){
    PRINT("==================");

    for (V i : mat)
    {
        printVector(i);
    }
    PRINT("MATRIX PRINTED");
    PRINT("==================");

}

// TODO: change method to operator overload * of QVector class

QVector<int> multipliedVecs(const QVector<int>& first, const QVector<int>& second)
{
    QVector<int> newVec;
    for (int i = 0 ; i < first.size(); i++)
    {
        newVec.push_back(first[i] * second[i]);
    }
    return newVec;
}


// overloads multiplication to matrix operation


QVector<QVector<int> > multipliedVecs(const QVector<QVector<int> >& first, const QVector<QVector<int> >& second)
{
    QVector<QVector<int> > newVec;
    for (int i = 0 ; i < first.size(); i++)
    {
        QVector<int> temp;
        for (int j = 0; j < first[0].size(); j++)
        {
            temp.push_back(first[i][j] * second[i][j]);
        }
        newVec.push_back(temp);
    }
    return newVec;
}


// Calculates the Matrix-Vector-Multiplication of vector "vec" and matrix "mat"


QVector<int> matVecMul(const QVector<int>& vec,const QVector<QVector<int> >& mat)
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


    for (int j = 0; j < temp[0].size() ; j++)
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


// matrix multiplication method which applies the matrix-vector method on every "vector" of mat1


QVector<QVector<int> > matMatMul (const QVector<QVector<int> >& mat1, const QVector<QVector<int> >& mat2)
{
    QVector<QVector<int> > res_mat;

    for (QVector<int> vec : mat1)
    {
        res_mat.push_back(matVecMul(vec,mat2));
    }
    return res_mat;
}

int dotProductVectors(const QVector<int>& vec1, const QVector<int>& vec2)
{
    int sum = 0;
    QVector<int> multiplied = multipliedVecs(vec1,vec2);
    for (int i : multiplied)
    {
        sum += i;
    }
    return sum;
}


// overloads dot product method to get the frobenius norm of two matrices


int dotProductVectors(const QVector<QVector<int> >& vec1, const QVector<QVector<int> >& vec2)
{
    int sum = 0;
    QVector<QVector<int>> multiplied = multipliedVecs(vec1,vec2);
    for (QVector<int> i : multiplied)
    {
        for (int j : i)
        {
            sum += j;
        }
    }
    return sum;
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

    ui->spinBoxMat1Cols->setMaximum(4);
    ui->spinBoxMat2Cols->setMaximum(4);
    ui->spinBoxMat1Rows->setMaximum(4);
    ui->spinBoxMat2Rows->setMaximum(4);


    // signal-slot methods for the dimension set and the calculation process


    connect(ui->pushButtonSetDim,SIGNAL(released()),this,SLOT(dimensionButtonPressed()));
    connect(ui->pushButton_calculate,SIGNAL(released()),this,SLOT(calculateButtonPressed()));
    connect(ui->comboBoxChooseOperation,SIGNAL(currentIndexChanged()),this,SLOT(on_comboBoxChooseOperation_currentIndexChanged(int index)));

}


MainWindow::~MainWindow()
{
    delete ui;
}


// method to avoid invalid entries to the dimension spinboxes and to show only the necesseary spinboxes


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

    if (ui->comboBoxChooseOperation->currentText() == "matrix multiplication" && ui->spinBoxMat1Cols->value() != ui->spinBoxMat2Rows->value())
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


    //shows only the used parts of the matrix frame


    for (int i = 0 ; i < MatrixVector1.size(); i++)
    {
        for(int j = 0 ; j < MatrixVector1.size(); j++)
        {
            MatrixVector1[i][j]->setRange(-100,100);
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
            MatrixVector2[i][j]->setRange(-100,100);
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
    ui->pushButtonSetDim->setText("set dimensions");
}


// calculation method. makes croppedMat helper matrices from above defined functions and sets the value in output matrix for each entry.


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


    //helper matrices (with ints instead of spinboxes created here)


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
            MatrixVector3[i][j]->setRange(-1000,1000);
            MatrixVector3[i][j]->hide();
        }
    }


    // conditional statements to differentiate between dot product for mat, for vec and matrix multiplication


    if (ui->comboBoxChooseOperation->currentText() == "matrix multiplication")
    {
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
            for (int j = 0; j < resultMatMul[0].size();j++)
            {
                MatrixVector3[j][i]->setValue(resultMatMul[i][j]);
            }
        }
    }

    else if (ui->comboBoxChooseOperation->currentText() == "dot product")
    {
        if (ui->spinBoxMat1Cols->value() > 1 && ui->spinBoxMat2Cols->value() > 1)
        {
            if (ui->spinBoxMat1Cols->value() == ui->spinBoxMat2Cols->value() && ui->spinBoxMat1Rows->value() == ui->spinBoxMat2Rows->value())
            {
                int result = dotProductVectors(CroppedMat1,CroppedMat2);
                ui->mat3_0_0->setValue(result);
                ui->mat3_0_0->show();
            }

            else
            {
                ui->pushButton_calculate->setText("invalid matrices for dot product");
                return;
            }
        }

        else if (ui->spinBoxMat1Cols->value() == 1 && ui->spinBoxMat2Cols->value() == 1)
        {
            if (ui->spinBoxMat1Rows->value() == ui->spinBoxMat2Rows->value())
            {

                int result = dotProductVectors(CroppedMat1[0],CroppedMat2[0]);
                ui->mat3_0_0->setValue(result);
                ui->mat3_0_0->show();
            }
            else
            {
                ui->pushButton_calculate->setText("invalid vectors for dot product");
                return;
            }

        }

        else
        {
            ui->pushButton_calculate->setText("invalid matrices for dot product");
            return;
        }
    }

    else if (ui->comboBoxChooseOperation->currentText() == "choose operation")
    {
        ui->pushButton_calculate->setText("choose operation first");
        return;
    }



    ui->frameMat3->show();
    ui->pushButton_calculate->setText("calculate");
}


void MainWindow::on_comboBoxChooseOperation_currentIndexChanged(int index)
{

    ui->frameMat1->hide();
    ui->frameMat2->hide();
    ui->frameMat3->hide();

}
