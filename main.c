#include <stdio.h>
#include <stdbool.h>

#define sp (registers[SP])
#define ip (registers[IP])

bool running = true;

int stack[256];

typedef enum {
	PSH,
	ADD,
	POP,
	SET,
	HLT
} InstructionSet;

typedef enum {
	A, B, C, D, E, F, IP, SP,
	NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

const int program[] = {
	PSH, 5,
	PSH, 6,
	ADD,
	POP,
	SET, IP, 0,
	HLT
};

void eval(int instr)
{
	switch (instr) {
		case HLT: {
			running = false;
			break;
		}
		case PSH: {
			sp++;
			stack[sp] = program[++ip];
			break;
		}
		case POP: {
			int val_popped = stack[sp--];

			printf("popped %d\n", val_popped);
			break;
		}
		case ADD: {
			int a = stack[sp--];
			int b = stack[sp--];
			
			int result = b + a;
			sp++;
			stack[sp] = result;
			break;
		}
		case SET: {
			int r = program[++ip];
			int v = program[++ip];

			registers[r] = v;
			break;
		}
	}
}

int fetch()
{
	return program[ip];
}

int main()
{
	while (running) {
		eval(fetch());
		ip++;
	}
	return 0;
}
