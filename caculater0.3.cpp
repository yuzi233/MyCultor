#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>
using namespace std;

#define ERROR -1
#define FUNCTION 6
#define END 0
#define EMBRACED 15

struct  CacuBlock {
	long double num = 0.0;
	long double image_num = 0.0;
	char op = ' ';
	int type = END;
};


// goble vaules
CacuBlock Larray[20];
int LarrayPostion = -1;

int brackets[20];
int BracketHead = -1;

bool problem = false;

const long double PI = 3.1415926535897932384626433832795;

bool IsNumber(char *formula, size_t start) {
	if (formula[start] >= '0' && formula[start] <= '9')
		return true;
	else
		switch (formula[start]) {
			case '-':
				return !isalnum(formula[start - 1]);
				break;
			case '.':
			case 'i':
			case 'p':
				return true;
				break;
			default :
				return false;

		}
}

CacuBlock Str2CacuBlock(char *formula, size_t *start) {
	CacuBlock block;
	bool native = false, point = false;
	int AfterDot = 0;
	bool NumEndFlag = false;
#define NUMCUT if (point) { \
		for (; AfterDot > 0; AfterDot--) { \
			block.num /= 10.0; \
		} \
	} \
	if (native) { \
		block.num *= -1.0; \
	} \
	native = false; \
	point = false; \
	AfterDot=0; \
	NumEndFlag = true;

	if (problem) {
		block.type = ERROR;
		return block;
	}

	for (; formula[*start] != '\0'; (*start)++) {
		if (IsNumber(formula, *start)) {
			if (formula[*start] >= '0' && formula[*start] <= '9') {

				if (NumEndFlag) {//check error
					problem = true;
					block.type = ERROR;
					return block;
				}

				block.num *= 10.0;
				block.num += double(formula[*start] - '0');
				if (point)
					AfterDot++;
			} else
				switch (formula[*start]) {
					case '.':
						point = true;
						break;
					case '-':
						native = true;
						break;
					case 'p':
						NUMCUT;
						if (IsNumber(formula, *start - 1))
							block.num *= PI;
						else
							block.num = PI;
						break;
					case 'i':
						NUMCUT;
						if (IsNumber(formula, *start - 1))	{
							block.image_num = block.num;
							block.num = 0.0;
						} else
							block.image_num = 1.0;
						break;
					default:
						block.type = ERROR;
						problem = true;
						return block;
				}
		} else {
			NUMCUT;
			switch (formula[*start]) {
				case '+':
					block.op = '+';
					block.type = 1;
					return block;
					break;

				case '-':
					block.op = '-';
					block.type = 1;
					return block;
					break;

				case '*':
					block.op = '*';
					block.type = 2;
					return block;
					break;

				case '/':
					block.op = '/';
					block.type = 2;
					return block;
					break;

				case '(':
					block.op = '(';
					block.type = EMBRACED;
					return block;
					break;

				case ')':
					block.op = ')';
					block.type = EMBRACED;
					return block;
					break;

				case 's':
					if (formula[*start + 1] == 'i' && formula[*start + 2] == 'n') {
						if (*start == 0)
							block.num = 1.0;
						block.op = 'S';
						block.type = FUNCTION;
						*start = *start + 2;
						if (!IsNumber(formula, *start - 1))
							block.num = 1.0;
						return block;
					} else
						block.type = ERROR;
					break;

				case 'c':
					if (*start == 0)
						block.num = 1.0;
					if (formula[*start + 1] == 'o' && formula[*start + 2] == 's') {
						block.op = 'C';
						block.type = FUNCTION;
						*start = *start + 2;
						if (!IsNumber(formula, *start - 1))
							block.num = 1.0;
						return block;
					} else
						block.type = ERROR;
					break;

				case 't':
					if (*start == 0)
						block.num = 1.0;
					if (formula[*start + 1] == 'a' && formula[*start + 2] == 'n') {
						block.op = 'T';
						block.type = FUNCTION;
						*start = *start + 2;
						if (!IsNumber(formula, *start - 1))
							block.num = 1.0;
						return block;
					} else
						block.type = ERROR;
					break;

				case '=':
					block.op = '=';
					block.type = END;
					return block;
					break;
				default:
					block.type = ERROR;
					problem = true;
					return block;
					break;
			} //switch
		} //else
	} //for
	block.op = '=';
	block.type = END;
	return block;
}

void CacuIt(CacuBlock *victim, CacuBlock injurer) {

	if ( victim->type >= 0 && victim->type <= 4) { //simple caculate funtion
		switch (victim->op) {
			case '+':
				victim->num += injurer.num;
				victim->image_num += injurer.image_num;
				break;
			case '-':
				victim->num = victim->num - injurer.num;
				victim->num = victim->image_num - injurer.image_num;
				break;
			case '*':
				double temp;
				temp = victim->num * injurer.num - ( victim->image_num * injurer.image_num);
				victim->image_num = victim->image_num * injurer.num + (victim->num * injurer.image_num);
				victim->num = temp;
				break;
			case '/':
				if (victim->image_num == 0.0 && injurer.image_num == 0.0)
					victim->num = victim->num / injurer.num;
				else {
					victim->num = (victim->image_num * injurer.image_num + victim->num * injurer.num) /
					              (injurer.num * injurer.num + injurer.image_num * injurer.image_num);
					victim->image_num = (victim->image_num * injurer.num - victim->num * injurer.image_num ) /
					                    (injurer.num * injurer.num + injurer.image_num * injurer.image_num);
				}
				break;
			case '=':
				break;
			default:
				injurer.type = ERROR;
				break;
		}
		victim->op = injurer.op;
		victim->type = injurer.type;
	} else if (victim->type == FUNCTION) {
		switch (victim->op) {
			case 'S':
				victim->num *= sin(injurer.num);
				break;
			case 'C':
				victim->num *= cos(injurer.num);
				break;
			case 'T':
				victim->num *= tan(injurer.num);
				break;
			default:
				injurer.type = ERROR;
				break;
		}
		victim->op = injurer.op;
		victim->type = injurer.type;
	}
	//cout << "debug: " << victim->num << " " << injurer.num << endl;
}


void Cacu2End() {
	for (; LarrayPostion >= 1 ; LarrayPostion--) {
		CacuIt(&(Larray[LarrayPostion - 1]), Larray[LarrayPostion]);
	}
}

bool ProcessBlock(CacuBlock block, double *result, double *image_result) {

	if (block.type == ERROR) {
		problem = true;
		return false;	
	}  
	if (block.type != END) {
		if (LarrayPostion == -1) {
			LarrayPostion = 0;
			Larray[LarrayPostion] = block;
		} else if (block.type >= 0 && block.type <= 6) { //simple caculate funtion
			if (Larray[LarrayPostion].type >= block.type)
				CacuIt(&(Larray[LarrayPostion]), block);
			else {
				LarrayPostion++;
				Larray[LarrayPostion] = block;
			}//else
		} //if it is simple
		else if (block.type == EMBRACED) {
			if (block.op == '(') {
				BracketHead++;
				brackets[BracketHead] = LarrayPostion;
			}

			if (block.op == ')') {
				for (;;) {
				}
			}
		}
	} else {
		LarrayPostion++;
		Larray[LarrayPostion] = block;
		Cacu2End();
		*result = (Larray[LarrayPostion].num);
		*image_result = (Larray[LarrayPostion].image_num);
		return false;
	}
	return true;
}

void test() {
	string str = "123+1=";
	size_t start = 0;
	double result = 0.0, resulti;
	cout << ProcessBlock(Str2CacuBlock(&str[0], &start), &result, &resulti) << endl;

}

int main() {
	string formula;
	cin >> formula;
	for (int i = 0; formula[i] != '\0'; i++) {
		cout << formula[i];
	}
	size_t start = 0;
	double result = 0.0;
	double resulti = 0.0;
	while (ProcessBlock(Str2CacuBlock(&formula[0], &start), &result, &resulti)) {
		if (problem == true) {
			cout << "warning" << endl;
		}
		start++;
	}
	if (problem == true) {
		cout << "error!" << endl;
	}
	cout << result << endl;
	cout << setiosflags(ios::fixed) << result << endl;
	if (resulti != 0)
		cout << "i:" << resulti << endl;
	return 0;
}
