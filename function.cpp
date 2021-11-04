#include <iostream>
using namespace std;

string * brain(string s , string * str , char delim)
{
    static int size=0;
    if(delim==' '){ 
    if(s.find(delim)> s.size())
    {
        str[size] = s;
        size = 0;
        return str;
    }
    int c = s.find(delim);
    str[size] = s.substr(0, c);   
    s.erase(0,c+1);
    size++;
    return brain(s ,str,delim);
    }
    else{ 
    if(s[0]=='['&& s[s.size()-1]==']')
    {
        s.erase(0);
        s.erase(s.size()-1);
    }
     if(s.find(delim)> s.size())
    {
        str[size] = s;
        size = 0;
        bool isStr=true,isInt=true,isFloat=true;
        for (size_t i = 0; i < str->size(); i++)
        {
            for(int j = 0 ; j <str[i].size() ; i++)
            {
                if((static_cast<int>(str[i][j])>=97 && static_cast<int>(str[i][j])<=122)||(static_cast<int>(str[i][j])>=65 && static_cast<int>(str[i][j])<=90))
                {
                    isInt=true
                }
                if(static_cast<int>(str[i][j])>=48 && static_cast<int>(str[i][j])<=57)
                {
                    isInt=true
                }

            }
        }
        
        return str;
    }
    int c = s.find(delim);
    str[size] = s.substr(0, c);   
    s.erase(0,c+1);
    size++;
    return brain(s ,str,delim);
    }
    

}
int main()
{
    string s = "12s ";
    cout<<stoi(s);
    
    return 0;
}