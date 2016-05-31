#include <Windows.h>
#ifndef __MODEL__
#define __MODEL__
#define SCREEN_WIDTH 800
#define GAP_SIZE 200
#define BIRD_SIZE 26
#define BIRD_SPOS 150
//#define VY_MAX 300
/*!
	\brief  TTube structure describes the parameters of the pipe, such as coordinate genereatsii pipe, 
	the gap between the pipe and the height of the pipe.
*/
struct TTube
{
	double X;///<coordinate generation pipe

	double Y;///<gap beetween tube

	double r;///<width tube
};
/*!
     \brief  TBird structure describes the parameters of the bird, such as coordinate generation bird, 
	speed and boost  bird , coordinate axis and speed along the coordinate axes
}; .
*/
struct TBird
{
	double X;///<coordinate generation bird
	double v, a;///<speed and boost
	double x, y;///<coordinate axis
	double vx, vy;///<speed along the coordinate axes
};
extern TBird ch;
extern 	double dX;
TTube CreateTube(int x);

#endif