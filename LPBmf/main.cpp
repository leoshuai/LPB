#include "stdafx.h"
#if defined(UNICODE)
#define _tcout std::wcout
#else
#define _tcout std::cout
#endif
using namespace Eigen;
void LPB(ProbData prob, VectorXd& x, void(*feval)(const VectorXd &, double &, VectorXd&), OutData & o)
// Added update for Delta. 2018 September	
//template<class X,typename T> OutData LPB(ProbData prob,X &x,T &feval)
	// Later optional input 
	// including options,pass value by reference.
	// Later I need to know the difference of explicit instantiation and implicit instantiation
	// and when to use them. // later I can set "Ref<VectorXd> x" to be "C x" where "C" is some class
	// so LPB can take vector<double> as arguments. This needs to be templated.
	// done! But inside this funciton there is still a line : VectorXd xStar(n),s(n);
	// how can I change it to X xStar,s;? I just did it and it works for Ref<Vector> 
	// I assume if clients only use vector<double> then it can also work as
	// long as it supports feval(X &x,double &y,S s) where X is type for x and S is type for 
	// subgradient vector. No! I just realized that there is inner product using eigen, and that X should 
	// be const but in the line there is a usage of X which means non-const type.
	// Conclusion: I need to move on for now and later if I can change this.
	// OLD version is template<typename T> OutData LPB(ProbData prob,const Ref<const VectorXd> x,T &feval)
	// Shuai Liu at 24/09/2015 6:00 PM
	// declaring a variable does not automatically add it to the model. I need to add it bu model.add(xv) after 
	// declaring it.
{
	using namespace std;
	using namespace Eigen;
	int n = x.size();
	int k = 0;
	int l = 0;
	int k_l = 0;
	bool b1 = false;
	double fx, ModelReduction, fxs, Delta, temp;
	VectorXd xStar(n), s(n);
	auto started = std::chrono::high_resolution_clock::now();
	feval(x, fx, s);
	Delta = 0.1*s.norm();
	//Delta = 1;
	IloEnv env;
	IloModel model(env);
	IloCplex cplex(model);
	//cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, 1e-9);
	//cplex.setParam(IloCplex::Param::Simplex::Tolerances::Feasibility,1e-9);
	IloNumVar z(env, -IloInfinity, IloInfinity);
	model.add(IloMinimize(env, z));
	IloNumArray lb(env, n);
	IloNumArray ub(env, n);
	IloNumArray xstar(env, n);
	// set lower and upper bounds
	size_t i;
	for (i = 0; i < n; ++i)
	{
		temp = *(x.data() + i);
		*lb.data(i) = temp - Delta;
		*ub.data(i) = temp + Delta;
		/*lb[i] = x(i) - Delta;
		ub[i] = x(i) + Delta;*/
		//lb.data
	}
	IloNumVarArray xv(env, lb, ub);
	model.add(xv);
	IloExpr expr(env);
	expr += fx - s.transpose()*x;
	for (i = 0; i < n; ++i)
		expr += s(i) * xv[i];
	//add the first cutting plane
	model.add(expr - z <= 0);
	cplex.setOut(env.getNullStream());
	const Param p;
	o.t_CPX = 0;
	/*auto done0 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done0 - started).count();
*/
	while (k < p.Iter_Limi)
	{
		cplex.resetTime();
		cplex.solve();
		o.t_CPX += cplex.getTime();
		// env.out()<<cplex.getStatus();
		if (cplex.getStatus() != IloAlgorithm::Status::Optimal)
		{
			env.out() << "\n Solution status = " << cplex.getStatus() << endl;
			// do something
			o.status = 1;
			break;
		}
		ModelReduction = fx - cplex.getObjValue();
		if (ModelReduction <= p.epsilon_tol)
		{
			b1 = true;
			o.status = 0;
			break;
		}
		cplex.getValues(xv, xstar);
		for (i = 0; i < n; ++i)
			*(xStar.data() + i) = *xstar.data(i);
		//xStar(i) = xstar[i];
		feval(xStar, fxs, s);
		if (fx - fxs >= p.m*ModelReduction)// serious step
		{
			x = xStar;
			fx = fxs;
			k_l = k + 1;
			l++;
			Delta = 2 * Delta;
			for (i = 0; i < n; i++)
			{
				temp = *(xStar.data() + i);
				*lb.data(i) = temp - Delta;
				*ub.data(i) = temp + Delta;
				//lb[i] = xStar(i) - Delta;
				//ub[i] = xStar(i) + Delta;
			}

		}
		else
		{
			Delta = 0.5 * Delta;
			for (i = 0; i < n; i++)
			{
				*lb.data(i) += Delta;
				*ub.data(i) -= Delta;
				//lb[i] = x(i) - Delta;
				//ub[i] = x(i) + Delta;
			}
		}
		xv.setBounds(lb, ub);
		IloExpr expr1(env);// I cannot just use the old expr because I don't know 
		// know how to reinitiate it.
		expr1 += fxs - s.transpose()*xStar;
		for (i = 0; i < n; ++i)
			expr1 += s(i) * xv[i];
		model.add(expr1 <= z);
		k++;
	}
	env.end();
	if (fx < fxs)
	{
		o.f_final = fx;
		o.Error = fx - prob.f_optimal;
	}
	else
	{
		o.f_final = fxs;
		o.Error = fxs - prob.f_optimal;
	}
	if (b1)
		cout << "\n SuccesS! Result:\nk=" << k << ", f_val=" << fx << ", error=" << o.Error << endl;
	else
	{
		cout << "\n iter limit Result:\nk=" << k << ", f_val=" << fx << ", error=" << o.Error << endl;
		o.status = 2;
	}
	//o.status=o.status;
	o.No_func_eval = k;
	o.k = k;
	o.L = k - l;
	auto done = std::chrono::high_resolution_clock::now();
	cout << o.status << " is the status\n";
	cout << o.Error << " is the error\n";
	cout << o.f_final << " is the final value\n";
	cout << o.k << " is the k\n";
	cout << o.L << " is the number of null steps\n";
	cout << o.No_func_eval << " is the no of func eval\n";
	std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(done - started);
	//o.time= std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
	o.time = elapsed.count();
	cout << o.time << " is the time\n";
	cout << o.t_CPX << " is the cplex time\n";
}

void GenMXH() {
	using namespace std;
	VectorXd mxl(50), mxl1(1000), mxl2(2000),mxl3(5000),mxl4(1000);
	mxl.setOnes(); mxl1.setOnes(); mxl2.setOnes(); mxl3.setOnes();mxl4.setOnes();
	mxl *= 2.4; mxl1 *=2.4; mxl2 *= 2.4; mxl3 *= 2.4;
	OutData oml, oml1, oml2,oml3,oml4;
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


