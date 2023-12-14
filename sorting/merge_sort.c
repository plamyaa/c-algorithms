#include "../utils.h"

void
merge(int *arr, int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    int larr[n1 + 1], rarr[n2 + 1];

    for (i = 0; i < n1; i++) {
        larr[i] = arr[p + i];
    }
    for (j = 0; j < n2; j++) {
        rarr[j] = arr[q + j + 1];
    }
    larr[n1] = INT_MAX;
    rarr[n2] = INT_MAX;

    i = 0;
    j = 0;
    for (k = p; k <= r; k++) {
        if (larr[i] <= rarr[j]) {
            arr[k] = larr[i];
            i++;
        } else {
            arr[k] = rarr[j];
            j++;
        }
    }
}

void
merge_sort(int *arr, int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

int main()
{
    int arr[6] = {5, 2, 4, 6, 1, 3};

    print_array(arr, 6);
    merge_sort(arr, 0, 5);
    print_array(arr, 6);

    return 0;
}