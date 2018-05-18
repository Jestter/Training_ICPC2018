#include <bits/stdc++.h>

using namespace std;

int max1DSum(int* arr,int size)
{
	int max_ending_here,max_so_far;
	max_ending_here = max_so_far = arr[0];
	for (int i = 1; i < size; ++i)
	{
		max_ending_here = max(arr[i],max_ending_here + arr[i]);
		max_so_far = max(max_so_far, max_ending_here);
	}
	return max_so_far;
}

int main()
{
	int arr[9] = {5,3, -16,7,-8,9,10,-14,33};
	//print: max 1D sum = 38
	cout << "max 1D sum = " << max1DSum(arr,9) << endl;
	return 0;
}