/*
Time : 2021-2-13 8:30
Writer : yuzi
push 1:I take it to the github. But i do not know  how to use;  
push 2:It mostly work !
*/
#include <iostream>
using namespace std;
char Uscreen[128]; //the Uscreen means UPscreen,above screen ,it record what you input, the same to the Dscreen; 
int Umny;  //the Umny is work for the Uscreen it means how many numbers you inputed
long double Dscreen=0,Dbscreen=1; //the Dscreen means Downscreen ,below screen , it record what it should output
long double rn[128];  // means Ready numbers
//long int rnf[128]; //means ready numbers' fraction below
long int arn[128/2+1]; //means acc ready numbers
int afterpoint=1;  
bool point=false;
bool flag=true;
bool negat=false;
int opeasp[64];
int opost=1;
int numberp=0;
int Nmny=0;
bool nc=true,nct=nc;//means number cut //nct means number cut i

void MemoryClear()
{
     for(Umny=128;Umny>0;Umny--)
    {
        Uscreen[Umny]=0;
        rn[Umny]=0.0;
        //rnf[Umny]=0;
        arn[Umny]=0;
        opeasp[Umny/2]=0;
        //numberp[Umny/2]=0.0;
        opost=1;
        Nmny=0;
    }
    Umny=0;
}

int main()
{
    //start part
    MemoryClear();
    cout<<"welcome";
    cout<<endl;
    //intput part
    do
    {
        Umny++;
        cin>>Uscreen[Umny];
        if(Umny>=128)
        {
            cout<<"you inputed too long , it more than 128! input agin"<<endl;
            Umny=0;
        }
    }
     while (Uscreen[Umny]!='z');
    cout<<endl;
    //break it part
    for(int i=1;i<128;i++)
    {
       int temp2=i-1;
nct = nc;
    switch( Uscreen[i] )
    {
        case '0': rn[numberp]*=10.0; if(point) afterpoint*=10; nc=true; break;
        case '1': rn[numberp]*=10.0; rn[numberp]+=1.0; if(point) afterpoint*=10; nc=true; break;
        case '2': rn[numberp]*=10.0; rn[numberp]+=2.0; if(point) afterpoint*=10; nc=true; break;
        case '3': rn[numberp]*=10.0; rn[numberp]+=3.0; if(point) afterpoint*=10; nc=true; break;
        case '4': rn[numberp]*=10.0; rn[numberp]+=4.0; if(point) afterpoint*=10; nc=true; break;
        case '5': rn[numberp]*=10.0; rn[numberp]+=5.0; if(point) afterpoint*=10; nc=true; break;
        case '6': rn[numberp]*=10.0; rn[numberp]+=6.0; if(point) afterpoint*=10; nc=true; break;
        case '7': rn[numberp]*=10.0; rn[numberp]+=7.0; if(point) afterpoint*=10; nc=true; break;
        case '8': rn[numberp]*=10.0; rn[numberp]+=8.0; if(point) afterpoint*=10; nc=true; break;
        case '9': rn[numberp]*=10.0; rn[numberp]+=9.0; if(point) afterpoint*=10; nc=true; break;
        case '-': switch (Uscreen[(i-1)])
        {
            case '0': case '1': case '3': case '4': case '5': case '6': case '7': case '8': case '9': 
            opeasp[opost]=2; opost++; nc=false; flag=false; if(point) rn[numberp]/=afterpoint; afterpoint=1; point=false; if(negat==true) rn[numberp]*=-1; negat=false; numberp++; nc=false; nc=true; negat=true; break;
            default : nc=true; negat=true; 
        } break; 
        case '.': point=true; nc=true; break;
        case 'z': nc=false; i=128;
        case '=': nc=false;
        default : flag=false; 
        if(point) rn[numberp]/=afterpoint; afterpoint=1; 
        point=false; 
        if(negat==true) rn[numberp]*=-1; 
        negat=false; 
        numberp++; 
        nc=false; break; 
    }


    switch(Uscreen[i])
    {
        case '+': opeasp[opost] = 1; opost++; opeasp[opost] = 0; nc=false; break;
        //   '-'				  2
        case '*': opeasp[opost] = 3; opost++; opeasp[opost] = 0; nc=false; break;
        case '/': opeasp[opost] = 4; opost++; opeasp[opost] = 0; nc=false; break;
        case '^': opeasp[opost] = 5; opost++; opeasp[opost] = 0; nc=false; break;
        case '@': opeasp[opost] = 6; opost++; opeasp[opost] = 0; nc=false; break;
    }
    if(nct==true && nc==false)
    {
        Nmny++;
        if(negat) if(rn[numberp]>=0) rn[numberp]=rn[numberp]*-1.0;
    }
    }
    int WhereEnd;
    // count part
    for(int i=1;i<Nmny;i++) // times & divide part
    {	//times part
    	if(opeasp[i] == 3 )
    	 {
    		rn[i]=rn[i-1]*rn[i];
    		//sncy part 
		 	WhereEnd=i;
			rn[i-1]=rn[i];
		 }
    	
		// divide part
		if(rn[i] == 4)
		{
		rn[i]=rn[i-1]/rn[i];
			// sncy part
		WhereEnd=i;
		rn[i-1]=rn[i];
		}
		
    }
    
    for(int i=1;i<=Nmny;i++) //plus & subtract part
    {	//plus part
    	if(opeasp[i] == 1)
    	{
    		rn[i]=rn[i-1]+rn[i];
    		WhereEnd=i;
			rn[i-1]=rn[i];
		}
    	
    	//subtact part
    	if(opeasp[i] == 2)
    		{
    		rn[i]=rn[i-1]-rn[i];
    		//sncy part
			WhereEnd=i;
			rn[i-1]=rn[i];
			}
	}
    cout<<endl<<"result:"<<rn[WhereEnd]<<endl;
    return 0;
}
