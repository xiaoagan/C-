#include "ChessGame.h"
#include "Chess.h"
#include <iostream>

int main() {
    Man man;
    Chess chess(14, 27, 27, 40 );
    ChessGame game(&man, &chess);
    cout << " game begin!" << endl;

    game.play();


    return 0;
}
