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
    Piece *eatenPiece;
    std::array<size_t,2> animateFrom;
    std::array<size_t,2> animateTo;
    int pieceAnimStartTime;

    int camAnimStartTime;
    int camAnimAngle;
    int lastCamAnimAngle;

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

        for(size_t j = 0; j < 8; j++) {
            for(size_t i = 0; i < 8; i++) {
                Square &square = board[i][j];
                bool shouldGlowAdjacent = 
                    abs((double)i - activePcPos[0]) == 1 && 
                    abs((double)j - activePcPos[1]) == 1 &&
                    square.get_pcAlloc() == NA;
                bool shouldGlowEating = 
                    abs((double)i - activePcPos[0]) == 2 && 
                    abs((double)j - activePcPos[1]) == 2 &&
                    square.get_pcAlloc() == NA &&
                    board[(i + activePcPos[0])/2][(j + activePcPos[1])/2]
                        .get_pcAlloc() == (getTurn() == DARK_TURN ? LIGHT_PIECE : DARK_PIECE);
                square.render(shouldGlowAdjacent || shouldGlowEating);
            }
        }
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

    std::array<size_t,2> calcNewPos(std::array<size_t,2> pos, MoveDirection direction) {
        switch (direction) {
        case UP_LEFT:   return getTurn() == DARK_TURN ? std::array{pos[0] - 1, pos[1] - 1} : std::array{pos[0] + 1, pos[1] + 1};
        case UP_RIGHT:  return getTurn() == DARK_TURN ? std::array{pos[0] + 1, pos[1] - 1} : std::array{pos[0] - 1, pos[1] + 1};
        case DOWN_LEFT: return getTurn() == DARK_TURN ? std::array{pos[0] - 1, pos[1] + 1} : std::array{pos[0] + 1, pos[1] - 1};
        case DOWN_RIGHT:return getTurn() == DARK_TURN ? std::array{pos[0] + 1, pos[1] + 1} : std::array{pos[0] - 1, pos[1] - 1};
        default: throw;
        }
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
        std::vector<Piece> &opponentPieces = getTurn() == DARK_TURN ? lightPieces : darkPieces;
        if(opponentPieces.empty())
            turnCounter += 2;
        else
            turnCounter++;
    }

    void animateCam() {
        if(camAnimAngle == -1) return;

        const int t = glutGet(GLUT_ELAPSED_TIME);
        const int animationPeriod = 750;
        if(camAnimStartTime == -1 || camAnimAngle != lastCamAnimAngle) camAnimStartTime = t;
        lastCamAnimAngle = camAnimAngle;
        double animationPercent = (double) (t - camAnimStartTime)/animationPeriod;

        cam.translate((-0.2 * cos(2 * M_PI * animationPercent) + 0.2) * (camAnimAngle - cam.get_pathAngle()));
        if(t >= (camAnimStartTime + animationPeriod)) {
            cam.set_pathAngle(camAnimAngle);
            camAnimAngle = -1;
            camAnimStartTime = -1;
        }
    }

    void animateMove() {
        // std::cout << animatedPiece << std::endl;
        if(animatedPiece == NULL) return;

        Square &orgSquare = board[animateFrom[0]][animateFrom[1]];
        Square &destSquare = board[animateTo[0]][animateTo[1]];

        const int t = glutGet(GLUT_ELAPSED_TIME);
        const int animationPeriod = 500;
        if(pieceAnimStartTime == -1) pieceAnimStartTime = t;
        double animationPercent = (double) (t - pieceAnimStartTime)/animationPeriod;
        double yMax = 1.5;

        double xDiff = destSquare.get_x() - orgSquare.get_x();
        double zDiff = destSquare.get_z() - orgSquare.get_z();
        animatedPiece->set_x(orgSquare.get_x() + (xDiff * animationPercent));
        animatedPiece->set_z(orgSquare.get_z() + (zDiff * animationPercent));
        animatedPiece->set_y(yMax * sin(M_PI * animationPercent));
        if(t >= (pieceAnimStartTime + animationPeriod)) {
            //Set final positions
                animatedPiece->set_x(destSquare.get_x());
                animatedPiece->set_z(destSquare.get_z());
                animatedPiece->set_y(0);
            //Update location info
                orgSquare.set_pcAlloc(NA);
                animatedPiece->set_posOnBoard(animateTo);
                destSquare.set_pcAlloc(animatedPiece->get_pcType());
            //Clear piece animation data
                animatedPiece = nullptr;
                pieceAnimStartTime = -1;
            //Delete eaten piece, if any, otherwise finish turn
            if(eatenPiece != NULL) {
                const std::array<size_t,2> &eatenPiecePos = eatenPiece->get_posOnBoard();
                board[eatenPiecePos[0]][eatenPiecePos[1]].set_pcAlloc(NA);

                std::vector<Piece> &opponentPieces = getTurn() == DARK_TURN ? lightPieces : darkPieces;
                Selector &opponentSelector = getTurn() == DARK_TURN ? lightPieceSelector : darkPieceSelector;
                for(auto it = opponentPieces.begin(); it != opponentPieces.end(); it++) {
                    if(&*it == eatenPiece) {
                        opponentPieces.erase(it);
                        break;
                    }
                }
                opponentSelector.set_size(opponentPieces.size());
                eatenPiece = nullptr;
            } else {
                nextTurn();
                camAnimAngle = getTurn() == DARK_TURN ? 90 : 270;
            }
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
        eatenPiece = nullptr;
        animateFrom = {0, 0};
        animateTo = {0, 0};
        pieceAnimStartTime = -1;

        camAnimAngle = -1;
        camAnimStartTime = -1;
        lastCamAnimAngle = camAnimAngle;

        cam = CircularCamera(camXZpathRadius, camYheight);
    }

    CheckersTurn getTurn() {
        return (turnCounter % 2 == 0) ? DARK_TURN : LIGHT_TURN;
    }

    void render() {
        animateMove();
        animateCam();
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
            std::array<size_t,2> eatenPos = newPos;
            try {
                newPos = calcNewPos(eatenPos, direction);
            } catch(const std::exception& e) {
                return;
            }
            if(isValidPos(newPos) && isEmptyPos(newPos)) {
                animatedPiece = &piece;
                std::vector<Piece> &opponentPieces = getTurn() == DARK_TURN ? lightPieces : darkPieces;
                for(Piece &piece : opponentPieces) {
                    if(piece.get_posOnBoard() == eatenPos) {
                        eatenPiece = &piece; break; 
                    }
                }
                animateFrom = pos;
                animateTo = newPos;
            }
        }
    }
};