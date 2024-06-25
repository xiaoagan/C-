//
// Created by 宁程 on 2024/6/23.
//

#include <iostream>
#include <conio.h>
#include "ChessGame.h"
using namespace std;


ChessGame::ChessGame(Man *players, Chess *chess) {
    for (int i = 0; i < 3; i++) {
        this->players[i] = players[i];
        this->players[i].init(chess);
    }
    this->chess = chess;
}


//开始游戏
void ChessGame::play() {
    chess->init();  //棋盘初始化
    chess_kind_t kinds[] = {CHESS_BLACK, CHESS_WHITE, CHESS_BLUE};
    while (true) {
        //cout << "Current player:" << kinds[currentPlayerIndex] << endl;
        // 显示当前玩家编号和棋子颜色
        cout << "Current player " << currentPlayerIndex + 1 << ": ";
        switch (kinds[currentPlayerIndex]) {
            case CHESS_BLACK:
                cout << "Black";
                break;
            case CHESS_WHITE:
                cout << "White";
                break;
            case CHESS_BLUE:
                cout << "Blue";
                break;
        }
        cout << endl;
        //现由棋手走棋
        players[currentPlayerIndex].go(kinds[currentPlayerIndex]);
        if(chess->checkOver()) {
            cout <<"player" << currentPlayerIndex + 1 << " Wins! " << endl;
            int x = 0, y = 207;
            switch (kinds[currentPlayerIndex]) {
                case CHESS_BLACK:
                    putimage(x, y, &chess->winBlackImg);
                    break;
                case CHESS_WHITE:
                    putimage(x, y, &chess->winWhiteImg);
                    break;
                case CHESS_BLUE:
                    putimage(x, y, &chess->winBlueImg);
                    break;
            }
            _getch();
            break;
        }

        //切换到下一个玩家
        currentPlayerIndex = (currentPlayerIndex + 1) % 3;

    }
}
