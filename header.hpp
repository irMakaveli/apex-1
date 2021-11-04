#include<vector>
#include <string>
#ifndef HEADER_H
#define HEADER_H
struct Matrix{
    std::string name;
    bool is_integer = false;
    int row,column;
    bool isfull =false;
    union type{
        int ** int_memeber;
        std::string ** str_member;
    }matrixType;
};
void help();
std::vector<std::string> brain(std::string , std::vector<std::string > &,char );
bool isInteger(std::string );
void getMatrixSize(std::string ,std::string ,int *);
Matrix getMatrix(std::vector<std::string >str,Matrix &mat1);
Matrix addMatrix(std::vector<std::string >str,Matrix &mat);
int isDiagonal(Matrix * mat , std::string str);
void isIdentify(Matrix * mat,std::string str);
bool triangular(Matrix * mat , std::string str , int i);
void edit(Matrix *mat,std::vector<std::string>str );
void triangular(Matrix * mat , std::string str);
void show(Matrix mat);
void showAll(Matrix *mat , std::vector<std::string >&str);
template<typename T>
bool isSymmetic(Matrix mat, T** a );
void symmetric(Matrix * mat , std::string name);
std::vector<std::string> getCommand(std::vector<std::string>&str);
void deletend(Matrix *mat,int j);
template<typename T>
void shift(Matrix *mat, T &a ,int j);
void deletmatrix(Matrix * mat ,std::string name);
template <typename T>
void invers(T** s ,Matrix &mat);
void inversing(Matrix * mat,std::vector<std::string >name,int & size);

#endif // !HEADER_H#def" "" 
