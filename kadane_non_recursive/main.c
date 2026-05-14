#include <stdio.h>

int kadane_max_sum(int arr[], int n)
{
    int i;

    int curr_sum;
    int max_sum;

    curr_sum = arr[0];
    max_sum = arr[0];

    for (i = 1; i < n; i++)
    {

        if (arr[i] > curr_sum + arr[i])
            curr_sum = arr[i];
        else
            curr_sum = curr_sum + arr[i];


        if (curr_sum > max_sum)
            max_sum = curr_sum;
    }

    return max_sum;
}

int main(void)
{
    int n;
    int i;
    int result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int nums[n];


    for (i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }


    printf("Input: nums = [");

    for (i = 0; i < n; i++)
    {
        printf("%d", nums[i]);

        if (i < n - 1)
        {
            printf(" ");
        }
    }

    printf("]\n");

    result = kadane_max_sum(nums, n);

    printf("Output: %d\n", result);

    return 0;
}
