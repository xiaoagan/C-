//
// Created by N on 2024/6/23.
//

#ifndef WUZIQI_CHESSGAME_H
#define WUZIQI_CHESSGAME_H

#include "Man.h"
#include "Chess.h"

class ChessGame {
public:
    ChessGame(Man players[3], Chess* chess);
    void play();    //开始对局

//添加数据成员
private:
    Man players[3];
    Chess* chess;
    int currentPlayerIndex = 0;     //当前玩家索引
};

#endif //WUZIQI_CHESSGAME_H
