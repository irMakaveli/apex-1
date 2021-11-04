#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <limits>
#include <limits.h>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
struct Matrix{
    string name;
    bool is_integer = false;
    int row,column;
    bool isfull =false;//matrix size
    union type{//matrix type
        int ** int_memeber;
        string ** str_member;
    }matrixType;
};
void help(){
    cout<<"enetr your command:"<<endl
        <<"add matrix : adding a matrix"<<endl
        <<"like :\nadd matrix matrix_name"<<endl
        <<"add matrix matrix_name [size] or add matrix matrix_name [size][size]"<<endl
        <<"add matrix matrix_name [size] parametr..."<<endl
        <<"add matrix matrix_name [size] [parametr,parametr,...]"<<endl
        <<"edit matrix:"<<endl
        <<"edit matri_name"<<endl
        <<"delete matrix"<<endl
        <<"delete matrix_name"<<endl
        <<"is diagonal:"<<endl
        <<"is_diagonal matirx_name"<<endl
        <<"is triangular :"<<endl
        <<"is_upper_triangular matrix_name"<<endl
        <<"is_lower_triangular matrix_name"<<endl
        <<"is_diagonal matrix_name"<<endl
        <<"symmetric :"<<endl
        <<"is_symmtric matrix_name"<<endl
        <<"inverse :"<<endl
        <<"inverse matrix_name"<<endl
        <<"identify :"<<endl
        <<"is_identify matrix_name"<<endl
        <<"show :"<<endl
        <<"show to show all"<<endl
        <<"show matrix_name"<<endl;
}//end help
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\######///////////////////////////////////////
vector<string> brain(string str, vector<string > &d,char delim)
{
//this function give a string and separat with a delimiter and push back into vector
    string temp;   
    for (size_t i = 0,j =0 ;i <= str.size(); i++)
    {
        if(delim==',')
        {
            if(str[i]=='['||str[i]==']')//delete [ and ] 
            {
                str[i]=',';
            }
        }//end if
        if(str[i]!=delim && str[i]!='\0' )
        {
            temp+=str[i];
        }
        else if(temp!=""){    

            d.push_back(temp);
            temp.erase();///clear string
        }
    }//end for
 
    return d;
}//end drain

bool isInteger(string str)
{
//this function return true if str is a number 
    vector<string> s;
    s = brain(str ,s,','); //separate if str have , or []
    for (size_t i = 0; s[0][i]!='\0'; i++)//check first parametr
    {
       
       if(!(s[0][i]>='0' && s[0][i] <='9'))//checking
       { 
           return false;
       }   
    }//end for
        return true;
}//end isinteger
void getMatrixSize(string str1,string str2,int *size)
{//this function return matrix size
//str1 is always a number but str2 can be string
    stringstream(str1)>>size[0];
    if(isInteger(str2)==true)//if str2 is number
    {
        stringstream(str2)>>size[1];
        return ;
    }
    size[1]=size[0];//if str2 is not  number
}//end getmatrixsize
Matrix getMatrix(vector<string >str,Matrix &mat1)
{//getmatrix initial matrix if matrix parametrs were in bracket
    int size[2] ;//row,column
    if(str.size()==5)//row =column
    {
    getMatrixSize(str[3],str[3],size);
    }
    else if(str.size()==6)//row != column
    {
    getMatrixSize(str[3],str[4],size);
    }
    mat1.name = str[2];//str[2] is matrix name 
    mat1.isfull=true;
    mat1.row=size[0];
    mat1.column=size[1];
    vector<string>str1;//for parametrs
    str1= brain(str[str.size()-1],str1,',');//separate parametrs  
    int c = 0;//number of parametrs
    mat1.is_integer=true;
    for(int i = 0 ; i<str1.size();i++)//parametrs are int or string
    {
        if(isInteger(str1[i])!=true)
        {
            mat1.is_integer=false;
            break;
        }
    }
    if(mat1.is_integer)//if parametrs are integer
    {
        mat1.matrixType.int_memeber= new int* [size[0]];
        for (size_t i = 0; i < size[0]; i++)
        {
           mat1.matrixType.int_memeber[i]=new int [size[1]];
        }//allocate memory 
        for (size_t i = 0; i <size[0]; i++)
        {
            for (size_t j = 0; j < size[1]; j++)
            {
                stringstream(str1[c])>>mat1.matrixType.int_memeber[i][j];//initial matrix
                c++;
            }//end for              
        }//end for
        return mat1;            
    }
    else//if parametrs are not integer
    {
        mat1.matrixType.str_member= new string* [size[0]];
        for (size_t i = 0; i < size[0]; i++)
        {
           mat1.matrixType.str_member[i]=new string [size[1]];
        }//allocate
        for (size_t i = 0; i <size[0]; i++)
        {
            for (size_t j = 0; j < size[1]; j++)
            {
                mat1.matrixType.str_member[i][j] = str1[c];//initialize
                c++;
            }//end for
        }//end for
        return mat1;            
    }
}//end getmatrix
Matrix addMatrix(vector<string >str,Matrix &mat)
{
    //this recersion function give a separated string as vector and add a new matrix
    int i = str.size();
    if(i==2)//add matrix
    {
        string s;
        cout<<"enter matrix name -->";
        getline(cin , s);
        str = brain(s ,str, ' ');//if s was more than a name then separate commands
        return addMatrix(str,mat);
    }
    if(i==3)//add matrix name
    {
        string s;
        cout<<"enter matrix size -->";
        getline(cin , s);
        int s1 = str.size();
        str = brain(s ,str, ' ');
        int s2 = str.size();
        if(s2-s1==1)//row = column
        {
            str.push_back(s);
            return addMatrix(str,mat);
        }
        else
        {
            return addMatrix(str,mat);
        }
    }//end if
    if(i==4)//add matrix name size
    {
        str=brain(str[3],str,' ');//push back row as column
        return addMatrix(str,mat);
    }
    if(i==5)//add matrix name size [p,p,p,...]
    {
        string parametrs;
        if(str[4][0]=='[')//if str[4] was parametr
        {
            return getMatrix(str,mat);
        }          
        else//else get parametrs one by one or like [o,o,...] 
        {
            cout<<"enter parametrs -->";
            fflush(stdin);//clear buffer
            getline(cin,parametrs);//get parametr
            if(parametrs[0]=='[')//parametrs with []
            {
                str.push_back(parametrs);
                return addMatrix(str,mat);
            }
            else//one by one
            { 
            int row;
            int column;
            stringstream(str[3])>>row;
            stringstream(str[4])>>column;
            mat.row=row;
            mat.column=column;
            mat.isfull=true;
            string param[row][column];//default matrix type is string
            for (int i = 0; i < row; i++)
            {
                for(int j = 0 ; j < column; j++)
                {
                    if(i==0&&j==0)
                    {
                        param[0][0]=parametrs;
                        if(isInteger(param[0][0])==true)//check parametrs type
                        {
                            mat.is_integer=true;
                        }
                        else
                        {
                            mat.is_integer=false;
                        }
                        continue;
                    }
                     cout<<"enter parametrs -->";
                     getline(cin,param[i][j],'\n');//get parametr
                }
            }
            if (mat.is_integer==true)//if matrix type is integer
            {
                mat.matrixType.int_memeber= new int *[row];
                for(int i = 0 ; i < row ; i++)
                {
                    mat.matrixType.int_memeber[i] = new int [column];
                }//allocating memory
                for (size_t i = 0; i < row; i++)
                {
                    for(int j = 0; j < column ; j++)
                    {
                       stringstream(param[i][j])>> mat.matrixType.int_memeber[i][j];//initialize
                    }
                }//end for
                mat.name = str[2];
                mat.isfull=true;
                return mat;
            }
            else{//if matrix type is string
                mat.matrixType.str_member = new string* [row];
                for(int i = 0 ; i < column ; i++)
                {
                    mat.matrixType.str_member[i] = new string [column];
                }
                for (size_t i = 0; i < row; i++)
                {
                    for(int j = 0; j < column ; j++)
                    {
                        mat.matrixType.str_member[i][j] = param[i][j];
                    }
                }
                mat.name = str[2];
                mat.isfull=true;
                return mat;
            }//end else
          }//end else
        }//ende else
        
    }//end if
    else//add matrix name size size [o,o,o,..]
    {    
        
        return getMatrix(str,mat);   
    }

}
int isDiagonal(Matrix * mat , string str)
{
      bool diagonal = true;//default
      bool identify = true;//default
      for(int i = 0;diagonal==true && mat[i].isfull  ;i++)
      {
        if(str==mat[i].name)
        {
            if(mat[i].row != mat[i].column)
            {
                cout<<str<<" is not diagonall"<<endl;
                return 1;//is not diagonal
            }
            if(mat[i].is_integer==true)
            {
                for (size_t j = 0; diagonal==true && j < mat[i].row; j++)
                {
                    for(int k = 0; k< mat[i].column ; k++)
                    {
                        if(k==j)//check if is identify
                        {
                            if(identify==true && mat[i].matrixType.int_memeber[j][k]!= 1)
                            {
                             identify = false;
                            }
                            continue;
                        }
                        else if(mat[i].matrixType.int_memeber[i][j]!=0)//check if is diagonal
                        {
                            diagonal = false;
                            break;
                        }
                    }//end for
               }//end for
            }//end if
            else{
                for (size_t j = 0; diagonal==true && j < mat[i].row; j++)
                {
                    for(int k = 0; k< mat[i].column ; k++)
                    {
                        if(k==j )
                        {
                            if(identify==true && mat[i].matrixType.str_member[j][k]!=mat[i].matrixType.str_member[0][mat[i].column-1]){
                            identify = false;
                            
                             }
                            continue;
                        }
                        else if(mat[i].matrixType.str_member[i][j]!=mat[i].matrixType.str_member[0][mat[i].column-1]){
                            diagonal = false;
                            break;
                         }
                    }//end for
                }//end for
            }//end else
        }//end if
    }//end for
    if(diagonal)
    {
        cout<<str<<" is diagonal"<<endl;
        if(identify==true)
        return 2;

        else
        return 1;//is not identify
    }
    else{
        cout<<str<<" is not diagonal"<<endl;
        return 1;
    }
}
void isIdentify(Matrix * mat,string str)
{
    if(isDiagonal(mat,str)==2)
    {
        cout<<str<<" is hamani"<<endl;

    }
    else{
        cout<<str<<" is not hamani"<<endl;
    }
}
bool triangular(Matrix * mat , string str , int i)
{
    bool triangular=true;//defaulte
        if(mat[i].row != mat[i].column)
        {
            return false;
        }
        for(int i = 0 ; mat[i].isfull==true &&  triangular==true;i++)
        {
            if(mat[i].name==str && mat[i].is_integer)
            {

                for(int j = 0;j< mat[i].row &&triangular==true; j++)
                {
                    for (size_t k = 0; k < mat[i].column && triangular==true; k++)
                    {
                        
                        if(j<k && i==1)//i = 1 lower triangular 
                        {
                            if((mat[i].matrixType.int_memeber[j][k]!=0 &&mat[i].is_integer==true) ||(mat[i].matrixType.str_member[j][k]!="zero"&&mat[i].is_integer==false))
                            {
                                cout<<str<<" is not lower triangular"<<endl;
                                triangular=false;
                                return triangular;
                            }
                        }
                        else if(j >k && i==2)//i=t upper triangular
                        {
                            if((mat[i].matrixType.int_memeber[j][k]!=0 &&mat[i].is_integer==true) ||(mat[i].matrixType.str_member[j][k]!="zero"&&mat[i].is_integer==false))
                            {
                                cout<<str<<" is not upper triangular"<<endl;
                                triangular=false;
                                return triangular;
                            }   
                        }
                    }
                  //end for  
                }
            //end if
            }
        //end if
        }
        //end for
        if(i==1)
        {
         cout<<str<<" is lower triangular"<<endl;   
        }
        if(i==2)
        {
         cout<<str<<" is upper triangular"<<endl;
        }
    return triangular;
}
void triangular(Matrix * mat , string str)
{
    //check triangular 
    if(triangular(mat,str,1)==true || triangular(mat,str,2)==true)
    {
        cout<<str<<" is triangular"<<endl;
    }
}
void edit(Matrix *mat,vector<string>str )
{//edit matrix
    for (size_t i = 0; mat[i].isfull==true; i++)//find matrix
    {
        if(mat[i].name == str[1])
        {
            if(mat[i].is_integer==true)//if mat[i] is integer
            {
                if(isInteger(str[4])==true)//str[4]is parametr
                {
                    int row,column;
                    stringstream(str[2])>>row;
                    stringstream(str[3])>>column;
                    stringstream(str[4])>>mat[i].matrixType.int_memeber[row][column];
                    cout<<str[1]<<" edited"<<endl;
                    return ;
                }
                else
                {//str[4] is not integer
                cout<<"wrong validate"<<endl;
                return ;
                }
            }
            else
            {
                if(isInteger(str[4])==false)
                {
                    int row,column;
                    stringstream(str[2])>>row;
                    stringstream(str[3])>>column;
                    mat[i].matrixType.str_member[row][column]=str[4];
                    cout<<str[1]<<" edited"<<endl;
                    return ;
                }
                else
                {
                cout<<"wrong validate"<<endl;
                return ;
                }
            }
        }
    }
    cout<<"I can not find "<<str[1]<<" !!"<<endl;
}
void show(Matrix mat)
{
    cout<<"matrix name : "<<mat.name<<endl;//show one matrix
    for(int i = 0 ; i <mat.row ; i++)
    {
        for(int j = 0 ;j < mat.column; ++j)
        {
            if(mat.is_integer==true)
            {
                cout<<left<<setw(7)<<mat.matrixType.int_memeber[i][j];
            }
            else{
                cout<<left<<setw(15)<<mat.matrixType.str_member[i][j];
            }
        }
        cout<<endl;
    }
        cout<<"********************"<<endl;
   
}
void showAll(Matrix *mat , vector<string >&str)//show all matrixes
{
    for (size_t i = 0; mat[i].isfull==true; i++)
    {   
        if(str.size()==2 && str[1]==mat[i].name)//command =show matrix_name
        {
          show(mat[i]);
          return ;
        }
        else if(str.size()==1)// command =show
        {
            show(mat[i]);
        }
    }
    
    return;
}

template<typename T>
bool isSymmetic(Matrix mat, T** a )
{//check symmetric matricx 
    T mat2[mat.row][mat.column];//create an array with same type with a
    for (size_t i = 0; i < mat.row; i++)
    {
        for(int j = 0; j < mat.column;j++)
        {
            mat2[j][i]=a[i][j];//initial mat2
        }
    }
   
     for (size_t i = 0; i < mat.row ; i++)
    {
        for(int j = 0; j < mat.column;j++)
        {
            if(mat2[i][j]!=a[i][j])//compare
            {
                return false;
            }
        }//end for
    }//end for
        return true;
}//end symemetric

void symmetric(Matrix * mat , string name)
{
    bool symmetric=true;//default
    for(int i = 0 ; mat[i].isfull ; i++)
    {
        if(mat[i].name == name)//find matrix
        {
            if(mat[i].is_integer==true)//if matrix type is integer
            {
              if(isSymmetic<int>(mat[i] , mat[i].matrixType.int_memeber)==true)//chick in function
                {
                    cout<<name<<" is symmetric"<<endl;
                }
                else
                {
                 cout<<name<<" is not symmetric"<<endl;   
                }

               
            }
            if(mat[i].is_integer==false)
            {
              if(isSymmetic<string>(mat[i] , mat[i].matrixType.str_member)==true)
                {
                    cout<<name<<" is symmetric"<<endl;
                }
                else
                {
                 cout<<name<<" is not symmetric"<<endl;   
                }
            }
        }
    }
}
vector<string> getCommand(vector<string>&str)
{
    //get command character by character
    string strCommand =""; 
    cout<<"Enter your command"<<endl;
    char ch;
    fflush(stdin);
    for (size_t i = 0; true; i++)
    {
       ch=cin.get();
       if(ch=='\n')
       {
           break;
       }
       strCommand+=ch;
    }
    brain(strCommand,str,' ');//separate command
    return str;
}
template<typename T>
void deletend(Matrix *mat,int j)
{//delete last element
   mat[j].isfull=false;
}
template<typename T>
void shift(Matrix *mat, T &a ,int j)
{
    for (size_t k = 0; k < mat[j].row; k++)
    {        
       delete []  a[k];//[z];   
    }
    delete [] a;
    //delete old memory
    if(mat[j+1].isfull)
    {            
        mat[j].row = mat[j+1].row;
        mat[j].name = mat[j+1].name;
        mat[j].column = mat[j+1].column;
        mat[j].is_integer = mat[j+1].is_integer;//initialize
        if(!mat[j].is_integer )//is string
        {
            mat[j].matrixType.str_member=new string * [mat[j].row];
            for(int h = 0 ; h < mat[j].row;h++)
            {
                mat[j].matrixType.str_member[h]=new string [mat[j].column];
            }//allocate momory
            for (size_t c = 0; c < mat[j].row; c++)
            {
                for (size_t x = 0; x < mat[j].column; x++)
                {
                    mat[j].matrixType.str_member[c][x] = mat[j+1].matrixType.str_member[c][x];
                }//initialize                 
            }               
        }
        else{//if matrix type is integer
            
            mat[j].matrixType.int_memeber=new int * [mat[j].row];
            for(int h = 0 ; h < mat[j].row;h++)
            {
                mat[j].matrixType.int_memeber[h]=new int [mat[j].column];
            }
            for (size_t c = 0; c < mat[j].row; c++)
            {
                for (size_t x = 0; x < mat[j].column; x++)
                {
                    mat[j].matrixType.int_memeber[c][x] = mat[j+1].matrixType.int_memeber[c][x];
                }       
            }//end for
        }//end else
   }//end if
}//end delete
void deletmatrix(Matrix * mat ,string name)
{
    for (size_t i = 0; mat[i].isfull==true; i++)
    {
        if(name == mat[i].name)//find matrix
        {
            for(int j = i ; mat[j].isfull ; j++)
            {
                if(mat[j].is_integer==true)//if matrix type is integer
                {
                    shift<int **>(mat, mat[j].matrixType.int_memeber,j);
                }
                if(mat[j].is_integer==false)//if matrix type is integer
                {
                    shift<string **>(mat, mat[j].matrixType.str_member,j);
                }
                 if(mat[j+1].isfull==false)
                {
                    cout<<j<<endl;
                    deletend<int **>(mat, j);//delete last element
                    return;
                }
            }
        }
    }
}
template <typename T>
void invers(T** s ,Matrix &mat)
{//inverse matrix
    for(int i=0; i<mat.row ; i++)
    {
        for(int j = 0; j < mat.column ; j++)
        {
            if(i<j)//half elements
            {    
                T temp = s[i][j];
                s[i][j] = s[j][i];
                s[j][i] = temp;//replacing
            }            
        }
    }
}
void inversing(Matrix * mat,vector<string >name,int & size)
{//inverse matrix
    for(int i = 0; mat[i].isfull ;i++)//search
    {
        if(mat[i].name == name[1] &&mat[i].row==mat[i].column)//find
        {
                if(name.size()==3)//invers and add into new matrix
                {
                    vector<string>str;//create a vector to push
                    str.push_back("add");//add matrix command
                    str.push_back("matrix");//add matrix command
                    str.push_back(name[2]);//matrix name
                    str.push_back(to_string(mat[i].row));//matix size
                    str.push_back(to_string(mat[i].column));//matrix size
                    string parametrs="[";
                    int c=0;//counter
                    for(int j = 0;j<mat[i].row;j++)//for row
                    {
                        for(int k = 0; k< mat[i].column;k++)//for column
                        {
                            if(mat[i].is_integer)//is matrix type is integer
                            {   //create parametrs like [p,p,p,...]
                                string param;
                                param = to_string(mat[i].matrixType.int_memeber[j][k]);
                                c++;
                                parametrs +=param ;
                                if(c==mat[i].row +mat[i].column)
                                parametrs += "]";
                                else
                                parametrs += ",";
                            }
                            else
                            {
                                string param;
                                param = mat[i].matrixType.str_member[j][k];
                                c++;
                                parametrs +=param ;
                                if(c==mat[i].row +mat[i].column)
                                parametrs += "]";
                                else
                                parametrs += ",";
                            }
                        }
                    }
                    str.push_back(parametrs);
                    mat[size]=addMatrix(str , mat[size]);//add matrix
                }
                if(mat[i].is_integer)//inverse integer matrix
                {
                    invers<int>(mat[i].matrixType.int_memeber , mat[i]);
                } 
                else//inverse string matrix
                {
                    invers<string>(mat[i].matrixType.str_member , mat[i]);
                }
            }
       } 
}//end inverse
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
        }
        if (commands[0]+commands[1]=="addmatrix")
        {
            mat[i]=addMatrix(commands,mat[i]);
            i++; 
        }
        if(commands[0]=="is_diagonal")
        {
            isDiagonal(mat,commands[1]);
        }
        if(commands[0]=="is_identify")
        {
            isIdentify(mat,commands[1]);
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
        }
        if(commands[0]=="edit")
        {
            edit(mat,commands);
        }
        if(commands[0]=="show")
        {
            cout<<"shower"<<endl;
            showAll(mat , commands); 
        }
        if(commands[0]=="delete")
        {
            deletmatrix(mat , commands[1]); 
            i--;
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
        }
        if(commands[0]=="inverse")
        {
            inversing(mat,commands,i);
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