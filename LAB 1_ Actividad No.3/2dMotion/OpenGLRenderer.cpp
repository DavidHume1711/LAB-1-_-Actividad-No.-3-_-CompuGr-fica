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
    if (projectile.y <= 0 && aux == 0) {
        aux++;
    }
    if (aux == 1) {
        aux++;
        cout << "Final position: (" << projectile.x << ", " << projectile.y << ")" << endl;
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
    }
    
    if (projectile.timerun) {
        trajectory.push_back(projectile.x);
        trajectory.push_back(projectile.y);
    }

    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    // Eje X
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    // Eje Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < trajectory.size(); i += 2) {
        if (trajectory[i + 1] <= 0) {
            break;
        }
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex2f(trajectory[i], trajectory[i + 1]);
    }
    glEnd();

    glTranslatef(projectile.x, projectile.y, 0);
    glutSolidSphere(5, 5, 5);

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
            cout << "Time: " << t << ", Position: (" << projectile.x << ", " << projectile.y << ")" << endl;
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
            cout << "Enter angle in degrees: ";
            cin >> OpenGLRenderer::projectile.angle;;
            valid_input = validate_input(OpenGLRenderer::projectile.angle, 15, 75);
            if (!valid_input) {
                input_error_message(15, 75);
            }   
        }
        OpenGLRenderer::projectile.angle = OpenGLRenderer::projectile.angle * M_PI / 180.0f;
        OpenGLRenderer::projectile.Vx = OpenGLRenderer::projectile.V * cos(OpenGLRenderer::projectile.angle);
        OpenGLRenderer::projectile.Vy = OpenGLRenderer::projectile.V * sin(OpenGLRenderer::projectile.angle);

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
            valid_input = validate_input(OpenGLRenderer::projectile.x_initial, -40, 0);
            if (!valid_input) {
                input_error_message(-40, 0);
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
    }

    int main(int argc, char **argv) {
        get_input();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(1000, 1000);
        glutCreateWindow("2D Projectile Motion");
        glutDisplayFunc(OpenGLRenderer::display);
        glutReshapeFunc(OpenGLRenderer::reshape);
        glutKeyboardFunc(OpenGLRenderer::keyboard);

        glutTimerFunc(0, OpenGLRenderer::timer, 0);
        glutMainLoop();

        return 0;
    }