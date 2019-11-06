#include "commoninclude.h"

uint64_t streak(uint64_t n)
{
    uint64_t k = 1;
    
    while (true)
    {
        if ((n + k) % (k + 1) != 0)
        {
            break;
        }
        k++;
    }

    return k;
}

uint64_t P(uint64_t s, uint64_t N)
{
    uint64_t cnt = 0;

    for (uint64_t i = 2; i < N; i++)
    {
        if (streak(i) == s)
        {
            cout << i << " = " << s << endl;
            cnt++;
        }
    }

    return cnt;
}

uint64_t PE601()
{
    uint64_t lcm = 1;
    uint64_t cnt = 0;

    for (uint64_t i = 1; i <= 31; i++)
    {
        uint64_t cntCur = 0;
        uint64_t c = gcd64(i, lcm);
        lcm = i * lcm / c;

        cout << lcm << endl;

        uint64_t N = (uint64_t)pow(4, i);

        for (uint64_t m = lcm; m <= N; m += lcm)
        {
            if (streak(m + 1) == i)
            {
                cntCur++;
            }
        }

        //cout << cntCur << endl;
        cnt += cntCur;
    }

    cout << "\n" << cnt << endl;

    __debugbreak();
    return 0;
}