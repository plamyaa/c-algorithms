#include "../utils.h"

int
binary_search(int *arr, int l, int r, int value)
{
    if (r < l) {
        return -1;
    }

    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == value) {
            return mid;
        }
        if (arr[mid] < r) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    return -1;
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int val = binary_search(arr, 0, 9, 8);
    printf("%d\n", val);
    
    return 0;
}