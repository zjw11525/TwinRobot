#pragma once
#ifndef Kinematic_h
#define Kinematic_h
#include <vector>
#include "TcPch.h"
using namespace TC_VECTOR_NAMESPACE;

#define PI 3.1415926

// D - H ����
#define d1  0.28
#define d4  0.35014205
#define d6  0.0745
#define a2  0.34966093

typedef vector<vector<double>> Array;//��άdouble����
typedef vector<double> Theta;

class Kinematic
{
public:
	Kinematic();
	Array Fkine_Step(Theta theta);//����
	Theta Ikine_Step(Array T, Theta Angle_Last);//����
	~Kinematic();
};

#endif