#pragma once
#include "Object.h"
class Chessboard : public Object
{
    float kingHeight;
    virtual void LoadShapes();
    struct Square;
    struct Travel {
        float stepX;
        float stepY;
        float stepZ;
        float currY;
        float yMax;
        float totalTravel;
        Square* endSquare;
    };
    struct Piece {
        Chessman* chessman;
        glm::vec3 currLocation;
        bool hasTravel;
        Travel travel;
    };

    static enum pieceIDs {
        whiteRookQueens, whiteKnightQueens, whiteBishopQueens, whiteQueen, whiteKing, whiteBishopKings, whiteKnightKings, whiteRookKings,
        whitePawnA, whitePawnB, whitePawnC, whitePawnD, whitePawnE, whitePawnF, whitePawnG, whitePawnH,
        blackPawnA, blackPawnB, blackPawnC, blackPawnD, blackPawnE, blackPawnF, blackPawnG, blackPawnH,
        blackRookQueens, blackKnightQueens, blackBishopQueens, blackQueen, blackKing, blackBishopKings, blackKnightKings, blackRookKings
    };
    Piece pieces[32];

    struct Square {
        glm::vec3 location;
        Shape* plane;
        Piece* piece;
        Material::materials material;
        Texture::textures texture;
    };

    static enum coordinateIDs {
        a1, a2, a3, a4, a5, a6, a7, a8,
        b1, b2, b3, b4, b5, b6, b7, b8,
        c1, c2, c3, c4, c5, c6, c7, c8,
        d1, d2, d3, d4, d5, d6, d7, d8,
        e1, e2, e3, e4, e5, e6, e7, e8,
        f1, f2, f3, f4, f5, f6, f7, f8,
        g1, g2, g3, g4, g5, g6, g7, g8,
        h1, h2, h3, h4, h5, h6, h7, h8
    };

    Square squares[64] = {};

    struct Turn {
        bool whiteToMove;
        bool pieceMoving;
        bool timeToMoveKing;
        bool turnEnded;

        bool whiteOOO;// queenside castle
        bool whiteOO;// kingside castle
        Square* whiteStart;
        Square* whiteEnd;

        bool blackOOO;// queenside castle
        bool blackOO;// kingside castle
        Square* blackStart;
        Square* blackEnd;

        Piece* currPiece;
        Piece* currCapture;
    };

    struct Game
    {
        std::vector<Turn> turns;
        int currentTurn;
        bool turnHappening;
        float turnDelay;
        int totalTurns;
    };

    Game currentGame;
    bool gameHappening;
    float gameDelay;
    float movementSpeed;

    float lastframe;


    int phaseLogic = 1;
    int phaseStep = 0;


    void Animate(Game* game, float deltaTime);
    void Animate(Turn* turn, float deltaTime);
    void Animate(Piece* piece, float deltaTime, Piece* capture = nullptr);
    
    
    Game CreateGame(std::vector<Turn> turns);
    Turn CreateTurn(Square* whiteStart, Square* whiteEnd, Square* blackStart, Square* blackEnd);
    void CreateTravel(Square* start, Square* destination);
    Piece* CreateCapture(Square* square);

    Game test;
    void loadTestGame();
public:
    Chessboard(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    void Animate();
};
