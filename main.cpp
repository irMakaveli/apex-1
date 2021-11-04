#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "header.hpp"
#include <vector>

using namespace std;

int main()
{   
    vector<string>commands;
    int choise;
    Matrix * mat=new Matrix [100];//allocate memory
    int i =0;//matrix size
    while(true){ 
        commands.clear();//clear vector elements
        getCommand(commands);
        if(commands[0]=="help")
        {
            help();//help function
            continue;
        }
        if (commands[0]+commands[1]=="addmatrix")
        {
            mat[i]=addMatrix(commands,mat[i]);
            i++; 
            continue;
        }
        if(commands[0]=="is_diagonal")
        {
            isDiagonal(mat,commands[1]);
            continue;
        }
        if(commands[0]=="is_identify")
        {
            isIdentify(mat,commands[1]);
            continue;
        }
        if(commands[0].size()>commands[0].find("triangular"))
        {
            if(commands[0]=="is_lower_triangular")
            {
                triangular(mat ,  commands[1] , 1);
            }
            if(commands[0]=="is_upper_triangular")
            {
                triangular(mat ,  commands[1] ,2);
            }
            if(commands[0]=="is_triangular")
            {
                triangular(mat ,  commands[1]);
            }
            continue;
        }
        if(commands[0]=="edit")
        {
            edit(mat,commands);
            continue;
        }
        if(commands[0]=="show")
        {
            cout<<"shower"<<endl;
            showAll(mat , commands); 
            continue;
        }
        if(commands[0]=="delete")
        {
            deletmatrix(mat , commands[1]); 
            i--;
            continue;
        }
        if(commands[0].find("symmetric")<commands[0].size())
        {
            if(commands[0]=="is_normal_symmetric")
            {
                symmetric(mat,commands[1]);
            }
            if(commands[0]=="is_skew_symmetric")
            {
                symmetric(mat,commands[1]);
            }
            continue;
        }
        if(commands[0]=="inverse")
        {
            inversing(mat,commands,i);
            continue;
        }
        if(commands[0]=="exit")
        {
            break;
            continue;
        }
        else{
            cout<<"I can not underestand your command"<<endl;
        }
    }
    for(int i = 0; mat[i].isfull;i++)//free memory
    {
        if(mat[i].is_integer)
        {
            for(int j = 0; j<mat[i].row;j++)
            {
                delete [] mat[i].matrixType.int_memeber[j];
            }
            delete [] mat[i].matrixType.int_memeber;
        }
        else
        {
            for(int j = 0; j<mat[i].row;j++)
            {
                delete [] mat[i].matrixType.str_member[j];
            }
            delete [] mat[i].matrixType.str_member;
        }
    }    
    delete [] mat;
    return 0;
}