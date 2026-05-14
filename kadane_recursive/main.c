#include <stdio.h>

int maxSum;

int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}

int maxEnd(int nums[], int i)
{
    int curr;

    if (i == 0)
        return nums[0];

    curr = max(nums[i],
                 nums[i] + maxEnd(nums, i - 1));

    maxSum = max(maxSum, curr);

    return curr;
}

int maxSubArr(int nums[], int n)
{
    maxSum = nums[0];

    maxEnd(nums, n - 1);

    return maxSum;
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

    printf("nums = [");

    for (i = 0; i < n; i++)
    {
        printf("%d", nums[i]);

        if (i < n - 1)
            printf(" ");
    }

    printf("]\n");

    result = maxSubArr(nums, n);

    printf("Output: %d\n", result);

    return 0;
}
