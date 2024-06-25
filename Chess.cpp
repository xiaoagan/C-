//
// Created by N on 2024/6/23.
//
#include <iostream>
#include "Chess.h"
#include <math.h>
#include <mmsyscom.h>
#include <iomanip>

using namespace std;

void putimagePNG(int x, int y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
    // 变量初始化
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                             | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize) {
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;

    for (int i = 0; i < gradeSize; i++) {
        vector<int> row;
        for (int j = 0; j < gradeSize; j++) {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}


void Chess::init() {
    //创建游戏窗口
    initgraph(615, 615, EW_SHOWCONSOLE);

    //显示棋盘图片
    loadimage(0, "E:/learn/code/C++/wuziqi/resource/qipan.png");

    //加载黑棋和白棋棋子图片
    loadimage(&chessBlackImg, "E:/learn/code/C++/wuziqi/resource/storn_black.png");
    loadimage(&chessWhiteImg, "E:/learn/code/C++/wuziqi/resource/storn_white.png");
    loadimage(&chessBlueImg, "E:/learn/code/C++/wuziqi/resource/storn_bule.png");
    loadimage(&winBlackImg, "E:/learn/code/C++/wuziqi/resource/black_win.png");
    loadimage(&winWhiteImg, "E:/learn/code/C++/wuziqi/resource/white_win.png");
    loadimage(&winBlueImg, "E:/learn/code/C++/wuziqi/resource/bule_win.png");

    //棋盘清零
    for (int i=0; i < gradeSize; i++) {
        for (int j=0; j < gradeSize; j++) {
            chessMap[i][j] = 0;
        }
    }


}

bool Chess::clickBoard(int x, int y, ChessPos *pos) {
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.4;

    int len;
    bool ret = false;

    do {
        //左上角判断
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col;
            if(chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        // 距离右上角的距离
        len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        // 距离左下角的距离
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

        // 距离右下角的距离
        len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col + 1;

            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }


    } while (0);

    return ret;


}

void Chess::chessDown(ChessPos *Pos, chess_kind_t kind) {

    int x = margin_x + chessSize * Pos->col - 0.5 * chessSize;
    int y = margin_y + chessSize * Pos->row - 0.5 * chessSize;

    if (kind == CHESS_WHITE) {
        putimagePNG(x, y, &chessWhiteImg);
    }
    else if (kind == CHESS_BLUE) {
        putimagePNG(x, y, &chessBlueImg);
    }
    else if (kind == CHESS_BLACK) {
        putimagePNG(x, y, &chessBlackImg);
    }

    updateGameMap(Pos, kind);
    cout << " Piece placed at " << Pos->row << "," << Pos->col << " by player " << kind  << endl;
}

bool Chess::checkOver() {
    //int n = gradeSize;
    //vector<vector<int>>& board = chessMap;
    //printBoard();
    int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}}; // 检查四个方向：水平、垂直、两个对角线
    for (int r = 0; r < gradeSize; r++) {
        for (int c = 0; c < gradeSize; c++) {
            if (chessMap[r][c] == 0) continue; // 如果当前位置是空的，跳过

            int piece = chessMap[r][c]; // 当前棋子类型
            for (auto& dir : directions) {
                int count = 1; // 当前位置已有1棋子

                // 向正方向检查
                int nr = r + dir[0], nc = c + dir[1];
                while (nr >= 0 && nr < gradeSize && nc >= 0 && nc < gradeSize && chessMap[nr][nc] == piece) {
                    count++;
                    nr += dir[0];
                    nc += dir[1];
                }

                // 向反方向检查
                nr = r - dir[0];
                nc = c - dir[1];
                while (nr >= 0 && nr < gradeSize && nc >= 0 && nc < gradeSize && chessMap[nr][nc] == piece) {
                    count++;
                    nr -= dir[0];
                    nc -= dir[1];
                }

                // 调试输出
                //cout << "Checked from (" << r << "," << c << ") in direction (" << dir[0] << "," << dir[1] << ") count: " << count << endl;

                // 如果计数达到5，则当前棋子赢得比赛
                if (count >= 5) {
                    cout << "Win detected starting at (" << r << "," << c << ") in direction (" << dir[0] << "," << dir[1] << ") with count " << count << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

void Chess::updateGameMap(ChessPos *pos, chess_kind_t kind) {
    chessMap[pos->row][pos->col] = kind;
}
/*
void Chess::printBoard() {
    cout << "Current chess board:" << endl;
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            // 检查当前位置的棋子类型并打印
            if (chessMap[i][j] == 1) {
                cout << setw(3) << "B";  // 黑棋用'B'表示
            } else if (chessMap[i][j] == -1) {
                cout << setw(3) << "W";  // 白棋用'W'表示
            } else if (chessMap[i][j] == 2) {
                cout << setw(3) << "U";  // 蓝棋用'U'表示（U for Blue）
            } else {
                cout << setw(3) << ".";  // 空位置用'.'表示
            }
        }
        cout << endl; // 每行结束后换行
    }
}
*/
