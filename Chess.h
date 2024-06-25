//
// Created by N on 2024/6/23.
//

#include <graphics.h>
#include <vector>
using namespace std;

#ifndef WUZIQI_CHESS_H
#define WUZIQI_CHESS_H



struct ChessPos {
    int row;
    int col;
};

typedef enum{
    CHESS_BLACK = 1,    //黑棋
    CHESS_WHITE = 2,   //白棋
    CHESS_BLUE = 3,     //蓝棋
}chess_kind_t;

class Chess {

    friend class ChessGame;

public:
    Chess(int gradeSize, int marginX, int marginY, float chessSize);
    void init();

    Chess();

    bool clickBoard(int x, int y, ChessPos* pos);       //是否点击棋盘
    void chessDown(ChessPos *Pos, chess_kind_t kind);
    //void printBoard();      //声明打印棋盘的成员函数

    bool checkOver();

private:
    IMAGE chessBlackImg;    //黑色棋子
    IMAGE chessWhiteImg;    //白棋棋子
    IMAGE chessBlueImg;    //蓝棋棋子
    IMAGE winWhiteImg;      //白棋胜利图片
    IMAGE winBlackImg;      //黑棋胜利图片
    IMAGE winBlueImg;       //蓝棋胜利图片

    int gradeSize;          //棋盘大小（13， 15， 17， 19）
    int margin_x;           //棋盘的左侧边界
    int margin_y;           //期盼的上侧边界
    float chessSize;        //棋子大小


    //存储当前棋局的棋子分布数据
    //chessMAP[3][5] 表示棋盘的第3行第5列的落子情况 0：空白 1:黑子 -1：白子
    vector<vector<int>> chessMap;



    void updateGameMap(ChessPos* pos, chess_kind_t kind);
};



#endif //WUZIQI_CHESS_H
