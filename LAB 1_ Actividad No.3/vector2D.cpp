#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <GL/glut.h>
using namespace std;

class Vector2D {
private:
    float x;
    float y;

public:
    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float x_val, float y_val) {
        x = x_val;
        y = y_val;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    void setX(float x_val) {
        x = x_val;
    }

    void setY(float y_val) {
        y = y_val;
    }

    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(const Vector2D& v) const {
        return Vector2D(x * v.x, y * v.y);
    }

    friend Vector2D operator*(const Vector2D& v, float scalar) {
    return Vector2D(v.getX() * scalar, v.getY() * scalar);
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D crossProduct(const Vector2D& v) const {
        return Vector2D(0.0f, 0.0f); // 2D vector does not have cross product
    }

    float dotProduct(const Vector2D& v) const {
        return x * v.x + y * v.y;
    }

    float magnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2D normalize() const {
        float mag = magnitude();
        return Vector2D(x / mag, y / mag);
    }

    float angleWith(const Vector2D& v) const {
        float dot = dotProduct(v);
        float mag1 = magnitude();
        float mag2 = v.magnitude();
        float angle_radians = acos(dot / (mag1 * mag2));
        return angle_radians * 180.0f / M_PI; // convert radians to degrees
    }
};

void drawGraph(const Vector2D& v1, const Vector2D& v2) {
    // Configurar la ventana y la vista
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30, 30, -30, 30, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    // Dibujar los ejes coordenados
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); // Rojo para el eje x
    glVertex3f(-30, 0, 0);
    glVertex3f(30, 0, 0);
    glColor3f(0, 1, 0); // Verde para el eje y
    glVertex3f(0, -30, 0);
    glVertex3f(0, 30, 0);
    glEnd();

    // Dibujar los vectores v1 y v2
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); // Blanco para v1
    glVertex3f(0, 0, 0);
    glVertex3f(v1.getX(), v1.getY(), 0);

    // Dibujar la punta de flecha para v1
    Vector2D v1_arrow = v1.normalize() * 0.8f; // longitud de la punta de flecha
    Vector2D v1_perp = Vector2D(-v1.getY(), v1.getX()).normalize() * 0.5f; // ancho de la punta de flecha
    glVertex3f(v1.getX(), v1.getY(), 0);
    glVertex3f(v1.getX() - v1_arrow.getX() + v1_perp.getX(), v1.getY() - v1_arrow.getY() + v1_perp.getY(), 0);
    glVertex3f(v1.getX(), v1.getY(), 0);
    glVertex3f(v1.getX() - v1_arrow.getX() - v1_perp.getX(), v1.getY() - v1_arrow.getY() - v1_perp.getY(), 0);

    glColor3f(0, 0, 1); // Azul para v2
    glVertex3f(0, 0, 0);
    glVertex3f(v2.getX(), v2.getY(), 0);

    Vector2D v2_arrow = v2.normalize() * 0.8f; 
    Vector2D v2_perp = Vector2D(-v2.getY(), v2.getX()).normalize() * 0.5f; 
    glVertex3f(v2.getX(), v2.getY(), 0);
    glVertex3f(v2.getX() - v2_arrow.getX() + v2_perp.getX(), v2.getY() - v2_arrow.getY() + v2_perp.getY(), 0);
    glVertex3f(v2.getX(), v2.getY(), 0);
    glVertex3f(v2.getX() - v2_arrow.getX() - v2_perp.getX(), v2.getY() - v2_arrow.getY() - v2_perp.getY(), 0);

    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {

    Vector2D v1, v2;

    float x, y;
    cout << "Enter the x-component of the first vector between -30 and 30: ";
    cin >> x;
    cout << "Enter the y-component of the first vector between -30 and 30: ";
    cin >> y;
    v1 = Vector2D(x, y);

    cout << "Enter the x-component of the second vector between -30 and 30: ";
    cin >> x;
    cout << "Enter the y-component of the second vector between -30 and 30: ";
    cin >> y;
    v2 = Vector2D(x, y);

    Vector2D v_sum = v1 + v2;
    Vector2D v_diff = v1 - v2;
    float v_prod = v1.dotProduct(v2);
    Vector2D v_norm = v1.normalize();
    float v_mag = v1.magnitude();
    float v_angle = v1.angleWith(v2);
    float scalar = 2.0f;
    Vector2D v6 = v1 / scalar;
    Vector2D v_scalar = v1 * scalar;

    cout << "The sum of vectors is (" << v_sum.getX() << ", " << v_sum.getY() << ")" << endl
         << "The difference of vectors is (" << v_diff.getX() << ", " << v_diff.getY() << ")" << endl
         << "The dot product is " << v_prod << endl
         << "v1 / " << scalar << " = (" << v6.getX() << ", " << v6.getY() <<")" << endl
         << "v1 * " << scalar << " = (" << v_scalar.getX() << ", " << v_scalar.getY() <<")" << endl
         << "The first vector normalized is (" << v_norm.getX() << ", " << v_norm.getY() << ")" << endl
         << "The magnitude of the first vector is " << v_mag << endl
         << "The angle between the vectors is " << v_angle << " degrees" << endl
         << "There is no cross product in 2D." << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Vectors");
    drawGraph(v1, v2);
    glutMainLoop();

    return 0;
}