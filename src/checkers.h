typedef int CheckersTurn;

const CheckersTurn DARK_TURN = 0;
const CheckersTurn LIGHT_TURN = 1;
class Checkers {
    double squareSide;
    std::array<std::array<Square,8>,8> board;
    std::array<Piece,12> darkPieces;
    std::array<Piece,12> lightPieces;
    Cycle darkPieceSelector;
    Cycle lightPieceSelector;
    int turnCounter;

    void initBoardAndPieces() {
        double boardOrigin = (double) -(squareSide * 4) + (squareSide / 2);
        bool lightCube = true;
        int darkPieceCounter = 0;
        int lightPieceCounter = 11;
        for(size_t j = 0; j < 8; j++) {
            for(size_t i = 0; i < 8; i++) {
                board[i][j] = Square(
                    (double) boardOrigin + (i * squareSide), 
                    (double) -(squareSide / 2), 
                    (double) boardOrigin + (j * squareSide), 
                    squareSide,
                    lightCube ? LIGHT_SQUARE : DARK_SQUARE
                );
                if(!lightCube) {
                    Square square = board[i][j];
                    std::array<int,2> posOnBoard = {i, j};
                    if(j <= 2) {
                        darkPieces[darkPieceCounter] = Piece(
                            square.get_x(), 0, square.get_z(), 
                            (squareSide/2) * 0.9, squareSide / 6,
                            DARK_PIECE, posOnBoard
                        );
                        darkPieceCounter++;
                    } else if(5 <= j) {
                        lightPieces[lightPieceCounter] = Piece(
                            square.get_x(), 0, square.get_z(), 
                            (squareSide/2) * 0.9, squareSide/6,
                            LIGHT_PIECE, posOnBoard
                        );
                        lightPieceCounter--;
                    }
                }
                lightCube = !lightCube;
            }
            lightCube = !lightCube;
        }
    }

    void renderTable() {
        GLUquadric *quad = gluNewQuadric();
        double tableThickness = squareSide * 0.75;
        double tableRadius = squareSide * 8;
        glPushMatrix();
    
        glTranslated(0, -tableThickness -squareSide/2, 0);
        glRotated(90, -1, 0, 0);

        glColor3ub(127, 127, 127);
        // Table Top
        glPushMatrix();
        glRotated(180, 1, 0, 0);
        gluDisk(quad, 0, tableRadius, 256, 1);
        glPopMatrix();
        // Table Bottom
        glPushMatrix();
        glTranslated(0, 0, tableThickness);
        gluDisk(quad, 0, tableRadius, 256, 1);
        glPopMatrix();

        // Table Border
        glColor3ub(143, 10, 41);
        glPushMatrix();
        glTranslated(0, 0, tableThickness/2);
        glutSolidTorus(tableThickness/2, tableRadius, 256, 256);
        glPopMatrix();

        // Board Border
        glPushMatrix();
        glRotated(45, 0, 0, 1);
        glColor3ub(59, 30, 2);
        glTranslated(0, 0, tableThickness);
        glutSolidTorus(squareSide * 0.24, (squareSide * 8 * sqrt(2)) / 2, 256, 4);
        glColor3ub(255, 228, 153);
        glTranslated(0, 0, squareSide/5);
        glutSolidTorus(squareSide * 0.24, (squareSide * 8 * sqrt(2)) / 2, 256, 4);
        glColor3ub(59, 30, 2);
        glScaled(1.01, 1.01, 1);
        glTranslated(0, 0, squareSide/5);
        glutSolidTorus(squareSide * 0.125, (squareSide * 8 * sqrt(2)) / 2, 256, 4);
        glPopMatrix();

        glPopMatrix();
        gluDeleteQuadric(quad);
    }

    void renderBoard() {
        for(size_t j = 0; j < 8; j++)
            for(size_t i = 0; i < 8; i++)
                board[i][j].render();
    }

    void renderPieces() {
        for(size_t i = 0; i < 12; i++) {
            darkPieces[i].render(getTurn() == DARK_TURN && i == darkPieceSelector.get_value());
            lightPieces[i].render(getTurn() == LIGHT_TURN && i == lightPieceSelector.get_value());
        }
    }

    Piece &getActivePiece() {
        return getTurn() == DARK_TURN ? 
            darkPieces[darkPieceSelector.get_value()] :
            lightPieces[lightPieceSelector.get_value()];
    }

    void movePiece(Piece &piece, double newXPos, double newZPos) {
        const double stepSize = 0.05;
        double xStepSize = piece.get_x() < newXPos ? stepSize : -stepSize;
        double zStepSize = piece.get_z() < newZPos ? stepSize : -stepSize;
        int moveStepCount = 100;
        for(int i = 0; i < moveStepCount; i++) {
            
        }
    }

public:
    Checkers(double sqSide) {
        squareSide = sqSide;
        darkPieceSelector = Cycle(12);
        lightPieceSelector = Cycle(12);
        turnCounter = 0;
        initBoardAndPieces();
    }

    CheckersTurn getTurn() {
        return turnCounter % 2;
    }

    void render() {
        renderTable();
        renderBoard();
        renderPieces();
    }

    void selectNextPiece() {
        getTurn() == DARK_TURN ? darkPieceSelector.next() : lightPieceSelector.next();
    }

    void selectPrevPiece() {
        getTurn() == DARK_TURN ? darkPieceSelector.prev() : lightPieceSelector.prev();
    }

    void moveUpRight() {
        Piece &piece = getActivePiece();   
        const std::array<int,2> &posOnBoard = piece.get_posOnBoard();
        if(posOnBoard[0] == -1 || posOnBoard[1] == -1) return;

        std::array<int,2> newPos = {posOnBoard[0] + 1, posOnBoard[1] + 1};

    }

    void moveUpLeft() {
        Piece &piece = getActivePiece();   
        const std::array<int,2> &posOnBoard = piece.get_posOnBoard();
        if(posOnBoard[0] == -1 || posOnBoard[1] == -1) return;

    }

    void moveDownRight() {
        Piece &piece = getActivePiece();   
        const std::array<int,2> &posOnBoard = piece.get_posOnBoard();
        if(posOnBoard[0] == -1 || posOnBoard[1] == -1) return;

    }

    void moveDownLeft() {
        Piece &piece = getActivePiece();   
        const std::array<int,2> &posOnBoard = piece.get_posOnBoard();
        if(posOnBoard[0] == -1 || posOnBoard[1] == -1) return;

    }
};