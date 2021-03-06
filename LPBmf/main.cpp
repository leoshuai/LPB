#include "stdafx.h"
#if defined(UNICODE)
#define _tcout std::wcout
#else
#define _tcout std::cout
#endif
using namespace Eigen;
void GenMXH() {
	using namespace std;
	VectorXd mxl(50), mxl1(1000), mxl2(2000), mxl3(5000), mxl4(10000);
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
	myfi.open("UpdateDelta2d4.txt");
	myfi << '8' << '&' << scientific << setprecision(3) << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << defaultfloat << setprecision(2) << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << '9' << '&' << scientific << setprecision(3) << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << defaultfloat << setprecision(2) << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "10" << '&' << scientific << setprecision(3) << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << defaultfloat << setprecision(2) << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "11" << '&' << scientific << setprecision(3) << oml3.Error << '&' << oml3.No_func_eval << '&' << oml3.k << '&' << oml3.L << '&' << defaultfloat << setprecision(2) << oml3.time << '&' << oml3.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "12" << '&' << scientific << setprecision(3) << oml4.Error << '&' << oml4.No_func_eval << '&' << oml4.k << '&' << oml4.L << '&' << defaultfloat << setprecision(2) << oml4.time << '&' << oml4.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi.close();
	// Now using new starting points
	/*myfi.open("Delta12d4.txt");
	mxl *= 2.4; mxl1 *= 2.4; mxl2 *= 2.4; mxl3 *= 2.4; mxl4 *= 2.4;
	LPBdelta1(MXL, mxl, GenMXHILB, oml);
	LPBdelta1(MXL, mxl1, GenMXHILB, oml1);
	LPBdelta1(MXL, mxl2, GenMXHILB, oml2);
	LPBdelta1(MXL, mxl3, GenMXHILB, oml3);
	LPBdelta1(MXL, mxl4, GenMXHILB, oml4);
	myfi << "13" << '&' << scientific << setprecision(3) << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << defaultfloat << setprecision(2) << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "14" << '&' << scientific << setprecision(3) << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << defaultfloat << setprecision(2) << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "15" << '&' << scientific << setprecision(3) << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << defaultfloat << setprecision(2) << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "16" << '&' << scientific << setprecision(3) << oml3.Error << '&' << oml3.No_func_eval << '&' << oml3.k << '&' << oml3.L << '&' << defaultfloat << setprecision(2) << oml3.time << '&' << oml3.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "17" << '&' << scientific << setprecision(3) << oml4.Error << '&' << oml4.No_func_eval << '&' << oml4.k << '&' << oml4.L << '&' << defaultfloat << setprecision(2) << oml4.time << '&' << oml4.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi.close();*/
}
void smallProbs7() {
	using namespace std;
	const int Num_of_Probs = 7;
	//int j = 1,n=2,np=7;
	MatrixXd X(2, 7);
	X.col(0) << 1, -0.1;
	X.col(1) << 2, 2;
	X.col(2) << 1, 1;
	X.col(3) << -1, 5;
	X.col(4) << -0.5, -0.5;
	X.col(5) << 0.8, 0.6;
	X.col(6) << 3, 2;
	ProbData probArray[Num_of_Probs] = {
		{"CB2",1.9522245},
		{"CB3",2},
		{"DEM",-3},
		{"QL",7.2},
		{"LQ",-sqrt(2)},
		{"Mifflin1",-1},
		{"Wolfe",-8} };
	void(*FunctionPointers[Num_of_Probs])(const VectorXd &, double &, VectorXd &) = {
		CB2,CB3,DEM,QL,LQ,Mifflin1,Wolfe };
	VectorXd x(2);
	OutData out;
	ofstream myfile;
	myfile.open("outputDelta1.txt");
	for (size_t r = 0; r < Num_of_Probs; r++)
	{
		x = X.col(r);
		LPBdelta1(probArray[r], x, FunctionPointers[r], out);
		myfile << r + 1 << '&';
		myfile << scientific << setprecision(3) << out.Error;
		myfile<< '&' << out.No_func_eval << '&' << out.k			<< '&' << out.L << '&';
		myfile <<defaultfloat<<setprecision(2) << out.time << '&' <<			out.t_CPX << "\\\\" << endl
			<< "\\hline" << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	//smallProbs7();
	GenMXH();
	return 0;
}


