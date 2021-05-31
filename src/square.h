enum SquareType {
    DARK_SQUARE,
    LIGHT_SQUARE,
};

class Square {
    double x;
    double y;
    double z;
    double side;
    SquareType sqType;
    PieceType pcAlloc;

public:
    Square() {}

    Square(double xPos, double yPos, double zPos, double sqSide, SquareType squareType) {
        x = xPos;
        y = yPos;
        z = zPos;
        side = sqSide;
        sqType = squareType;
        pcAlloc = NA;
    }
    double get_x() { return x; }
    double get_y() { return y; }
    double get_z() { return z; }
    int get_sqType() { return sqType; }
    PieceType get_pcAlloc() { return pcAlloc; }
    void set_pcAlloc(PieceType pieceAlloc) { pcAlloc = pieceAlloc; }

    void render(bool glow) {
        glPushMatrix();
        glTranslated(x, y, z);
        //Solid Square
            glPushMatrix();
            switch (sqType) {
            case LIGHT_SQUARE:  glColor3ub(255, 244, 191); break;
            case DARK_SQUARE:   glColor3ub(92, 23, 2); break;
            default:            glColor3ub(127, 127, 127); break;
            }
            glutSolidCube(side);
            glPopMatrix();
        //Wire Square
        if(glow) {
            const int t = glutGet(GLUT_ELAPSED_TIME);
            const int wirePeriod = 1500;
            double wireIntensity = abs(((double) (t % wirePeriod) / (wirePeriod/2)) - 1);

            glPushMatrix();
            glColor4ub(43, 255, 15, wireIntensity * 80);
            glTranslated(0, side/2, 0);
            glScaled(0.7, 0.01, 0.7);
            glutSolidOctahedron();
            glPopMatrix();
        }
        glPopMatrix();
    }
};