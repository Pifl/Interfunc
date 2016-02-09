#include <stdio.h>
#include <string.h>

//Opcodes
#define HALT 0
#define ICONST 1
#define IADD 2
#define PRINT 24


typedef struct
{
	int opnum;
	char opcode[10];
	int operands;
} Instruction;

typedef struct
{
	int value;
	char name[5];
} Varible;

Instruction instructions[] = {
	{HALT, "HALT", 0},
	{ICONST, "ICONST", 1},
	{IADD, "IADD", 0},
	{PRINT, "PRINT", 0}
};

/*
>>int v = 1;
	int u = 1;
	v+u;
	print;
*/

const int code[100] = {};

const char prog[] = "int v = 1;\n int u = 2;\n v += u;\n print v;\n\0";

const int MAX_CODE_LENGTH  = 100;

int main ()
{
	int instructionPointer = -1;
	int codePointer = -1;


	int funcStack[50] = {0};
	int dataStack[50] = {0};
	int funcPointer = -1;
	int dataPointer = -1;

	int currentValue = -1;

	int charIndex = 0;
	int	workingIndex = 0;
 	int eleIndex = 0;

	char elements[5][10];
	char word[10];

	while (prog[charIndex] != '\0')
	{		
		if(prog[charIndex] != '\n')
		{
			if(prog[charIndex] == ' ' || prog[charIndex] == ';')
			{
				word[workingIndex] = '\0';
				int i;
				for(i=0;i<10; i = i + 1)
				{				
					if(word[i] == '\0')	
					{
						break;
					}
					elements[eleIndex][i] = word[i];
				}
				
				printf("%s ", word);
				workingIndex = -1;

				eleIndex++;
			}else
			{
				word[workingIndex] = prog[charIndex];
			}	
			workingIndex++;
		}	
		charIndex++;
	}

	while(++instructionPointer < MAX_CODE_LENGTH)
	{
		codePointer = instructionPointer;
		int instruction = code[instructionPointer];
		switch ( instruction) {
		case HALT:
			printf("exit\n");
			return 0;
		case ICONST:
			;
			int value = code[++codePointer];
			dataStack[++dataPointer] = value;			
			break;
		case IADD:
			;
			int v = dataStack[dataPointer--];
			int u = dataStack[dataPointer--];
			int result = v+u;
			dataStack[dataPointer] = result;
			break;
		case PRINT:
			;
			v = dataStack[dataPointer--];
			printf("%i\n", v);
			break;
		}

		instructionPointer = codePointer;

	}


	return 0;
}

