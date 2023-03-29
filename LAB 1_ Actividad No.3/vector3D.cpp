#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <GL/glut.h>
using namespace std;

class Vector3D {
private:
float x;
float y;
float z;

public:
Vector3D() {
x = 0.0f;
y = 0.0f;
z = 0.0f;
}

Vector3D(float x_val, float y_val, float z_val) {
    x = x_val;
    y = y_val;
    z = z_val;
}

float getX() const {
    return x;
}

float getY() const {
    return y;
}

float getZ() const {
    return z;
}

void setX(float x_val) {
    x = x_val;
}

void setY(float y_val) {
    y = y_val;
}

void setZ(float z_val) {
    z = z_val;
}

Vector3D operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D operator*(const Vector3D& v) const {
    return Vector3D(x * v.x, y * v.y, z * v.z);
}

friend Vector3D operator*(const Vector3D& v, float scalar) {
    return Vector3D(v.getX() * scalar, v.getY() * scalar, v.getZ() * scalar);
}

Vector3D operator/(float scalar) const {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

Vector3D crossProduct(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

float dotProduct(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

float magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

Vector3D normalize() const {
    float mag = magnitude();
    return Vector3D(x / mag, y / mag, z / mag);
}

float angleWith(const Vector3D& v) const {
    float dot = dotProduct(v);
    float mag1 = magnitude();
    float mag2 = v.magnitude();
    float angle_radians = acos(dot / (mag1 * mag2));
    return angle_radians * 180.0f / M_PI; // convert radians to degrees
}
};

void drawArrowHead(const Vector3D& v, const Vector3D& color) {
  Vector3D arrow = v.normalize() * 0.8f;
  Vector3D cross = v.crossProduct(Vector3D(0, 1, 0)).normalize();
  if (cross.magnitude() < 0.0001f) {
    cross = v.crossProduct(Vector3D(1, 0, 0)).normalize();
  } 
  Vector3D perp1 = v.crossProduct(cross).normalize() * 0.5f;
  Vector3D perp2 = cross.crossProduct(v).normalize() * 0.5f;
  glColor3f(color.getX(), color.getY(), color.getZ());
  glVertex3f(v.getX(), v.getY(), v.getZ());
  glVertex3f(v.getX() - arrow.getX() + perp1.getX(), v.getY() - arrow.getY() + perp1.getY(), v.getZ() - arrow.getZ() + perp1.getZ());
  glVertex3f(v.getX(), v.getY(), v.getZ());
  glVertex3f(v.getX() - arrow.getX() + perp2.getX(), v.getY() - arrow.getY() + perp2.getY(), v.getZ() - arrow.getZ() + perp2.getZ());
}
float cx = 150.0f, cy = 150.0f, cz = 150.0f;  // Posición de la cámara
float dx = -1.0f, dy = -1.0f, dz = -1.0f;     // Dirección de la vista

void drawGraph(const Vector3D& v1, const Vector3D& v2) {

  //glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, 800, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 1200.0);
  //glOrtho(-30, 30, -30, 30, 1, 100);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glPushMatrix();
  glTranslatef(110.0f, 0.0f, 0.0f);
  glScalef(0.1f, 0.1f, 0.1f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'X');
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, 110.0f, 0.0f);
  glScalef(0.1f, 0.1f, 0.1f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 110.0f);
  glScalef(0.1f, 0.1f, 0.1f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Z');
  glPopMatrix();

  // Draw axes
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f); // red x-axis
  glVertex3f(-100.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);
  drawArrowHead(Vector3D(100.0f, 0.0f, 0.0f), Vector3D(1.0f, 0.0f, 0.0f));

  glColor3f(0.0f, 1.0f, 0.0f); // green y-axis
  glVertex3f(0.0f, -100.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);
  drawArrowHead(Vector3D(0.0f, 100.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f));

  glColor3f(0.0f, 0.0f, 1.0f); // blue z-axis
  glVertex3f(0.0f, 0.0f, -100.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);
  drawArrowHead(Vector3D(0.0f, 0.0f, 100.0f), Vector3D(0.0f, 0.0f, 1.0f));

  glColor3f(1.0f, 1.0f, 0.0f); // yellow vector 1
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(v1.getX(), v1.getY(), v1.getZ());
  drawArrowHead(v1, Vector3D(1.0f, 1.0f, 0.0f));

  glColor3f(1.0f, 0.0f, 1.0f); // magenta vector 2
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(v2.getX(), v2.getY(), v2.getZ());
  drawArrowHead(v2, Vector3D(1.0f, 0.0f, 1.0f));

  glEnd();
  glutSwapBuffers(); // Swap the buffers
  glFlush();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}
Vector3D v1, v2;
void drawGraphWrapper() {
  drawGraph(v1, v2);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'o') {
        exit(0);
    }
    if (key == 'f') {
        glutFullScreen();
    }

    const float step = 5.0f;  // Tamaño del paso de movimiento
    switch(key) {
        case 'w':  // Mover hacia adelante
            cx += step * dx;
            cy += step * dy;
            cz += step * dz;
            break;
        case 's':  // Mover hacia atrás
            cx -= step * dx;
            cy -= step * dy;
            cz -= step * dz;
            break;
        case 'a': {  // Mover hacia la izquierda
            float ux = 0.0f, uy = 1.0f, uz = 0.0f;
            float vx = dy * uz - dz * uy;
            float vy = dz * ux - dx * uz;
            float vz = dx * uy - dy * ux;
            cx -= step * vx;
            cy -= step * vy;
            cz -= step * vz;
            break;
        }
        case 'd': {  // Mover hacia la derecha
            float ux = 0.0f, uy = 1.0f, uz = 0.0f;
            float vx = dy * uz - dz * uy;
            float vy = dz * ux - dx * uz;
            float vz = dx * uy - dy * ux;
            cx += step * vx;
            cy += step * vy;
            cz += step * vz;
            break;
        }
    }
}

int main(int argc, char** argv) {

  float x, y, z;
  cout << "Enter the first vector (x, y, z) Press ENTER after each individual component: ";
  cin >> x >> y >> z;
  v1.setX(x);
  v1.setY(y);
  v1.setZ(z);

  cout << "Enter the second vector (x, y, z) Press ENTER after each individual component: ";
  cin >> x >> y >> z;
  v2.setX(x);
  v2.setY(y);
  v2.setZ(z);

  
  Vector3D sum = v1 + v2;
  Vector3D diff = v1 - v2;
  Vector3D cross = v1.crossProduct(v2);
  float dot = v1.dotProduct(v2);
  float angle = v1.angleWith(v2);
  Vector3D mult = v1 * v2;
  Vector3D div = v1 / 2.0f;
  Vector3D scalar1 = v1 * 2.0f;
  Vector3D scalar2 = v2 * 3.0f;
  Vector3D norm1 = v1.normalize();
  Vector3D norm2 = v2.normalize();

  cout << "Addition: " << sum.getX() << ", " << sum.getY() << ", " << sum.getZ() << endl;
  cout << "Subtraction: " << diff.getX() << ", " << diff.getY() << ", " << diff.getZ() << endl;
  cout << "Cross product: " << cross.getX() << ", " << cross.getY() << ", " << cross.getZ() << endl;
  cout << "Dot product: " << dot << endl;
  cout << "Angle between vectors: " << angle << " degrees" << endl;
  cout << "Multiplication by components: " << mult.getX() << ", " << mult.getY() << ", " << mult.getZ() << endl;
  cout << "Scalar division (v1 / 2): " << div.getX() << ", " << div.getY() << ", " << div.getZ() << endl;
  cout << "Scalar multiplication (v1 * 2): " << scalar1.getX() << ", " << scalar1.getY() << ", " << scalar1.getZ() << endl;
  cout << "Scalar multiplication (v2 * 3): " << scalar2.getX() << ", " << scalar2.getY() << ", " << scalar2.getZ() << endl;
  cout << "Normalization (v1): " << norm1.getX() << ", " << norm1.getY() << ", " << norm1.getZ() << endl;
  cout << "Normalization (v2): " << norm2.getX() << ", " << norm2.getY() << ", " << norm2.getZ() << endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("3D Vector");
  glutDisplayFunc(display);
  glutIdleFunc(drawGraphWrapper);
  glutKeyboardFunc(keyboard);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();

  return 0;
}