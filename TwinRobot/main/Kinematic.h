#pragma once

#include "TcPch.h"
#include <vector>

using namespace TC_VECTOR_NAMESPACE;

#define PI 3.1415926

// D - H 参数
#define d1  0.28
#define d4  0.35014205
#define d6  0.0745
#define a2  0.34966093

typedef vector<vector<double>> Array;//二维double数组
typedef vector<double> Theta;

Array Fkine_Final(Theta theta);//正解
Theta Ikine_Step(Array T, Theta Angle_Last);//反解