#include "Model.h"

double dX = -150; ///<tube speed

//double  = 250; // bird
TBird ch;
/*!
	\brief  The function creates a tube with a certain width and a coordinate along the X axis along which it moves. The gap between the pipe is generated opredlenie width but a randomly place the tube
*/
TTube CreateTube(int x)
{
	TTube result;

	result.X = x;
	result.Y = 50 + rand() % (600 - GAP_SIZE - 100);

	result.r = 15;

	return result;
}