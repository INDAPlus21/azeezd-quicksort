#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS "-0123456789"
#define SWAP(a, b) \
    temp = a;      \
    a = b;         \
    b = temp;

static long amount = 0;
static long array[2 << 18];
static long *arr_ptr = array;
static int curr_char;
static long temp;
static long curr_val;
static int negative = 0;
static unsigned char chars[256] = {0};

void partition(long *array, long low, long high, long *i, long *j)
{
    *i = low;
    *j = high;
    long mid = low;
    long pivot = array[low];

    while (mid <= *j)
    {
        // three way partition
        if (array[mid] < pivot)
        {
            SWAP(array[*i], array[mid])
            (*i)++;
            mid++;
        }
        else if (array[mid] > pivot)
        {
            SWAP(array[*j], array[mid])
            (*j)--;
        }
        else
            mid++;
    }
}

void insertionSort(long *array, long low, long high)
{
    long j;
    for (size_t i = low + 1; i < high + 1; i++)
    {
        j = i;
        while (j > 0 && array[j - 1] > array[j])
        {
            SWAP(array[j], array[j - 1])
            j--;
        }
    }
}

void quicksort(long *array, long low, long high)
{
    if (low >= high)
        return;

    if (high - low <= 10)
    {
        insertionSort(array, low, high);
        return;
    }
    long i, j;
    partition(array, low, high, &i, &j); // partition

    quicksort(array, low, i - 1);
    quicksort(array, j + 1, high);
}

int main()
{
    srand(time(0));
    for (unsigned char *ch = (unsigned char *)NUMBERS; *ch; ch++)
        chars[*ch] = *ch;

    for (curr_char = getchar(); chars[curr_char]; curr_char = getchar())
        amount = amount * 10 + (curr_char - '0');

    do
    {
        curr_val = 0;
        curr_char = getchar();

        negative = curr_char == '-';

        if (!negative)
            curr_val = curr_val * 10 + (curr_char - '0');

        for (curr_char = getchar(); chars[curr_char] && curr_char != EOF; curr_char = getchar())
            curr_val = curr_val * 10 + (curr_char - '0');

        *arr_ptr++ = negative ? -curr_val : curr_val;
    } while (curr_char != EOF);

    size_t j;
    for (size_t i = amount - 1; i > 0; i--)
    {
        j = rand() % (amount - i) + i;
        SWAP(array[i], array[j])
    }

    quicksort(array, 0, amount - 1);

    for (long i = 0; i < amount; i++)
        printf("%ld ", array[i]);

    return 0;
}
