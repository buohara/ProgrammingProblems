#include "problems.h"

double f(double x)
{
    if (x >= 0.0 && x <= 1.0)
    {
        return (x - 0.5) * (x - 0.5);
    }
    else
    {
        return 0.0;
    }
}

double mutate(double x)
{
    double randVal = (double)rand() / (double)RAND_MAX;
    return x + 0.1 * (randVal - 0.5);
}

double accept(double x0, double x1)
{
    return min<double>(1.0, f(x1) / f(x0));
}

void TestMetropolis()
{
    const uint32_t numVals = 10000;
    vector<double> randomValues(numVals);
    double r1 = (double)rand() / (double)RAND_MAX;;
    randomValues[0] = r1;

    uint32_t numPoints = 1;

    while(true)
    {
        if (numPoints % 10 == 0)
        {
            r1 = (double)rand() / (double)RAND_MAX;
            randomValues[numPoints++] = r1;
            continue;
        }

        double r2 = mutate(r1);
        double a = accept(r1, r2);

        if (a > 0.9)
        {
            randomValues[numPoints++] = r2;
            r1 = r2;
        }

        if (numPoints >= numVals)
        {
            break;
        }
    }

    const uint32_t numBuckets = 10;
    double bucketWidth = 1.0 / (double)numBuckets;
    vector<double> bucketSizes(numBuckets);

    for (uint32_t i = 0; i < numBuckets; i++)
    {
        uint32_t bucketCnt = 0;
        double k1 = (i * bucketWidth);
        double k2 = ((i + 1) * bucketWidth);

        for (uint32_t j = 0; j < randomValues.size(); j++)
        {
            double curVal = randomValues[j];

            if (curVal > k1 && curVal <= k2)
            {
                bucketCnt++;
            }
        }

        bucketSizes[i] = (double)bucketCnt / (double)numVals;
    }

    __debugbreak();
}