#include<iostream>
#include<cmath>
#include<string>
using namespace std;
long double numbers[8]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
int operations[8];
int head=0;
bool native=false,dot=false;
int afterdot=0;

void OccurOperation(int op)
    {
    if(native) numbers[head]*=-1;
    native=false;
    if(dot) 
    for(;afterdot>0;afterdot--)
    {
        numbers[head]/=10.0;
    }
    afterdot=0;
    dot=false; 
    //这里封装数字,开启运算符号处�?
    if(op==0)
    {
    	for(;head>0;head--)
        {
        switch (operations[head-1])
        {
        case 1: numbers[head-1]+=numbers[head]; break;
        case -1: numbers[head-1]-=numbers[head]; break;
        case 2: numbers[head-1]*=numbers[head]; break;
        case -2: numbers[head-1]/=numbers[head]; break;
        case +3: numbers[head-1]=pow(numbers[head-1],numbers[head]); break;
        default: cout<<"error: unknow inner operations2 "<<endl; break;
        }
		}
		cout<<"result:"<<numbers[head];
	}
    /**像这样operations[head]对应着被操作数numbers[head]和操作数numbesr[head-1]
     * numbers      [] [] []
     *               |/ |/ |   
     * operations   [] [] []
     * 
     *  formula [n] [o] [n] [n] [o]
     */
    if(head==0)
    {
        operations[head]=op;
    }
    else
    if(abs(op)<=abs(operations[head-1]))
    {
        switch (operations[head-1])
        {
        case +1: numbers[head-1]+=numbers[head]; break;
        case -1: numbers[head-1]-=numbers[head]; break;
        case +2: numbers[head-1]*=numbers[head]; break;
        case -2: numbers[head-1]/=numbers[head]; break;
        case +3: numbers[head-1]=pow(numbers[head-1],numbers[head]); break;
        case -3: numbers[head-1]/=numbers[head]; break;
        default: cout<<"error: unknow inner operations "<<endl; break;
        }
        numbers[head]=0.0;
        head--;
        operations[head]=op;
    }
    else
        operations[head]=op;
    head++;
    }

int main()
{
    
 
    
    string formula;
    for(int i=8;i>0;i--)
    {
        operations[i]=0;
    }
    //输入部分
    cout<<"welcome , cultor user"<<endl;
    cin>>formula;
    //识别部分
    for(int i=0;i<=formula.size();i++)
    {   //数字识别
        if(formula[i]>='0' && formula[i]<='9')
        {
            if(dot) afterdot++;
            numbers[head]*=10;
            numbers[head]+=int(formula[i]-'0');
        }
        //数字符号识别
        else
        if(formula[i]=='.')
        {
            if(dot) cout<<"error: already have a dot"<<endl;
            dot=true;
        }
        else if(formula[i]=='-')
        {
            if(i==0) native=true;
            else
            switch (formula[i])
            {
            case '+': case '-': case '*' : case '/': native=true; break; 
            case '.': cout<<"error: '-' should'nt  occur berfore '.' "<<endl;
            default:
                break;
            }
        }
        //运算符号识别
        else switch (formula[i])
        {
        case '+':  OccurOperation(1); break;
        case '-':  OccurOperation(-1); break;
        case '*':  OccurOperation(2); break;
        case '/':  OccurOperation(-2); break; 
        case '^':  OccurOperation(3); break; 
        case '=':  OccurOperation(0); break;
        default: cout<<"unkown char'"<<formula[i]<<"' "<<endl; break;
        }
        if(formula[i]=='=') break;//去除�?'/n' ' '这样的未知字符报�?
    }


    return 0;
}
