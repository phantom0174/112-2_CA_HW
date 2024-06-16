// A Naive recursive solution for Rod cutting problem
#include<iostream>
using namespace std;
// Refernce : https://www.geeksforgeeks.org/c-program-for-cutting-a-rod-dp-13/?ref=header_search


//==============testcase1==============
int arr[] = { 1, 5, 8, 9, 10, 17, 17, 20 };
int length = 8;
//output: 22
//=====================================

//==============testcase2==============
// int arr[] = { 3, 5, 8, 9, 10, 17, 17, 20 };
// int length = 8;
//output: 24
//=====================================

//==============testcase2==============
// int arr[] = { 5, 4, 11, 20, 17, 24, 20 };
// int length = 7;
//output: 35
//=====================================

//==============testcase4==============
// int arr[] = { 15, 5 };
// int length = 2;
//output: 30
//=====================================

//==============testcase4==============
// int arr[] = { 8, 13, 5, 9 };
// int length = 4;
//output: 32
//=====================================

//==============testcase6==============
// int arr[] = { 3, 6, 12, 5, 10 };
// int length = 5;
//output: 18
//=====================================
	
/* Returns the best obtainable price for a rod of length n and
price[] as prices of different pieces */
int cutRod(int n)
{
	if (n <= 0)
		return 0;

	int max_val = 0;

	// Recursively cut the rod in different pieces and compare different
	// configurations
    // int i = 0;
    // int temp = 0;
	for (int i = 0; i < n; i++) {
        int temp = cutRod(n - i - 1);
		max_val = max(max_val, arr[i] + temp);
    }

	return max_val;
}

/* Driver program to test above functions */
int main()
{
	int temp = cutRod(length);
    cout << "output: " << temp;
	return 0;
}
