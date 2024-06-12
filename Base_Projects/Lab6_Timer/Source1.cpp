#include <iostream>
#include <cmath>
using namespace std;
int N = 613244;
int main()
{
	
	checkhappy(N);
	
}

int checkhappy(int number)
{
	int 3dgts = number % 1000;
	int ones = 3dgts % 10;
	int tens = (3dgts % 100) / 10;
	int hundreds = 3dgts / 100;
	int sum1 = ones + tens + hunderds;
	int reversed = 0; 

	while(n != 0){
		reverse = reverse * 10;
		reverse += number % 10; 
		number = number / 10;
	}

	cout << sum1;

}