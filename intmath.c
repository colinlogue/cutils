#include "intmath.h"


int max_int(int a, int b) {
	if (a > b) return a; else return b;
}


int min_int(int a, int b) {
	if (a < b) return a; else return b;
}


int int_to_power(int base, int power) {
	assert(power >= 0);
	int x = 1;
	for (int i = 0; i < power; i++) x *= base;
	return x;
}


int factorial(int n) {
	int x = 1;
	for (int i=1; i < n; i++) {
		x *= i;
	}
	return x;
}


int max_of_n(int n, ...) {
	va_list nums;
	va_start (nums, n);
	int max_x = va_arg(nums, int);
	for (int i=1; i<n; i++) {
		int x = va_arg(nums, int);
		if (x > max_x) {
			max_x = x;
		}
	}
	va_end(nums);
	return max_x;
}


int min_of_n(int n, ...) {
	va_list nums;
	va_start (nums, n);
	int min_x = va_arg(nums, int);
	for (int i=1; i<n; i++) {
		int x = va_arg(nums, int);
		if (x < min_x) {
			min_x = x;
		}
	}
	va_end(nums);
	return min_x;
}

int sum_of_n(int n, ...) {
	va_list nums;
	int sum = 0;
	va_start (nums, n);
	for (int i=0; i<n; i++) {
		sum += va_arg(nums, int);
	}
	va_end(nums);
	return sum;
}