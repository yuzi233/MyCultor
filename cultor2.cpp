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
    if(dot) 
    for(;afterdot>0;afterdot--)
    {
        numbers[head]/=10;
    }
    if(head==0)
    {
        operations[head]=op;
    }
    else
    if(abs(op)<=abs(operations[head-1]))
    {
        switch (operations[head-1])
        {
        case 1: numbers[head-1]+=numbers[head]; break;
        case -1: numbers[head-1]-=numbers[head]; break;
        case 2: numbers[head-1]*=numbers[head]; break;
        case -2: numbers[head-1]/=numbers[head]; break;
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
    
    cout<<"welcome , cultor user"<<endl;
    cin>>formula;
    for(int i=0;i<=formula.size();i++)
    {
        if(formula[i]>='0' && formula[i]<='9')
        {
            if(dot) afterdot++;
            numbers[head]*=10;
            numbers[head]+=int(formula[i]-'0');
        }
        else
        if(formula[i]=='.')
        {
            if(dot) cout<<"error: already have a dot"<<endl;
            else dot=true;
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
        else switch (formula[i])
        {
        case '+':  OccurOperation(1); break;
        case '-':  OccurOperation(-1); break;
        case '*':  OccurOperation(2); break;
        case '/':  OccurOperation(-2); break; 
        case '=': for(;head>0;head--)
        {
        switch (operations[head-1])
        {
        case 1: numbers[head-1]+=numbers[head]; break;
        case -1: numbers[head-1]-=numbers[head]; break;
        case 2: numbers[head-1]*=numbers[head]; break;
        case -2: numbers[head-1]/=numbers[head]; break;
        default: cout<<"error: unknow inner operations "<<endl; break;
        }
		}
		cout<<"result:"<<numbers[head]; break;
        default: cout<<"unkown char'"<<formula[i]<<"' "<<endl; break;
        }
        if(formula[i]=='=') break;
    }


    return 0;
}