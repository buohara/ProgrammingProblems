#include "commoninclude.h"

/**
 * getIntegrationLimit - Get upper limit for PE587 integral, which is where
 * the bottom left curve of a circle intersects the line y = x/N.
 * 
 * The equation for the circle centered at (1, 1) is (x - 1)^2 + (y - 1)^2 = 1.
 * Substitute y = x/N for y, and solve for x in terms of N using the quadratic
 * formula.
 *
 * @param n The value N in y = x/N.
 *
 * @return Upper integration limit for PE587.
 */

double getIntegrationLimit(uint32_t n)
{
    uint32_t a = 1 + n * n;
    uint32_t b = 2 * (n + n * n);
    uint32_t c = n * n;

    double ad = (double)a;
    double bd = -(double)b;
    double cd = (double)c;

    return (-bd - sqrt(bd * bd - 4.0 * ad * cd)) / (2.0 * ad);
}

/**
 * PE587 - Find the value of N for which the area of a "concave triangle" is
 * <= 0.1% of an "L-triangle" (see problem description for diagrams of concave
 * and L-triangles).
 *
 * An L-triangle is cut into two concave triangles t1 and t2 by the line y = x/N. 
 * The solution here works by finding the area of t1, which is the integral between two
 * curves: the top carve is cut out by a circle of radius 1 centered at (1, 1), the bottom 
 * curve is the line y = x/N. To get area(t2), do area(L) - area(t1). Area(L) = (4 - pi) / 4. 
 * The limits of the integral are zero to where the circle and y = x/N intersect. The helper 
 * function getIntegrationLimit computes this limit. Keep computing area(t2) / area(L) for
 * increasing N until the ratio is <= 0.001 (0.1%).
 */

uint32_t PE587()
{
    const double pi = 3.14159265359;
    const double lArea = (4.0 - pi) / 4.0;
    uint32_t i = 1;

    while (true)
    {
        double n = (double)i;
        double k = getIntegrationLimit(i);
        double a = k;
        double b = (k * k) / (2.0 * n);
        
        double u = asin(k - 1);
        double l = -pi / 2.0;
        double c1 = 0.5 * (u + sin(u) * cos(u));
        double c2 = 0.5 * (l + sin(l) * cos(l));
        double c = c1 - c2;

        double triArea = lArea - (a - b - c);
        double ratio = triArea / lArea;
        
        if (ratio < 0.001)
        {
            break;
        }

        i++;
    }

    return i;
}