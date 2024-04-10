#include<iostream>
#include <string.h>
#include <math.h>
using namespace std;

#define ERROR -1
#define FUNCTION 6
#define END 0
#define embrace 15

struct  CacuBlock{
double num=0.0;
char op=' ';
int type=ERROR;
};


// goble vaules
CacuBlock Larray[20];
int LarrayPostion=-1;

int braces[20];
int bracePostion=0;
 
 
bool IsNumber(char *str)
{
    if (*str >= '0' && *str <= '9')
        return true;
    else if (*str == '.')
        return true;
    else if (*str == '-')
        return !(IsNumber(str-1));
    else 
        return false;
}

CacuBlock Str2CacuBlock(char *formula,int *start)
{
    CacuBlock block;
	bool native=false,dot=false;
	int AfterDot=0;
    for(;formula[*start]!='\0';(*start)++)
    {
        if(IsNumber(formula+*start))
        {
            if(formula[*start]>='0' && formula[*start] <= '9')
            {
            
                block.num*=10.0;
			    block.num+=double(formula[*start]-'0');
			    if (dot) 
                	AfterDot++;
            }
            else if(formula[*start] == '.')
                    dot=true;
            else if(formula[*start] == '-')
                    native=true;
        }
        else
        {
        	cout<<"num is "<<block.num<<endl;
        	if(dot)
        		for(;AfterDot>0;AfterDot--)
        		{
        			block.num/=10.0;
				}
			if(native)
				block.num/=-1.0;
            switch (formula[*start])
            {
            case '+': 
                block.op='+';
                block.type=1;
                return block;
                break;

            case '-': 
                block.op='-';
                block.type=1;
                return block;
                break;

            case '*': 
                block.op='*';
                block.type=2;
                return block;
                break;

            case '/': 
                block.op='/';
                block.type=2;
                return block;
                break;
            
            case '(': 
                block.op='(';
                block.type=embrace;
                return block;
                break;
            
            case ')': 
                block.op=')';
                block.type=embrace;
                return block;
                break;
        
            case 's': 
                if(formula[*start+1]== 'i' && formula[*start+2]=='n')
                { 
                    block.op='S';
                    block.type=FUNCTION;
                    *start=*start+2;
                    return block;
                }
                else block.type=ERROR;
                break;

            case 'c': 
                if(formula[*start+1]== 'o' && formula[*start+2]=='s')
                { 
                    block.op='C';
                    block.type=FUNCTION;
                    *start=*start+2;
                    return block;
                }
                else block.type=ERROR;
                break;
            
            case 't': 
                if(formula[*start+1]== 'a' && formula[*start+2]=='n')
                { 
                    block.op='T';
                    block.type=FUNCTION;
                    *start=*start+2;
                    return block;
                }
                else block.type=ERROR;
                break;

                case '=': 
                block.op='=';
                block.type=END;
                return block;
                break;
            default:
                block.type=ERROR;
                return block;
                break;
            } //switch
        } //else
    } //for
    block.op='=';
    block.type=END;
    return block;
}

void CacuIt(CacuBlock *victim,CacuBlock injurer)
{
    
    if( victim->type>=0 && victim->type<=2) //simple caculate funtion
    {
            switch (victim->op)
            {
            case '+':
                victim->num=victim->num+injurer.num;
                break;
            case '-':
                victim->num=victim->num-injurer.num;
                break;
            case '*':
                victim->num=victim->num*injurer.num;
                break;
            case '/':
                victim->num=victim->num/injurer.num;
                break;
            case '=': 
                break;
            default: 
                injurer.type=ERROR;
                break;
            }
            victim->op=injurer.op;
            victim->type=injurer.type;
    }
        else if(victim->type == FUNCTION)
        {
            switch (victim->op)
            {
            case 'S':
                victim->num=sin(injurer.num);
                break;
            case 'C':
                victim->num=cos(injurer.num);
                break;
            case 'T':
                victim->num=tan(injurer.num);
                break;            
            default:
                injurer.type=ERROR;
                break;
            }
            victim->op=injurer.op;
            victim->type=injurer.type;
        }
    cout<<"debug: "<<victim->num<<" "<<injurer.num<<endl;
}


void Cacu2End()
{
    for(;LarrayPostion>=1;LarrayPostion--)
    {
        CacuIt(&(Larray[LarrayPostion-1]),Larray[LarrayPostion]);
    }
}
bool ProcessBlock(CacuBlock block,double* result)
{


    if(block.type != END){
    	if(LarrayPostion==-1)
    		{
    			LarrayPostion=0;
    			Larray[LarrayPostion]=block;
			}
         else if(block.type>=0 && block.type<=4) //simple caculate funtion
        {
            if(Larray[LarrayPostion].type >= block.type)
                CacuIt(&(Larray[LarrayPostion]),block);
            else
            {
                LarrayPostion++;
                Larray[LarrayPostion]=block;
            }//else
        } //if it is simple
	}
    else 
    {
        LarrayPostion++;
        Larray[LarrayPostion]=block;
        Cacu2End();
        *result=(Larray[LarrayPostion].num);
        return false;
    }
    cout<<"debug return NULL"<<endl;
    return true;
}
void test()
{
	string str="123+1=";
	int start=0;
	double result=0.0;
	cout<<ProcessBlock(Str2CacuBlock(&str[0],&start),&result)<<endl;
	
}
int main(){
    string formula;
    cin>>formula;
     for(int i=0;formula[i]!='\0';i++)
    {
    	cout<<formula[i];
	}
    int start=0;
    double result=0.0;

    while (ProcessBlock(Str2CacuBlock(&formula[0],&start),&result)){
    	start++;
	}
   	cout<<endl<<"result:"<<result<<endl;
    
   /* while (ProcessBlock(Str2CacuBlock(&formula[0],&start),&Larray[0])==NULL)
    {
    	cout<<start<<"ok"<<endl;
    	start++;
    } */
	cout<<result;
    return 0;
}