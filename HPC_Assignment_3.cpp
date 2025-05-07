#include <bits/stdc++.h>
#include <omp.h>

using namespace std;


void minOperation(vector<int> arr){
    int minValue = arr[0];
    double start = omp_get_wtime();
    #pragma omp parallel reduction(min:minValue)
    for(int i=0;i<arr.size();i++){
        minValue = min(minValue,arr[i]);
    }
    double end = omp_get_wtime();
    cout<<"Min - "<<minValue<<", time taken - "<<end-start<<endl;
    
}


void maxOperation(vector<int> arr){
    int maxValue = arr[0];
    double start = omp_get_wtime();
    #pragma omp parallel reduction(max:maxValue)
    for(int i=0;i<arr.size();i++){
        maxValue = max(maxValue,arr[i]);
    }
    double end = omp_get_wtime();
    cout<<"Max - "<<maxValue<<", time taken - "<<end-start<<endl;
    
}

void sumOperation(vector<int> arr){
    int sum = 0;
    double start = omp_get_wtime();
    #pragma omp parallel reduction(+:sum)
    for(int i=0;i<arr.size();i++){
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout<<"Sum - "<<sum<<", time taken - "<<end-start<<endl;
}


void averageOperation(vector<int> arr){
    int sum = 0;
    double start = omp_get_wtime();
    #pragma omp parallel reduction(+:sum)
    for(int i=0;i<arr.size();i++){
        sum += arr[i];
    }
    double end = omp_get_wtime();
    double avg = (double) (sum) / (double)(arr.size());
    cout<<"Average - "<<avg<<", time taken - "<<end-start<<endl;
}

int main()
{
    vector<int> arr = {5, 33, 4, 1, 2, 3, 9};
    minOperation(arr);
    maxOperation(arr);
    sumOperation(arr);
    averageOperation(arr);
    return 0;
}
