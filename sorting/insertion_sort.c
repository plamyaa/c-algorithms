#include "../utils.h"

void
insertion_sort(int *arr, int len)
{
    int key, i;

    for (int j = 1; j < len; j++) {
        key = arr[j];
        i = j - 1;

        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

int main()
{
    int arr[6] = {5, 2, 4, 6, 1, 3};

    print_array(&arr, 6);
    insertion_sort(&arr, 6);
    print_array(&arr, 6);

    return 0;
}