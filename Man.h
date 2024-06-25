//
// Created by 宁程 on 2024/6/23.
//

#ifndef WUZIQI_MAN_H
#define WUZIQI_MAN_H

#include "Chess.h"


class Man {
public:
    void init(Chess* chess);
    void go(chess_kind_t kind0);

private:
    Chess *chess;       //添加棋盘成员
};



#endif //WUZIQI_MAN_H
