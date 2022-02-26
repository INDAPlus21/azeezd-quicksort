#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBERS "-0123456789"

static long amount = 0;
static long array[2 << 18];
static long *arr_ptr = array;
static int curr_char;
static long temp;
static long curr_val;
static int negative = 0;
static unsigned char chars[256] = {0};

long partition(long *array, long low, long high)
{
    long pivot = array[high];
    long low_index = low - 1;

    for (long j = low; j <= high - 1; j++)
    {
        if (array[j] < pivot)
        {
            low_index++;
            temp = array[low_index];
            array[low_index] = array[j];
            array[j] = temp;
        }
    }

    temp = array[low_index + 1];
    array[low_index + 1] = array[high];
    array[high] = temp;

    return low_index + 1;
}

long par_rand(long *array, long low, long high)
{
    long r = rand() % (high - low) + low;

    temp = array[r];
    array[r] = array[high];
    array[high] = temp;

    partition(array, low, high);
}

void quicksort(long *array, long low, long high)
{
    if (low < high)
    {
            long index = par_rand(array, low, high); // partition

            quicksort(array, low, index-1);
            quicksort(array, index + 1, high);
    }
}

int main()
{

    srand(time(0));
    for (unsigned char* ch = (unsigned char*) NUMBERS; *ch; ch++)
        chars[*ch] = *ch;   
    
    for (curr_char = getchar(); chars[curr_char]; curr_char = getchar())
        amount = amount * 10 + (curr_char - '0');

    do
    {
        curr_val = 0;
        curr_char = getchar();
              
        negative = curr_char == '-';

        if (!negative) curr_val = curr_val * 10 + (curr_char - '0');

        for (curr_char = getchar(); chars[curr_char] && curr_char != EOF; curr_char = getchar())
            curr_val = curr_val * 10 + (curr_char - '0');

        *arr_ptr++ = negative ? -curr_val : curr_val;
    } while (curr_char != EOF);
    
    quicksort(array, 0, amount - 1);

    for (long i = 0; i < amount; i++)
        printf("%ld ", array[i]);

    return 0;
}

