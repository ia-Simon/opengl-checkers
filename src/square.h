#define SQUARE_DARK 0
#define SQUARE_LIGHT 1

class Square {
    double x;
    double y;
    double z;
    double side;
    int color;

    public:
        Square() {}

        Square(double xPos, double yPos, double zPos, double sqSide, int sqColor) {
            x = xPos;
            y = yPos;
            z = zPos;
            side = sqSide;
            color = sqColor;
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

        void render() {
            glPushMatrix();
            switch (color) {
            case SQUARE_LIGHT:  glColor3ub(255, 244, 191); break;
            case SQUARE_DARK:   glColor3ub(92, 23, 2); break;
            default:            glColor3ub(127, 127, 127); break;
            }
            glTranslated(x, y, z);
            glutSolidCube(side);
            glPopMatrix();
        }
};