#include "Projectile.cpp"


class OpenGLRenderer {
public:
    static int aux;
    static int aux1;
    static float t;
    static vector<float> trajectory;
    static Projectile projectile;

    static float cx; 
    static float cy;
    static float cz;
    static float dx;
    static float dy;
    static float dz;

    static void keyboard(unsigned char key, int x, int y);
    static void newdis();
    static void handler();
    static void display();
    static void reshape(GLsizei width, GLsizei height);
    static void timer(int value);
};

float OpenGLRenderer::cx = 150.0f;
float OpenGLRenderer::cy = 150.0f;
float OpenGLRenderer::cz = 150.0f;
float OpenGLRenderer::dx = -1.0f;
float OpenGLRenderer::dy = -1.0f;
float OpenGLRenderer::dz = -1.0f;
int OpenGLRenderer::aux = 0;
int OpenGLRenderer::aux1 = 0;
float OpenGLRenderer::t = 0.0f;
vector<float> OpenGLRenderer::trajectory;
Projectile OpenGLRenderer::projectile;

void OpenGLRenderer::keyboard(unsigned char key, int x, int y) {
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

void OpenGLRenderer::newdis() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::handler() {
    if (projectile.y <= 0 && aux == 0) {
        aux++;
    }
    if (aux == 1) {
        aux++;
        cout << "Final position: (" << projectile.x << ", " << projectile.y << ", " << projectile.z << ")" << endl;
    }
}

void OpenGLRenderer::display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 1200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);

    glColor3f(0.2f, 1.0f, 1.0f);

    projectile.update(t);

    if (projectile.y > 0) {
        projectile.timerun = true;
    } else {
        if (aux1 == 0) {
            aux1++;
        }
        if (aux1 == 1) {
            aux1++;
            cout << "This is the end" << endl;
            glutKeyboardFunc(keyboard);
        }
        projectile.timerun = false;
        newdis();
        trajectory.push_back(projectile.x_initial);
        trajectory.push_back(projectile.y_initial);
        trajectory.push_back(projectile.z_initial);

    }
    trajectory.push_back(projectile.x);
    trajectory.push_back(projectile.y);
    trajectory.push_back(projectile.z);

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


    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // Eje X
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Eje Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < trajectory.size(); i += 3) {
      glColor3f(0.0f, 1.0f, 1.0f);
      glVertex3f(trajectory[i], trajectory[i + 1], trajectory[i + 2]);
    }
    glEnd();
    glTranslatef(projectile.x, projectile.y, projectile.z);
    glutSolidSphere(5, 50, 50);

    handler();

    glutSwapBuffers();
    glutPostRedisplay();
    glutKeyboardFunc(keyboard);
    }

    void OpenGLRenderer::reshape(GLsizei width, GLsizei height) {
        if (height == 0) height = 1;
        GLfloat aspect = (GLfloat)width / (GLfloat)height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    }

    void OpenGLRenderer::timer(int value) {
        if (projectile.timerun == true) {
            t += projectile.delta_t;
            cout << "Time: " << t << ", Position: (" << projectile.x << ", " << projectile.y << ", " << projectile.z << ")" << endl;
            glutTimerFunc(80, timer, 200);
            glutPostRedisplay();
        }
    }

    bool validate_input(float input, float lower_bound, float upper_bound) {
        return input >= lower_bound && input <= upper_bound;
    }   

    void input_error_message(float lower_bound, float upper_bound) {
        cout << "Error: Input must be between " << lower_bound << " and " << upper_bound << endl;
    }

    void get_input() {
        bool valid_input = false;
        while (!valid_input) {
            cout << "Enter Vx: ";
            cin >> OpenGLRenderer::projectile.Vx;
            valid_input = validate_input(OpenGLRenderer::projectile.Vx, 1, 10);
            if (!valid_input) {
                input_error_message(1, 10);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Enter Vy: ";
            cin >> OpenGLRenderer::projectile.Vy;;
            valid_input = validate_input(OpenGLRenderer::projectile.Vy, 1, 10);
            if (!valid_input) {
                input_error_message(1, 10);
            }   
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Enter Vz: ";
            cin >> OpenGLRenderer::projectile.Vz;
            valid_input = validate_input(OpenGLRenderer::projectile.Vz, 1, 10);
            if (!valid_input) {
                input_error_message(1, 10);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Time interval: ";
            cin >> OpenGLRenderer::projectile.delta_t;
            valid_input = validate_input(OpenGLRenderer::projectile.delta_t, 0.1, 0.5);
            if (!valid_input) {
                input_error_message(0.1, 0.5);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Enter initial position in x: ";
            cin >> OpenGLRenderer::projectile.x_initial;
            valid_input = validate_input(OpenGLRenderer::projectile.x_initial, 0, 30);
            if (!valid_input) {
                input_error_message(0, 30);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Enter initial position in y: ";
            cin >> OpenGLRenderer::projectile.y_initial;
            valid_input = validate_input(OpenGLRenderer::projectile.y_initial, 0, 30);
            if (!valid_input) {
                input_error_message(0, 30);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Enter initial position in z: ";
            cin >> OpenGLRenderer::projectile.z_initial;
            valid_input = validate_input(OpenGLRenderer::projectile.z_initial, 0, 30);
            if (!valid_input) {
                input_error_message(0, 30);
            }
        }
    }

    int main(int argc, char **argv) {
        get_input();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(1000, 600);
        glutCreateWindow("3D Projectile Motion");
        glutDisplayFunc(OpenGLRenderer::display);
        glutReshapeFunc(OpenGLRenderer::reshape);
        glutKeyboardFunc(OpenGLRenderer::keyboard);
        glEnable(GL_DEPTH_TEST);

        glutTimerFunc(0, OpenGLRenderer::timer, 0);
        glutMainLoop();

        return 0;
    }