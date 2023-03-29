
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <GL/glut.h>
using namespace std;

class Vector1D {
private:
    float x;

public:
    Vector1D() {
        x = 0.0f;
    }

    Vector1D(float x_val) {
        x = x_val;
    }

    float getX() const {
        return x;
    }

    void setX(float x_val) {
        x = x_val;
    }

    Vector1D operator+(const Vector1D& v) const {
        return Vector1D(x + v.x);
    }

    Vector1D operator-(const Vector1D& v) const {
        return Vector1D(x - v.x);
    }

    Vector1D operator*(const Vector1D& v) const {
        return Vector1D(x * v.x);
    }

    Vector1D operator/(float scalar) const {
        return Vector1D(x / scalar);
    }

    Vector1D operator*(float scalar) const {
        return Vector1D(x * scalar);
    }

    Vector1D crossProduct(const Vector1D& v) const {
        return Vector1D(0.0f); // 1D vector does not have cross product
    }

    float dotProduct(const Vector1D& v) const {
        return x * v.x;
    }

    float magnitude() const {
        return abs(x);
    }

    Vector1D normalize() const {
        float mag = magnitude();
        return Vector1D(x / mag);
    }

    float angleWith(const Vector1D& v) const {
        float dot = dotProduct(v);
        float mag1 = magnitude();
        float mag2 = v.magnitude();
        float angle_radians = acos(dot / (mag1 * mag2));
        return angle_radians * 180.0f / M_PI; // convert radians to degrees
    }
};

void drawGraph(const Vector1D& v1, const Vector1D& v2) {
    // Configurar la ventana y la vista
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30, 30, -30, 30, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Dibujar los ejes coordenados
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-30.0f, 0.0f);
    glVertex2f(30.0f, 0.0f);
    // Eje Y
    glVertex2f(0.0f, -30.0f);
    glVertex2f(0.0f, 30.0f);
    glEnd();

    // Dibujar los vectores
    glLineWidth(3.0f);
    // Dibujar el vector más largo primero
    if (v1.magnitude() >= v2.magnitude()) {
        glBegin(GL_LINES);
        // Vector v1
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(v1.getX(), 0.0f);

        float arrow_length = 0.5f;
        float angle = atan2(0.0f, v1.getX());
        glVertex2f(v1.getX(), 0.0f);
        glVertex2f(v1.getX() - arrow_length * cos(angle - M_PI/6), arrow_length * sin(angle - M_PI/6));
        glVertex2f(v1.getX(), 0.0f);
        glVertex2f(v1.getX() - arrow_length * cos(angle + M_PI/6), arrow_length * sin(angle + M_PI/6));
        glEnd();

        // Dibujar el vector más corto en la parte superior
        glBegin(GL_LINES);
        // Vector v2
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(v2.getX(), 0.0f);
        angle = atan2(0.0f, v2.getX());
        glVertex2f(v2.getX(), 0.0f);
        glVertex2f(v2.getX() - arrow_length * cos(angle - M_PI/6), arrow_length * sin(angle - M_PI/6));
        glVertex2f(v2.getX(), 0.0f);
        glVertex2f(v2.getX() - arrow_length * cos(angle + M_PI/6), arrow_length * sin(angle + M_PI/6));
        glEnd();
    } else {
        glBegin(GL_LINES);
        // Vector v2
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(v2.getX(), 0.0f);
        float arrow_length = 0.5f;
        float angle = atan2(0.0f, v2.getX());
        glVertex2f(v2.getX(), 0.0f);
        glVertex2f(v2.getX() - arrow_length * cos(angle - M_PI/6), arrow_length * sin(angle - M_PI/6));
        glVertex2f(v2.getX(), 0.0f);
        glVertex2f(v2.getX() - arrow_length * cos(angle + M_PI/6), arrow_length * sin(angle + M_PI/6));
        glEnd();

        // Dibujar el vector más corto en la parte superior
        glBegin(GL_LINES);
        // Vector v1
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(v1.getX(), 0.0f);
        // Arrow tip for v1
        angle = atan2(0.0f, v1.getX());
        glVertex2f(v1.getX(), 0.0f);
        glVertex2f(v1.getX() - arrow_length * cos(angle - M_PI/6), arrow_length * sin(angle - M_PI/6));
        glVertex2f(v1.getX(), 0.0f);
        glVertex2f(v1.getX() - arrow_length * cos(angle + M_PI/6), arrow_length * sin(angle + M_PI/6));
        glEnd();
    }

    // Actualizar la pantalla
    glutSwapBuffers();
}

vector<float> parseInput(string input) {
    vector<float> values;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        float value = stof(token);
        values.push_back(value);
    }
    return values;
}

int main(int argc, char **argv) {
    string input;
    cout << "Enter the x-value of the first vector between -30 and 30: ";
    cin >> input;
    vector<float> values = parseInput(input);
    Vector1D v1(values[0]);

    cout << "Enter the x-value of the second vector between -30 and 30: ";
    cin >> input;
    values = parseInput(input);
    Vector1D v2(values[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("1D Vector");
    drawGraph(v1, v2);
    Vector1D v3 = v1 + v2;
    Vector1D v4 = v1 - v2;
    float v5 = v1.dotProduct(v2);
    float scalar = 2.0f;
    Vector1D v6 = v1 / scalar;
    Vector1D v_scalar = v1 * scalar;

    cout << "v1 + v2 = (" << v3.getX() << ")" << endl;
    cout << "v1 - v2 = (" << v4.getX() << ")" << endl;
    cout << "v1 / " << scalar << " = (" << v6.getX() << ")" << endl;
    cout << "v1 * " << scalar << " = (" << v_scalar.getX() << ")" << endl;
    cout << "The dot product is: " << v5 << endl;
    cout << "Magnitude of v1: " << v1.magnitude() << endl;
    cout << "Normalized v1: (" << v1.normalize().getX() << ")" << endl;
    cout << "The angle between the vectors is " << v1.angleWith(v2) << " degrees" << endl;
    cout << "There is no cross product in 1D "<< endl;

    glutMainLoop();
    

    return 0;
} 