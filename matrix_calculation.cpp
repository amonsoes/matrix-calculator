#include <vector>
#include <iostream>

#define PRINT(x) std::cout << x << std::endl

template <typename T>
void printVector(std::vector<T> vec){
    PRINT("----------------");
    for (T i : vec)
    {
        PRINT(i);
    }
    PRINT("VECTOR PRINTED");
    PRINT("----------------");

}

template <typename V>
void printMatrix(std::vector<V> mat){
    PRINT("==================");

    for (V i : mat)
    {
        printVector(i);
    }
    PRINT("MATRIX PRINTED");
    PRINT("==================");

}

std::vector<int> matVecMul( std::vector<int> vec,std::vector<std::vector<int> > mat)
{
    std::vector<int> result;
    result.reserve(vec.size());
    std::vector<std::vector<int> > temp;

    for (int i = 0 ; i < vec.size() ; i++) //vec (1,2,3)
    {
        std::vector<int> subTemp;

        for (int num : mat[i])
        {
            subTemp.push_back(num * vec[i]);
        }
        temp.push_back(subTemp);
    }

    for (int j = 0; j < temp[j].size(); j++)
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

std::vector<std::vector<int> > matMatMul (std::vector<std::vector<int> > mat1, std::vector<std::vector<int>  > mat2)
{   
    std::vector<std::vector<int> > res_mat;

    for (std::vector<int> vec : mat1)
    {
        res_mat.push_back(matVecMul(vec,mat2));
    }
    return res_mat;
}


int main(){

    std::vector<int> testVec;
    std::vector<int> testVec2;

    testVec.push_back(1);
    testVec.push_back(2);
    testVec.push_back(3);

    testVec2.push_back(4);
    testVec2.push_back(5);
    testVec2.push_back(6);

    std::vector<std::vector<int> > testMat;
    std::vector<std::vector<int> > testMat2;

    testMat2.push_back(testVec);
    testMat2.push_back(testVec2);

    std::vector<int> v1;
    v1.push_back(5);
    v1.push_back(6);
    std::vector<int> v2;
    v2.push_back(8);
    v2.push_back(9);
    std::vector<int> v3;
    v3.push_back(10);
    v3.push_back(11);
    testMat.push_back(v1);
    testMat.push_back(v2);
    testMat.push_back(v3);
    PRINT("--**TEST OBJECTS**--");
    printMatrix(testMat);
    printMatrix(testMat2);
    PRINT("--##**START FUNCTION**##--");

    std::vector<int> vecMulti = matVecMul(testVec,testMat);
    printVector(vecMulti);



    std::vector<std::vector<int> > matMulti = matMatMul(testMat2,testMat);

    printMatrix(matMulti);

}
