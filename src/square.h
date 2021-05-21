typedef int SquareType;

const SquareType DARK_SQUARE = 0;
const SquareType LIGHT_SQUARE = 1;

class Square {
    double x;
    double y;
    double z;
    double side;
    int sqType;

    public:
        Square() {}

        Square(double xPos, double yPos, double zPos, double sqSide, SquareType squareType) {
            x = xPos;
            y = yPos;
            z = zPos;
            side = sqSide;
            sqType = squareType;
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
        int get_sqType() {
            return sqType;
        }

        void render() {
            glPushMatrix();
            switch (sqType) {
            case LIGHT_SQUARE:  glColor3ub(255, 244, 191); break;
            case DARK_SQUARE:   glColor3ub(92, 23, 2); break;
            default:            glColor3ub(127, 127, 127); break;
            }
            glTranslated(x, y, z);
            glutSolidCube(side);
            glPopMatrix();
        }
};