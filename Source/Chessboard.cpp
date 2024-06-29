#include "Chessboard.h"
#include "GLFW/glfw3.h" 
#include <cmath>
void Chessboard::LoadShapes() {
    Texture::textures blackSquareTex = Texture::woodCherry;
    Texture::textures whiteSquareTex = Texture::woodLight;
    Texture::textures accentBoardTex = Texture::woodDark;
    Texture::textures blackPieceTex = Texture::woodDark;
    Texture::textures whitePieceTex = Texture::woodLight;


    Material::materials blackSquareMat = Material::paper;
    Material::materials whiteSquareMat = Material::paper;
    Material::materials accentBoardMst = Material::paper;
    Material::materials blackPieceMat = Material::paper;
    Material::materials whitePieceMat = Material::paper;

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.05f, 0.025f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.025f, 0.4125f),
            accentBoardTex, 8, .5,
            accentBoardMst
        )
    );
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.05f, 0.025f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.025f, -0.4125f),
            accentBoardTex, 8, .5,
            accentBoardMst
        )
    );
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.025f, 0.05f, 0.85f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.4125f, 0.025f, 0.0f),
            accentBoardTex, .5, 8.5,
            accentBoardMst
        )
    );
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.025f, 0.05f, 0.85f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-0.4125f, 0.025f, 0.0f),
            accentBoardTex, .5, 8.5,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.85f, 0.025f),
            glm::vec3(-90.0f, 0.0f, 0.0f),
            glm::vec3(-0.425f, 0.025f, 0.425f),
            blackSquareTex, 8, 8,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.85f, 0.025f),
            glm::vec3(-90.0f, 0.0f, 0.0f),
            glm::vec3(0.425f, 0.025f, 0.425f),
            blackSquareTex, 8, 8,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.85f, 0.075f),
            glm::vec3(0.0f, 0.0f, -90.0f),
            glm::vec3(-0.425f, 0.025f, 0.425f),
            blackSquareTex, 8, 8,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.85f, 0.075f),
            glm::vec3(0.0f, 0.0f, -90.0f),
            glm::vec3(-0.425f, 0.025f, -0.425f),
            blackSquareTex, 8, 8,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-0.425f, 0.025f, -0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.425f, 0.025f, -0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-0.425f, 0.025f, 0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.425f, 0.025f, 0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.425f, 0.0f, 0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.425f, 0.0f, -0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-0.425f, 0.0f, -0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.075f, 0.025f, 0.075f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(-0.425f, 0.0f, 0.425f),
            blackSquareTex, 1, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.85f, 0.025f, 1),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0, 0.0125f, 0),
            blackSquareTex, 10, 1,
            accentBoardMst
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(1, 0.02495f, 0.85f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0, 0.0125f, 0),
            blackSquareTex, 10, 1,
            accentBoardMst
        )
    );

    float squareSpacing = 0.1f;
    float squareY = 0.05f;
    glm::vec3 squareScale = glm::vec3(squareSpacing / 2, squareSpacing / 2, squareSpacing / 2);
    glm::vec3 squareRotation = glm::vec3(0.0f, 0.0f, 0.0f);

    // Init loop variables
    int squareID = 0;
    float currX = squareSpacing * 4 * -1 + .05;
    float currZ = squareSpacing * 4 - .05;
    bool isBlack = 1;
    glm::vec3 currPos;
    Shape* currPlane;
    Square currSquare;


    for (int File = 0; File < 8; File++) {//for every file
        for (int square = 0; square < 8; square++) {//create eight squares
            currPos = glm::vec3(currX, squareY, currZ);

            // get textures and materials
            if (isBlack) {
                currSquare.material = blackSquareMat;
                currSquare.texture = blackSquareTex;
            }
            else {
                currSquare.material = whiteSquareMat;
                currSquare.texture = whiteSquareTex;
            }

            // create Square object
            currSquare.location = glm::vec3(currX, squareY, currZ);
            currSquare.piece = nullptr;
            currSquare.plane = new Shape(
                Shape::plane,
                squareScale,// scale
                squareRotation,// rotation
                currSquare.location,// position
                currSquare.texture, 1.0f, 1.0f, // texture
                currSquare.material // material
            );

            // Add data to relevant sections
            AddToObject(currSquare.plane);
            squares[squareID] = currSquare;

            // prepare for next loop
            isBlack = !isBlack;
            currZ -= squareSpacing;
            squareID++;
        }

        // prepare for next row
        isBlack = !isBlack;
        currZ = squareSpacing * 4 - .05;
        currX += squareSpacing;
    }


    kingHeight = 0.1f;
    glm::vec3 currRotation = glm::vec3(0.0f, 180.0f, 0.0f);
    glm::vec3 currHeight = glm::vec3(kingHeight, kingHeight, kingHeight);
    Piece currPiece;
    int count = 0;
    Chessman::variants order[] = {
        Chessman::rook, Chessman::knight ,Chessman::bishop,Chessman::queen,Chessman::king,Chessman::bishop,Chessman::knight,Chessman::rook,
    };
    int orderIndex = 0;

    // load white back rank
    for (int coord = a1; coord <= h1; coord += 8) {
        currPiece.currLocation = squares[coord].location;
        currPiece.chessman = new Chessman(currHeight, currRotation, currPiece.currLocation, Chessman::white, order[orderIndex]);
        orderIndex++;
        currPiece.hasTravel = false;
        AddToObject(currPiece.chessman);
        pieces[count] = currPiece;
        squares[coord].piece = &pieces[count];
        count++;
    }

    // load white pawns
    for (int coord = a2; coord <= h2; coord += 8) {
        currPiece.currLocation = squares[coord].location;
        currPiece.chessman = new Chessman(currHeight, currRotation, currPiece.currLocation, Chessman::white, Chessman::pawn);
        currPiece.hasTravel = false;
        AddToObject(currPiece.chessman);
        pieces[count] = currPiece;
        squares[coord].piece = &pieces[count];
        count++;
    }

    currRotation[1] = 0;
    // load black pawns
    for (int coord = a7; coord <= h7; coord += 8) {
        currPiece.currLocation = squares[coord].location;
        currPiece.chessman = new Chessman(currHeight, currRotation, currPiece.currLocation, Chessman::black, Chessman::pawn);
        currPiece.hasTravel = false;
        AddToObject(currPiece.chessman);
        pieces[count] = currPiece;
        squares[coord].piece = &pieces[count];
        count++;
    }

    orderIndex = 0;
    for (int coord = a8; coord <= h8; coord += 8) {
        currPiece.currLocation = squares[coord].location;
        currPiece.chessman = new Chessman(currHeight, currRotation, currPiece.currLocation, Chessman::black, order[orderIndex]);
        orderIndex++;
        currPiece.hasTravel = false;
        AddToObject(currPiece.chessman);
        pieces[count] = currPiece;
        squares[coord].piece = &pieces[count];
        count++;
    }
}

Chessboard::Chessboard(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
    lastframe = 0.0f;
    movementSpeed = .09f;// reasonable speed
    //movementSpeed = 0.01f; //testing speed

    loadTestGame();

}
void Chessboard::loadTestGame() {
    coordinateIDs moves[] = {
        c2,c3,d7,d5,
        d1,a4,b8,c6,
        a4,h4,g8,f6,
        f2,f3,g7,g5,
        h4,g5,h8,g8,
        g5,h4,e7,e5,
        e1,d1,c8,f5,
        h4,e1,d8,d6,
        d2,d3,a8,d8,/// black ooo
        b1,d2,e5,e4,
        d3,d4,e4,e3
        //d2,b3,d8,e8
        //g2,g4,g8,g4
    };
    int size = sizeof(moves) / sizeof(coordinateIDs);
    std::vector<Turn> turns;

    int blackOOO = 32;
    Turn currTurn;
    for (int i = 0; i < size; i += 4) {
        currTurn = CreateTurn(&squares[moves[i]], &squares[moves[i + 1]], &squares[moves[i + 2]], &squares[moves[i + 3]]);
        if (i == blackOOO) currTurn.blackOOO = true;
        turns.push_back(currTurn);
    }
    this->test = CreateGame(turns);
    
}


Chessboard::Turn Chessboard::CreateTurn(Square* whiteStart, Square* whiteEnd, Square* blackStart, Square* blackEnd) {
    Turn turn;
    turn.whiteStart = whiteStart;
    turn.whiteEnd = whiteEnd;
    turn.blackStart = blackStart;
    turn.blackEnd = blackEnd;
    turn.whiteToMove = true;
    turn.whiteOOO = false;
    turn.whiteOO = false;
    turn.blackOOO = false;
    turn.blackOO = false;

    turn.pieceMoving = false;
    turn.turnEnded = false;
    turn.timeToMoveKing = false;
    turn.currPiece = nullptr;
    return turn;
}

Chessboard::Game Chessboard::CreateGame(std::vector<Turn> turns) {
    Game game;
    game.turnDelay = 0;
    game.turnHappening = false;
    game.currentTurn = 0;
    game.totalTurns = turns.size() - 1;
    game.turns = turns;
    return game;
}

void Chessboard::CreateTravel(Square* start, Square* destination) {
    if (start->piece == nullptr) return;
    Travel travel;
    float stepLength = 1.0f * movementSpeed;
    glm::vec3 startLocation = start->location;
    travel.endSquare = destination;

    float distanceX = travel.endSquare->location[0] - startLocation[0];
    float distanceZ = travel.endSquare->location[2] - startLocation[2];
    float totalDistance = sqrt((distanceX * distanceX) + (distanceZ * distanceZ));
    int stepCount = round(totalDistance / stepLength);
    travel.yMax = totalDistance / 2;
    travel.currY = 0;

    travel.stepX = distanceX / stepCount;
    travel.stepY = totalDistance / stepCount;
    travel.stepZ = distanceZ / stepCount;

    start->piece->hasTravel = true;
    start->piece->travel = travel;
    destination->piece = start->piece;
    start->piece = nullptr;


}

Chessboard::Piece* Chessboard::CreateCapture(Square* square) {
    //if (square->piece == nullptr) return;
    Piece* captured = square->piece;
    square->piece = nullptr;
    return captured;
}

void Chessboard::Animate() {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastframe;
    lastframe = currentFrame;

    // Silly animation
    /*
    if (phaseStep > 10) phaseLogic *= -1;
    if (phaseStep < -50) phaseLogic *= -1;
    phaseStep += phaseLogic;

    float scalestep = phaseLogic * .1;
    this->modifyScale(glm::vec3(scalestep, scalestep, scalestep));

    float positionstep = phaseLogic * .1;
    if (phaseStep < 0) positionstep = 0;
    this->modifyPosition(glm::vec3(positionstep, 0, positionstep));

    float rotationstep = phaseLogic * 10;
    if (phaseStep < 7) this->setRotation(glm::vec3(0, 0, 0));
    else this->modifyRotation(glm::vec3(rotationstep, 0, 0));
    */

    Animate(&test, deltaTime);
}

void Chessboard::Animate(Game* game, float deltaTime) {
    std::cout << game->currentTurn << ":" << game->totalTurns << std::endl;

    if (game->currentTurn > game->totalTurns) return;
    if (game->turns[game->currentTurn].turnEnded) {
        game->currentTurn++;
        if (game->currentTurn > game->totalTurns) return;
    }

    Animate(&(game->turns[game->currentTurn]), deltaTime);
}

void Chessboard::Animate(Turn* turn, float deltaTime) {
    std::cout << "Castling black??? " << turn->blackOOO << std::endl;
    if (turn->turnEnded) return;
    
    
    if (turn->whiteToMove && !turn->pieceMoving && !turn->timeToMoveKing) {//if this is the first run
        std::cout << "Innerloop clear " << std::endl;
        if (turn->whiteOOO) 
        {
            turn->whiteStart = &squares[a1];// white moves queens side rook
            turn->whiteEnd = &squares[d1];
        }
        if (turn->whiteOO) 
        {
            turn->whiteStart = &squares[h1];// white moves kings side rook
            turn->whiteEnd = &squares[f1];
        }
        if (turn->blackOOO) 
        {
            turn->blackStart = &squares[a8];// black moves queens side rook
            turn->blackEnd = &squares[d8];
        }
        if (turn->blackOO) 
        {
            turn->blackStart = &squares[h8];// black moves kings side rook
            turn->blackEnd = &squares[f8];
        }

        std::cout << "pre assign " << std::endl;
        turn->currPiece = turn->whiteStart->piece;// currpiece is white start
        std::cout << "assigned " << std::endl;
    }

    if (turn->currPiece->hasTravel) {// if the piece can move
        Animate(turn->currPiece, deltaTime, turn->currCapture);//move the piece
        return;// and end the method
    }


    // Update logical values.
    if (!turn->pieceMoving) {// if the piece needs to start moving
        turn->currCapture = nullptr;
        if (turn->whiteToMove) {
            if (turn->whiteEnd->piece != nullptr) turn->currCapture = CreateCapture(turn->whiteEnd);
            CreateTravel(turn->whiteStart, turn->whiteEnd);
        }
        else {
            if (turn->blackEnd->piece != nullptr) turn->currCapture = CreateCapture(turn->blackEnd);
            CreateTravel(turn->blackStart, turn->blackEnd);
        }
        turn->pieceMoving = true;
    }

    
    else {// if the piece has completed its travel
        turn->pieceMoving = false;// 
        if (turn->whiteToMove) {//if white is done
            if (!turn->whiteOOO && !turn->whiteOO) {// and if we're not castling
                turn->whiteToMove = false;// it's black's turn
                turn->currPiece = turn->blackStart->piece;
            }
            else if(!turn->timeToMoveKing) {
                turn->timeToMoveKing = true; // else we start moving the king
                turn->currPiece = squares[e1].piece; // currpiece is the white king
                if (turn->whiteOOO) CreateTravel(&squares[e1], &squares[c1]);// give the king a queenside travel
                else CreateTravel(&squares[e1], &squares[g1]);// give the king a kingside travel
            }
            else {// else we've already moved the king, so it's black's turn
                turn->whiteToMove = false;
                turn->timeToMoveKing = false;
            }

        }
        else {// if black is done
            if (!turn->blackOOO && !turn->blackOO) {// and if we're not castling
                turn->turnEnded = true;// the turn is over
            }
            else if (!turn->timeToMoveKing) { // else we start moving the king
                turn->timeToMoveKing = true; // else we start moving the king
                turn->currPiece = squares[e8].piece;// currpiece is the black king
                if (turn->blackOOO) CreateTravel(&squares[e8], &squares[c8]);// give the king a queenside travel
                else CreateTravel(&squares[e8], &squares[g8]);// give the king a kingside travel
            }
            else {// else we've already moved the king, so the turn is over
                turn->turnEnded = true;// the turn is over
                turn->timeToMoveKing = false;
            }
        }
    }
    


}

void Chessboard::Animate(Piece* piece, float deltaTime, Piece* capture) {
    Travel* travel = &(piece->travel);

    float x = travel->stepX * deltaTime;
    float y = travel->stepY * deltaTime;
    float z = travel->stepZ * deltaTime;

    travel->currY += y;

    if (travel->currY > travel->yMax) y *= -1;
    if (travel->currY > (travel->yMax) * 2) {
        piece->hasTravel = false;
        piece->chessman->setPosition(travel->endSquare->location);
        if (capture != nullptr) capture->chessman->setScale(glm::vec3(0, 0, 0));
        travel->endSquare->piece = piece;
        return;
    }

    piece->currLocation[0] += x;
    piece->currLocation[1] += y;
    piece->currLocation[2] += z;
    if (capture != nullptr) capture->chessman->modifyScale(glm::vec3(-(kingHeight * 0.1), -(kingHeight * 0.1), -(kingHeight * 0.1)));
    piece->chessman->modifyPosition(glm::vec3(x, y, z));
}