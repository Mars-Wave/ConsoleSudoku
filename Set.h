#ifndef Set_h
#define Set_h
const int NUMBERS = 9;

typedef bool tNumbers[NUMBERS];
typedef struct {
	tNumbers nums;
	int counter;
}tSet;


void emptySet(tSet &set); 
void fullSet(tSet &set); 
bool isIn(const tSet &set, int n); 
void add(tSet &set, int n);
void erase(tSet &set, int n); 
int size(const tSet &set);
bool one(const tSet &set, int &n);
void display(const tSet &set); 
#endif 