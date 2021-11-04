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

#endif // !HEADER_H#def" "" 
