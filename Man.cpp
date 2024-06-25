//
// Created by 宁程 on 2024/6/23.
//

#include "Man.h"
#include <cstdio>


void Man::init(Chess *chess) {
    this->chess = chess;

}

void Man::go(chess_kind_t kind) {
    MOUSEMSG msg;       //获取鼠标点击信息
    ChessPos pos;

    while(true) {
        //获取鼠标点击消息
        msg = GetMouseMsg();

        //通过chess对象，来调用判断落子是否有效，以及落子功能
        if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
            break;
        }
    }

    printf("%d, %d\n", pos.row, pos.col);
    //落子
    chess->chessDown(&pos, kind);


}
