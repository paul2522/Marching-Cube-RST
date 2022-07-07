#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>

#define MinDelta 0.00000000000001
//using namespace std;


int edgeTable[256] = {
	0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
	0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
	0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
	0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
	0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
	0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
	0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
	0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
	0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
	0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
	0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
	0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
	0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
	0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
	0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
	0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
	0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
	0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
	0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
	0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
	0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
	0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
	0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
	0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
	0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
	0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
	0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
	0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
	0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
	0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
	0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
	0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0 };

int triTable[256][16] =
{ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
{ 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 },
{ 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 },
{ 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
{ 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 },
{ 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 },
{ 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 },
{ 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 },
{ 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 },
{ 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 },
{ 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
{ 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 },
{ 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 },
{ 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 },
{ 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 },
{ 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 },
{ 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 },
{ 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
{ 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 },
{ 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 },
{ 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 },
{ 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 },
{ 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 },
{ 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 },
{ 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 },
{ 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 },
{ 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 },
{ 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 },
{ 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 },
{ 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 },
{ 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
{ 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 },
{ 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 },
{ 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 },
{ 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 },
{ 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 },
{ 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 },
{ 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 },
{ 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 },
{ 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
{ 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 },
{ 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 },
{ 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 },
{ 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 },
{ 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 },
{ 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 },
{ 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 },
{ 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 },
{ 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 },
{ 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 },
{ 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 },
{ 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 },
{ 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 },
{ 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 },
{ 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 },
{ 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 },
{ 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 },
{ 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 },
{ 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 },
{ 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1 },
{ 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 },
{ 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 },
{ 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 },
{ 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 },
{ 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 },
{ 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 },
{ 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 },
{ 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 },
{ 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 },
{ 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 },
{ 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 },
{ 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 },
{ 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 },
{ 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 },
{ 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 },
{ 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 },
{ 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 },
{ 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 },
{ 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 },
{ 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 },
{ 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 },
{ 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 },
{ 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 },
{ 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 },
{ 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 },
{ 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 },
{ 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 },
{ 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 },
{ 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 },
{ 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 },
{ 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 },
{ 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 },
{ 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 },
{ 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 },
{ 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 },
{ 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 },
{ 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 },
{ 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 },
{ 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 },
{ 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 },
{ 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 },
{ 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
{ 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 },
{ 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 },
{ 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 },
{ 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 },
{ 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 },
{ 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 },
{ 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
{ 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 },
{ 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } };

//Resource From Paul Broke http://paulbourke.net/geometry/polygonise/

typedef struct point {
	double x;
	double y;
	double z;
}Point;

typedef struct re_check {
	int number[12]; //vertex�� vertex���Ͽ� �����ġ���ִ��� ǥ��
	Point point;
	int array[12];
}re_check;

void marchingcube(FILE* fpVertex, FILE* fpFace, Point* p, double* density, int* vertexNum, int b, int c, int h, int* faceNum);
Point pointcal(Point p1, Point p2, double val1, double val2);
void vertex_algo(FILE* fpVertex, int i, int* vertexNum, int r, int c, Point* vertlist, int* face_array);
void getEdgeLength(Point p1, Point p2, Point p3);
void convertVertex(Point p1, Point p2, Point p3);
double shortestEdge(double a, double b, double c);
double longestEdge(double a, double b, double c);

double** arr1, ** arr2;
re_check** arr3, ** arr4;
int row, col, height;
int counts = 0;
int cubeVertexCheck[12][8] = { 0 };
//�������� ������ ���������� �ƴ��� �Ǵ��ϴ� �迭, 12�� edge 8�� �ش� ������
double cl = 0;			// contour Level �Է� �ޱ� �� ����
//step_size ���� 1~9 2�̻��� ���� �������� �ش� resolution���� ���� sit������ �ʿ���.(�Է� �ޱ� ����)
int step_size = 1;

//edge�� �������� ���������� Ȯ���ϴ� ���� ������ ���� ����
FILE* fpEdgePassCheckFile1;
//edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum
//edgePassNum	:	�������� edge�� mesh�� ������ ����
//edgePassSum	:	�������� edge�� mesh�� ������ ��ġ�� 0~11���� �Ͽ� 2������ ���� �� 10������ ǥ��
//b,c,h			:	������ ��, ��, ��ġ ���� = row, col, height
//vertexInNum	:	�������� mesh�� ���ԵǴ� vertex�� ����
//vertexInSum	:	�������� mesh�� ���ԵǴ� vertex�� ��ġ�� 2������ ���� �� 10������ ǥ��
//voxelIndex	:	�ش� ������ index(��ȣ)

//�� ���Ͽ��� edgeList�� ���� ����(�̻��)
FILE* fpEdgePassCheckFile2;
//Skinny Triangle ����
FILE* fpErrorInfoFile;
//Skinny Triangle�� ������ Face ����
FILE* fpErrorFaceInfoFile;

point changeA, changeB, changeC;
double vertexXSum = 0;
double vertexYSum = 0;
double vertexZSum = 0;

double minLength = 0.1;					//�ּ� length ���� ����(�Է� ����)
double minSize = 0.01;					//�ּ� face ũ�� ����(�Է� ����)

//������ ���� �̻��
//double faceSizeSum = 0;				//face ��ü ũ��
//double faceAvgSize = 0;				//face ��� ũ��

double faceLengthSum = 0;				//��ü face�� ��ü edge ����(�� edge�� ���� face�� ��ģ�ٸ� �ߺ�ó���Ǿ� ����)
double faceAvgLength = 0;				//face edge�� ��� ����
int faceTotalNum = 0;					//face ��ü ����

double faceMaxLength = 0;				//face edge�� �ִ� ����
double faceMinLength = 1000;			//face edge�� �ּ� ����

//������ ���� �̻��
//double faceMaxSize = 0;				//face edge�� �ִ� ũ��
//double faceMinSize = 1000;			//face edge�� �ּ� ũ��

double length1, length2, length3;		//face edge���� ����
int isErrorFace = 0;					//�ش� face�� Skinny triangle���� �ƴ��� Ȯ���ϴ� ��
int errorLengthFaceNum = 0;				//�ּ� length���� ���� length�� ������ face�� ����
int valVoxelIndex = 0;					//Face�� ������ ���ǹ��� ������ index
int errorVoxelNum = 0;					//Skinny Triangle�� ������ ������ ����
int isErrorVoxel = 0;					//Skinny Triangle�� ������ ���� Ȯ��

//������ ���� �̻��
//int errorSizeFaceNum = 0;				//�ּ� Size���� ���� Size�� ������ face�� ����
//int errorBothFaceNum = 0;				//�ּ� length ���� ª�� �ּ� Size���� ���� face�� ����

int main(void)
{
	//EMD ���� �Է�, ���ڸ� �Է��ϸ� �ش� ���ڿ� �´� ������ �����ȴ�.
	//char S[40] = "1003";				//����׿�
	char S[40] = "";					//emd ����
	char S1[40] = "emd_";				//emd_	
	char stepName[40] = "step_";		//stepName = "step_"
	char stepSize[40] = "";				//stepsize step����
	char stepOFF[40] = "";				//step���� OFF ���� �̸�
	char stepSit[40] = "";				//step���� sit ���� �̸�
	char stepVertex[40] = "";			//step���� vertex ���� �̸�
	char stepFace[40] = "";				//step���� face ���� �̸�
	char stepCenter[40] = "";			//step���� center ���� �̸�
	char stepEdgePass1[40] = "";		//step���� edegPassCheckFile1
	char stepEdgePass2[40] = "";		//step���� edegPassCheckFile2
	char stepErrorInfo[40] = "";		//step���� error ���� ���� �̸�
	char stepErrorFaceInfo[40] = "";	//step���� errro Face ���� �̸�
	char Center[40] = "Center_";		//Center = "Center_"

	//EMD ���� �Է¹ޱ�
	printf("���� ������ �ִ� EMD : 0204 0840 1003 1059 1303 1709 1815 3947 4124 4372 5778 5805 6493 6552 8743 9102 10676\n");
	printf("EMD ���� �Է�\n");
	scanf("%s", S);

	//contour level �Է� �ޱ�
	printf("EMD 0204	0.09\nEMD 0840	0.0128\nEMD 1003	82.8\nEMD 1059	0.144\nEMD 1303	74.3\nEMD 1709	0.03\nEMD 1815	3.5\nEMD 3947	0.075\nEMD 4124	0.56\nEMD 4372	0.3\nEMD 5778	7\nEMD 5805	35.0\nEMD 6493	2.7\nEMD 6552	0.03\nEMD 8743	0.045\nEMD 9102	0.0135\nEMD 10676	0.0601\n");
	printf("EMD_%s Contour Level �Է¹ޱ�\n", S);
	scanf("%lf", &cl);

	printf("���� �Ǵ� ���� �Է�\n");
	scanf("%lf", &minLength);

	//������ ���� �̻��
	//printf("���� �Ǵ� ���� �Է�\n");
	//scanf("%lf", &minSize);

	//step size �Է¹ޱ�
	//printf("step size �Է�:");
	//scanf("%d", &step_size);

	//emd_****, nstep_ �����
	strcat(S1, S);						//S1 = "emd_****"
	sprintf(stepSize, "%d", step_size); //stepSize = "n"
	strcat(stepSize, stepName);			//stepSize = "nstep_"
	strcat(stepSit, stepSize);			//stepSit = "nstep_"
	strcpy(stepOFF, stepSize);			//stepOFF = "nstep_"
	strcpy(stepVertex, stepSize);		//stepVertex = "nstep_"
	strcpy(stepFace, stepSize);			//stepFace = "nstep_"	
	strcpy(stepCenter, stepSize);		//stepCenter = "nstep_"
	strcpy(stepEdgePass1, stepSize);	//stepEdgePass1 = "nstep_"
	strcpy(stepEdgePass2, stepSize);	//stepEdgePass2 = "nstep_"
	strcpy(stepErrorInfo, stepSize);	//stepErrorInfo = "nstep_"
	strcpy(stepErrorFaceInfo, stepSize);//stepErrorFaceInfo = "nstep_"
	strcpy(stepOFF, stepSize);			//stepOFF = "nstep_"
				
	//�е��� ����� ����
	strcat(stepSit, S1);								//stepSit = "nstep_emd_****"
	strcat(stepSit, ".sit");							// stepSit = "nstep_emd_****.sit"
	FILE* fpDensity = fopen(stepSit, "r");				//stepSit = "nstep_emd_****.sit" , step ��ȭ ���� �� 1step���� �ؾ���
	
	//vertex, face ����
	strcat(stepVertex, S1);								//stepVertex = "nstep_emd_****"
	strcat(stepVertex, "_vertex.txt");					//stepVertex = "nstep_emd_****_vertex.txt"
	strcat(stepFace, S1);								//stepFace = "nstep_emd_****"
	strcat(stepFace, "_face.txt");						//stepVertex = "nstep_emd_****_face.txt"
	FILE* fpVertex = fopen(stepVertex, "w");			//step���� vertex���� ���� : nstep_emd_****_vertex.txt
	FILE* fpFace = fopen(stepFace, "w");				//step���� face���� ���� : nstep_emd_****_face.txt

	//EdgePass, ErrorInfo ���� �����
	strcat(stepEdgePass1, S1);							//stepEdgePass1 = "nstep_emd_****"
	strcat(stepEdgePass2, S1);							//stepEdgePass2 = "nstep_emd_****"
	strcat(stepErrorInfo, S1);							//stepErrorInfo = "nstep_emd_****"
	strcat(stepErrorFaceInfo, S1);						//stepErrorFaceInfo = "nstep_emd_****"
	strcat(stepEdgePass1, "_EdgePassCheck1.txt");		//stepEdgePass1 = nstep_emd_****_EdgePassCheck1.txt
	strcat(stepEdgePass2, "_EdgePassCheck2.txt");		//stepEdgePass2 = nstep_emd_****_EdgePassCheck2.txt
	strcat(stepErrorInfo, "_ErrorInfo.txt");			//stepErrorInfo = nstep_emd_****_ErrorInfo.txt
	strcat(stepErrorFaceInfo, "_ErrorFaceInfo.txt");	//stepErrorInfo = nstep_emd_****_ErrorFaceInfo.txt
	fpEdgePassCheckFile1 = fopen(stepEdgePass1, "w");	//edge�� �������� ���������� Ȯ���ϴ� ����
	fpEdgePassCheckFile2 = fopen(stepEdgePass2, "w");	//edge�� �������� ���������� Ȯ���ϴ� �ι�° ����
	fpErrorInfoFile = fopen(stepErrorInfo, "w");		//Error ���� ����
	fpErrorFaceInfoFile = fopen(stepErrorFaceInfo, "w");//Error Face ���� ����

	//EdegPassCheckFile1,2 �����̸� �ֱ� - FindVoxelCase���� �ٽ� �����ϴ� ���ŷο��� ���� ����
	//fprintf(fpEdgePassCheckFile1, "edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum\n");
	//fprintf(fpEdgePassCheckFile2, "edgePassBy2, edgePassNum, edgePassSum, b, c, h, vertexInNum, vertexInSum\n");

	//��ü �߰��� ���� �����
	strcat(Center, S);									//Center ���� : Center****
	strcat(stepCenter, Center);							//stepCenter ���� : nstep_Center****
	strcat(stepCenter, ".txt");							//stepCenter ���� : nstep_Center****.txt

	//���� OFF���� �����
	strcat(stepOFF, S1);								//stepOFF = "nstep_emd_****"
	strcat(stepOFF, ".OFF");							//stepOFF = "nstep_emd_****.OFF"
	FILE* fpOFF = fopen(stepOFF, "w");					//stepOFF ���� : nstep_emd_****.OFF
	
	//OFF���Ͽ��� Face ���� VoxelIndex �� Skinny Triangle ���� ����
	char stepOFF2[40] = "V_";							//���ο� step���� OFF ���� �̸�(voxelNum�߰�)
	strcat(stepOFF2, stepOFF);							//���ο� step���� OFF ���� : V_nstep_emd_****.OFF
	FILE* fpOFF2 = fopen(stepOFF2, "w");				//���ο� stepOFF ���� : V_nstep_emd_****.OFF

	//�̸� ��� �����
	printf("%s\n", stepOFF);							//stepOFF = "nstep_emd_****.OFF"
	printf("%s\n", stepOFF2);							//stepOFF = "V_nstep_emd_****.OFF"

	//�е��� ����(sit)�� �ùٸ��� ����
	if (fpDensity == NULL)
	{
		printf("open() error!");
		exit(1);
	}

	double data[7];
	//��, ��, ���� �Է� �ޱ�
	for (int i = 0; i < 7; i++)
	{
		fscanf(fpDensity, "%lf", &data[i]);
		if (i == 4)
			row = (int)data[i];
		else if (i == 5)
			col = (int)data[i];
		else if (i == 6)
			height = (int)data[i];
	}

	//double** arr1,**arr2;
	//double ���� ������ ������ �迭 2���� row ũ�⸸ŭ �����Ҵ�
	arr1 = (double**)malloc(sizeof(double*) * row);
	arr2 = (double**)malloc(sizeof(double*) * row);

	arr3 = (re_check**)malloc(sizeof(re_check*) * row);
	arr4 = (re_check**)malloc(sizeof(re_check*) * row);


	for (int i = 0; i < row; i++)
	{
		arr1[i] = (double*)malloc(sizeof(double) * col);
		arr2[i] = (double*)malloc(sizeof(double) * col);
	}

	for (int i = 0; i < row; i++)
	{
		arr3[i] = (re_check*)malloc(sizeof(re_check) * col);
		arr4[i] = (re_check*)malloc(sizeof(re_check) * col);
	}


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fscanf(fpDensity, "%lf", &arr1[i][j]);
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			fscanf(fpDensity, "%lf", &arr2[i][j]);
	}
	//2���� �迭 �б� (��ü�� �ƴ϶� ó���� �ո�, �ڸ� 1�� �б�)

	int h = 0; //z��ǥ
	int vertexNum = 0;
	int faceNum = 0;
	Point p[8];
	double density[8];

	while (h != (height - 1)) //0~ height - 2 ���� �� (height -1) �� arr2�� 2�� ������
	{
		if (counts == 1)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
					fscanf(fpDensity, "%lf", &arr2[i][j]);
			}
		} // ó���� 2���� �迭�� �������� 2���� ������ �������ʹ� �ϳ��� �д´�. ������ ���Ͽ��� ���� 2�����迭 �ϳ��� �� ����ϱ� �����̴�.

		int flag = 0; // ������ �е����� �� 8�� �ִµ�(�� 8���� �������� �ֱ� ����) contour_level ���� �е��� ���̿� ������ flag=1�� ���� �� ��Īť�� ����

					  //��Ī ť�� �����ϱ��� contour_level�� ����(�����ü �ϳ�)�� �� vertex�� �е��� ���̿� �ѹ��̶� �����Ѵٸ� flag=1�� ���� �� ��Īť�� ����  
		for (int b = 0; b < row - 1; b++)
		{
			for (int c = 0; c < col - 1; c++)
			{
				if ((arr2[b + 1][c] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr2[b + 1][c] >= cl)) //0&1 - edge : 0
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c + 1] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr1[b + 1][c + 1] >= cl))//2&1 - edge : 1
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c] <= cl && arr1[b + 1][c + 1] >= cl) || (arr1[b + 1][c + 1] <= cl && arr1[b + 1][c] >= cl)) //3&2 - edge : 2
				{
					flag = 1;
				}
				else if ((arr1[b + 1][c] <= cl && arr2[b + 1][c] >= cl) || (arr2[b + 1][c] <= cl && arr1[b + 1][c] >= cl))//3&0 - edge : 3
				{
					flag = 1;
				}
				else if ((arr2[b][c] <= cl && arr2[b][c + 1] >= cl) || (arr2[b][c + 1] <= cl && arr2[b][c] >= cl)) //4&5 - edge : 4
				{
					flag = 1;
				}
				else if ((arr1[b][c + 1] <= cl && arr2[b][c + 1] >= cl) || (arr2[b][c + 1] <= cl && arr1[b][c + 1] >= cl)) //6&5 - edge : 5
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr1[b][c + 1] >= cl) || (arr1[b][c + 1] <= cl && arr1[b][c] >= cl)) //7&6 - edge : 6
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr2[b][c] >= cl) || (arr2[b][c] <= cl) && arr1[b][c] >= cl) //7&4 - edge : 7
				{
					flag = 1;
				}
				else if ((arr2[b][c] <= cl && arr2[b + 1][c] >= cl) || (arr2[b + 1][c] <= cl && arr2[b][c] >= cl)) //4&0 - edge : 8
				{
					flag = 1;
				}
				else if ((arr2[b][c + 1] <= cl && arr2[b + 1][c + 1] >= cl) || (arr2[b + 1][c + 1] <= cl && arr2[b][c + 1] >= cl)) //5&1 - edge : 9
				{
					flag = 1;
				}
				else if ((arr1[b][c + 1] <= cl && arr1[b + 1][c + 1] >= cl) || (arr1[b + 1][c + 1] <= cl && arr1[b][c + 1] >= cl)) //6&2 - edge : 10
				{
					flag = 1;
				}
				else if ((arr1[b][c] <= cl && arr1[b + 1][c] >= cl) || (arr1[b + 1][c] <= cl && arr1[b][c] >= cl)) //7&3 - edge : 11
				{
					flag = 1;
				}

				if (flag == 1) //flag�� 1�ΰ�� ��Īť�� ����
				{
					//vertex ��ġ ��ǥ�� �ε����� ���� (���� 0,0,2���ִ� vertex�� (0,0,2)���ȴ�. p�� ����ü Point����)
					//�׸����� �����ΰ��� x�� ����(b) ���������� ���� y�� ����(c) �޸��� h �� ������ ����.
					//�ֳ��ϸ� b���� row���� ���� c�� col������ ���� ��ķ� ����ѵ�
					//arr1
					p[7].x = b;			p[7].y = c;			p[7].z = h;
					p[3].x = (b + 1);	p[3].y = c;			p[3].z = h;
					p[6].x = b;			p[6].y = (c + 1);	p[6].z = h;
					p[2].x = (b + 1);	p[2].y = (c + 1);	p[2].z = h;
					//arr2
					p[4].x = b;			p[4].y = c;			p[4].z = (h + 1);
					p[0].x = (b + 1);	p[0].y = c;			p[0].z = (h + 1);
					p[5].x = b;			p[5].y = (c + 1);	p[5].z = (h + 1);
					p[1].x = (b + 1);	p[1].y = (c + 1);	p[1].z = (h + 1);
					//�� �������� ������ vertex�� ��ǥ�� ����

					density[0] = arr2[b + 1][c];
					density[1] = arr2[b + 1][c + 1];
					density[2] = arr1[b + 1][c + 1];
					density[3] = arr1[b + 1][c];
					density[4] = arr2[b][c];
					density[5] = arr2[b][c + 1];
					density[6] = arr1[b][c + 1];
					density[7] = arr1[b][c]; //vertex�� �ش��ϴ� �е��� ����		

					marchingcube(fpVertex, fpFace, p, density, &vertexNum, b, c, h, &faceNum); //marching cube ���� 
					//fpVertex,fpFace : ���� ������  , p : ������ ��������(8��) ��ġ���� ���� ,density : ������ �� �������� �е��� ����, vertexNum, faceNum : ���Ͽ� ����� vertex��(vertexNum)�� face��(faceNum) ����뵵 
					if (isErrorVoxel == 1)
						errorVoxelNum++;
					valVoxelIndex++;
				}
				//printf("b = %d c = %d , h = %d\n", b, c, h);
				//flage�� 1�̾ƴϸ� �ٸ� ������ �ٽ� �˻��Ϸ� �ö󰣴�
				flag = 0;
			}
		}
		//arr1, arr2�� �����, arr1�� arr2�� �� ��
		//arr3, aar4�� ��������, arr3�� arr4�� �� ����
		double** temp; // �ΰ��� �������迭�� ��� ���� �� �����͸� �ٲپ ù��° �������迭�� ����Ű�� �����ʹ� �ι�°�� ����Ű�� �ι�°�����ʹ� ���Ӱ� �ٽ� ���Ͽ��� �о�´�.
		temp = arr1;
		arr1 = arr2;
		arr2 = temp;
		h++;
		counts = 1;

		re_check** temp2;
		temp2 = arr3;

		arr3 = arr4;
		arr4 = temp2;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				for (int k = 0; k < 12; k++)
					arr4[i][j].array[k] = 0;
	}
	
	//�Է� ���ϵ� �� ���� ���� �ݱ�
	fprintf(fpVertex, "%d", vertexNum);
	fprintf(fpFace, "%d", faceNum);
	fclose(fpVertex);
	fclose(fpFace);
	
	//OFF���� ����
	fprintf(fpOFF, "OFF\n\n");
	fprintf(fpOFF, "%d %d 0\n", vertexNum, faceNum);

	//fprintf(fpOFF2, "OFF\n\n"); //�ٸ� ó�����Ͽ��� OFF �� ����������ϱ� ������ ����
	//face�� ������ ���ǹ��� ������ ���� ���� �߰�(valVoxelIndex)
	fprintf(fpOFF2, "%d %d 0 %d\n", vertexNum, faceNum, valVoxelIndex);

	//OFF������ ����� ���� �ٽ� ���� �б�
	FILE* fpVertexOpen = fopen(stepVertex, "r");		//vertex���� ���� �б�
	FILE* fpFaceOpen = fopen(stepFace, "r");			//face���� ���� �б�

	double Vx = 0, Vy = 0, Vz = 0;
	for (int i = 0; i < vertexNum; i++)
	{
		fscanf(fpVertexOpen, "%lf %lf %lf", &Vx, &Vy, &Vz);
		fprintf(fpOFF, "%lf %lf %lf\n", Vx, Vy, Vz);
		fprintf(fpOFF2, "%lf %lf %lf\n", Vx, Vy, Vz);
	}

	int FN, Fx, Fy, Fz, Fvn, Fief;
	//3 array1  array2  array3  valVoxelIndex  isErrorFace
	for (int i = 0; i < faceNum; i++)
	{
		fscanf(fpFaceOpen, "%d %d %d %d %d %d", &FN, &Fx, &Fy, &Fz, &Fvn, &Fief);
		fprintf(fpOFF, "%d %d %d %d\n", FN, Fx, Fy, Fz);
		fprintf(fpOFF2, "%d %d %d %d %d %d\n", FN, Fx, Fy, Fz, Fvn, Fief);
		
	}

	fclose(fpDensity);
	fclose(fpVertexOpen);
	fclose(fpFaceOpen);
	fclose(fpEdgePassCheckFile1);
	fclose(fpEdgePassCheckFile2);
	fclose(fpOFF);
	fclose(fpOFF2);

	//��ü ��ǥ �����߽� ���ϱ�
	/*
	FILE* fpCenter = fopen(stepCenter, "w");
	fprintf(fpCenter, S1);
	fprintf(fpCenter, "\nvertex ������ %d\n", vertexNum);
	fprintf(fpCenter, "x,y,z ��ǥ �հ�� %lf, %lf, %lf\n", vertexXSum, vertexYSum, vertexZSum);

	vertexXSum /= vertexNum;
	vertexYSum /= vertexNum;
	vertexZSum /= vertexNum;

	fprintf(fpCenter, "x,y,z �����߽� ��ǥ�� %lf, %lf, %lf", vertexXSum, vertexYSum, vertexZSum);
	fclose(fpCenter);
	*/

	faceAvgLength = faceLengthSum / faceTotalNum * 3;
	//������ ���� �̻��
	//faceAvgSize = faceSizeSum / faceTotalNum;
	
	printf("\n���� ��ü�� ũ��� %d�̴�.\n", row* col* height);
	printf("Face�� ������ ���ǹ��� ������ �� ������ %d\n", valVoxelIndex);
	printf("face�� edge�� �� ���̴� %lf�̰� ����� %lf�̴�.\n", faceLengthSum, faceAvgLength);
	printf("�� face�� ������ %d�� �̴�.\n\n", faceTotalNum);
	printf("Edge�� %lf���� ª�� Skinny triangle�� ������ %d\n", minLength, errorLengthFaceNum);
	printf("Skinny Triangle/faceNumd�� %lf�̴�\n", double(errorLengthFaceNum) / faceTotalNum);
	printf("Skinny Triangle�� ������ ������ �� ������ %d\n", errorVoxelNum);
	printf("Skinny Triangle ���� / ���ǹ��� ������ %lf\n\n", (double)errorVoxelNum / valVoxelIndex);
	printf("���� ª�� edge�� %lf, ���� �� edge�� %lf\n", faceMinLength, faceMaxLength);

	//������ ���� �̻��
	//printf("face�� �� ���̴� %lf�̰� ����� %lf�̴�.\n", faceSizeSum, faceAvgSize);
	//printf("Face ���̰� %lf���� �۱⸸ �ؼ� ������ �Ǵ� Face�� ������ %d\n", minSize, errorSizeFaceNum);
	//printf("Face Edge�� %lf���� ª�� ũ�Ⱑ %lf���� ���� Face�� ������ %d\n", minLength, minSize, errorBothFaceNum);
	//printf("�� Skinny Triangledml ������ %d�̰� Skinny Triangle/faceNumd�� %lf�̴�\n", errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum, double(errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum) / faceTotalNum);
	//printf("���� ���� Face�� ũ��� %.20lf, ���� ū ũ��� %lf\n", faceMinSize, faceMaxSize);
	//�ּ� ũ���� Face�� �ʹ� �۾Ƽ� �Ҽ��� �ڸ� ����

	fprintf(fpErrorInfoFile, "���� ��ü�� ũ��� %d�̴�.\n", row* col* height);
	fprintf(fpErrorInfoFile, "Face�� ������ ���ǹ��� ������ �� ������ %d\n", valVoxelIndex);
	fprintf(fpErrorInfoFile, "face�� edge�� �� ���̴� %lf�̰� ����� %lf�̴�.\n", faceLengthSum, faceAvgLength);
	fprintf(fpErrorInfoFile, "�� face�� ������ %d�� �̴�.\n\n", faceTotalNum);
	fprintf(fpErrorInfoFile, "Edge�� %lf���� ª�� Skinny triangle�� ������ %d\n", minLength, errorLengthFaceNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle/faceNumd�� %lf�̴�\n", double(errorLengthFaceNum) / faceTotalNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle�� ������ ������ �� ������ %d\n", errorVoxelNum);
	fprintf(fpErrorInfoFile, "Skinny Triangle ���� / ���ǹ��� ������ %lf\n\n", (double)errorVoxelNum / valVoxelIndex);
	fprintf(fpErrorInfoFile, "���� ª�� edge�� %lf, ���� �� edge�� %lf\n", faceMinLength, faceMaxLength);
	
	//������ ���� �̻��
	//fprintf(fpErrorInfoFile, "face�� �� ���̴� %lf�̰� ����� %lf�̴�.\n", faceSizeSum, faceAvgSize);
	//fprintf(fpErrorInfoFile, "Face ���̰� %lf���� �۱⸸ �ؼ� ������ �Ǵ� Face�� ������ %d\n", minSize, errorSizeFaceNum);
	//fprintf(fpErrorInfoFile, "Face Edge�� %lf���� ª�� ũ�Ⱑ %lf���� ���� Face�� ������ %d\n", minLength, minSize, errorBothFaceNum);
	//fprintf(fpErrorInfoFile, "�� Skinny Triangledml ������ %d�̰� Skinny Triangle/faceNumd�� %lf�̴�\n", errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum, double(errorLengthFaceNum + errorSizeFaceNum + errorBothFaceNum) / faceTotalNum);
	//fprintf(fpErrorInfoFile, "���� ���� Face�� ũ��� %.20lf, ���� ū ũ��� %lf\n", faceMinSize, faceMaxSize);
	
	fclose(fpErrorInfoFile);
	fclose(fpErrorFaceInfoFile);
}

//fpVertex,fpFace : ���� ������, p : ������ ��������(8��) ��ġ���� ���� ,density : ������ �� �������� �е��� ����, vertexNum, faceNum : ���Ͽ� ����� vertex��(vertexNum)�� face��(faceNum) ����뵵
void marchingcube(FILE* fpVertex, FILE* fpFace, Point* p, double* density, int* vertexNum, int b, int c, int h, int* faceNum)  //�����ڷ� : http://paulbourke.net/geometry/polygonise/
{
	int vertexInNum = 0; //���� index ����
	int cubeIndex = 0;

	int val[12];							//val���� -1�̸� �������� �������̴� edge 12���� ��
	Point belowPoint[12];					//val���� -1�� �ƴѰ��(�������� �������� �ƴ� ���) �� edge���� cl���� ���� density�� ������ ��
	int face_array[12] = { 0 };				//�������� vertex ���Ͽ����� ��ġ��
	if (density[0] < cl) {
		cubeIndex |= 1;
		vertexInNum++;
	}
	if (density[1] < cl) {
		cubeIndex |= 2;
		vertexInNum++;
	}
	if (density[2] < cl) {
		cubeIndex |= 4;
		vertexInNum++;
	}
	if (density[3] < cl) {
		cubeIndex |= 8;
		vertexInNum++;
	}
	if (density[4] < cl) {
		cubeIndex |= 16;
		vertexInNum++;
	}
	if (density[5] < cl) {
		cubeIndex |= 32;
		vertexInNum++;
	}
	if (density[6] < cl) {
		cubeIndex |= 64;
		vertexInNum++;
	}
	if (density[7] < cl) {
		cubeIndex |= 128;
		vertexInNum++;
	}
	// determine cubeIndex
	// cubeIndex cl���� ������ �ܺ�! �� 0�� ���ΰ� 1�� ���ΰ� �ƴ�

	Point vertlist[12]; //edge�� 12���� �� 12���̸� ������ edge���� ���ü� �ִ� vertex�� ����ؼ� ����(�������� ����ؼ� ����)
	int edgePassCheck[12];//vertex �ֳ� ���� üũ(�������� �ֳ� ���� üũ)
	for (int i = 0; i < 12; i++)
	{
		edgePassCheck[i] = 0;      // include vertex check(������ üũ)
		val[i] = 0;		   // i edge�� ��ġ�ϴ� �������� ���������� �ƴ� �Ǵ��ϴ� �� �ʱ�ȭ
	}

	if (edgeTable[cubeIndex] == 0)//������ ǥ����� ������ ����
	{
		//printf("������ ǥ��� ������ ���� ���� marchingCube �Լ����� �߰�\n");
		return;
	}

	if (edgeTable[cubeIndex] & 1) //ǥ���� edge 0(0,1)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[0] = *face_vertexNum;
		edgePassCheck[0] = 1;	//ǥ���� edge 0�� ����
		vertlist[0] = pointcal(p[0], p[1], density[0], density[1]);//edge 0�� ǥ���� ������ ��ġ
		if ((vertlist[0].x == p[0].x) && (vertlist[0].y == p[0].y) && (vertlist[0].z == p[0].z))
		{
			val[0] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[0][0] = 1;	//vertex�� edge 0�� ������ 0 ��ġ�̴�.
		}
		else if ((vertlist[0].x == p[1].x) && (vertlist[0].y == p[1].y) && (vertlist[0].z == p[1].z))
		{
			val[0] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[0][1] = 1;	//vertex�� edge 0�� ������ 1 ��ġ�̴�.
		}
		else
		{
			if (density[0] < density[1])
				belowPoint[0] = p[0];		//point[0]�� edge 0������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 0(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[0] = p[1];		//point[0]�� edge 0������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 1(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 2) //ǥ���� edge 1(1,2)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[1] = *face_vertexNum;
		edgePassCheck[1] = 1;	//ǥ���� edge 1�� ����
		vertlist[1] = pointcal(p[1], p[2], density[1], density[2]);//edge 1�� ǥ���� ������ ��ġ
		if ((vertlist[1].x == p[1].x) && (vertlist[1].y == p[1].y) && (vertlist[1].z == p[1].z))
		{
			val[1] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[1][1] = 1;	//vertex�� edge 1�� ������ 1 ��ġ�̴�.
		}

		else if ((vertlist[1].x == p[2].x) && (vertlist[1].y == p[2].y) && (vertlist[1].z == p[2].z))
		{
			val[1] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[1][2] = 1;	//vertex�� edge 1�� ������ 2 ��ġ�̴�.
		}
		else
		{
			if (density[1] < density[2])
				belowPoint[1] = p[1];		//point[1]�� edge 1������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 1(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[1] = p[2];		//point[1]�� edge 1������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 2(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 4) //ǥ���� edge 2(2,3)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[2] = *face_vertexNum;
		edgePassCheck[2] = 1;	//ǥ���� edge 2�� ����
		vertlist[2] = pointcal(p[2], p[3], density[2], density[3]);//edge 2�� ǥ���� ������ ��ġ
		if ((vertlist[2].x == p[2].x) && (vertlist[2].y == p[2].y) && (vertlist[2].z == p[2].z))
		{
			val[2] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[2][2] = 1;	//vertex�� edge 2�� ������ 2 ��ġ�̴�.
		}
		else if ((vertlist[2].x == p[3].x) && (vertlist[2].y == p[3].y) && (vertlist[2].z == p[3].z))
		{
			val[2] = -1;				//�������� ������ ������ �̴�.	
			cubeVertexCheck[2][3] = 1;	//vertex�� edge 2�� ������ 3 ��ġ�̴�.
		}
		else
		{
			if (density[2] < density[3])
				belowPoint[2] = p[2];		//point[2]�� edge 2������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 2(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[2] = p[3];		//point[2]�� edge 2������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 3(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 8) //ǥ���� edge 3(3,0)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[3] = *face_vertexNum;
		edgePassCheck[3] = 1;	//ǥ���� edge 3�� ����
		vertlist[3] = pointcal(p[3], p[0], density[3], density[0]);//edge 3�� ǥ���� ������ ��ġ
		if ((vertlist[3].x == p[3].x) && (vertlist[3].y == p[3].y) && (vertlist[3].z == p[3].z))
		{
			val[3] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[3][3] = 1;	//vertex�� edge 3�� ������ 3 ��ġ�̴�.
		}

		else if ((vertlist[3].x == p[0].x) && (vertlist[3].y == p[0].y) && (vertlist[3].z == p[0].z))
		{
			val[3] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[3][0] = 1;	//vertex�� edge 3�� ������ 0 ��ġ�̴�.
		}
		else
		{
			if (density[3] < density[0])
				belowPoint[3] = p[3];		//point[3]�� edge 3������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 3(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[3] = p[0];		//point[3]�� edge 3������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 0(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 16) //ǥ���� edge 4(4,5)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[4] = *face_vertexNum;
		edgePassCheck[4] = 1;	//ǥ���� edge 4�� ����
		vertlist[4] = pointcal(p[4], p[5], density[4], density[5]);//edge 4�� ǥ���� ������ ��ġ
		if ((vertlist[4].x == p[4].x) && (vertlist[4].y == p[4].y) && (vertlist[4].z == p[4].z))
		{
			val[4] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[4][4] = 1;	//vertex�� edge 4�� ������ 4 ��ġ�̴�.
		}
		else if ((vertlist[4].x == p[5].x) && (vertlist[4].y == p[5].y) && (vertlist[4].z == p[5].z))
		{
			val[4] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[4][5] = 1;	//vertex�� edge 4�� ������ 5 ��ġ�̴�.
		}
		else
		{
			if (density[4] < density[5])
				belowPoint[4] = p[4];		//point[4]�� edge 4������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 4(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[4] = p[5];		//point[4]�� edge 4������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 4(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 32) //ǥ���� edge 5(5,6)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[5] = *face_vertexNum;
		edgePassCheck[5] = 1;	//ǥ���� edge 5�� ����
		vertlist[5] = pointcal(p[5], p[6], density[5], density[6]);//edge 5�� ǥ���� ������ ��ġ
		if ((vertlist[5].x == p[5].x) && (vertlist[5].y == p[5].y) && (vertlist[5].z == p[5].z))
		{
			val[5] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[5][5] = 1;	//vertex�� edge 5�� ������ 5 ��ġ�̴�.
		}
		else if ((vertlist[5].x == p[6].x) && (vertlist[5].y == p[6].y) && (vertlist[5].z == p[6].z))
		{
			val[5] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[5][6] = 1;	//vertex�� edge 5�� ������ 6 ��ġ�̴�.
		}
		else
		{

			if (density[5] < density[6])
				belowPoint[5] = p[5];		//point[5]�� edge 5������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 5(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[5] = p[6];		//point[5]�� edge 5������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 6(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 64) //ǥ���� edge 6(6,7)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[6] = *face_vertexNum;
		edgePassCheck[6] = 1;	//ǥ���� edge 6�� ����
		vertlist[6] = pointcal(p[6], p[7], density[6], density[7]);//edge 6�� ǥ���� ������ ��ġ
		if ((vertlist[6].x == p[6].x) && (vertlist[6].y == p[6].y) && (vertlist[6].z == p[6].z))
		{
			val[6] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[6][6] = 1;	//vertex�� edge 6�� ������ 6 ��ġ�̴�.
		}
		else if ((vertlist[6].x == p[7].x) && (vertlist[6].y == p[7].y) && (vertlist[6].z == p[7].z))
		{
			val[6] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[6][7] = 1;	//vertex�� edge 6�� ������ 7 ��ġ�̴�.
		}
		else
		{
			if (density[6] < density[7])
				belowPoint[6] = p[6];		//point[6]�� edge 6������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 6(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[6] = p[7];		//point[6]�� edge 6������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 7(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 128) //ǥ���� edge 7(7,4)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[7] = *face_vertexNum;
		edgePassCheck[7] = 1;	//ǥ���� edge 7�� ����
		vertlist[7] = pointcal(p[7], p[4], density[7], density[4]);//edge 7�� ǥ���� ������ ��ġ
		if ((vertlist[7].x == p[7].x) && (vertlist[7].y == p[7].y) && (vertlist[7].z == p[7].z))
		{
			val[7] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[7][7] = 1;	//vertex�� edge 7�� ������ 7 ��ġ�̴�.
		}
		else if ((vertlist[7].x == p[4].x) && (vertlist[7].y == p[4].y) && (vertlist[7].z == p[4].z))
		{
			val[7] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[7][4] = 1;	//vertex�� edge 7�� ������ 4 ��ġ�̴�.
		}
		else
		{
			if (density[7] < density[4])
				belowPoint[7] = p[7];		//point[7]�� edge 7������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 7(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[7] = p[4];		//point[7]�� edge 7������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 4(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 256)  //ǥ���� edge 8(0,4)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[8] = *face_vertexNum;
		edgePassCheck[8] = 1;	//ǥ���� edge 8�� ����
		vertlist[8] = pointcal(p[0], p[4], density[0], density[4]);//edge 8�� ǥ���� ������ ��ġ
		if ((vertlist[8].x == p[0].x) && (vertlist[8].y == p[0].y) && (vertlist[8].z == p[0].z))
		{
			val[8] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[8][0] = 1;	//vertex�� edge 8�� ������ 0 ��ġ�̴�.
		}
		else if ((vertlist[8].x == p[4].x) && (vertlist[8].y == p[4].y) && (vertlist[8].z == p[4].z))
		{
			val[8] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[8][4] = 1;	//vertex�� edge 8�� ������ 4 ��ġ�̴�.
		}
		else
		{
			if (density[0] < density[4])
				belowPoint[8] = p[0];		//point[8]�� edge 8������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 0(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[8] = p[4];		//point[8]�� edge 8������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 4(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 512)  //ǥ���� edge 9(1,5)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[9] = *face_vertexNum;
		edgePassCheck[9] = 1;	//ǥ���� edge 9�� ����
		vertlist[9] = pointcal(p[1], p[5], density[1], density[5]);//edge 9�� ǥ���� ������ ��ġ
		if ((vertlist[9].x == p[1].x) && (vertlist[9].y == p[1].y) && (vertlist[9].z == p[1].z))
		{
			val[9] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[9][1] = 1;	//vertex�� edge 9�� ������ 1 ��ġ�̴�.
		}
		else if ((vertlist[9].x == p[5].x) && (vertlist[9].y == p[5].y) && (vertlist[9].z == p[5].z))
		{
			val[9] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[9][5] = 1;	//vertex�� edge 9�� ������ 5 ��ġ�̴�.
		}
		else
		{
			if (density[1] < density[5])
				belowPoint[9] = p[1];		//point[9]�� edge 9������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 1(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[9] = p[5];		//point[9]�� edge 9������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 5(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 1024)  //ǥ���� edge 10(2,6)�� ����
	{
		//	(*face_vertexNum)++;
		//	face_array[10] = *face_vertexNum;
		edgePassCheck[10] = 1;	//ǥ���� edge 10�� ����
		vertlist[10] = pointcal(p[2], p[6], density[2], density[6]);//edge 10�� ǥ���� ������ ��ġ
		if ((vertlist[10].x == p[2].x) && (vertlist[10].y == p[2].y) && (vertlist[10].z == p[2].z))
		{
			val[10] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[10][2] = 1;	//vertex�� edge 10�� ������ 2 ��ġ�̴�.
		}
		else if ((vertlist[10].x == p[6].x) && (vertlist[10].y == p[6].y) && (vertlist[10].z == p[6].z))
		{
			val[10] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[10][6] = 1;	//vertex�� edge 10�� ������ 6 ��ġ�̴�.
		}
		else
		{
			if (density[2] < density[6])
				belowPoint[10] = p[2];		//point[10]�� edge 10������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 2(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[10] = p[6];		//point[10]�� edge 10������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 6(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	if (edgeTable[cubeIndex] & 2048)  //ǥ���� edge 11(3,7)�� ����
	{
		edgePassCheck[11] = 1;	//ǥ���� edge 11�� ����
		vertlist[11] = pointcal(p[3], p[7], density[3], density[7]);//edge 11�� ǥ���� ������ ��ġ
		if ((vertlist[11].x == p[3].x) && (vertlist[11].y == p[3].y) && (vertlist[11].z == p[3].z))
		{
			val[11] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[11][3] = 1;	//vertex�� edge 11�� ������ 3 ��ġ�̴�.
		}
		else if ((vertlist[11].x == p[7].x) && (vertlist[11].y == p[7].y) && (vertlist[11].z == p[7].z))
		{
			val[11] = -1;				//�������� ������ ������ �̴�.
			cubeVertexCheck[11][7] = 1;	//vertex�� edge 11�� ������ 7 ��ġ�̴�.
		}
		else
		{
			if (density[3] < density[7])
				belowPoint[11] = p[3];		//point[11]�� edge 11������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 3(�� ��ġ��) = ������ �ۿ� ����
			else
				belowPoint[11] = p[7];		//point[11]�� edge 11������ contour_level ���� ���� �е����� ���� �������� ��ġ�� = 7(�� ��ġ��) = ������ �ۿ� ����
		}
	}
	/*
	//cubeVertexCheck �˻�� - �������� ������ �������� ��츦 ���
	for (int i = 0; i < 12; i++)
	{
	for (int j = 0; j < 8; j++)
	if (cubeVertexCheck[i][j] == 1)
	{
	printf("%2d edge %d vertex ��ǥ %f, %f, %f\n", i, j, p[j].x, p[j].y, p[j].z);
	}
	}
	*/

	int edgepassNum = 0;	//��� ���ϴ� edge ������ ��
	int edgepassSum = 0;	//EdgeList 2������ 10����ȭ
	int edgePassBY2[12] = { 0 }; //EdgeList 2����

	int vertexInSum = 0;	//���� index list 10���� = cubeIndex


	vertexInSum = cubeIndex;

	int k1 = 1;
	for (int i = 0; i < 12; i++)
	{
		edgepassSum += k1 * edgePassCheck[i];
		edgepassNum += edgePassCheck[i];
		edgePassBY2[i] = edgePassCheck[i];
		k1 *= 2;

		//fprintf(fpEdgePassCheckFile2, "%d", edgePassCheck[i]); // �ܼ���� ���
	}

	fprintf(fpEdgePassCheckFile1, "%2d %4d %3d %3d %3d %d %3d\n", edgepassNum, edgepassSum, b, c, h, vertexInNum, vertexInSum);
	for (int i = 0; i < 12; i++)
	{
		fprintf(fpEdgePassCheckFile2, "%d", edgePassBY2[i]);
	}
	fprintf(fpEdgePassCheckFile2, " %2d %4d %3d %3d %3d %d %3d\n", edgepassNum, edgepassSum, b, c, h, vertexInNum, vertexInSum);



	//�������� �ߺ��� �ȵǰ� �����ϴ� �˰��� ����
	for (int i = 0; i < 12; i++)
	{
		if (edgePassCheck[i] == 1)//ǥ���� edge i �� ���� = edge i ���� �������� ���� �ߺ� �˻� �ǽ�
		{
			vertex_algo(fpVertex, i, vertexNum, b, c, vertlist, face_array);
		}
	}
	//cubeVertexCheck �Լ� �ʱ�ȭ(�������� ������ ������(8��)�� �ϳ����� üũ�ϴ� �Լ� - vertex algo���� ����ó�� �ϱ� ���� ���)
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cubeVertexCheck[i][j] = 0;
		}
	}

	/*
	//cube���� Ư�� ������ face���� �����ϴ� ��츸�� face array�� ���
	for (int i = 0; i < 16; i += 3)//i 012, 345, 678, 91011, 121314, 15�� �׻� -1, �ѹ��� �ϳ��� �ﰢ��
	{
		//if (triTable[cubeIndex][3] == -1)//�� ť���� �����Ǵ� face�� 1���� ���� ����.
		//if (triTable[cubeIndex][6] == -1 && triTable[cubeIndex][3] != -1)//�� ť���� �����Ǵ� face�� 2���� ���� ����.
		//if (triTable[cubeIndex][9] == -1 && triTable[cubeIndex][6] != -1)//�� ť���� �����Ǵ� face�� 3���� ���� ����.
		if (triTable[cubeIndex][12] == -1 && triTable[cubeIndex][9] != -1)//�� ť���� �����Ǵ� face�� 4���� ���� ����.
		//if (triTable[cubeIndex][12] != -1)//�� ť���� �����Ǵ� face�� 5���� ���� ����.
		//if (triTable[cubeIndex][9] == -1)//�� ť���� �����Ǵ� face�� 3�������� ���� ����.
		//if (triTable[cubeIndex][9] != -1)//�� ť���� �����Ǵ� face�� 4�� �̻��� ���� ����.
		{
			if (triTable[cubeIndex][i] == -1)// �ﰢ���� �������� �ʴ´� �Ǵ� �״��� �ﰢ�� �����ε� ����
				break;

			fprintf(fpFace, "%d %d %d %d\n", 3, face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);
			(*faceNum)++;
			//printf("%d %d %d\n",face_array[triTable[cubeIndex][i]],face_array[triTable[cubeIndex][i+1]],face_array[triTable[cubeIndex][i+2]]);
		}
	}
	*/
	

	isErrorVoxel = 0;
	//face�� ���� face�� �����°� �ϼ��� �ﰢ�� 3 a b c / abc�� ���� ���° ��ġ�� vertex ���� ������
	for (int i = 0; i < 16; i += 3)//i 012, 345, 678, 91011, 121314, 15�� �׻� -1, �ѹ��� �ϳ��� �ﰢ��
	{
		//if (triTable[cubeIndex][12] != -1)//�� ť�꿡 �����Ǵ� face�� 5���� ���� ����.

		if (triTable[cubeIndex][i] == -1)// �ﰢ���� �������� �ʴ´� �Ǵ� �״��� �ﰢ�� �����ε� ����
			break;

		//���� 3���� ���� ���� ������ ��� �� ����
		if (face_array[triTable[cubeIndex][i]] == face_array[triTable[cubeIndex][i + 1]] || face_array[triTable[cubeIndex][i]] == face_array[triTable[cubeIndex][i + 2]] || face_array[triTable[cubeIndex][i + 1]] == face_array[triTable[cubeIndex][i + 2]])
		{
			printf("3���� ���� �� �߻�\n%d %d %d\n", face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);
		}
		else
		{
			//double faceSize = 0;
			double s = 0;
			isErrorFace = 0;

			changeA.x = step_size * vertlist[triTable[cubeIndex][i]].x;
			changeA.y = step_size * vertlist[triTable[cubeIndex][i]].y;
			changeA.z = step_size * vertlist[triTable[cubeIndex][i]].z;

			changeB.x = step_size * vertlist[triTable[cubeIndex][i + 1]].x;
			changeB.y = step_size * vertlist[triTable[cubeIndex][i + 1]].y;
			changeB.z = step_size * vertlist[triTable[cubeIndex][i + 1]].z;

			changeC.x = step_size * vertlist[triTable[cubeIndex][i + 2]].x;
			changeC.y = step_size * vertlist[triTable[cubeIndex][i + 2]].y;
			changeC.z = step_size * vertlist[triTable[cubeIndex][i + 2]].z;

			//���� Face�� edge�� �� ���̸� ���ϴ� ���
			getEdgeLength(changeA, changeB, changeC);
			//length1~3�� ���������� ����Ҷ����� 0���� �ʱ�ȭ �� �� ����Ѵ�.
			s = 0.5 * (length1 + length2 + length3);

			//������ ���� �̻��
			/*
			faceSize = sqrt(s * (s - length1) * (s - length2) * (s - length3));
			
			if (faceSize == 0)
				printf("face ũ�Ⱑ 0 ���� = %lf %lf %lf\n", length1, length2, length3);

			if (faceSize < faceMinSize)
				faceMinSize = faceSize;
			if (faceSize > faceMaxSize)
				faceMaxSize = faceSize;

			faceSizeSum += faceSize;
			*/
			//���� ª�� edge�� ���� �� edge�� ���� ���ϱ�
			if (shortestEdge(length1, length2, length3) < faceMinLength)
				faceMinLength = shortestEdge(length1, length2, length3);
			if (longestEdge(length1, length2, length3) > faceMaxLength)
				faceMaxLength = longestEdge(length1, length2, length3);

			
			//���� face�� ���̰� ���� ������ ���� ���
			if (length1 < minLength || length2 < minLength || length3 < minLength)
			{
				isErrorFace = 1;
				isErrorVoxel = 1;
				errorLengthFaceNum++;
				
				//if (faceSize >= minSize) //������ ���� �̻��
				fprintf(fpErrorFaceInfoFile, "%6d�� Face : ª�� edge %lf %lf %lf\n", faceTotalNum, length1, length2, length3);
			}
			//������ ���� �̻��
			/*
			if (faceSize < minSize)
			{
				if (isErrorFace == 1)
				{
					fprintf(fpErrorFaceInfoFile, "%6d�� Face : ª�� edge %lf %lf %lf ���� ũ�� %lf\n", faceTotalNum, length1, length2, length3, faceSize);
					errorLengthFaceNum--;
					errorBothFaceNum++;
				}
				else
				{
					fprintf(fpErrorFaceInfoFile, "%6d�� Face : ���� ũ�� %lf\n", faceTotalNum, faceSize);
					errorSizeFaceNum++;
				}
				isErrorFace = 1;
				isErrorVoxel = 1;
			}
			faceSizeSum += faceSize;
			*/
			//s = 0.5 * (length1 + length2 + length3) �̹Ƿ�
			faceLengthSum += (s * 2);
			faceTotalNum++;

			//����
			//fprintf(fpFace, "%d %d %d %d\n", 3, face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]]);

			//voxelvalNumber �߰�
			fprintf(fpFace, "3 %d %d %d %d %d\n", face_array[triTable[cubeIndex][i]], face_array[triTable[cubeIndex][i + 1]], face_array[triTable[cubeIndex][i + 2]], valVoxelIndex , isErrorFace);
			(*faceNum)++;
		}
		//A,B,C ��, A �������� ���� edge���� vertex ��ġ��,  B �������� ���� edge���� vertex ��ġ��,  C �������� ���� edge���� vertex ��ġ��
	}

}

//fpVertex = vertex ���� ��� ������, i = ǥ���� edge i�� ���� = edge i ���� �������� ����, vertexNum = face_array�� ����Ǵ� vertex���Ͽ����� ��ġ����, b,c = row, col ���� ��ġ��, vertlist = ���������� ��ġ ����
//face_array 12ĭ�� ���� int �迭 
void vertex_algo(FILE* fpVertex, int i, int* vertexNum, int b, int c, Point* vertlist, int* face_array)
{
	if (arr4[b][c].array[i] == 1)										//�̹� ������ �Ҵ����� ���� ���� ������
	{
		face_array[i] = arr4[b][c].number[i];
	}
	else
	{
		if (i == 4)														//edge 4�� ����� ����
		{

			if (b - 1 >= 0)												//�� ���� ĭ�� �ƴϴ�
			{
				if (arr4[b - 1][c].array[0] == 1)						//��ĭ ������ edge 0���� �������� �̹� ����
				{
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 4���� �������� ������ ǥ��
					arr4[b][c].number[i] = arr4[b - 1][c].number[0];	//�ش� ������ edge 4�� vertex ��ġ�� ��ĭ ������ edge 0�� vertex ��ġ
					face_array[i] = arr4[b - 1][c].number[0];			//face array�� ��ĭ ������ edge 0�� vertex ��ġ �� �ֱ�
				}
				else if (arr4[b - 1][c].array[0] == 0)					//��ĭ ������ edge 0���� �ش���� ����
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);	//vertex���Ͽ� ���
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 4���� �������� ������ ǥ��
					arr4[b][c].number[i] = *vertexNum;					//�ش� ������ edge 4�� vertex ��ġ �� �ֱ�
					face_array[i] = *vertexNum;							//face array�� �ش� ������ edge 4�� vertex ��ġ �� �ֱ�
					arr4[b - 1][c].array[0] = 1;						//��ĭ ������ edge 0���� �������� ������ ǥ��
					arr4[b - 1][c].number[0] = *vertexNum;				//��ĭ ������ edge 0�� vertex ��ġ �� �ֱ�

					if (cubeVertexCheck[4][4] == 1)						//���࿡ �������� edge 4�� ������ 4���
					{
						//�ش� ������ ������ 4�� ����� edge�鿡 ������ ǥ��(4,7,8) + 4 �̹� ����
						arr4[b][c].array[7] = 1;						//�ش� ������ edge 7���� �������� ������ ǥ��
						arr4[b][c].number[7] = *vertexNum;				//�ش� ������ edge 7�� vertex ��ġ �� �ֱ�
						arr4[b][c].array[8] = 1;						//�ش� ������ edge 8���� �������� ������ ǥ��
						arr4[b][c].number[8] = *vertexNum;				//�ش� ������ edge 8�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 0�� ����� edge�鿡 ������ ǥ��(0,3,8) + 0 �̹� ����
						arr4[b - 1][c].array[3] = 1;					//��ĭ ������ edge 3���� �������� ������ ǥ��
						arr4[b - 1][c].number[3] = *vertexNum;			//��ĭ ������ edge 3�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].array[8] = 1;					//��ĭ ������ edge 8���� �������� ������ ǥ��
						arr4[b - 1][c].number[8] = *vertexNum;			//��ĭ ������ edge 8�� vertex ��ġ �� �ֱ�
						if (c >= 1)										//�� ���� ĭ�� �ƴϴ�(+ �� ���� ĭ�� �ƴϴ�)
						{
							//��ĭ ������ ������ 5�� ����� edge�鿡 ������ ǥ��(4,5,9)
							arr4[b][c - 1].array[4] = 1;				//��ĭ ������ edge 4���� �������� ������ ǥ��
							arr4[b][c - 1].number[4] = *vertexNum;		//��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
							arr4[b][c - 1].array[5] = 1;				//��ĭ ������ edge 5���� �������� ������ ǥ��
							arr4[b][c - 1].number[5] = *vertexNum;		//��ĭ ������ edge 5�� vertex ��ġ �� �ֱ�
							arr4[b][c - 1].array[9] = 1;				//��ĭ ������ edge 9���� �������� ������ ǥ��
							arr4[b][c - 1].number[9] = *vertexNum;		//��ĭ ������ edge 9�� vertex ��ġ �� �ֱ�
																		//���� ������ ������ 1�� ����� edge�鿡 ������ ǥ��(0,1,9)
							arr4[b - 1][c - 1].array[0] = 1;			//���� ������ edge 0���� �������� ������ ǥ��
							arr4[b - 1][c - 1].number[0] = *vertexNum;	//���� ������ edge 0�� vertex ��ġ �� �ֱ�
							arr4[b - 1][c - 1].array[1] = 1;			//���� ������ edge 1���� �������� ������ ǥ��
							arr4[b - 1][c - 1].number[1] = *vertexNum;	//���� ������ edge 1�� vertex ��ġ �� �ֱ�
							arr4[b - 1][c - 1].array[9] = 1;			//���� ������ edge 9���� �������� ������ ǥ��
							arr4[b - 1][c - 1].number[9] = *vertexNum;	//���� ������ edge 9�� vertex ��ġ �� �ֱ�
						}
					}
					if (cubeVertexCheck[4][5] == 1)						//���࿡ �������� edge 4�� ������ 5���
					{
						//�ش� ������ ������ 5�� ����� edge�鿡 ������ ǥ��(4,5,9) + 4 �̹� ����
						arr4[b][c].array[5] = 1;						//�ش� ������ edge 5���� �������� ������ ǥ��
						arr4[b][c].number[5] = *vertexNum;				//�ش� ������ edge 5�� vertex ��ġ �� �ֱ�
						arr4[b][c].array[9] = 1;						//�ش� ������ edge 9���� �������� ������ ǥ��
						arr4[b][c].number[9] = *vertexNum;				//�ش� ������ edge 9�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 1�� ����� edge�鿡 ������ ǥ��(0,1,9) + 0 �̹� ����
						arr4[b - 1][c].array[1] = 1;					//��ĭ ������ edge 1���� �������� ������ ǥ��
						arr4[b - 1][c].number[1] = *vertexNum;			//��ĭ ������ edge 1�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].array[9] = 1;					//��ĭ ������ edge 9���� �������� ������ ǥ��
						arr4[b - 1][c].number[9] = *vertexNum;			//��ĭ ������ edge 9�� vertex ��ġ �� �ֱ�
					}
					(*vertexNum)++;										//������ ���� 1�� ����
				}
			}
		}
		else if (i == 5)												//edge 5�� ����� ����
		{
			if (b - 1 >= 0)												//�� ���� ĭ�� �ƴϴ�
			{
				if (arr4[b - 1][c].array[1] == 1)						//��ĭ ������ edge 1���� �̹� �������� ����
				{
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 5���� �������� ������ ǥ��
					arr4[b][c].number[i] = arr4[b - 1][c].number[1];	//�ش� ������ edge 5�� vertex ��ġ�� ��ĭ ������ edge 1�� vertex ��ġ
					face_array[i] = arr4[b - 1][c].number[1];			//face array�� ��ĭ ������ edge 1�� vertex ��ġ �� �ֱ�
				}
				else if (arr4[b - 1][c].array[1] == 0)					//��ĭ ������ edge 1 ���� �ش���� ����
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);	//vertex���Ͽ� ���
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 5���� �������� ������ ǥ��
					arr4[b][c].number[i] = *vertexNum;					//�ش� ������ edge 5�� vertex ��ġ �� �ֱ�
					arr4[b - 1][c].array[1] = 1;						//��ĭ ������ edge 1���� �������� ������ ǥ��
					arr4[b - 1][c].number[1] = *vertexNum;				//��ĭ ������ edge 1�� vertex ��ġ �� �ֱ�
					face_array[i] = *vertexNum;							//face array�� �ش� ������ edge 5�� vertex ��ġ �� �ֱ�
					if (cubeVertexCheck[5][5] == 1)						//���࿡ �������� edge5�� ������ 5���
					{
						//�ش� ������ ������ 5�� ����� edge�鿡 ������ ǥ��(4,5,9) + 5 �̹� ����
						arr4[b][c].array[4] = 1;						//�ش� ������ edge 4���� �������� ������ ǥ��
						arr4[b][c].number[4] = *vertexNum;				//�ش� ������ edge 4�� vertex ��ġ �� �ֱ�
						arr4[b][c].array[9] = 1;						//�ش� ������ edge 9���� �������� ������ ǥ��
						arr4[b][c].number[9] = *vertexNum;				//�ش� ������ edge 9�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 1�� ����� edge�鿡 ������ ǥ��(0,1,9) + 1 �̹� ����
						arr4[b - 1][c].array[0] = 1;					//��ĭ ������ edge 0���� �������� ������ ǥ��
						arr4[b - 1][c].number[0] = *vertexNum;			//��ĭ ������ edge 0�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].array[9] = 1;					//��ĭ ������ edge 9���� �������� ������ ǥ��
						arr4[b - 1][c].number[9] = *vertexNum;			//��ĭ ������ edge 9�� vertex ��ġ �� �ֱ�
					}
					if (cubeVertexCheck[5][6] == 1)						//���࿡ �������� edge 5�� ������ 6���
					{
						//�ش� ������ ������ 6�� ����� edge�鿡 ������ ǥ��(5,6,10) + 5 �̹� ����
						arr4[b][c].number[6] = *vertexNum;				//�ش� ������ edge 6���� �������� ������ ǥ��
						arr4[b][c].array[6] = 1;						//�ش� ������ edge 6�� vertex ��ġ �� �ֱ�
						arr4[b][c].number[10] = *vertexNum;				//�ش� ������ edge 10���� �������� ������ ǥ��
						arr4[b][c].array[10] = 1;						//�ش� ������ edge 10�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 2�� ����� edge�鿡 ������ ǥ��(1,2,10) + 1 �̹� ����
						arr4[b - 1][c].array[2] = 1;					//��ĭ ������ edge 2���� �������� ������ ǥ��
						arr4[b - 1][c].number[2] = *vertexNum;			//��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].array[10] = 1;					//��ĭ ������ edge 10���� �������� ������ ǥ��
						arr4[b - 1][c].number[10] = *vertexNum;			//��ĭ ������ edge 10�� vertex ��ġ �� �ֱ�

						if (counts == 1)									//�� ���� ĭ�� �ƴϴ�(+ �� ���� ĭ�� �ƴϴ�)
						{												//��ĭ ������ ������ 5�� ����� edge�鿡 ������ ǥ��(4,5,9)
							arr3[b][c].array[4] = 1;					//��ĭ ������ edge 4���� �������� ������ ǥ��
							arr3[b][c].number[4] = *vertexNum;			//��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
							arr3[b][c].array[5] = 1;					//��ĭ ������ edge 5���� �������� ������ ǥ��
							arr3[b][c].number[5] = *vertexNum;			//��ĭ ������ edge 5�� vertex ��ġ �� �ֱ�
							arr3[b][c].array[9] = 1;					//��ĭ ������ edge 9���� �������� ������ ǥ��
							arr3[b][c].number[9] = *vertexNum;			//��ĭ ������ edge 9�� vertex ��ġ �� �ֱ�
																		//���� ������ ������ 1�� ����� edge�鿡 ������ ǥ��(0,1,9)
							arr3[b - 1][c].array[0] = 1;				//���� ������ edge 0���� �������� ������ ǥ��
							arr3[b - 1][c].number[0] = *vertexNum;		//���� ������ edge 0�� vertex ��ġ �� �ֱ�
							arr3[b - 1][c].array[1] = 1;				//���� ������ edge 1���� �������� ������ ǥ��
							arr3[b - 1][c].number[1] = *vertexNum;		//���� ������ edge 1�� vertex ��ġ �� �ֱ�
							arr3[b - 1][c].array[9] = 1;				//���� ������ edge 9���� �������� ������ ǥ��
							arr3[b - 1][c].number[9] = *vertexNum;		//���� ������ edge 9�� vertex ��ġ �� �ֱ�
						}
					}
					(*vertexNum)++;										//������ ���� 1�� ����
				}
			}
		}
		else if (i == 6)												//edge 6�� ����� ����
		{
			if ((b - 1 >= 0) && (counts == 1))							//�� ���� ĭ�� �� ���� ĭ�� �ƴϴ�
			{
				//��ĭ ������ edge 2 �Ǵ� ��ĭ ������ edge 4 �Ǵ� ���� ������ edge 0�� �̹� �������� ����
				if ((arr4[b - 1][c].array[2] == 1) || (arr3[b][c].array[4] == 1) || (arr3[b - 1][c].array[0] == 1))
				{
					if (arr4[b - 1][c].array[2] == 1)					//��ĭ ������ edge 2���� �̹� �������� ����
					{
						int k = arr4[b - 1][c].number[2];				//��ĭ ������ edge 2�� vertex ��ġ ��
						arr4[b][c].number[i] = k;						//�ش� ������ edge 6�� vertex ��ġ ���� ��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
						arr3[b][c].number[4] = k;						//��ĭ ������ edge 4�� vertex ��ġ ���� ��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
						arr3[b - 1][c].number[0] = k;					//���� ������ edge 0�� vertex ��ġ ���� ��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
						face_array[i] = k;								//face array�� ��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
					}
					else if (arr3[b][c].array[4] == 1)					//��ĭ ������ edge 4���� �̹� �������� ����
					{
						int k = arr3[b][c].number[4];					//��ĭ ������ edge 4�� vertex ��ġ ��
						arr4[b][c].number[i] = k;						//�ش� ������ edge 6�� vertex ��ġ ���� ��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].number[2] = k;					//��ĭ ������ edge 2�� vertex ��ġ ���� ��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
						arr3[b - 1][c].number[0] = k;					//���� ������ edge 0�� vertex ��ġ ���� ��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
						face_array[i] = k;								//face array�� ��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
					}
					else if (arr3[b - 1][c].array[0] == 1)				//���� ������ edge 0���� �̹� �������� ����
					{
						int k = arr3[b - 1][c].number[0];				//���� ������ edge 0�� vertex ��ġ ��
						arr4[b][c].number[i] = k;						//�ش� ������ edge 6�� vertex ��ġ ���� ���� ������ edge 0�� vertex ��ġ �� �ֱ�
						arr3[b][c].number[4] = k;						//��ĭ ������ edge 4�� vertex ��ġ ���� ���� ������ edge 0�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].number[2] = k;					//��ĭ ������ edge 2�� vertex ��ġ ���� ���� ������ edge 0�� vertex ��ġ �� �ֱ�
						face_array[i] = k;								//face array�� ���� ������ edge 0�� vertex ��ġ �� �ֱ�
					}
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 6���� �������� ������ ǥ��
					arr4[b - 1][c].array[2] = 1;						//��ĭ ������ edge 2���� �������� ������ ǥ��
					arr3[b][c].array[4] = 1;							//��ĭ ������ edge 4���� �������� ������ ǥ��
					arr3[b - 1][c].array[0] = 1;						//���� ������ edge 0���� �������� ������ ǥ��
				}
				else
				{														//��ĭ ������ edge 2 �Ǵ� ��ĭ ������ edge 4 �Ǵ� ���� ������ edge 0���� �ش���� ����
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z); //vertex���Ͽ� ���
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;							//�ش� ������ edge 6���� �������� ������ ǥ��
					arr4[b][c].number[i] = *vertexNum;					//�ش� ������ edge 6�� vertex ��ġ �� �ֱ�
					arr3[b][c].array[4] = 1;							//��ĭ ������ edge 4���� �������� ������ ǥ��
					arr3[b][c].number[4] = *vertexNum;					//��ĭ ������ edge 4�� vertex ��ġ �� �ֱ�
					arr3[b - 1][c].array[0] = 1;						//���� ������ edge 0���� �������� ������ ǥ��
					arr3[b - 1][c].number[0] = *vertexNum;				//���� ������ edge 0�� vertex ��ġ �� �ֱ�
					arr4[b - 1][c].array[2] = 1;						//��ĭ ������ edge 2�� �������� ������ ǥ��
					arr4[b - 1][c].number[2] = *vertexNum;				//��ĭ ������ edge 2�� vertex ��ġ �� �ֱ�
					face_array[i] = *vertexNum;							//face array�� �ش� ������ edge 6�� vertex ��ġ �� �ֱ�
					if (cubeVertexCheck[6][7] == 1)						//���࿡ �������� edge 6�� ������ 7���
					{													//�ش� ������ ������ 7�� ����� edge�鿡 ������ ǥ��(6,7,11) + 6 �̹� ����
						arr4[b][c].array[7] = 1;						//�ش� ������ edge 7���� �������� ������ ǥ��
						arr4[b][c].number[7] = *vertexNum;				//�ش� ������ edge 7�� vertex ��ġ �� �ֱ�
						arr4[b][c].array[11] = 1;						//�ش� ������ edge 11���� �������� ������ ǥ��
						arr4[b][c].number[11] = *vertexNum;				//�ش� ������ edge 11�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 4�� ����� edge�鿡 ������ ǥ��(4,7,8) + 4 �̹� ����
						arr3[b][c].array[7] = 1;						//��ĭ ������ edge 7���� �������� ������ ǥ��
						arr3[b][c].number[7] = *vertexNum;				//��ĭ ������ edge 7�� vertex ��ġ �� �ֱ�
						arr3[b][c].array[8] = 1;						//��ĭ ������ edge 8���� �������� ������ ǥ��
						arr3[b][c].number[8] = *vertexNum;				//��ĭ ������ edge 8�� vertex ��ġ �� �ֱ�
																		//���� ������ ������ 0�� ����� edge�鿡 ������ ǥ��(0,3,8) + 0 �̹� ����
						arr3[b - 1][c].array[3] = 1;					//���� ������ edge 3���� �������� ������ ǥ��
						arr3[b - 1][c].number[3] = *vertexNum;			//���� ������ edge 3�� vertex ��ġ �� �ֱ�
						arr3[b - 1][c].array[8] = 1;					//���� ������ edge 8���� �������� ������ ǥ��
						arr3[b - 1][c].number[8] = *vertexNum;			//���� ������ edge 8�� vertex ��ġ �� �ֱ�
																		//��ĭ ������ ������ 3�� ����� edge�鿡 ������ ǥ��(2,3,11) + 2 �̹� ����
						arr4[b - 1][c].array[3] = 1;					//��ĭ ������ edge 3���� �������� ������ ǥ��
						arr4[b - 1][c].number[3] = *vertexNum;			//��ĭ ������ edge 3�� vertex ��ġ �� �ֱ�
						arr4[b - 1][c].array[11] = 1;					//��ĭ ������ edge 11���� �������� ������ ǥ��
						arr4[b - 1][c].number[11] = *vertexNum;			//��ĭ ������ edge 11�� vertex ��ġ �� �ֱ�
						if (c >= 1)										//�� ���� ĭ�� �ƴϴ�.(+ �� ���� ĭ�� �� ���� ĭ�� �ƴϴ�)
						{												//��ĭ ������ ������ 6�� ����� edge�鿡 ������ ǥ��(5,6,10)
							arr4[b][c - 1].array[5] = 1;				//��ĭ ������ edge 5���� �������� ������ ǥ��
							arr4[b][c - 1].number[5] = *vertexNum;		//��ĭ ������ edge 5�� vertex ��ġ �� �ֱ�
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;

							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;

							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[6][6] == 1)//���࿡ ���� edg6�� vertex 6���
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr4[b - 1][c].array[10] = 1;
						arr4[b - 1][c].number[10] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;

						arr3[b][c].array[5] = 1;
						arr3[b][c].number[5] = *vertexNum;
						arr3[b][c].array[9] = 1;
						arr3[b][c].number[9] = *vertexNum;

						arr3[b - 1][c].array[1] = 1;
						arr3[b - 1][c].number[1] = *vertexNum;
						arr3[b - 1][c].array[9] = 1;
						arr3[b - 1][c].number[9] = *vertexNum;
					}

					(*vertexNum)++;
				}
			}
			else if (b - 1 >= 0) //������ �ƴϰ� �Ǿ��̴�
			{
				if (arr4[b - 1][c].array[2] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b - 1][c].number[2];
					face_array[i] = arr4[b - 1][c].number[2];
				}
				else if (arr4[b - 1][c].array[2] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr4[b - 1][c].number[2] = *vertexNum;
					arr4[b - 1][c].array[2] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[6][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[3] = 1;
						arr4[b - 1][c].number[3] = *vertexNum;

						if (c >= 1)
						{
							arr4[b][c - 1].array[5] = 1;
							arr4[b][c - 1].number[5] = *vertexNum;
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
						}

					}
					if (cubeVertexCheck[6][6] == 1)
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr4[b - 1][c].array[10] = 1;
						arr4[b - 1][c].number[10] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;
					}

					(*vertexNum)++;
				}
			}
			else if (counts == 1) // �Ǿ��� �ƴѵ� �� ����
			{
				if (arr3[b][c].array[4] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr3[b][c].number[4];
					face_array[i] = arr3[b][c].number[4];
				}
				else if (arr3[b][c].array[4] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr3[b][c].number[4] = *vertexNum;
					arr3[b][c].array[4] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[6][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr3[b][c].number[7] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[8] = *vertexNum;
						arr3[b][c].array[8] = 1;
						if (c >= 1)
						{
							arr4[b][c - 1].array[5] = 1;
							arr4[b][c - 1].number[5] = *vertexNum;
							arr4[b][c - 1].array[6] = 1;
							arr4[b][c - 1].number[6] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;

							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[6][6] == 1)
					{
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr3[b][c].number[5] = *vertexNum;
						arr3[b][c].array[5] = 1;
						arr3[b][c].number[9] = *vertexNum;
						arr3[b][c].array[9] = 1;
					}
					(*vertexNum)++;

				}
			}
		}//�Ϸ�
		else if (i == 7)
		{
			if ((b - 1) >= 0 && (c - 1) >= 0)//������ �ƴϰ� �� ���� �ƴϴ� �� �հ���
			{
				if ((arr4[b][c - 1].array[5] == 1) || (arr4[b - 1][c].array[3] == 1) || (arr4[b - 1][c - 1].array[1] == 1))
				{
					if (arr4[b][c - 1].array[5] == 1)
					{
						int k = arr4[b][c - 1].number[5];
						arr4[b][c].number[i] = k;
						arr4[b - 1][c].number[3] = k;
						arr4[b - 1][c - 1].number[1] = k;
						face_array[i] = k;
					}
					else if (arr4[b - 1][c].array[3] == 1)
					{
						int k = arr4[b - 1][c].number[3];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[5] = k;
						arr4[b - 1][c - 1].number[1] = k;
						face_array[i] = k;
					}
					else if (arr4[b - 1][c - 1].array[1] == 1)
					{
						int k = arr4[b - 1][c - 1].number[1];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[5] = k;
						arr4[b - 1][c].number[3] = k;
						face_array[i] = k;
					}
					arr4[b][c - 1].array[5] = 1;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c - 1].array[1] = 1;
					arr4[b][c].array[i] = 1;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					arr4[b][c - 1].number[5] = *vertexNum;
					arr4[b][c - 1].array[5] = 1;
					arr4[b - 1][c].number[3] = *vertexNum;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c - 1].number[1] = *vertexNum;
					arr4[b - 1][c - 1].array[1] = 1;
					face_array[i] = *vertexNum;

					if (cubeVertexCheck[7][7] == 1) // edge 7�� vertex 7
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						arr4[b][c - 1].array[10] = 1;

						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[2] = *vertexNum;
						arr4[b - 1][c].array[2] = 1;

						arr4[b - 1][c - 1].number[2] = *vertexNum;
						arr4[b - 1][c - 1].array[2] = 1;
						arr4[b - 1][c - 1].number[10] = *vertexNum;
						arr4[b - 1][c - 1].array[10] = 1;
						if (counts == 1)//�Ǿյ� �ƴϴ�
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;

							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)// edge 7�� vertex 4
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;

						arr4[b - 1][c].number[8] = *vertexNum;
						arr4[b - 1][c].array[8] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;

						arr4[b - 1][c - 1].number[0] = *vertexNum;
						arr4[b - 1][c - 1].array[0] = 1;
						arr4[b - 1][c - 1].number[9] = *vertexNum;
						arr4[b - 1][c - 1].array[9] = 1;
					}
					(*vertexNum)++;
				}

			}
			else if (b - 1 >= 0) // ������ �ƴϰ� �ǿ��̴� �Ǿո�
			{
				if (arr4[b - 1][c].array[3] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b - 1][c].number[3];
					face_array[i] = arr4[b - 1][c].number[3];
				}
				else if (arr4[b - 1][c].array[3] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b - 1][c].array[3] = 1;
					arr4[b - 1][c].number[3] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[7][7] == 1)
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b - 1][c].array[11] = 1;
						arr4[b - 1][c].number[11] = *vertexNum;
						arr4[b - 1][c].array[2] = 1;
						arr4[b - 1][c].number[2] = *vertexNum;
						if (counts == 1)//�Ǿյ� �ƴϴ�
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b - 1][c].array[8] = 1;
						arr4[b - 1][c].number[8] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
			else if (c - 1 >= 0) // �� ���� �ƴϰ� �� ����
			{
				if (arr4[b][c - 1].array[5] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b][c - 1].number[5];
					face_array[i] = arr4[b][c - 1].number[5];
				}
				else if (arr4[b][c - 1].array[5] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[5] = 1;
					arr4[b][c - 1].number[5] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[7][7] == 1)
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[10] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						if (counts == 1)
						{
							arr3[b][c].number[4] = *vertexNum;
							arr3[b][c].array[4] = 1;
							arr3[b][c].number[8] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[7] = *vertexNum;
							arr3[b][c].array[7] = 1;

							arr3[b][c - 1].number[4] = *vertexNum;
							arr3[b][c - 1].array[4] = 1;
							arr3[b][c - 1].number[5] = *vertexNum;
							arr3[b][c - 1].array[5] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[7][4] == 1)
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//�Ϸ�
		else if (i == 3)
		{
			if (c - 1 >= 0)//�� ������ �ƴϴ�
			{
				if (arr4[b][c - 1].array[1] == 1)
				{
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = arr4[b][c - 1].number[1];
					face_array[i] = arr4[b][c - 1].number[1];
				}
				else if (arr4[b][c - 1].array[1] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[1] = 1;
					arr4[b][c - 1].number[1] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[3][3] == 1)//���� edge 3�� vertex 3 ���̸�
					{
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;

						arr4[b][c - 1].array[10] = 1;
						arr4[b][c - 1].number[10] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						if (counts == 1)
						{
							arr3[b][c].array[0] = 1;
							arr3[b][c].number[0] = *vertexNum;
							arr3[b][c].array[3] = 1;
							arr3[b][c].number[3] = *vertexNum;
							arr3[b][c].array[8] = 1;
							arr3[b][c].number[8] = *vertexNum;

							arr3[b][c - 1].array[0] = 1;
							arr3[b][c - 1].number[0] = *vertexNum;
							arr3[b][c - 1].array[1] = 1;
							arr3[b][c - 1].number[1] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[3][0] == 1)//���࿡ edge 3�� vertex 0 ���̸�
					{
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;

						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//�Ϸ�
		else if (i == 8)
		{
			if (c - 1 >= 0)//�ǿ��� �ƴ�
			{
				if (arr4[b][c - 1].array[9] == 1)
				{
					int k = arr4[b][c - 1].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr4[b][c - 1].array[9] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[9] = 1;
					arr4[b][c - 1].number[9] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[8][4] == 1)//���࿡ edge 8�� vertex 4�̸�
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;

						arr4[b][c - 1].array[4] = 1;
						arr4[b][c - 1].number[4] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						if (b >= 1)
						{
							arr4[b - 1][c].array[0] = 1;
							arr4[b - 1][c].number[0] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[8] = 1;
							arr4[b - 1][c].number[8] = *vertexNum;

							arr4[b - 1][c - 1].array[0] = 1;
							arr4[b - 1][c - 1].number[0] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[9] = 1;
							arr4[b - 1][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[8][0] == 1)//���࿡ edge 8�� vertex 0�̸�
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;

						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[1] = *vertexNum;
					}

					(*vertexNum)++;
				}

			}
		}//�Ϸ�
		else if (i == 11)
		{
			if ((c - 1) >= 0 && (counts == 1))//�� ���� �ƴ� �� �յ� �ƴ� ������ ����
			{
				if ((arr4[b][c - 1].array[10] == 1) || (arr3[b][c].array[8] == 1) || (arr3[b][c - 1].array[9] == 1))
				{
					if (arr4[b][c - 1].array[10] == 1)
					{
						int k = arr4[b][c - 1].number[10];
						arr4[b][c].number[i] = k;
						arr3[b][c].number[8] = k;
						arr3[b][c - 1].number[9] = k;
						face_array[i] = k;
					}
					else if (arr3[b][c].array[8] == 1)
					{
						int k = arr3[b][c].number[8];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[10] = k;
						arr3[b][c - 1].number[9] = k;
						face_array[i] = k;
					}
					else if (arr3[b][c - 1].array[9] == 1)
					{
						int k = arr3[b][c - 1].number[9];
						arr4[b][c].number[i] = k;
						arr4[b][c - 1].number[10] = k;
						arr3[b][c].number[8] = k;
						face_array[i] = k;
					}
					arr4[b][c - 1].array[10] = 1;
					arr3[b][c].array[8] = 1;
					arr3[b][c - 1].array[9] = 1;
					arr4[b][c].array[i] = 1;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].number[10] = *vertexNum;
					arr4[b][c - 1].array[10] = 1;
					arr3[b][c].number[8] = *vertexNum;
					arr3[b][c].array[8] = 1;
					arr3[b][c - 1].number[9] = *vertexNum;
					arr3[b][c - 1].array[9] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7] == 1)//���� edge 11�� vertex 7�̸�
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;

						arr3[b][c].number[7] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[4] = 1;

						arr3[b][c - 1].number[4] = *vertexNum;
						arr3[b][c - 1].array[4] = 1;
						arr3[b][c - 1].number[5] = *vertexNum;
						arr3[b][c - 1].array[5] = 1;
						if (b >= 1)//������ �ƴϾ�
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;

							arr3[b - 1][c - 1].number[0] = *vertexNum;
							arr3[b - 1][c - 1].array[0] = 1;
							arr3[b - 1][c - 1].number[1] = *vertexNum;
							arr3[b - 1][c - 1].array[1] = 1;
							arr3[b - 1][c - 1].number[9] = *vertexNum;
							arr3[b - 1][c - 1].array[9] = 1;
						}
					}
					if (cubeVertexCheck[11][3] == 1)//���� edge 11�� vertex 3�̸�
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;

						arr3[b][c].number[0] = *vertexNum;
						arr3[b][c].array[0] = 1;
						arr3[b][c].number[3] = *vertexNum;
						arr3[b][c].array[3] = 1;

						arr3[b][c - 1].number[0] = *vertexNum;
						arr3[b][c - 1].array[0] = 1;
						arr3[b][c - 1].number[1] = *vertexNum;
						arr3[b][c - 1].array[1] = 1;
					}

					(*vertexNum)++;
				}
			}
			else if (c - 1 >= 0)// �� ���� �ƴϰ� �Ǿ��̴� ������ ��
			{
				if (arr4[b][c - 1].array[10] == 1)
				{
					int k = arr4[b][c - 1].number[10];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr4[b][c - 1].array[10] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c - 1].array[10] = 1;
					arr4[b][c - 1].number[10] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7])
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr4[b][c - 1].number[6] = *vertexNum;
						arr4[b][c - 1].array[6] = 1;
						arr4[b][c - 1].number[5] = *vertexNum;
						arr4[b][c - 1].array[5] = 1;
						if (b >= 1)
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr4[b - 1][c - 1].number[1] = *vertexNum;
							arr4[b - 1][c - 1].array[1] = 1;
							arr4[b - 1][c - 1].number[2] = *vertexNum;
							arr4[b - 1][c - 1].array[2] = 1;
							arr4[b - 1][c - 1].number[10] = *vertexNum;
							arr4[b - 1][c - 1].array[10] = 1;
						}
					}
					if (cubeVertexCheck[11][3])
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[2] = *vertexNum;
						arr4[b][c - 1].array[2] = 1;
					}
					(*vertexNum)++;
				}
			}
			if (counts == 1) // �Ǿ��� �ƴѵ� �ǿ��� ���� ��
			{
				if (arr3[b][c].array[8] == 1)
				{
					int k = arr3[b][c].number[8];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[8] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[8] = 1;
					arr3[b][c].number[8] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[11][7] == 1)
					{
						arr4[b][c].number[7] = *vertexNum;
						arr4[b][c].array[7] = 1;
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;

						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[7] = 1;
						arr3[b][c].number[4] = *vertexNum;
						if (b >= 1)	//������ �ƴ�
						{
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[3] = *vertexNum;
							arr4[b - 1][c].array[3] = 1;
							arr4[b - 1][c].number[11] = *vertexNum;
							arr4[b - 1][c].array[11] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[3] = *vertexNum;
							arr3[b - 1][c].array[3] = 1;
							arr3[b - 1][c].number[8] = *vertexNum;
							arr3[b - 1][c].array[8] = 1;
						}
					}
					if (cubeVertexCheck[11][3] == 1)
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;

						arr3[b][c].array[3] = 1;
						arr3[b][c].number[3] = *vertexNum;
						arr3[b][c].array[0] = 1;
						arr3[b][c].number[0] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//�Ϸ�
		else if (i == 2)
		{
			if (counts == 1)//�Ǿ��� �ƴҶ� ���� �ǿ�����
			{
				if (arr3[b][c].array[0] == 1)
				{
					int k = arr3[b][c].number[0];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[0] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[0] = 1;
					arr3[b][c].number[0] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[2][3] == 1)//����2���� vertex 3
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[11] = *vertexNum;
						arr4[b][c].array[11] = 1;

						arr3[b][c].array[8] = 1;
						arr3[b][c].number[8] = *vertexNum;
						arr3[b][c].array[3] = 1;
						arr3[b][c].number[3] = *vertexNum;
						if (c >= 1)
						{
							arr4[b][c - 1].number[1] = *vertexNum;
							arr4[b][c - 1].array[1] = 1;
							arr4[b][c - 1].number[2] = *vertexNum;
							arr4[b][c - 1].array[2] = 1;
							arr4[b][c - 1].number[10] = *vertexNum;
							arr4[b][c - 1].array[10] = 1;

							arr3[b][c - 1].array[0] = 1;
							arr3[b][c - 1].number[0] = *vertexNum;
							arr3[b][c - 1].array[1] = 1;
							arr3[b][c - 1].number[1] = *vertexNum;
							arr3[b][c - 1].array[9] = 1;
							arr3[b][c - 1].number[9] = *vertexNum;
						}
					}
					if (cubeVertexCheck[2][2] == 1)//����2���� vertex 2
					{
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						arr3[b][c].array[9] = 1;
						arr3[b][c].number[9] = *vertexNum;
						arr3[b][c].array[1] = 1;
						arr3[b][c].number[1] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}

		}//�Ϸ�
		else if (i == 10)
		{
			if (counts == 1)//�Ǿ��� �ƴ� ���� �ǿ� ��
			{
				if (arr3[b][c].array[9] == 1)
				{
					int k = arr3[b][c].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else if (arr3[b][c].array[9] == 0)
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					arr3[b][c].array[9] = 1;
					arr3[b][c].number[9] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[10][6] == 1)//����10 vertex 6
					{
						arr4[b][c].number[6] = *vertexNum;
						arr4[b][c].array[6] = 1;
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;

						arr3[b][c].array[4] = 1;
						arr3[b][c].number[4] = *vertexNum;
						arr3[b][c].array[5] = 1;
						arr3[b][c].number[5] = *vertexNum;
						if (b >= 1) // ������ �Ƴ� 
						{
							arr4[b - 1][c].number[1] = *vertexNum;
							arr4[b - 1][c].array[1] = 1;
							arr4[b - 1][c].number[2] = *vertexNum;
							arr4[b - 1][c].array[2] = 1;
							arr4[b - 1][c].number[10] = *vertexNum;
							arr4[b - 1][c].array[10] = 1;

							arr3[b - 1][c].number[0] = *vertexNum;
							arr3[b - 1][c].array[0] = 1;
							arr3[b - 1][c].number[1] = *vertexNum;
							arr3[b - 1][c].array[1] = 1;
							arr3[b - 1][c].number[9] = *vertexNum;
							arr3[b - 1][c].array[9] = 1;
						}
					}
					if (cubeVertexCheck[10][2] == 1)//����10 vertex 2
					{
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;

						arr3[b][c].array[0] = 1;
						arr3[b][c].number[0] = *vertexNum;
						arr3[b][c].array[1] = 1;
						arr3[b][c].number[1] = *vertexNum;
					}
					(*vertexNum)++;
				}
			}
		}//�Ϸ�
		else if (i == 0) // edge 0
		{
			if (c >= 1)
			{
				if ((arr4[b][c - 1].array[0] == 1) && (cubeVertexCheck[0][0] == 1))
				{
					int k = arr4[b][c - 1].number[0];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[0][0] == 1)//����0 vertex 0
					{
						arr4[b][c].number[3] = *vertexNum;
						arr4[b][c].array[3] = 1;
						arr4[b][c].number[8] = *vertexNum;
						arr4[b][c].array[8] = 1;
						//c>=1
						arr4[b][c - 1].number[0] = *vertexNum;
						arr4[b][c - 1].array[0] = 1;
						arr4[b][c - 1].number[1] = *vertexNum;
						arr4[b][c - 1].array[1] = 1;
						arr4[b][c - 1].number[9] = *vertexNum;
						arr4[b][c - 1].array[9] = 1;
					}
					if (cubeVertexCheck[0][1] == 1)//����0 vertex 1
					{
						arr4[b][c].number[9] = *vertexNum;
						arr4[b][c].array[9] = 1;
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
					}
					(*vertexNum)++;
				}
			}
			else // c < 1 ==  c=0
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].number[i] = *vertexNum;
				arr4[b][c].array[i] = 1;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[0][0] == 1)//����0 vertex 0
				{
					arr4[b][c].number[3] = *vertexNum;
					arr4[b][c].array[3] = 1;
					arr4[b][c].number[8] = *vertexNum;
					arr4[b][c].array[8] = 1;
				}
				if (cubeVertexCheck[0][1] == 1)//����0 vertex 1
				{
					arr4[b][c].number[9] = *vertexNum;
					arr4[b][c].array[9] = 1;
					arr4[b][c].number[1] = *vertexNum;
					arr4[b][c].array[1] = 1;
				}
				(*vertexNum)++;
			}
		}
		else if (i == 1)
		{
			if (counts == 1)//�Ǿ��� �ƴϴ�
			{
				if ((arr3[b][c].array[1] == 1) && cubeVertexCheck[1][2] == 1)//�տ� �̹� ����
				{
					int k = arr3[b][c].number[1];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].number[i] = *vertexNum;
					arr4[b][c].array[i] = 1;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[1][1] == 1)//����1 vertex 1
					{
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;
						arr4[b][c].number[9] = *vertexNum;
						arr4[b][c].array[9] = 1;
					}
					if (cubeVertexCheck[1][2] == 1)//����1 vertex 2
					{
						arr4[b][c].number[2] = *vertexNum;
						arr4[b][c].array[2] = 1;
						arr4[b][c].number[10] = *vertexNum;
						arr4[b][c].array[10] = 1;

						if (counts == 1)
						{
							arr3[b][c].number[0] = *vertexNum;
							arr3[b][c].array[0] = 1;
							arr3[b][c].number[1] = *vertexNum;
							arr3[b][c].array[1] = 1;
							arr3[b][c].number[9] = *vertexNum;
							arr3[b][c].array[9] = 1;
						}
					}
					(*vertexNum)++;
				}
			}
			else //count ==0 �Ǿ�
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].number[i] = *vertexNum;
				arr4[b][c].array[i] = 1;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[1][1] == 1)//����1 vertex 1
				{
					arr4[b][c].number[0] = *vertexNum;
					arr4[b][c].array[0] = 1;
					arr4[b][c].number[9] = *vertexNum;
					arr4[b][c].array[9] = 1;
				}
				if (cubeVertexCheck[1][2] == 1)//����1 vertex 2
				{
					arr4[b][c].number[2] = *vertexNum;
					arr4[b][c].array[2] = 1;
					arr4[b][c].number[10] = *vertexNum;
					arr4[b][c].array[10] = 1;
				}
				(*vertexNum)++;
			}
		}
		else if (i == 9)
		{
			if (b >= 1)
			{
				if ((arr4[b - 1][c].array[9] == 1) && (cubeVertexCheck[9][5] == 1))
				{
					int k = arr4[b - 1][c].number[9];
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = k;
					face_array[i] = k;
				}
				else
				{
					fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
					vertexXSum += step_size * vertlist[i].x;
					vertexYSum += step_size * vertlist[i].y;
					vertexZSum += step_size * vertlist[i].z;
					arr4[b][c].array[i] = 1;
					arr4[b][c].number[i] = *vertexNum;
					face_array[i] = *vertexNum;
					if (cubeVertexCheck[9][1] == 1)//����9 vertex 1
					{
						arr4[b][c].number[0] = *vertexNum;
						arr4[b][c].array[0] = 1;
						arr4[b][c].number[1] = *vertexNum;
						arr4[b][c].array[1] = 1;
					}
					if (cubeVertexCheck[9][5] == 1)//����9 vertex 5
					{
						arr4[b][c].number[4] = *vertexNum;
						arr4[b][c].array[4] = 1;
						arr4[b][c].number[5] = *vertexNum;
						arr4[b][c].array[5] = 1;
						arr4[b - 1][c].number[0] = *vertexNum;
						arr4[b - 1][c].array[0] = 1;
						arr4[b - 1][c].number[1] = *vertexNum;
						arr4[b - 1][c].array[1] = 1;
						arr4[b - 1][c].number[9] = *vertexNum;
						arr4[b - 1][c].array[9] = 1;
					}
					(*vertexNum)++;
				}
			}
			else // b = 0
			{
				fprintf(fpVertex, "%lf %lf %lf\n", step_size * vertlist[i].x, step_size * vertlist[i].y, step_size * vertlist[i].z);
				vertexXSum += step_size * vertlist[i].x;
				vertexYSum += step_size * vertlist[i].y;
				vertexZSum += step_size * vertlist[i].z;
				arr4[b][c].array[i] = 1;
				arr4[b][c].number[i] = *vertexNum;
				face_array[i] = *vertexNum;
				if (cubeVertexCheck[9][1] == 1)//����9 vertex 1
				{
					arr4[b][c].number[0] = *vertexNum;
					arr4[b][c].array[0] = 1;
					arr4[b][c].number[1] = *vertexNum;
					arr4[b][c].array[1] = 1;
				}
				if (cubeVertexCheck[9][5] == 1)//����9 vertex 5
				{
					arr4[b][c].number[4] = *vertexNum;
					arr4[b][c].array[4] = 1;
					arr4[b][c].number[5] = *vertexNum;
					arr4[b][c].array[5] = 1;
				}
				(*vertexNum)++;
			}

		}
	}
}


Point pointcal(Point p1, Point p2, double val1, double val2) //edge���� ������ vertex�� ��ǥ �� ���
{
	Point p;
	if (abs(cl - val1) < 0.00001)
	{
		return p1;
	}
	if (abs(cl - val2) < 0.00001)
	{
		return p2;
	}
	if (abs(val1 - val2) < 0.00001)
	{

		return p1;
	}
	double mu = (cl - val1) / (val2 - val1);
	p.x = p1.x + mu * (p2.x - p1.x);
	p.y = p1.y + mu * (p2.y - p1.y);
	p.z = p1.z + mu * (p2.z - p1.z);

	return p;
}

void getEdgeLength(Point p1, Point p2, Point p3)
{
	//double length1, length2, length3

	length1 = 0;
	length2 = 0;
	length3 = 0;

	length1 = pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2) + pow((p2.z - p1.z), 2);
	length1 = sqrt(length1);

	length2 = pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2) + pow((p3.z - p1.z), 2);
	length2 = sqrt(length2);

	length3 = pow((p2.x - p3.x), 2) + pow((p2.y - p3.y), 2) + pow((p2.z - p3.z), 2);
	length3 = sqrt(length3);

}

void convertVertex(Point p1, Point p2, Point p3)
{

}

double shortestEdge(double a, double b, double c)
{
	if (a <= b)
	{
		if (a <= c)
			return a;
		else
			return c;
	}
	else //a > b
	{
		if (b <= c)
			return b;
		else
			return c;
	}
}
double longestEdge(double a, double b, double c)
{
	if (a >= b)
	{
		if (a >= c)
			return a;
		else
			return c;
	}
	else //a < b
	{
		if (b >= c)
			return b;
		else
			return c;
	}
}