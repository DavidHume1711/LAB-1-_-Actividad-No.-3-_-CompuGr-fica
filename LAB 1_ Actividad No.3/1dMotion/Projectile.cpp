#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>

using namespace std;

class Projectile {
public:
    float V = 0.0f;
    float Vx = 0.0f;
    float x = 0.0f;
    float x_initial = 0.0f;
    float total_time = 0.0f;
    float delta_t = 0.0f;
    bool timerun = true;

    void update(float t) {
        x = x_initial + V * t;
    }
};