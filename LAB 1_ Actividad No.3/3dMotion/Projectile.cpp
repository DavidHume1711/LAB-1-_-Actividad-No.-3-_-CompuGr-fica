#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>

using namespace std;

class Projectile {
public:
    float Vx = 0.0f, Vy = 0.0f, Vz = 0.0f;
    float x = 0.0f, y = 0.0f, z = 0.0f;
    float x_initial = 0.0f, y_initial = 0.0f, z_initial = 0.0f;
    float g = 0.8f;
    float delta_t = 0.0f;
    bool timerun = true;

    void update(float t) {
        x = x_initial + Vx * t;
        y = y_initial + Vy * t - (g / 2.0f) * t * t;
        z = z_initial + Vz * t;
    }
};