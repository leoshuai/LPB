#pragma once
struct ProbData
{
	std::string Prob_Name;
	double f_optimal;
};
struct OutData
{
	int status;// Status of output 
	double Error;// For public version, I don't need this because I will not know the optimal value of all the problems.
	double f_final;// The approximate optimal value returned by LPB
	int No_func_eval;// Number of function evaluation
	int k;// Number of all iterations
	int L;// Number of null steps
	double time;// Time spent in solving a problem
	double t_CPX;// Total time spent in CPLEX
};
class Param
{
public:
	double epsilon_tol;
	double m;
	int Iter_Limi;

	Param() :
		epsilon_tol(1.0e-4),
		m(1e-4),
		Iter_Limi(2000)
	{}
	Param(const double eps_tol, const double mp, const unsigned int itli) :
		epsilon_tol(eps_tol),
		m(mp),
		Iter_Limi(itli)
	{}
};
void LPB(ProbData prob, Eigen::VectorXd& x,
	void(*feval)(const Eigen::VectorXd &, double &, Eigen::VectorXd&), OutData & o);
void LPBdelta1(ProbData prob, Eigen::VectorXd& x,
	void(*feval)(const Eigen::VectorXd &, double &, Eigen::VectorXd&), OutData & o);


