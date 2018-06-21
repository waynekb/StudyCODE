
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        if(threshold <0 || rows<0 || cols <0)return 0;
        checkerboard=new vector<char>(rows*cols,0);
        board_rows=rows-1;
        board_cols=cols-1;
        counts=0;
        move(threshold, 0 ,0);
        return counts;
    }
    
private:
    void move(int threshold, int rows, int cols){
        if(rows < 0 || rows >board_rows || cols <0 || cols > board_cols)return ;
        int sum=0;
        int index=rows;
        while(index >0){
            sum+=index%10;
            index=index/10;
        }
        index=cols;
        while(index >0){
            sum+=index%10;
            index=index/10;
        }
        if(sum > threshold)return;
        index=rows*board_cols+cols;
        if((*checkerboard)[index])return ;
        (*checkerboard)[index]=1;
        counts++;
        cout<< rows<<" "<<cols<<endl;
        move(threshold, rows+1, cols);
        move(threshold, rows-1, cols);
        move(threshold, rows, cols+1);
        move(threshold, rows, cols-1);
        return ;
    }
    vector<char>* checkerboard=NULL;
    int board_rows=0;
    int board_cols=0;
    int counts=0;
};

int main(){
    Solution sol;
    cout<<sol.movingCount(15,20,20)<<endl;
    return 0;
}


select salary_growth.emp_no,salary_growth.growth
from(select h.emp_no, h.hire_salary, b.salary,(b.salary-h.hire_salary) as growth
     from (select e.emp_no, a.salary as hire_salary
            from employees as e inner join salaries as a 
             on e.emp_no=a.emp_no
             and e.hire_date=a.from_date) as h 
    inner join salaries as b
    on h.emp_no=b.emp_no
     and b.to_date='9999-01-01'
    )as salary_growth;