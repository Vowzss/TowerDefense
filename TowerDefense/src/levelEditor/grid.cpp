#include "grid.hpp"


using namespace myMath;
using namespace collision;
using namespace GameTextures;
using namespace GameSounds;


int Grid::GridCell(Vec2 pos)
{
    if(pos.x >= 0 && pos.x < gridWidth && pos.y >= 0 && pos.y < gridHeight)
    {
        return dataGrid[(int)pos.x][(int)pos.y];
    }else
    {
        if((pos.x == -1 && pos.y < gridHeight + 1) ||
         (pos.y == -1 && pos.x < gridWidth + 1) ||
          (pos.x == gridWidth&& pos.y < gridHeight + 1) ||
           (pos.y == gridHeight&& pos.x < gridWidth + 1))
            return -1;
        else
            return -2;
    }
}

void Grid::UpdateSprite(myMath::Vec2 pos, bool randomizeGrass)
{
    if(GridCell(pos) < 0)
    {
        return;
    }
    if(GridCell(pos) == 1)
    {
        int links = 0;
        Vec2 neighbours[8] = {Vec2{0, 1}, Vec2{1, 0}, Vec2{0, -1}, Vec2{-1, 0},
        Vec2{1, 1}, Vec2{1, -1}, Vec2{-1, -1}, Vec2{-1, 1}};

        for (int i = 0; i < 8; i++)
        {
            if(GridCell(pos + neighbours[i]) == -1 || GridCell(pos + neighbours[i]) == 1)
                links += myMath::pow(10, i);
        }
        switch(links % 10000)
        {
            case        0 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(3, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case        1 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(3, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case       10 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case      100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(3, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case      101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(3, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case     1000 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case     1010 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
        }
        switch(links)
        {
            case       11 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case      110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case      111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case     1111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    10011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    10110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    10111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case    11111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(9, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   100011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   100110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   100111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   101111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(9, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   110011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   110110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   110111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case   111111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1000011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1000110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1000111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1001111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(10,3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1010011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1010110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1010111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1011111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(9, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1100011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1100110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1100111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1101111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1110011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1110110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1110111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case  1111111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10000011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10000110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10000111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10001111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(10,2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10010011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10010110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10010111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10011111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(8, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10100011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10100110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10100111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10101111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(9, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10110011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10110110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10110111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(7, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 10111111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(6, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11000011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11000110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11000111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11001111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 4) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11010011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11010110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11010111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 3) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11011111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11100011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11100110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11100111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(4, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11101111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(5, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11110011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11110110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11110111 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111001 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111011 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 0) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111100 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111101 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(2, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            case 11111110 : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
            default : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(1, 5) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); break;
        }
    }else if(GridCell(pos) == 0)
    {
        if(randomizeGrass)
        {
            spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(Clamp((rand() % 16) - 7, 0, 4), 5) + mBiomeOffset, tileSet,
            Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); 
        }else
        {
            spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(0, 5) + mBiomeOffset, tileSet,
            Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2));
        }
    }else if(GridCell(pos) >= 2 && GridCell(pos) <= 10)
    {
        spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(GridCell(pos) + 7, 4) + mBiomeOffset, tileSet,
        Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
        
    }else if(GridCell(pos) > 10)
    {
        switch(GridCell(pos))
        {
            case(11) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(12, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(12) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(13, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(13) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(12, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(14) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(13, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(15) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(15, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(16) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(16, 1) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(17) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(15, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
            case(18) : spriteGrid[(int)pos.x][(int)pos.y] = Sprite(Vec2(16, 2) + mBiomeOffset, tileSet, Vec2(36, 21), Vec2(caseSize / 2, caseSize / 2)); return;
        }
    }
}

void Grid::PutTree(Vec2 pos)
{
    if(GridCell(pos) == 16 || GridCell(pos) == 17 || GridCell(pos) == 11)
    {
        return;
    }

    if(GridCell(pos) == 18 || GridCell(pos) == 12 || GridCell(pos) == 13)
    {
        dataGrid[(int)pos.x][(int)pos.y] = 12;
    }
    else
    {
        dataGrid[(int)pos.x][(int)pos.y] = 15;
    }

    if(GridCell(pos + Vec2(1, 0)) == 17 || GridCell(pos + Vec2(1, 0)) == 11 ||  GridCell(pos + Vec2(1, 0)) == 14)
    {
        dataGrid[(int)pos.x + 1][(int)pos.y] = 11;
    }
    else
    {
        dataGrid[(int)pos.x + 1][(int)pos.y] = 16;
    }

    if(GridCell(pos + Vec2(0, 1)) == 16 || GridCell(pos + Vec2(0, 1)) == 11)
    {
        if(GridCell(pos + Vec2(1, 1)) == 15 || GridCell(pos + Vec2(1, 1)) == 12)
        {
            if(!(GridCell(pos + Vec2(1, 2)) == 11 || GridCell(pos + Vec2(0, 2)) == 12))
            {
                dataGrid[(int)pos.x][(int)pos.y + 2] = 13;
                dataGrid[(int)pos.x + 1][(int)pos.y + 2] = 14;
            }
        }
        dataGrid[(int)pos.x][(int)pos.y + 1] = 11;
    }
    else
    {
        if(GridCell(pos + Vec2(-1, 0)) == 11)
        {
            dataGrid[(int)pos.x][(int)pos.y + 1] = 14;
            dataGrid[(int)pos.x - 1][(int)pos.y + 1] = 13;
        }else
        {
            dataGrid[(int)pos.x][(int)pos.y + 1] = 17;
        }
    }

    if(GridCell(pos + Vec2(1, 1)) == 15 || GridCell(pos + Vec2(1, 1)) == 12)
    {
        dataGrid[(int)pos.x + 1][(int)pos.y + 1] = 12;
    }
    else
    {
        if(GridCell(pos + Vec2(2, 0)) == 12)
        {
            dataGrid[(int)pos.x + 1][(int)pos.y + 1] = 13;
            dataGrid[(int)pos.x + 2][(int)pos.y + 1] = 14;
        }else
        {
            dataGrid[(int)pos.x + 1][(int)pos.y + 1] = 18;
        } 
    }

}

