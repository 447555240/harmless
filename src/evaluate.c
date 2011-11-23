#include "evaluate.h"

BYTE piece_type[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6,
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6
};

/* 棋子价值数组 */
static BYTE position_values[2][7][256] =
{
	{
		{ /* 红帅 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 10, 10, 10,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 15, 20, 15,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红仕 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 30,  0, 30,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0, 22,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 30,  0, 30,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红相 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 25,  0,  0,  0, 25,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 20,  0,  0,  0, 35,  0,  0,  0, 20,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 30,  0,  0,  0, 30,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红马 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 70, 80, 90, 80, 70, 80, 90, 80, 70,  0,  0,  0,  0,
			0,  0,  0, 80,110,125, 90, 70, 90,125,110, 80,  0,  0,  0,  0,
			0,  0,  0, 90,100,120,125,120,125,120,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100,120,130,110,130,120,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,110,110,120,100,120,110,110, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100,100,110,100,110,100,100, 90,  0,  0,  0,  0,
			0,  0,  0, 80, 90,100,100, 90,100,100, 90, 80,  0,  0,  0,  0,
			0,  0,  0, 80, 80, 90, 90, 80, 90, 90, 80, 80,  0,  0,  0,  0,
			0,  0,  0, 70, 75, 75, 70, 50, 70, 75, 75, 70,  0,  0,  0,  0,
			0,  0,  0, 60, 70, 75, 70, 60, 70, 75, 70, 60,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红车 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,160,170,160,150,150,150,160,170,160,  0,  0,  0,  0,
			0,  0,  0,170,180,170,190,250,190,170,180,170,  0,  0,  0,  0,
			0,  0,  0,170,190,200,220,240,220,200,190,170,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,170,190,180,220,240,220,200,190,170,  0,  0,  0,  0,
			0,  0,  0,170,180,170,170,160,170,170,180,170,  0,  0,  0,  0,
			0,  0,  0,160,170,160,160,150,160,160,170,160,  0,  0,  0,  0,
			0,  0,  0,150,160,150,160,150,160,150,160,150,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红炮 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,125,130,100, 70, 60, 70,100,130,125,  0,  0,  0,  0,
			0,  0,  0,110,125,100, 70, 60, 70,100,125,110,  0,  0,  0,  0,
			0,  0,  0,100,120, 90, 80, 80, 80, 90,120,100,  0,  0,  0,  0,
			0,  0,  0, 90,110, 90,110,130,110, 90,110, 90,  0,  0,  0,  0,
			0,  0,  0, 90,110, 90,110,130,110, 90,110, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100, 90,110,130,110, 90,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100, 90, 90,110, 90, 90,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100, 80, 80, 70, 80, 80,100, 90,  0,  0,  0,  0,
			0,  0,  0, 80, 90, 80, 70, 65, 70, 80, 90, 80,  0,  0,  0,  0,
			0,  0,  0, 80, 90, 80, 70, 60, 70, 80, 90, 80,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 红兵 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 10, 10, 10, 20, 25, 20, 10, 10, 10,  0,  0,  0,  0,
			0,  0,  0, 25, 30, 40, 50, 60, 50, 40, 30, 25,  0,  0,  0,  0,
			0,  0,  0, 25, 30, 30, 40, 40, 40, 30, 30, 25,  0,  0,  0,  0,
			0,  0,  0, 20, 25, 25, 30, 30, 30, 25, 25, 20,  0,  0,  0,  0,
			0,  0,  0, 15, 20, 20, 20, 20, 20, 20, 20, 15,  0,  0,  0,  0,
			0,  0,  0, 10,  0, 15,  0, 15,  0, 15,  0, 10,  0,  0,  0,  0,
			0,  0,  0, 10,  0, 10,  0, 15,  0, 10,  0, 10,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}
	},
	{
		{ /* 黑将 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 15, 20, 15,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 10, 10, 10,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑士 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 30,  0, 30,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0, 22,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0, 30,  0, 30,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑象 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 30,  0,  0,  0, 30,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 20,  0,  0,  0, 35,  0,  0,  0, 20,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0, 25,  0,  0,  0, 25,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑马 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 60, 70, 75, 70, 60, 70, 75, 70, 60,  0,  0,  0,  0,
			0,  0,  0, 70, 75, 75, 70, 50, 70, 75, 75, 70,  0,  0,  0,  0,
			0,  0,  0, 80, 80, 90, 90, 80, 90, 90, 80, 80,  0,  0,  0,  0,
			0,  0,  0, 80, 90,100,100, 90,100,100, 90, 80,  0,  0,  0,  0,
			0,  0,  0, 90,100,100,110,100,110,100,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,110,110,120,100,120,110,110, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100,120,130,110,130,120,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100,120,125,120,125,120,100, 90,  0,  0,  0,  0,
			0,  0,  0, 80,110,125, 90, 70, 90,125,110, 80,  0,  0,  0,  0,
			0,  0,  0, 70, 80, 90, 80, 70, 80, 90, 80, 70,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑车 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,150,160,150,160,150,160,150,160,150,  0,  0,  0,  0,
			0,  0,  0,160,170,160,160,150,160,160,170,160,  0,  0,  0,  0,
			0,  0,  0,170,180,170,170,160,170,170,180,170,  0,  0,  0,  0,
			0,  0,  0,170,190,200,220,240,220,180,190,170,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,180,220,210,240,250,240,210,220,180,  0,  0,  0,  0,
			0,  0,  0,170,190,200,220,240,220,200,190,170,  0,  0,  0,  0,
			0,  0,  0,170,180,170,190,250,190,170,180,170,  0,  0,  0,  0,
			0,  0,  0,160,170,160,150,150,150,160,170,160,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑炮 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 80, 90, 80, 70, 60, 70, 80, 90, 80,  0,  0,  0,  0,
			0,  0,  0, 80, 90, 80, 70, 65, 70, 80, 90, 80,  0,  0,  0,  0,
			0,  0,  0, 90,100, 80, 80, 70, 80, 80,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100, 90, 90,110, 90, 90,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,100, 90,110,130,110, 90,100, 90,  0,  0,  0,  0,
			0,  0,  0, 90,110, 90,110,130,110, 90,110, 90,  0,  0,  0,  0,
			0,  0,  0, 90,110, 90,110,130,110, 90,110, 90,  0,  0,  0,  0,
			0,  0,  0,100,120, 90, 80, 80, 80, 90,120,100,  0,  0,  0,  0,
			0,  0,  0,110,125,100, 70, 60, 70,100,125,110,  0,  0,  0,  0,
			0,  0,  0,125,130,100, 70, 60, 70,100,130,125,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		},
		{ /* 黑卒 */
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0, 10,  0, 10,  0, 15,  0, 10,  0, 10,  0,  0,  0,  0,
			0,  0,  0, 10,  0, 15,  0, 15,  0, 15,  0, 10,  0,  0,  0,  0,
			0,  0,  0, 15, 20, 20, 20, 20, 20, 20, 20, 15,  0,  0,  0,  0,
			0,  0,  0, 20, 25, 25, 30, 30, 30, 25, 25, 20,  0,  0,  0,  0,
			0,  0,  0, 25, 30, 30, 40, 40, 40, 30, 30, 25,  0,  0,  0,  0,
			0,  0,  0, 25, 30, 40, 50, 60, 50, 40, 30, 25,  0,  0,  0,  0,
			0,  0,  0, 10, 10, 10, 20, 25, 20, 10, 10, 10,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
			0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
		}
	}
};

int evaluate()
{
    int i,j,k,r;
    
    BYTE p, next, m;
    
    int side_tag;
    int over_flag;

    /* 红(r)、黑(b)棋子价值分量 */
    short r_value, b_value;
    
    /* 红[0]、黑[1]棋子灵活度分量 */
    short flexible[2] = {0, 0};

    r_value = b_value = 0;

    for (i = 16; i < 32; i++) {
        if (piece[i] > 0)
            r_value += position_values[0][piece_type[i]][piece[i]];
    }

    for (i = 32; i < 48; i++) {
        if (piece[i] > 0)
            b_value += position_values[1][piece_type[i]][piece[i]];
    }

    for (r = 0; r <= 1; r++) {
        side_tag = 16 + 16 * r;

        /* 将(帅)的灵活性 */
        p = piece[side_tag];
        
        for (k = 0; k < 4; k++) {
            next = p + king_dir[k];

            if (legal_position[r][next] & position_mask[KING]) {
                /* 目标位置上没有本方棋子 */
                if (!(board[next] & side_tag))
                    flexible[r] += F_KING;
            }
        }

        /* 士(仕)的灵活性 */
        for (i = 1; i <= 2; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 4; k++) {
                next = p + advisor_dir[k];
                                
                if (legal_position[r][next] & position_mask[ADVISOR]) {

                    if (!(board[next] & side_tag))
                        flexible[r] += F_ADVISOR;
                }
            }
        }

        /* 象(相)的灵活性 */
        for (i = 3; i <= 4; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 4; k++) {
                next = p + bishop_dir[k];

                if (legal_position[r][next] & position_mask[BISHOP]) {
                    m = p + bishop_check[k];
                                        
                    if (!board[m]) {
                        if (!(board[next] & side_tag))
                            flexible[r] += F_BISHOP;
                    }
                }
            }
        }

        /* 马的灵活性 */
        for (i = 5; i <= 6; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 8; k++) {
                next = p + knight_dir[k];

                if (legal_position[r][next] & position_mask[KNIGHT]) {
                    m = p + knight_check[k];

                    if (!board[m]) {
                        if (!(board[next] & side_tag))
                            flexible[r] += F_KNIGHT;
                    }
                }
            }
        }

        /* 车的灵活性 */
        for (i = 7; i <= 8; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 4; k++) {
                for (j = 1; j < 10; ++j) {
                    next = p + j * rook_dir[k];

                    if (!(legal_position[r][next] & position_mask[ROOK]))
                        break;

                    if (!board[next]) {
                        flexible[r] += F_ROOK;
                    } else if (board[next] & side_tag) {
                        break;
                    } else {
                        flexible[r] += F_ROOK;
                        break;
                    }
                }
            }
        }

        /* 炮的灵活性 */
        for (i = 9; i <= 10; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 4; k++) {
                /* 中间隔子数量 */
                over_flag = 0;

                for (j = 1; j < 10; ++j) {
                    next = p + j * cannon_dir[k];

                    if(!(legal_position[r][next] & position_mask[CANNON]))
                        break;

                    if (!board[next]) {
                        if (!over_flag)
                            flexible[r] += F_CANNON;
                    } else {
                        if (!over_flag) {
                            over_flag = 1;
                        } else {
                            if (!(board[next] & side_tag))
                                flexible[r] += F_CANNON;
                            break;
                        }
                    }
                }
            }
        }

        /* 兵(卒)的灵活性 */
        for (i = 11; i <= 15; i++) {
            p = piece[side_tag + i];

            if (!p) continue;

            for (k = 0; k < 3; k++) {
                next = p + pawn_dir[r][k];

                if (legal_position[r][next] & position_mask[PAWN]) {
                    if (!(board[next] & side_tag))
                        flexible[r] += F_PAWN;
                }
            }
        }
    }

    int result =  (flexible[0] + r_value) - (flexible[1] + b_value);

    if (side == RED)
        return result;
    else
        return -result;
}
