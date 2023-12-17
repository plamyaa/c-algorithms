#include "../utils.h"

// void
// bubble_sort(int *arr, int len)
// {
//     for (int i = 0; i < len - 1; i++) {
//         for (int j = 0; j < len - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 swap(&arr[j], &arr[j + 1]);
//             }
//         }
//     }
// }

void
bubble_sort(int *arr, int len)
{
    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j > i; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(&arr[j], &arr[j - 1]);
            }
        }
    }
}

int main()
{
    int arr[6] = {5, 2, 4, 6, 1, 3};

    print_array(arr, 6);
    bubble_sort(arr, 6);
    print_array(arr, 6);

    return 0;
}