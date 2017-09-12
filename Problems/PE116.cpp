#include "problems.h"

/**
 * countConfigs Count possible configurations of tiles of width tileWidth in
 * a row of length rowSize by sliding the tile from left to right, summing
 * configurations at each position.
 *
 * @param  rowSize      Size of the row.
 * @param  tileWidth    Size of the tile.
 * @param  configCounts Congigurations of tiles for row widths < rowSize.
 * @return              Number of configurations.
 */

uint64_t countConfigs(
    uint64_t rowSize,
    uint64_t tileWidth,
    vector<uint64_t> &configCounts)
{
    uint64_t nPositions = rowSize - tileWidth + 1;
    uint64_t configCnt = 0;

    for (uint64_t pos = 0; pos < nPositions; pos++)
    {
        uint64_t rBoxSize = rowSize - tileWidth - pos;
        configCnt += (1 + configCounts[rBoxSize]);
    }

    return configCnt;
}

/**
 * PE116 description - Count possible configurations of red, blue, and green tiles
 * in a row of 50 tiles.
 *
 * DP solution. Initialize red, blue, and green tile counts up to a row of width 4.
 * Then, for a row of width M and tile of width N, slide the tile from the leftmost position
 * to the rightmost position. At each of these positions, there's 1 + number of possible
 * configurations in the space remaining to the right of the tile. This is what countConfigs
 * above does.
 *
 * @return Zero. Print result.
 */

uint64_t PE116()
{
    vector<uint64_t> rCfgs(51, 0);
    vector<uint64_t> gCfgs(51, 0);
    vector<uint64_t> bCfgs(51, 0);

    rCfgs[0] = 0;
    rCfgs[1] = 0;
    rCfgs[2] = 1;
    rCfgs[3] = 2;
    rCfgs[4] = 4;

    gCfgs[0] = 0;
    gCfgs[1] = 0;
    gCfgs[2] = 0;
    gCfgs[3] = 1;
    gCfgs[4] = 2;

    bCfgs[0] = 0;
    bCfgs[1] = 0;
    bCfgs[2] = 0;
    bCfgs[3] = 0;
    bCfgs[4] = 1;

    for (uint64_t n = 5; n <= 50; n++)
    {
        rCfgs[n] = countConfigs(n, 2, rCfgs);
        gCfgs[n] = countConfigs(n, 3, gCfgs);
        bCfgs[n] = countConfigs(n, 4, bCfgs);
    }

    cout << rCfgs[50] + gCfgs[50] + bCfgs[50] << endl;

    __debugbreak();
    return 0;
}