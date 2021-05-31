enum CheckersTurn {
    DARK_TURN,
    LIGHT_TURN,
};

enum MoveDirection {
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
};

class Checkers {
    double squareSide;
    std::array<std::array<Square,8>,8> board;
    std::vector<Piece> darkPieces;
    std::vector<Piece> lightPieces;
    Selector darkPieceSelector;
    Selector lightPieceSelector;
    int turnCounter;

    Piece *animatedPiece;
    std::array<size_t,2> animateFrom;
    std::array<size_t,2> animateTo;
    int animationStartTime;

    void initBoard() {
        double boardOrigin = (double) -(squareSide * 4) + (squareSide / 2);
        bool lightCube = true;
        for(size_t j = 0; j < 8; j++) {
            for(size_t i = 0; i < 8; i++) {
                board[i][j] = Square(
                    (double) boardOrigin + (i * squareSide), 
                    (double) -(squareSide / 2), 
                    (double) boardOrigin + (j * squareSide), 
                    squareSide,
                    lightCube ? LIGHT_SQUARE : DARK_SQUARE
                );
                lightCube = !lightCube;
            }
            lightCube = !lightCube;
        }
    }

    void initPieces() {
        for(size_t j = 0; j < 8; j++) {
            for(size_t i = 0; i < 8; i++) {
                Square &square = board[i][j];
                if(square.get_sqType() == LIGHT_SQUARE) continue;

                if(j <= 2) {
                    lightPieces.insert(lightPieces.begin(), Piece(
                        square.get_x(), 0, square.get_z(), 
                        (squareSide/2) * 0.9, squareSide / 6,
                        LIGHT_PIECE, std::array{i, j}
                    ));
                    square.set_pcAlloc(LIGHT_PIECE);
                } else if(5 <= j) {
                    darkPieces.push_back(Piece(
                        square.get_x(), 0, square.get_z(), 
                        (squareSide/2) * 0.9, squareSide/6,
                        DARK_PIECE, std::array{i, j}
                    ));
                    square.set_pcAlloc(DARK_PIECE);
                }
            }
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
        std::array<size_t,2> activePcPos = getActivePiece().get_posOnBoard();

        for(size_t j = 0; j < 8; j++)
            for(size_t i = 0; i < 8; i++)
                board[i][j].render(abs((double)i - activePcPos[0]) == 1 && abs((double)j - activePcPos[1]) == 1);
    }

    void renderPieces() {
        Piece &activePiece = getActivePiece();

        for(Piece &piece : darkPieces)
            piece.render(&piece == &activePiece);
            
        for(Piece &piece : lightPieces)
            piece.render(&piece == &activePiece);
    }

    Piece &getActivePiece() {
        return getTurn() == DARK_TURN ? 
            darkPieces.at(darkPieceSelector.get_val()) :
            lightPieces.at(lightPieceSelector.get_val());
    }

    bool isValidPos(std::array<size_t,2> pos) {
        return pos[0] < 8 && pos[1] < 8;
    }

    bool isEmptyPos(std::array<size_t,2> pos) {
        return board[pos[0]][pos[1]].get_pcAlloc() == NA;
    }

    bool isOpponentPos(std::array<size_t,2> pos) {
        CheckersTurn turn = getTurn();
        PieceType pcTypeOnPos = board[pos[0]][pos[1]].get_pcAlloc();
        return (turn == DARK_TURN && pcTypeOnPos == LIGHT_PIECE) ||
               (turn == LIGHT_TURN && pcTypeOnPos == DARK_PIECE);
    }
    
    void nextTurn() {
        turnCounter++;
    }

    void animateMove() {
        // std::cout << animatedPiece << std::endl;
        if(animatedPiece == NULL) return;

        Square &orgSquare = board[animateFrom[0]][animateFrom[1]];
        Square &destSquare = board[animateTo[0]][animateTo[1]];

        const int t = glutGet(GLUT_ELAPSED_TIME);
        const int animationPeriod = 600;
        if(animationStartTime == -1) animationStartTime = t;
        double animationPercent = (double) (t - animationStartTime)/animationPeriod;
        double yMax = 1.5;

        double xDiff = destSquare.get_x() - orgSquare.get_x();
        double zDiff = destSquare.get_z() - orgSquare.get_z();
        animatedPiece->set_x(orgSquare.get_x() + (xDiff * animationPercent));
        animatedPiece->set_z(orgSquare.get_z() + (zDiff * animationPercent));
        animatedPiece->set_y(yMax * sin(M_PI * animationPercent));
        cam.translate(pow(animationPercent, (double) animationPeriod / 71.4285) * ((getTurn() == DARK_TURN ? 270 : 90) - cam.get_pathAngle()));
        if(t > (animationStartTime + animationPeriod)) {
            animatedPiece->set_x(destSquare.get_x());
            animatedPiece->set_z(destSquare.get_z());
            animatedPiece->set_y(0);
            cam.set_pathAngle(getTurn() == DARK_TURN ? 270 : 90);
            orgSquare.set_pcAlloc(NA);
            animatedPiece->set_posOnBoard(animateTo);
            destSquare.set_pcAlloc(animatedPiece->get_pcType());
            animatedPiece = nullptr;
            animationStartTime = -1;
            nextTurn();
        }
    }

    std::array<size_t,2> calcNewPos(std::array<size_t,2> pos, MoveDirection direction) {
        switch (direction) {
        case UP_LEFT:   return getTurn() == DARK_TURN ? std::array{pos[0] - 1, pos[1] - 1} : std::array{pos[0] + 1, pos[1] + 1};
        case UP_RIGHT:  return getTurn() == DARK_TURN ? std::array{pos[0] + 1, pos[1] - 1} : std::array{pos[0] - 1, pos[1] + 1};
        case DOWN_LEFT: return getTurn() == DARK_TURN ? std::array{pos[0] - 1, pos[1] + 1} : std::array{pos[0] + 1, pos[1] - 1};
        case DOWN_RIGHT:return getTurn() == DARK_TURN ? std::array{pos[0] + 1, pos[1] + 1} : std::array{pos[0] - 1, pos[1] - 1};
        default: throw;
        }
    }

public:
    CircularCamera cam;

    Checkers(double sqSide, double camXZpathRadius, double camYheight) {
        squareSide = sqSide;
        initBoard();
        initPieces();
        darkPieceSelector = Selector(darkPieces.size());
        lightPieceSelector = Selector(lightPieces.size());
        turnCounter = 0;

        animatedPiece = nullptr;
        animateFrom = {0, 0};
        animateTo = {0, 0};
        animationStartTime = -1;

        cam = CircularCamera(camXZpathRadius, camYheight);
    }

    CheckersTurn getTurn() {
        return (turnCounter % 2 == 0) ? DARK_TURN : LIGHT_TURN;
    }

    void render() {
        animateMove();
        renderTable();
        renderBoard();
        renderPieces();
    }

    void nextPiece() {
        getTurn() == DARK_TURN ? darkPieceSelector.next() : lightPieceSelector.next();
    }

    void prevPiece() {
        getTurn() == DARK_TURN ? darkPieceSelector.prev() : lightPieceSelector.prev();
    }

    void movePiece(MoveDirection direction) {
        if(animatedPiece != NULL) return;
        
        Piece &piece = getActivePiece();
        const std::array<size_t,2> &pos = piece.get_posOnBoard();
        std::array<size_t,2> newPos;
        try {
            newPos = calcNewPos(pos, direction);
        } catch(const std::exception& e) {
            return;
        }   

        if(isValidPos(newPos) && isEmptyPos(newPos)) {
            animatedPiece = &piece;
            animateFrom = pos;
            animateTo = newPos;
        } else if(isValidPos(newPos) && isOpponentPos(newPos)) {
            try {
                newPos = calcNewPos(newPos, direction);
            } catch(const std::exception& e) {
                return;
            }
            if(isValidPos(newPos) && isEmptyPos(newPos)) {
                animatedPiece = &piece;
                animateFrom = pos;
                animateTo = newPos;
            }
        }
    }
};