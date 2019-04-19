#pragma once
#ifndef Trajplanning_h
#define Trajplanning_h
#include "Kinematic.h"
#include <vector>
#include "TcPch.h"

using namespace TC_VECTOR_NAMESPACE;

class Trajplanning
{
public:
	Trajplanning();
	Array MoveLine(Array pose_start, Array trans, double Velocity, double Acceleration, double t);
	~Trajplanning();
	//
	Array DataBase;
private:
	vector<double> ScurveGen(double Start, double End, double Velocity, double Acceleration, int Num);
	double SCurveScaling(double t, double V, double A, double J, vector<double> T, double Tf);
};

#endif