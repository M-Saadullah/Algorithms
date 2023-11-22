#include<iostream>
using namespace std;

// postmanSort is a little bit different from radix sort it starts from most significant digit while 
// radix sort starts from least significant digit

// like in array   121,432,564,3,1,45,788 
// in postmanSort after first go/iteration the array become    3,1,45,121,432,564,788
// it is sorted from 121 to 788 in first go
// next iteration starts from 3 and end at 45 (it will not iterate 121,432 and so on);
// and so on.


int countingSort(int arr[], int size, int pos)
{
	int* count = new int[10];     // maximum no of element can be 10 --> 0 to 9;
	for (int i = 0; i < 10; i++)
		count[i] = 0;             // initialize each count[i] value to zero;

	for (int i = 0; i < size; i++)
	{
		count[(arr[i] / pos) % 10]++;		// increament the count of index ((arr[i]/pos) %10) --> if arr[i] = 198 and
	}										// pos = 100 so it increament count[1];

	for (int i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}


	int* temp = new int[size];    // temporary array to store sorted elements
	int remainingSize = -1;
	for (int i = size - 1; i >= 0; i--)                                // loop iterate reverse from size to 0;
	{
		temp[count[(arr[i] / pos) % 10] - 1] = arr[i];				   // basic logic of counting sort;
		if ((arr[i] / pos) % 10 == 0 && count[(arr[i] / pos) % 10] > remainingSize)
		{
			remainingSize = count[(arr[i] / pos) % 10];			//	first element having pos digit is zero
		}														//  as loop reverse iterate it means last element
		count[(arr[i] / pos) % 10]--;
	}

	for (int i = 0; i < size; i++)
	{
		arr[i] = temp[i];			  // move sorted element from temporary array to main array
	}

	return remainingSize;            // it will return the remaining unsorted array size from 0 to remainingSort
}


void postmanSort(int arr[], int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)    // get max element from array
	{
		if (arr[i] > max)
			max = arr[i];
	}
	int pos = 1;
	while (max / 10)
	{
		max = max / 10;
		pos = pos * 10;
	}

	for (int i = pos; i >= 1; i = i / 10)
	{
		size = countingSort(arr, size, i);  // countSort return size of subarray in original that is
	}	                                    // unsorted from 0 to newSize;
	
}


void printArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}




int main()
{
	int size = 7;
	int* arr = new int[size]{ 121,432,564,3,1,45,788 };
	postmanSort(arr, size);
	printArray(arr, size);
}