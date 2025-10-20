#include <stdio.h>

template<typename I>
I add(I a, I b) {


	return 0;
}

template<>
float add<float>(float a, float b) {

	return a - b;

}

template<typename T>
T Min(T a, T b) {
	return (a < b) ? a : b;
}

int main() {

	int num1I = 200;
	int num2I = 400;

	float num1F = 500.13f;
	float num2F = 200.34f;

	double num1D = 500.5632754;
	double num2D = 300.5632754;

	printf("%d\n", Min<int>(num1I, num2I));
	printf("%f\n", Min<float>(num1F, num2F));
	printf("%f\n", Min<double>(num1D, num2D));

	return 0;
}