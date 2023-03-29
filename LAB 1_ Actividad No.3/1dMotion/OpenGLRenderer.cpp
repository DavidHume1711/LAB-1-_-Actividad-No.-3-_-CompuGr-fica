#include "Projectile.cpp"


class OpenGLRenderer {
public:
    static int aux;
    static int aux1;
    static float t;
    static vector<float> trajectory;
    static Projectile projectile;

    static void keyboard(unsigned char key, int x, int y);
    static void newdis();
    static void handler();
    static void display();
    static void reshape(GLsizei width, GLsizei height);
    static void timer(int value);
};

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
}

void OpenGLRenderer::newdis() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::handler() {
    if (projectile.total_time == t && aux == 0) {
        aux++;
    }
    if (aux == 1) {
        aux++;
        cout << "Final position: (" << projectile.x << ")" << endl;
    }
}

void OpenGLRenderer::display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.2f, 1.0f, 1.0f);

    projectile.update(t);

    if (t < projectile.total_time) {
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
        handler();
        trajectory.push_back(projectile.x_initial);
    }
    trajectory.push_back(projectile.x);

    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    // Eje y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (float position : trajectory) {
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2f(position, 0.0f);
    }
    glEnd();

    glTranslatef(projectile.x, 0, 0);
    glutSolidSphere(5, 15, 15);

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
            cout << "Time: " << t << ", Position: (" << projectile.x << ")" << endl;
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
            cout << "Enter initial velocity: ";
            cin >> OpenGLRenderer::projectile.V;
            valid_input = validate_input(OpenGLRenderer::projectile.V, 1, 8);
            if (!valid_input) {
                input_error_message(1, 8);
            }
        }

        valid_input = false;
        while (!valid_input) {
            cout << "Total time of the motion: ";
            cin >> OpenGLRenderer::projectile.total_time;
            valid_input = validate_input(OpenGLRenderer::projectile.total_time, 2, 10);
            if (!valid_input) {
                input_error_message(2, 10);
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
            valid_input = validate_input(OpenGLRenderer::projectile.x_initial, -60, 0);
            if (!valid_input) {
                input_error_message(-60, 0);
            }
        }
    }

    int main(int argc, char **argv) {
        get_input();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(1000, 1000);
        glutCreateWindow("1D Projectile Motion");
        glutDisplayFunc(OpenGLRenderer::display);
        glutReshapeFunc(OpenGLRenderer::reshape);
        glutKeyboardFunc(OpenGLRenderer::keyboard);

        glutTimerFunc(0, OpenGLRenderer::timer, 0);
        glutMainLoop();

        return 0;
    }