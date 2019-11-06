#include "commoninclude.h"

struct vec3
{
    double x;
    double y;
    double z;

    vec3() : x(0.0), y(0.0), z(0.0) {};
    vec3(double x, double y, double z) : x(x), y(y), z(z) {};
    vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {};
    vec3(double s) : x(s), y(s), z(s) {};
    vec3(const vec3&& v) : x(v.x), y(v.y), z(v.z) {};

    vec3& operator*=(const double& s)    { x *= s; y *= s; z *= s; return *this; }
    vec3& operator+=(const vec3& v)      { x += v.x; y += v.y; z += v.z; return *this; }
    vec3& operator-=(const vec3& v)      { x -= v.x; y -= v.y; z -= v.z; return *this; }
    vec3& operator=(const vec3& other)   { if (this == &other) return *this; x = other.x; y = other.y; z = other.z; return *this; }
    vec3& operator=(const vec3&& other)  { if (this == &other) return *this; x = other.x; y = other.y; z = other.z; return *this;}

    vec3 operator+(const vec3 &v) { return (*this) += v; }
    vec3 operator-(const vec3& v) { return (*this) -= v; }
    vec3 operator*(const double& s) { return (*this) *= s; }
};

struct particle
{
    vec3 pos;
    double m;
};

void NBodyDirect(vector<particle> &particles, vector<vec3> &forces)
{
    for (uint32_t i = 0; i < particles.size(); i++)
    {
        forces[i] = { 0.0 };
        auto& p1 = particles[i];

        for (uint32_t j = 0; j < particles.size(); j++)
        {
            if (i == j) break;
            auto& p2 = particles[j];

            double rsq = (p2.pos.x - p1.pos.x) * (p2.pos.x - p1.pos.x) +
                (p2.pos.y - p1.pos.y) * (p2.pos.y - p1.pos.y) +
                (p2.pos.z - p1.pos.z) * (p2.pos.z - p1.pos.z);

            forces[i] += (p2.pos - p1.pos) * ((p1.m * p2.m) / rsq);
        }
    }
}

void NBodyMultiple()
{

}

void TestMultipole()
{
    const double xmax           = 1000.0;
    const double ymax           = 1000.0;
    const double zmax           = 1000.0;
    const double mmax           = 5.0;

    const uint32_t nParticles   = 100000;

    vector<particle> particles(nParticles);
    vector<vec3> forces(nParticles);

    for (uint32_t i = 0; i < nParticles; i++)
    {
        particle p;

        p.pos.x = fmod((double)rand(), xmax);
        p.pos.y = fmod((double)rand(), ymax);
        p.pos.z = fmod((double)rand(), zmax);
        p.m     = fmod((double)rand(), mmax);

        particles[i] = p;
    }

    long long t1 = GetMilliseconds();
    NBodyDirect(particles, forces);
    long long t2 = GetMilliseconds();

    double elapsedTime = (double)(t2 - t1);

    printf("NBody Direct Elapsed Time: %gms\n", elapsedTime);

    __debugbreak();
}