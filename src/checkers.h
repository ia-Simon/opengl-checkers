class Checkers {
    double squareSide;
    Square board[8][8];
    Piece darkPieces[12];
    Piece lightPieces[12];

    void initBoard() {
        double boardOrigin = (double) -(squareSide * 4) + (squareSide / 2);
        bool lightCube = true;
        for(int j = 0; j < 8; j++) {
            for(int i = 0; i < 8; i++) {
                board[i][j] = Square(
                    (double) boardOrigin + (i * squareSide), 
                    (double) -(squareSide / 2), 
                    (double) boardOrigin + (j * squareSide), 
                    squareSide,
                    lightCube ? SQUARE_LIGHT : SQUARE_DARK
                );
                lightCube = !lightCube;
            }
            lightCube = !lightCube;
        }
    }
    
    void initPieces() {
        for(int i = 0; i < 12; i++) {
            darkPieces[i] = Piece(-12, i, -12, (squareSide/2) * 0.8, squareSide/6, PIECE_DARK);
            lightPieces[i] = Piece(-9, i, -12, (squareSide/2) * 0.8, squareSide/6, PIECE_LIGHT);
        }
    }

    void renderTable() {
        GLUquadric *quad = gluNewQuadric();
        double tableThickness = squareSide * 0.75;
        double tableRadius = squareSide * 8;
        glPushMatrix();
        glColor3ub(127, 127, 127);
        glTranslated(0, -squareSide/2, 0);
        glRotated(90, -1, 0, 0);
        gluDisk(quad, 0, tableRadius, 256, 1);
        glTranslated(0, 0, -tableThickness);
        glRotated(180, 1, 0, 0);
        gluDisk(quad, 0, tableRadius, 256, 1);
        glColor3ub(191, 163, 17);
        glTranslated(0, 0, -tableThickness/2);
        glutSolidTorus(tableThickness/2, tableRadius, 256, 256);
        glPopMatrix();
        gluDeleteQuadric(quad);
    }

    public:
        Checkers(double sqSide) {
            squareSide = sqSide;
            initBoard();
            initPieces();
        }

        void render() {
            renderTable();
            for(int j = 0; j < 8; j++)
                for(int i = 0; i < 8; i++)
                    board[i][j].render();
            for(int i = 0; i < 12; i++) {
                darkPieces[i].render();
                lightPieces[i].render();
            }
        }
};