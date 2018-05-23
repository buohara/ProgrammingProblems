#include "problems.h"

/**
 * Time Compute time required to cross marsh as function of angles used
 * to enter each section.
 * 
 * @param  thetas Angles used to enter each section.
 * @return        Time needed to cross marsh.
 */

double Time(vector<double> &thetas)
{
    const double k = 2.5 * (sqrt(2.0) - 1.0);

    double t1 = (k / cos(thetas[0]));
    double t2 = (10.0 / 9.0) / cos(thetas[1]);
    double t3 = (10.0 / 8.0) / cos(thetas[2]);
    double t4 = (10.0 / 7.0) / cos(thetas[3]);
    double t5 = (10.0 / 6.0) / cos(thetas[4]);
    double t6 = (10.0 / 5.0) / cos(thetas[5]);

    double h = t1 * sin(thetas[0]) * 10.0 +
        t2 * sin(thetas[1]) * 9.0 +
        t3 * sin(thetas[2]) * 8.0 +
        t4 * sin(thetas[3]) * 7.0 +
        t5 * sin(thetas[4]) * 6.0 +
        t6 * sin(thetas[5]) * 5.0;

    double a = (100.0 / sqrt(2.0)) - h;
    double b = 25.0 * (sqrt(2.0) - 1.0);
    double t7 = sqrt(a * a + b * b) / 10.0;

    return t1 + t2 + t3 + t4 + t5 + t6 + t7;
}

/**
 * Gradient Compute finite difference graident (f(x + h) - f(x - h)) / 2h
 * @param thetas Position to evaluate gradient.
 * @param grad   Output vector to place gradient values.
 */

void Gradient(vector<double> &thetas, vector<double> &grad)
{
    const double h = 0.001;

    for (uint32_t i = 0; i < thetas.size(); i++)
    {
        thetas[i] += h;
        double t2 = Time(thetas);
        thetas[i] -= 2.0 * h;
        double t1 = Time(thetas);
        thetas[i] += h;

        grad[i] = (t2 - t1) / (2.0 * h);
    }
}

/**
 * GradStep Update current position with gradient descent step.
 * @param thetas Old position.
 * @param grad   Gradient at current position.
 * @param step   Gradient step size.
 */

void GradStep(vector<double> &thetas, vector<double> &grad, double step)
{
    for (uint32_t i = 0; i < thetas.size(); i++)
    {
        thetas[i] -= grad[i] * step;
    }
}

/**
 * GradLength Gradient length.
 * @param  grad Current gradient vector.
 * @return      Gradient length.
 */

double GradLength(vector<double> &grad)
{
    return sqrt(grad[0] * grad[0] +
        grad[1] * grad[1] +
        grad[2] * grad[2] +
        grad[3] * grad[3] +
        grad[4] * grad[4] +
        grad[5] * grad[5]
    );
}

/**
 * PE607 Given points A and B in a marsh 100 leagues apart and strips of marsh with
 * varying travel speeds, find the minimum time required to cross marsh.
 *
 * This approach uses gradient descent optimization. The function to optimize is
 * travel time required as a function of travel angles into each section of marsh.
 * 
 * @return Zero. Print problem result.
 */

uint64_t PE607()
{
    vector<double> thetas(6, 0.78539816);
    vector<double> grad(6, 0.0);
    const double step = 0.1;
    const double tol = 0.00001;

    double t0 = Time(thetas);
    Gradient(thetas, grad);
    GradStep(thetas, grad, step);
    double t1 = Time(thetas);

    const uint32_t maxSteps = 1000;
    uint32_t steps = 1;

    while (GradLength(grad) > tol)
    {
        t0 = t1;
        Gradient(thetas, grad);
        GradStep(thetas, grad, step);
        t1 = Time(thetas);

        steps++;

        if (steps > maxSteps)
        {
            cout << "Failed to converge after " << maxSteps << " steps." << endl;
            __debugbreak();
        }
    }

    cout << "Min time: " << t1 << endl;
    __debugbreak();
    return 0;
}