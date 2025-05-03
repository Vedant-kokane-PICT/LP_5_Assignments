#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>
using namespace std;



void helper(vector<int> &arr){
    int n = arr.size();
    int minElement = INT_MAX;
    int maxElement = INT_MIN;
    int sum = 0;
    double avg = 0.0;
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(min:minElement) reduction(max:maxElement) reduction(+:sum)
    for(int i=0;i<n;i++){
        if(arr[i] < minElement){
            minElement = arr[i];
        }
        if(arr[i] > maxElement){
            maxElement = arr[i];
        }
        
        sum += arr[i];
    }
    double endTime = omp_get_wtime();
    cout<<"Start - "<<startTime<<", End - "<<endTime<<endl;
    cout<<"Difference - "<<endTime - startTime<<endl;
    avg = (double) sum / (double) n;
    cout<<"Min - "<<minElement<<endl;
    cout<<"Max - "<<maxElement<<endl;
    cout<<"Sum - "<<sum<<endl;
    cout<<"Avg - "<<avg<<endl;
    
}

int main()
{
   
    vector<int> arr = {1,2,3,4,5};
    helper(arr);
    return 0;
}
