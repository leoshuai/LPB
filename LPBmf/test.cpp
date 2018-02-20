#include "stdafx.h"
#if defined(UNICODE)
#define _tcout std::wcout
#else
#define _tcout std::cout
#endif
// uncomment the following line to disable assert()
// #define NDEBUG
using namespace Eigen;
//std::ostream& operator<<(std::ostream& os, const OutData& outData) {
//	return os << '&' << outData.Error
//		<< '&' << outData.No_func_eval
//		<< '&' << outData.k
//		<< '&' << outData.L
//		<< '&' << outData.time
//		<< '&' << outData.t_CPX
//		<< "\\\\" << std::endl << "\\hline" << std::endl;
//
//}
int _tmain(int argc, _TCHAR* argv[])
	{
	using namespace std;
	const int Num_of_Probs=7;
	int j = 1;
	VectorXd x0(2),x1(2),x2(2),x3(2),x4(2),x5(2),x6(2);
	x0<<1,-0.1;
	x1<<2,2;
	x2<<1,1;
	x3<<-1,5;
	x4 << -0.5, -0.5;
	x5 << 0.8,0.6;
	x6<<3,2;
	Ref<VectorXd> X[Num_of_Probs]={
		x0,x1,x2,x3,x4,x5,x6};
	ProbData probArray[Num_of_Probs]={
		{"CB2",1.9522245},
		{"CB3",2},
		{"DEM",-3},
		{"QL",7.2},
		{"LQ",-sqrt(2)},
		{"Mifflin1",-1},
		{"Wolfe",-8}};
	void (*FunctionPointers[Num_of_Probs])(const Ref<const VectorXd>& ,double &,Ref<VectorXd> ) = { 
		CB2,CB3,DEM,QL,LQ,Mifflin1,Wolfe };
	OutData out;
	FILE * myfile;
	myfile = fopen("output.txt", "a");
	for (int r=0;r<Num_of_Probs;r++)
		{
		out= LPB(probArray[r],X[r],FunctionPointers[r]);
		fprintf(myfile, " %d & %e & %d&", r + 1, out.Error, out.No_func_eval);
		fprintf(myfile,"%d & %d & %.1e & %.2e \\\\ \n \\hline\n", out.k, out.L, out.time, out.t_CPX);
		/*myfile << r+1 << '&' << out.Error << '&' << out.No_func_eval;
		myfile << '&' << out.k << '&' << out.L << '&';
		myfile<<scientific<< out.time << '&' << out.t_CPX << "" << endl << "\\hline" << endl;*/


		}
	/*int n=100;
	VectorXd clq(n);
	clq.setOnes();
	clq*=-0.5;
	ProbData pr={"Chained_LQ",-(n-1)*sqrt(2)};
	LPB(pr,clq,Chained_LQ);
	double y0;
	VectorXd s0(2);
	Wolfe(x6,y0,s0);
	std::cout<<"x6="<<x6<<" and y0="<<y0<<" and s0="<<s0<<std::endl;*/

	VectorXd mxl(50), mxl1(1000), mxl2(2000);
	mxl.setOnes(); mxl1.setOnes(); mxl2.setOnes();
	mxl = mxl*0.4; mxl1 = mxl1*0.4; mxl2 = mxl2*0.4;
	OutData oml, oml1, oml2;
	ProbData MXL = { "MXLHIB",0.0 };
	oml=LPB(MXL, mxl, GenMXHILB);
	oml1=LPB(MXL, mxl1, GenMXHILB);
	oml2=LPB(MXL, mxl2, GenMXHILB);
	
	//copy(out, out + Num_of_Probs, ostream_iterator<OutData>(cout, "\n "));
		
	//for (j = 1; j < 8; j++)
	//{
	//	myfile << out[j-1];
	//	//myfile << j << '&' << out[j - 1].Error << '&' << out[j - 1].No_func_eval;
	//	//myfile <<'&' << out[j - 1].k << '&' << out[j - 1].L << '&' << out[j - 1].time << '&' << out[j - 1].t_CPX << "\\\\" << endl << "\\hline" << endl;
	//}
	ofstream myfi;
	myfi << '8' << '&' << oml.Error << '&' << oml.No_func_eval << '&' << oml.k << '&' << oml.L << '&' << oml.time << '&' << oml.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << '9'<< '&' << oml1.Error << '&' << oml1.No_func_eval << '&' << oml1.k << '&' << oml1.L << '&' << oml1.time << '&' << oml1.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi << "10" << '&' << oml2.Error << '&' << oml2.No_func_eval << '&' << oml2.k << '&' << oml2.L << '&' << oml2.time << '&' << oml2.t_CPX << "\\\\" << endl << "\\hline" << endl;
	myfi.close();
	return 0;
	}