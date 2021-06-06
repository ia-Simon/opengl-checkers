enum PieceType {
    DARK_PIECE,
    LIGHT_PIECE,
    NA,
};

class Piece {
    GLUquadric *quad;
    double x;
    double y;
    double z;
    double radius;
    double height;
    PieceType pcType;
    std::array<size_t,2> posOnBoard;

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

    void wirePiece() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glRotated(90, -1, 0, 0);
        gluCylinder(quad, radius, radius, height, 32, 2);
        // InnerCone:
            glPushMatrix();
            glCullFace(GL_FRONT);
            glTranslated(0, 0, height * 0.8);
            gluCylinder(quad, radius * 0.6, radius * 0.75, height * 0.2, 16, 1);
            glCullFace(GL_BACK);
            glPopMatrix();
        //InnerDisk:
            glPushMatrix();
            glTranslated(0, 0, height * 0.8);
            gluDisk(quad, 0, radius * 0.6, 16, 3);
            glPopMatrix();
        // TopDisk:
            glPushMatrix();
            glTranslated(0, 0, height);
            gluDisk(quad, radius * 0.75, radius, 32, 1);
            glPopMatrix();
        // BottomDisk:
            glPushMatrix();
            glRotated(180, 1, 0, 0);
            gluDisk(quad, 0, radius, 32, 2);
            glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

public:
    Piece() {quad = gluNewQuadric();}

    Piece(double xPos, double yPos, double zPos, double pcRadius, double pcHeight, 
    PieceType pieceType, std::array<size_t,2> positionOnBoard) {
        quad = gluNewQuadric();
        x = xPos;
        y = yPos;
        z = zPos;
        radius = pcRadius;
        height = pcHeight;
        pcType = pieceType; 
        posOnBoard = positionOnBoard;
    }
    double get_x() { return x; }
    double get_y() { return y; }
    double get_z() { return z; }
    const std::array<size_t,2> &get_posOnBoard() { return posOnBoard; }
    PieceType get_pcType() { return pcType; }
    void set_x(double xPos) { x = xPos; }
    void set_y(double yPos) { y = yPos; }
    void set_z(double zPos) { z = zPos; }
    void set_posOnBoard(std::array<size_t,2> positionOnBoard) { posOnBoard = positionOnBoard; }
    
    void render(bool glow) {
        glPushMatrix();
        glTranslated(x, y, z);
        //Solid Piece
            glPushMatrix();
            switch (pcType) {
            case LIGHT_PIECE:   glColor3ub(220, 220, 220); break;
            case DARK_PIECE:    glColor3ub(32, 32, 32); break;
            default:            glColor3ub(127, 127, 127); break;
            }
            solidPiece();
            glPopMatrix();
        //Wire Piece
        if(glow) {
            const int t = glutGet(GLUT_ELAPSED_TIME);
            const int wirePeriod = 1500;
            double wireIntensity = 0.35 * cos(M_PI*2*((double) (t % wirePeriod) / wirePeriod)) + 0.65;

            glPushMatrix();
            glColor4ub(0, 235, 196, wireIntensity * 255);
            glScaled(1.005, 1.005, 1.005);
            wirePiece();
            glPopMatrix();
        }
        glPopMatrix();
    }
};