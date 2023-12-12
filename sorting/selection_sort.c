#include "../utils.h"

void
selection_sort(int *arr, int len)
{
    int i, j, min_index;

    for (i = 0; i < len - 1; i++) {
        min_index = i;
        for (j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
    }
}

int main()
{
    int arr[6] = {5, 2, 4, 6, 1, 3};

    print_array(&arr, 6);
    selection_sort(&arr, 6);
    print_array(&arr, 6);

    return 0;
}