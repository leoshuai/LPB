#include "stdafx.h"
using namespace Eigen;
void LPB(ProbData prob, VectorXd& x,
	void(*feval)(const VectorXd &, double &, VectorXd&), OutData & o)
	// Added update for Delta. 2018 September	
	// To do: eliminate xstar the IloNumArray by making feval accpeting something like 
	// feval(xstar.data())
	//template<class X,typename T> OutData LPB(ProbData prob,X &x,T &feval)
		// Later optional input 
		// including options,
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
	int n = x.size();
	int k = 0;
	int l = 0;// Iterator for serious steps
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
	while (k < p.Iter_Limi)
	{
		cplex.resetTime();
		cplex.solve();
		o.t_CPX += cplex.getTime();
		if (cplex.getStatus() != IloAlgorithm::Status::Optimal)
		{
			env.out() << "\n Solution status = " << cplex.getStatus() << endl;
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
		feval(xStar, fxs, s);
		if (fx - fxs >= p.m*ModelReduction)// serious step
		{
			x = xStar;
			fx = fxs;
			l++;
			Delta = 2 * Delta;
			for (i = 0; i < n; i++)
			{
				temp = *(xStar.data() + i);
				*lb.data(i) = temp - Delta;
				*ub.data(i) = temp + Delta;
			}
		}
		else
		{
			Delta = 0.5 * Delta;
			for (i = 0; i < n; i++)
			{
				*lb.data(i) += Delta;
				*ub.data(i) -= Delta;
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
		o.f_final = fx;		
	else
		o.f_final = fxs;	
	o.Error = o.f_final - prob.f_optimal;
	if (b1)
		cout << "\n SuccesS! Result:\nk=" << k << ", f_val=" << fx << ", error=" << o.Error << endl;
	else
	{
		cout << "\n iter limit Result:\nk=" << k << ", f_val=" << fx << ", error=" << o.Error << endl;
		o.status = 2;
	}
	o.No_func_eval = k;
	o.k = k;
	o.L = k - l;// Number of null steps = k minus the number of serious steps
	auto done = std::chrono::high_resolution_clock::now();
	cout << o.status << " is the status\n";
	cout << o.Error << " is the error\n";
	cout << o.f_final << " is the final value\n";
	cout << o.k << " is the k\n";
	cout << o.L << " is the number of null steps\n";
	cout << o.No_func_eval << " is the no of func eval\n";
	std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(done - started);
	o.time = elapsed.count();
	cout << o.time << " is the time\n";
	cout << o.t_CPX << " is the cplex time\n";
}
