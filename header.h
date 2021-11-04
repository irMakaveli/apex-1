#include<vector>
#include <string>
using namespace std;
#ifndef HEADER_H
#define HEADER_H
struct Matrix{
    string name;
    bool is_integer = false;
    int row,column;
    bool isfull =false;
    union type{
        int ** int_memeber;
        string ** str_member;
    }matrixType;
};
void help();
vector<string> brain(string , vector<string > ,char );
bool isInteger(string );
void getMatrixSize(string str1,string str2,int *size);
Matrix getMatrix(vector<string >str,Matrix &mat1);
Matrix addMatrix(vector<string >str,Matrix &mat);
int isDiagonal(Matrix * mat , string str);
void isIdentify(Matrix * mat,string str);
bool triangular(Matrix * mat , string str , int i);
void edit(Matrix *mat,vector<string>str );
void triangular(Matrix * mat , string str);
void show(Matrix mat);
void showAll(Matrix *mat , vector<string >&str);
template<typename T>
bool isSymmetic(Matrix mat, T** a );
void symmetric(Matrix * mat , string name);
vector<string> getCommand(vector<string>&str);
void deletend(Matrix *mat,int j);
template<typename T>
void shift(Matrix *mat, T &a ,int j);
void deletmatrix(Matrix * mat ,string name);
template <typename T>
void invers(T** s ,Matrix &mat);
void inversing(Matrix * mat,vector<string >name,int & size);

#endif // !HEADER_H#def" "" 
