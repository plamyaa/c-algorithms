#include "../../utils.h"

int 
find_max_crossing_subarray(int *arr, int low, int mid, int high)
{
    int left_sum = -1000000;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
        }
    }

    int right_sum = -1000000;
    sum = 0;
    for (int j = mid + 1; j <= high; j++) {
        sum += arr[j];
        if (sum > right_sum) {
            right_sum = sum;
        }
    }
    return (left_sum + right_sum);
}

int
find_max_subarray(int *arr, int low, int high)
{
    if (high == low) {
        return arr[low]; // single element
    }
    else {
        int mid = (low + high) / 2;
        int left_sum = find_max_subarray(arr, low, mid);
        int right_sum = find_max_subarray(arr, mid + 1, high);
        int cross_sum = find_max_crossing_subarray(arr, low, mid, high);

        if (left_sum >= right_sum && left_sum >= cross_sum) {
            return left_sum;
        } else if (right_sum >= left_sum && right_sum >= cross_sum) {
            return right_sum;
        } else {
            return cross_sum;
        }
    }
}

int main()
{
    int a[] = {3, -1, -1, 10, -3, -2, 4};
    
    printf("%d\n", find_max_subarray(a, 0, 6));

    return 0;
}