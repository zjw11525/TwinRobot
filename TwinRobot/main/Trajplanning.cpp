//#include "TcPch.h"
#include "Trajplanning.h"
//����
Trajplanning::Trajplanning() {}
//����
Trajplanning::~Trajplanning()
{
	//cout << "Deleting Trajplanning object..." << endl;
}

vector<double> Trajplanning::ScurveGen(double Start, double End, double Velocity, double Acceleration, int Num)
{
	int N = Num;

	double ThetaStart = Start;
	double ThetaEnd = End;
	double VTheta = Velocity;
	double ATheta = Acceleration;
	double Tf = 1.8;

	double v = abs(VTheta / (ThetaEnd - ThetaStart));
	double a = abs(ATheta / (ThetaEnd - ThetaStart));

	vector<double> theta(N, 0);
	vector<double> s(N, 0);


	vector<double> T(7, 0);
	double V = 0;
	double A = 0;
	double J = 0;
	double TF = 0;
	for (int i = 0; i < 1000; i++)
	{
		J = (pow_(a, 2) * v) / (Tf*v*a - pow_(v, 2) - a);
		T[0] = a / J;
		T[1] = v / a - a / J; // t2 = v / a - t1;
		T[2] = T[0];
		T[3] = Tf - 2 * a / J - 2 * v / a;    // t4 = Tf - 4 * t1 - 2 * t2;
		T[4] = T[2];
		T[5] = T[1];
		T[6] = T[0];
		if (T[1] < -1e-6)
			a = sqrt_(v*J);
		else if (T[3] < -1e-6)
			v = Tf * a / 2 - a * a / J;
		else if (J < -1e-6)
			Tf = (pow_(v, 2) + a) / (v*a) + 1e-1;
		else break;
	}
	A = a;
	V = v;
	TF = Tf;

	vector<double> t(N, 0);
	int  j = 0;
	double count = 0;
	for (count = 0; count < TF; count += (TF / (N - 1)))	//t = linspace(0, TF, N);
		t[j++] = count;
	t[N - 1] = TF;

	for (int i = 0; i < N; i++)
	{
		if (i == N)
			a = a;

		s[i] = SCurveScaling(t[i], V, A, J, T, TF);
		theta[i] = ThetaStart + s[i] * (ThetaEnd - ThetaStart);
	}
	return theta;
}

double Trajplanning::SCurveScaling(double t, double V, double A, double J, vector<double> T, double Tf)
{
	double dt = 0;
	double s = 0;
	double t_temp = 0;

	if ((t >= 0) && (t <= T[0]))
		s = 1 / 6 * J * pow_(t, 3);
	else if ((t > T[0]) && t <= (T[0] + T[1]))
	{
		dt = t - T[0];
		s = 0.5 * A * pow_(dt, 2) + pow_(A, 2) / (2 * J) * dt + pow_(A, 3) / (6 * pow_(J, 2));
	}
	else if (t > (T[0] + T[1]) && t <= (T[0] + T[1] + T[2]))
	{
		dt = t - T[0] - T[1];
		s = -0.1667 * J*pow_(dt, 3) + 0.5 * A*pow_(dt, 2) + (A*T[1] + pow_(A, 2) / (2 * J))*dt
			+ 0.5 * A*pow_(T[1], 2) + pow_(A, 2) / (2 * J)*T[1] + pow_(A, 3) / (6 * pow_(J, 2));
	}
	else if (t > (T[0] + T[1] + T[2]) && t <= (T[0] + T[1] + T[2] + T[3]))
	{
		dt = t - T[0] - T[1] - T[2];
		s = V * dt + (-0.1667 * J*pow_(T[2], 3)) + 0.5 * A*pow_(T[2], 2) + (A*T[1] + pow_(A, 2) / (2 * J))*T[2]
			+ 0.5 * A*pow_(T[1], 2) + pow_(A, 2) / (2 * J)*T[1] + pow_(A, 3) / (6 * pow_(J, 2));
	}
	else if (t > (T[0] + T[1] + T[2] + T[3]) && t <= (T[0] + T[1] + T[2] + T[3] + T[4]))
	{
		t_temp = Tf - t;
		dt = t_temp - T[0] - T[1];
		s = -0.1667 * J*pow_(dt, 3) + 0.5 * A*pow_(dt, 2) + (A*T[1] + pow_(A, 2) / (2 * J))*dt
			+ 0.5 * A*pow_(T[1], 2) + pow_(A, 2) / (2 * J)*T[1] + pow_(A, 3) / (6 * pow_(J, 2));
		s = 1 - s;
	}
	else if (t > (T[0] + T[1] + T[2] + T[3] + T[4]) && t <= (T[0] + T[1] + T[2] + T[3] + T[4] + T[5]))
	{
		t_temp = Tf - t;
		dt = t_temp - T[0];
		s = 0.5 * A * pow_(dt, 2) + pow_(A, 2) / (2 * J) * dt + pow_(A, 3) / (6 * pow_(J, 2));
		s = 1 - s;
	}
	else if (t > (T[0] + T[1] + T[2] + T[3] + T[4] + T[5]) && t <= (T[0] + T[1] + T[2] + T[3] + T[4] + T[5] + T[6] + 1e5))
	{
		t_temp = Tf - t;
		s = 0.1667 * J * pow_(t_temp, 3);
		s = 1 - s;
	}
	return s;
}

Array Trajplanning::MoveLine(Array pose_start, Array trans, double Velocity, double Acceleration, double t)
{
	double transx = trans[0][3];
	double transy = trans[1][3];
	double transz = trans[2][3];
	double L = sqrt_(pow_(transx, 2) + pow_(transy, 2) + pow_(transz, 2));//�˶�����
	int N = ceil_(L / (Velocity*t)) + 1;//����岹����

	vector<double> s = ScurveGen(0, 1, Velocity, Acceleration, N);
	Array Position(3, vector<double>(N, 0));

	for (int i = 0; i < N; i++)
	{
		Position[0][i] = pose_start[0][3] + transx * s[i];
		Position[1][i] = pose_start[1][3] + transy * s[i];
		Position[2][i] = pose_start[2][3] + transz * s[i];
	}
	return Position;
}