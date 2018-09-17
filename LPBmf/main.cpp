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
	OutData oml, oml1, oml2, oml3, oml4;
	ProbData MXL = { "MXLHIB",0.0 };
	/*LPBdelta1(MXL, mxl, GenMXHILB, oml);
	LPBdelta1(MXL, mxl1, GenMXHILB, oml1);
	LPBdelta1(MXL, mxl2, GenMXHILB, oml2);
	LPBdelta1(MXL, mxl3, GenMXHILB, oml3);
	LPBdelta1(MXL, mxl4, GenMXHILB, oml4);*/
	ofstream myfi;
	myfi.open("delta1NoCombined2d4.txt");
	//myfi << '8' << '&' << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	//myfi << '9' << '&' << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	//myfi << "10" << '&' << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	//myfi << "11" << '&' << oml3.Error << '&' << oml3.No_func_eval << '&' << oml3.k << '&' << oml3.L << '&' << oml3.time << '&' << oml3.t_CPX << "\\\\" << endl << "\\hline" << endl;
	//myfi << "12" << '&' << oml4.Error << '&' << oml4.No_func_eval << '&' << oml4.k << '&' << oml4.L << '&' << oml4.time << '&' << oml4.t_CPX << "\\\\" << endl << "\\hline" << endl;
	//// Now using new starting points
	mxl *= 2.4; mxl1 *= 2.4; mxl2 *= 2.4; mxl3 *= 2.4; mxl4 *= 2.4;
	LPBdelta1(MXL, mxl, GenMXHILB, oml);
	LPBdelta1(MXL, mxl1, GenMXHILB, oml1);
	LPBdelta1(MXL, mxl2, GenMXHILB, oml2);
	LPBdelta1(MXL, mxl3, GenMXHILB, oml3);
	LPBdelta1(MXL, mxl4, GenMXHILB, oml4);
	myfi << '13' << '&' << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << '14' << '&' << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "15" << '&' << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "16" << '&' << oml3.Error << '&' << oml3.No_func_eval << '&' << oml3.k << '&' << oml3.L << '&' << oml3.time << '&' << oml3.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "17" << '&' << oml4.Error << '&' << oml4.No_func_eval << '&' << oml4.k << '&' << oml4.L << '&' << oml4.time << '&' << oml4.t_CPX << "\\\\" << endl << "\\hline" << endl;

	myfi.close();
}
void smallProbs7() {
	using namespace std;
	const int Num_of_Probs = 7;
	//int j = 1,n=2,np=7;
	MatrixXd X(2,7);
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
	myfile.open("delta1output20.txt");
	for (size_t r = 0; r < Num_of_Probs; r++)
	{
		x=X.col(r);
		LPBdelta1(probArray[r],x, FunctionPointers[r],out);
		myfile << r+1 << '&' << out.Error << '&' << out.No_func_eval << '&' << out.k 
			<< '&' << out.L << '&' << out.time << '&' << out.t_CPX << "\\\\" << endl 
			<< "\\hline" << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
//	using namespace std;
	//smallProbs7();
	GenMXH();
	return 0;
}


