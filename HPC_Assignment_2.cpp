#include <iostream>
#include<omp.h>
#include<vector>

using namespace std;

// sequential 
void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i] > arr[j]){
                swap(arr[i], arr[j]);
            }
        }
    }
}


// parallel
void bubbleSortParallel(vector<int> &arr){
    int n = arr.size();
    for(int i=0;i<n;i++){
        #pragma omp parallel for 
        for(int j=i+1;j<n;j++){
            if(arr[i] > arr[j]){
                #pragma omp  critical
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }
}


void merge(int start,int mid,int end,vector<int> &arr){
    vector<int> left, right;
    for(int i=start;i<=mid;i++){
        left.push_back(arr[i]);
    }
    for(int i=mid+1;i<=end;i++){
        right.push_back(arr[i]);
    }
    
    int i=0, j=0, k=start;
    while(i < left.size() && j < right.size()){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while(i < left.size()){
        arr[k] = left[i];
        i++;
        k++;
    }
    
    while(j < right.size()){
        arr[k] = right[j];
        j++;
        k++;
    }
    
}




// sequential
void mergeSort(int start,int end,vector<int> &arr){
    if(start < end){
        int mid = (start + end) / 2;
        mergeSort(start,mid,arr);
        mergeSort(mid+1,end,arr);
        merge(start,mid,end,arr);
    }
}

// Parallel
void mergeSortParallel(int start,int end,vector<int> &arr){
    if(start < end){
        int mid = (start + end) / 2;
        #pragma omp parallel sections
        {   
            #pragma omp section
            mergeSort(start,mid,arr);
            
            #pragma omp section
            mergeSort(mid+1,end,arr);
        }
        
        merge(start,mid,end,arr);
        
    }
}

int main()
{
    vector<int> arr = {5, 33, 4, 1, 2, 3, 9};
    for(auto x:arr){
        cout<<x<<" ";
    }
    cout<<endl;
    //bubbleSortParallel(arr);
    int startTime = omp_get_wtime();
    mergeSortParallel(0,arr.size()-1,arr);
    int endTime = omp_get_wtime();
    for(auto x:arr){
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<startTime <<" "<<endTime;
    cout<<endTime - startTime<<endl;
    return 0;
}
