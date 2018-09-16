#include "stdafx.h"
using namespace Eigen;
//void smallProbs7() {
//	const int Num_of_Probs = 7;
//	int j = 1;
//	VectorXd x0(2), x1(2), x2(2), x3(2), x4(2), x5(2), x6(2);
//	x0 << 1, -0.1;
//	x1 << 2, 2;
//	x2 << 1, 1;
//	x3 << -1, 5;
//	x4 << -0.5, -0.5;
//	x5 << 0.8, 0.6;
//	x6 << 3, 2;
//	Ref<VectorXd> X[Num_of_Probs] = {
//		x0,x1,x2,x3,x4,x5,x6 };
//	ProbData probArray[Num_of_Probs] = {
//		{"CB2",1.9522245},
//		{"CB3",2},
//		{"DEM",-3},
//		{"QL",7.2},
//		{"LQ",-sqrt(2)},
//		{"Mifflin1",-1},
//		{"Wolfe",-8} };
//	void(*FunctionPointers[Num_of_Probs])(const Ref<const VectorXd>&, double &, Ref<VectorXd>) = {
//		CB2,CB3,DEM,QL,LQ,Mifflin1,Wolfe };
//	OutData out;
//	FILE * myfile;
//	myfile = fopen("output2.txt", "a");
//	for (int r = 0; r < Num_of_Probs; r++)
//	{
//		out = LPB(probArray[r], X[r], FunctionPointers[r]);
//		fprintf(myfile, " %d & %e & %d&", r + 1, out.Error, out.No_func_eval);
//		fprintf(myfile, "%d & %d & %.1e & %.2e \\\\ \n \\hline\n", out.k, out.L, out.time, out.t_CPX);
//	}
//	
//}
