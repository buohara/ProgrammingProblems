#include "quicksort.h"
#include "utils.h"
#include <time.h>

/**
 * QuickSort Simple quick sort of uint32_t list. Recursively sorts around a pivot
 * (first element in list), then sorts sublists greater than and less than pivot.
 * 
 * @param pList List to sort [in][out].
 * @param len   Length of list to sort.
 */

void QuickSort(uint32_t *pList, uint32_t len)
{
    // Lists of size 0 and 1 don't need to be sorted.

    if (len <= 1)
    {
        return;
    }

    uint32_t piv    = pList[0];
    uint32_t l      = 1;
    uint32_t r      = len - 1;
    bool foundSplit = false;

    while (1)
    {
        while (pList[l] <= piv)
        {
            l++;
            if (r < l)
            {
                goto pivotFound;
            }
        }

        while (pList[r] >= piv)
        {
            r--;
            if (r < l)
            {
                goto pivotFound;
            }
        }

        if (l == r)
        {
            goto pivotFound;
        }

        uint32_t tmp    = pList[l];
        pList[l]        = pList[r];
        pList[r]        = tmp;
    }

pivotFound:

    uint32_t tmp    = piv;
    pList[0]        = pList[r];
    pList[r]        = tmp;

    uint32_t *pLList = pList;
    uint32_t *pRList = &pList[r + 1];

    QuickSort(pLList, r);
    QuickSort(pRList, len - r - 1);
}

/**
 * TestQuickSort Quick sort test. For 1000 iterations, generate lists of random
 * length and values, then sort. Capture list size and sort time for each list.
 */

void TestQuickSort()
{
    const uint32_t maxSize  = 0x10000;
    const uint32_t numIters = 1000;

    struct TimingData
    {
        uint32_t size;
        double sortTimeMS;
    };

    vector<TimingData> testResults(numIters, {0, 0.0});

    srand(time(NULL));

    for (uint32_t n = 0; n < numIters; n++)
    {
        // Generate a random list.

        uint32_t size = rand() % maxSize;
        vector<uint32_t> list(size, 0);

        for (uint32_t i = 0; i < size; i++)
        {
            list[i] = rand() % maxSize;
        }

        // Sort the list and get time.

        long long t1 = GetMilliseconds();
        QuickSort(&list[0], size);
        long long t2 = GetMilliseconds();

        // Check list that list is really sorted and record results.

        for (uint32_t i = 1; i < size; i++)
        {
            if (list[i] < list[i - 1])
            {
                __debugbreak();
            }
        }

        testResults[n] = { size, (double)(t2 - t1) };
    }

    __debugbreak();
}