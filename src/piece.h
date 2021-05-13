#define PIECE_DARK 0
#define PIECE_LIGHT 1

class Piece {
    double x;
    double y;
    double z;
    double radius;
    double height;
    int color;
    GLUquadric *quad;

    void solidPiece() {
        glRotated(90, -1, 0, 0);
        gluCylinder(quad, radius, radius, height, 64, 1);
        // InnerCone:
            glPushMatrix();
            glCullFace(GL_FRONT);
            glTranslated(0, 0, height * 0.8);
            gluCylinder(quad, radius * 0.6, radius * 0.75, height * 0.2, 64, 8);
            glCullFace(GL_BACK);
            glPopMatrix();
        //InnerDisk:
            glPushMatrix();
            glTranslated(0, 0, height * 0.8);
            gluDisk(quad, 0, radius * 0.6, 64, 8);
            glPopMatrix();
        // TopDisk:
            glPushMatrix();
            glTranslated(0, 0, height);
            gluDisk(quad, radius * 0.75, radius, 64, 8);
            glPopMatrix();
        // BottomDisk:
            glPushMatrix();
            glRotated(180, 1, 0, 0);
            gluDisk(quad, 0, radius, 64, 8);
            glPopMatrix();
    }

    public:
        Piece() {quad = gluNewQuadric();}

        Piece(double xPos, double yPos, double zPos, double pcRadius, double pcHeight, int pcColor) {
            x = xPos;
            y = yPos;
            z = zPos;
            radius = pcRadius;
            height = pcHeight;
            color = pcColor;
            quad = gluNewQuadric();
        }
        double get_x() {
            return x;
        }
        double get_y() {
            return y;
        }
        double get_z() {
            return z;
        }
        int get_color() {
            return color;
        }
        void set_x(double xPos) {
            x = xPos;
        }
        void set_y(double yPos) {
            y = yPos;
        }
        void set_z(double zPos) {
            z = zPos;
        }

        void render() {
            glPushMatrix();
            switch (color) {
            case PIECE_LIGHT:   glColor3ub(240, 240, 240); break;
            case PIECE_DARK:    glColor3ub(32, 32, 32); break;
            default:            glColor3ub(127, 127, 127); break;
            }
            glTranslated(x, y, z);
            solidPiece();
            glPopMatrix();
        }
};