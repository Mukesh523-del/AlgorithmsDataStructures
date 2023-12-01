#include<iostream>
#include<algorithm>
using namespace std;

int main() {
   /* getting input array size and elements */
   int numOfEle;
   cout << "enter the total number of elements:- ";
   cin >> numOfEle;
   int arrEle[numOfEle+1], result[numOfEle+1];
   cout << "Enter unsorted array elements individually:-" << endl;
   for(int i = 1; i<=numOfEle; i++) {
      cin >> arrEle[i];
   }
   int maxArrValue = arrEle[1];
   for(int k = 2; k<=numOfEle; k++) {
      if(arrEle[k] > maxArrValue)
         maxArrValue = arrEle[k];
   }
   int arrCount[maxArrValue+1];
   /* init arrCount to 0's */
   for(int i = 0; i<=maxArrValue; i++)
      arrCount[i] = 0;  
   /* incrementing arrCount */
   for(int i = 1; i <=numOfEle; i++)
      arrCount[arrEle[i]]++;
   /* finding cumulative frequency of each element */
   for(int i = 1; i<=maxArrValue; i++)
      arrCount[i] += arrCount[i-1];    
   /* decrementing arrCount for same elements */
   for(int i = numOfEle; i>=1; i--) {
      result[arrCount[arrEle[i]]] = arrEle[i];
      arrCount[arrEle[i]] -= 1; 
   }
   for(int i = 1; i<=numOfEle; i++) {
      arrEle[i] = result[i];
   }
   /* printing the sorted array */
   cout << " After Sorting the array is:- ";
   for(int j = 1; j<=numOfEle; j++)
      cout << arrEle[j] << " ";  
}
