#include "Kinematic.h"


#define cosd(x) cos_(x * 180 / PI)
#define sind(x) sin_(x * 180 / PI)
// D - H 参数
double d1 = 0.28;
double d4 = 0.35014205;
double d6 = 0.0745;
double a2 = 0.34966093;


typedef double(*PoseArray)[4];//二维数组，相当于4个指针，可以指向

PoseArray Fkine_Final(double Theta[])
{
	Theta[1] = Theta[1] - 90; //offset

	double T[4][4];

	//计算三角函数
	double s1 = sind(Theta[0]);
	double c1 = cosd(Theta[0]);

	double s2 = sind(Theta[1]);
	double c2 = cosd(Theta[1]);

	double s23 = sind(Theta[1] + Theta[2]);
	double c23 = cosd(Theta[1] + Theta[2]);

	double s4 = sind(Theta[3]);
	double c4 = cosd(Theta[3]);

	double s5 = sind(Theta[4]);
	double c5 = cosd(Theta[4]);

	double s6 = sind(Theta[5]);
	double c6 = cosd(Theta[5]);


	double a = c23*(c4*c5*c6 - s4*s6) - s23*s5*c6;
	double b = c23*(-c4*c5*s6 - s4*c6) + s23*s5*s6;
	double c = -c23*c4*s5 - s23*c5;
	double d = -c23*c4*s5*d6 - s23*(c5*d6 + d4) + a2*c2;
	double e = s23*(c4*c5*c6 - s4*s6) + c23*s5*c6;
	double f = s23*(-c4*c5*s6 - s4*c6) - c23*s5*s6;
	double g = -s23*c4*s5 + c23*c5;
	double h = -s23*c4*s5*d6 + c23*(c5*d6 + d4) + a2*s2;
	double i = -s4*c5*c6 - c4*s6;
	double j = s4*c5*s6 - c4*c6;
	double k = s4*s5;
	double l = s4*s5*d6;


	T[0][0] = c1*a - s1*i;
	T[0][1] = c1*b - s1*j;
	T[0][2] = c1*c - s1*k;
	T[0][3] = c1*d - s1*l;
	T[1][0] = s1*a + c1*i;
	T[1][1] = s1*b + c1*j;
	T[1][2] = s1*c + c1*k;
	T[1][3] = s1*d + c1*l;
	T[2][0] = -e;
	T[2][1] = -f;
	T[2][2] = -g;
	T[2][3] = -h + d1;
	T[3][0] = 0;
	T[3][1] = 0;
	T[3][2] = 0;
	T[3][3] = 1;

	return T;
}





