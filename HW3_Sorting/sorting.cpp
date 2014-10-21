/*

  sorting.cpp

  Please refer to sorting.h for documentation on each function.

  Your Name:
  Your TA:
  List O' Collaborators:


   + ------ N O T E: -- Big scary warning! ------------------------------
   |
   |    We clearly can't use unit testing to ensure that you're
   |    actually implementing the correct algorithm. I suppose we could
   |    write some complicated static analysis checker. But it is
   |    easier to just look at it with our eyeballs.
   |
   |    After the assignment is due, we will look at the most recent
   |    version of your implementation that got the highest score and
   |    make sure you're not doing something sneaky like using a
   |    standard library call to sort a vector.
   |
   |    Anyone caught doing this (even though it is kinda funny) will
   |    be given 0/15 on the assignment.
   |
   +-------------------------------------------------------------------- 

 */

#include "sorting.h"

using namespace std;

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void quicksort(vector<int> &data, int low_idx, int high_idx) {
	if ( low_idx < high_idx)    
	{
		int split = quicksort_partition(data, low_idx, high_idx, data[high_idx]);
		quicksort(data, low_idx, split-1);        
		quicksort(data, split+1, high_idx);
	} else {
		return;
	}
}

int quicksort_partition(vector<int> &data, int low_idx, int high_idx,
			int pivot_index) {                            
	int left = low_idx - 1;                                                  
	int right = high_idx;                                                          
	bool need = true;
	while (need){
		while (need)
		{
			left += 1;                 
			if (left == right){
				need = false;                      
				break;
			}
			if (data[left] > pivot_index){
				data[right] = data[left];      
				break;
			}
		}
		while (need)
		{
			right = right-1;                     
			if (right == left){
				need = false;                     
				break;
			}
			if (data[right] < pivot_index)
			{
				data[left] = data[right];
				break;
			}     
		}
	}
    data[right] = pivot_index;                         
    return right;
}

void bubblesort(vector<int> &data) {
	bool end = false;
	while(!end){
		end = true;
		for (int i = 0; i < data.size() - 1; i++){
			if (data[i] > data[i+1]){
				swap(data[i], data[i+1]);
				
				end = false;
			}
		}
	}
	return;
  // implement me
//give variable true or false to see if you have swapped or not, if so repeat
}






void mergesort(vector<int> &data) {
	if (data.size() <= 1){
		return;
	} else {
		vector<int> left;
		vector<int> right;
		int middle = (data.size()/2);
		for (int i = 0 ;i < middle ; i++){
			left.push_back(data[i]);
		}
		for (int i = middle ; i < data.size(); i++){
			right.push_back(data[i]);
		}  
		if(left.size() > 1){
			mergesort(left);
		}
		if(right.size() > 1){
			mergesort(right);
		}
		data = merge(left, right);
	}
	
	
/*
 * pick a dividing index - use middle index
 * left is data
 * right is data
 * mergesort(left) if left.size > 1
 * mergesort(right) if right.size > 1
 * merge(left, right)
 */
  // implement me

}



vector<int> merge(vector<int> &left, vector<int> &right) {
	vector<int> result;
	while(left.size() > 0 || right.size() > 0){
		if(left.size() > 0 && right.size() > 0){
			if(left[0] < right[0]){
				int popped = left[0];
				result.push_back(popped);
				left.erase(left.begin());	
			} else {
				int popped = right[0];
				result.push_back(popped);
				right.erase(right.begin());
			}
		} else if (0 < left.size()){
				int popped = left[0];
				result.push_back(popped);
				left.erase(left.begin());
			}
			else if(0 < right.size()){
				int popped = right[0];
				result.push_back(popped);
				right.erase(right.begin());
			}
		}
		
		return result;

}



void mystery_sort(vector<int> &data) {
	int i;
	int j;
	int tmp;
	int n = data.size();
	for (i=1; i<n; i++){
		j=i;
		tmp=data[i];
		while ( j > 0 && tmp < data[j-1])
		{
           data[j]=data[j-1];
           j--;
		}
     data[j]=tmp;
	}
}
	
  
  // implement me. choose a different sorting algorithm and go to
  // town.
//bubble sort but minus two if swapped
