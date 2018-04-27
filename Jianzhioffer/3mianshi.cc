#include <iostream>
using namespace std;

bool Find(int **matrix,int rows, int columns, int number)
{
    bool ret=false;
    if(matrix == NULL|| rows < 0 ||columns < 0)return ret;
    int x=0;
    int y=columns-1;
    while(x<rows && y>-1)
    {
        // if(number==matrix[x*columns+y])
        if(number==matrix[x][y])
        {
            ret=true;
            break;
        }
        else if(number > matrix[x][y])
        {
            x++;
        }
        else
        {
            y--;
        }
    }
    return ret;
}

int main(int argc,char** argv)
{   
    int num;
    int arry[4][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
    int rows,columns;
    // rows=atoi(argv[1]);
    // columns=atoi(argv[2]);
    // int **arry=new int*[rows];
    cin>>num;
    // cout<<"please input a arry"<<endl;
    // for(int i=0;i<rows;i++)
    // {
    //     arry[i]=new int[columns];
    //     for(int j=0;j<columns;j++){
    //         cin >> arry[i][j];
    //     }
    // }
    int* p[4];
    for(int i=0;i<4;i++)
    {
        p[i]=arry[i];
    }
    bool res=Find(p,4,4,num);
    if(res==true)cout<<"find "<<endl;
    else cout<<"no find"<<endl;
    return 0;
}   
