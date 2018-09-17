#include "stdafx.h"
#if defined(UNICODE)
#define _tcout std::wcout
#else
#define _tcout std::cout
#endif
using namespace Eigen;
void GenMXH() {
	using namespace std;
	VectorXd mxl(50), mxl1(1000), mxl2(2000), mxl3(5000), mxl4(1000);
	mxl.setOnes(); mxl1.setOnes(); mxl2.setOnes(); mxl3.setOnes(); mxl4.setOnes();
	mxl *= 2.4; mxl1 *= 2.4; mxl2 *= 2.4; mxl3 *= 2.4; mxl4 *= 2.4;
	OutData oml, oml1, oml2, oml3, oml4;
	ProbData MXL = { "MXLHIB",0.0 };
	LPB(MXL, mxl, GenMXHILB, oml);
	LPB(MXL, mxl1, GenMXHILB, oml1);
	LPB(MXL, mxl2, GenMXHILB, oml2);
	LPB(MXL, mxl3, GenMXHILB, oml3);
	LPB(MXL, mxl4, GenMXHILB, oml4);
	ofstream myfi;
	myfi.open("afile2d4Start.txt");
	myfi << '8' << '&' << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << '9' << '&' << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "10" << '&' << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "11" << '&' << oml3.Error << '&' << oml3.No_func_eval << '&' << oml3.k << '&' << oml3.L << '&' << oml3.time << '&' << oml3.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "12" << '&' << oml4.Error << '&' << oml4.No_func_eval << '&' << oml4.k << '&' << oml4.L << '&' << oml4.time << '&' << oml4.t_CPX << "\\\\" << endl << "\\hline" << endl;

	myfi.close();
}
void smallProbs7() {
	const int Num_of_Probs = 7;
	int j = 1;
	VectorXd x0(2), x1(2), x2(2), x3(2), x4(2), x5(2), x6(2);
	x0 << 1, -0.1;
	x1 << 2, 2;
	x2 << 1, 1;
	x3 << -1, 5;
	x4 << -0.5, -0.5;
	x5 << 0.8, 0.6;
	x6 << 3, 2;
	Ref<VectorXd> X[Num_of_Probs] = {
		x0,x1,x2,x3,x4,x5,x6 };
	ProbData probArray[Num_of_Probs] = {
		{"CB2",1.9522245},
		{"CB3",2},
		{"DEM",-3},
		{"QL",7.2},
		{"LQ",-sqrt(2)},
		{"Mifflin1",-1},
		{"Wolfe",-8} };
	void(*FunctionPointers[Num_of_Probs])(const Ref<const VectorXd>&, double &, Ref<VectorXd>) = {
		CB2,CB3,DEM,QL,LQ,Mifflin1,Wolfe };
	OutData out;
	FILE * myfile;
	myfile = fopen("output2.txt", "a");
	for (int r = 0; r < Num_of_Probs; r++)
	{
		out = LPB(probArray[r], X[r], FunctionPointers[r]);
		fprintf(myfile, " %d & %e & %d&", r + 1, out.Error, out.No_func_eval);
		fprintf(myfile, "%d & %d & %.1e & %.2e \\\\ \n \\hline\n", out.k, out.L, out.time, out.t_CPX);
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	//smallProbs7();
	GenMXH();
	IloEnv env;
	IloModel model(env);
	IloCplex cplex(model);
	int n = 5;
	VectorXd x(n);
	x << 1, 2, 3, 4, 5;
	double Delta = 1.2;
	IloNumArray lb(env, n);
	IloNumArray ub(env, n);
	for (size_t i = 0; i < n; ++i)
	{
		lb[i] = x(i) - Delta;
		ub[i] = x(i) + Delta;
		//lb.data
		cout << *lb.data(i);
	}
	return 0;
}


