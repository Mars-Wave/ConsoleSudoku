#include <iostream>
#include "checkML.h"
#include "Set.h"
using namespace std;

void emptySet(tSet &set) {
	set.counter = 0;
	for (int i = 0; i < NUMBERS; i++) {
		set.nums[i] = false;
	}
}

void fullSet(tSet &set) {
	set.counter = NUMBERS;
	for (int i = 0; i < NUMBERS; i++) {
		set.nums[i] = true;
	}
}

bool isIn(const tSet &set, int n) {
	bool belongs = true;
	if (!set.nums[n - 1]) {
		belongs = false;
	}
	return belongs;
}

void add(tSet &set, int n) {
	if (set.nums[n - 1] == false) {
		set.nums[n - 1] = true;
		set.counter++;
	}
}

void erase(tSet &set, int n) {
	if (set.nums[n - 1] == true) {
		set.nums[n - 1] = false;
		set.counter--;
	}
}

int size(const tSet &set) {
	return set.counter;
}

bool one(const tSet &set, int &n) {
	bool isOne = false;
	if (size(set) == 1) {
		isOne = true;
		for (int i = 0; i < NUMBERS; i++) {
			if (set.nums[i]) {
				n = i + 1;
			}
		}
	}
	return isOne;
}

void display(const tSet &set) {
	for (int i = 0; i < NUMBERS; i++) {
		if (set.nums[i]) {
			cout << "   " << i + 1 << endl;
		}
	}
}