#include "../../utils.h"

int
find_max_subarray(int arr[], int len)
{
    int max_sum = INT_MIN;
    for (int i = 1; i < len; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] - arr[j] > max_sum) {
                max_sum = arr[i] - arr[j];
            }
        }
    }
    return max_sum;
}

int main()
{
    int arr[] = { 3, -1, -1, 10, -3, -2, 4 };
    
    printf("%d\n", find_max_subarray(arr, 6));

    return 0;
}