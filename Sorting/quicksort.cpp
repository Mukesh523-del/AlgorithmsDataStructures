#include <iostream>
using namespace std;

int partitionArray(int st, int ed, int* arrEle)
{
    /* assigning last item as pivot value */
	int pivotIndex, pivotEle = arrEle[st];
	int countValue = 0;
	for (int j = st + 1; j <= ed; j++) {
		if (arrEle[j] <= pivotEle)
		{
			countValue++;
		}
	}
	/* Assigning pivot to the right index */
	pivotIndex = st + countValue;
	swap(arrEle[pivotIndex], arrEle[st]);
        /* get index */
	int x = st, y = ed;
	while(y > pivotIndex && x < pivotIndex) {
	    while (arrEle[y] > pivotEle)
			y=y-1;
		while (arrEle[x] <= pivotEle)
			x=x+1;
		if (x < pivotIndex && y > pivotIndex)
			swap(arrEle[x++], arrEle[y--]);	
	}

	return pivotIndex;
}

int quickSortArray(int st, int ed, int *arrEle)
{
    if (st >= ed)
    {
		return 0;
    } else {
		int index = partitionArray(st, ed, arrEle);
		/* sorting left side elements from pivotEle */
		quickSortArray(st, index - 1, arrEle);
		/* sorting right side elements from pivotEle */
		quickSortArray(index + 1, ed, arrEle);
	}
	return 0;
}

int main()
{
   /* getting input array size and elements */
   int numOfEle;
   cout << "enter the No of items:- ";
   cin >> numOfEle;
   int arrEle[numOfEle];
   cout << "Enter array items:-" << endl;
   for(int i = 0; i<numOfEle; i++){
      cin >> arrEle[i];
   }
	quickSortArray(0, numOfEle - 1, arrEle);
	/* printing the sorted array */
	cout << "After Sorting : ";
	for (int i = 0; i < numOfEle; i++){
	   cout << arrEle[i] << " ";
	}
	return 0;
}

