#include "commoninclude.h"

struct vec2
{
    int32_t x;
    int32_t y;
};

/**
 * dot - A simple dot product for two-component vectors.
 *
 * @param l1 - First input vector.
 * @param l2 - Second input vector.
 *
 * @return Dot product of l1 and l2.
 */

int32_t dot(vec2 &l1, vec2 &l2)
{
    return l1.x * l2.x + l1.y * l2.y;
}

/**
 * PE91 - Count the number of right triangles with one vertex at
 * the origin and the other vertices at integer lattice points in a
 * 50 x 50 grid.
 *
 * This solution uses a brute force approach by looking at every pair
 * of integer lattice points in the 50 x 50 grid. Using these two points
 * and the origin, compute the three sides of the resulting triangle and dot
 * each pair of sides together. If two sides are perpendicular (dot product zero),
 * it's a right triangle.
 */

void PE91()
{
    const uint32_t dim = 50;
    const uint32_t nPoints = (dim + 1) * (dim + 1);
    uint32_t numTris = 0;

    for (int32_t i = 1; i < nPoints; i++)
    {
        for (int32_t j = i + 1; j < nPoints; j++)
        {
            vec2 l1;
            vec2 l2;
            vec2 l3;

            l1.y = i / (dim + 1);
            l1.x = i % (dim + 1);

            l2.y = j / (dim + 1);
            l2.x = j % (dim + 1);

            l3.x = l2.x - l1.x;
            l3.y = l2.y - l1.y;

            if ((dot(l1, l2) == 0) ||
                (dot(l2, l3) == 0) ||
                (dot(l3, l1) == 0))
            {
                numTris++;
            }
        }
    }

    printf("%d\n", numTris);
}