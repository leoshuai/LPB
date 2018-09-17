MatrixXd X(2, 7);
X.col(0) << 1, -0.1;
X.col(1) << 2, 2;
X.col(2) << 1, 1;
X.col(3) << -1, 5;
X.col(4) << -0.5, -0.5;
X.col(5) << 0.8, 0.6;
X.col(6) << 3, 2;
cout << X;
VectorXd x(2);
x = X.col(6);
cout << endl << x;

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
}//std::ostream& operator<<(std::ostream& os, const OutData& outData) {
//	return os << '&' << outData.Error
//		<< '&' << outData.No_func_eval
//		<< '&' << outData.k
//		<< '&' << outData.L
//		<< '&' << outData.time
//		<< '&' << outData.t_CPX
//		<< "\\\\" << std::endl << "\\hline" << std::endl;
//
//}

/*myfile << r+1 << '&' << out.Error << '&' << out.No_func_eval;
		myfile << '&' << out.k << '&' << out.L << '&';
		myfile<<scientific<< out.time << '&' << out.t_CPX << "" << endl << "\\hline" << endl;*/
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

		//copy(out, out + Num_of_Probs, ostream_iterator<OutData>(cout, "\n "));

		//for (j = 1; j < 8; j++)
		//{
		//	myfile << out[j-1];
		//	//myfile << j << '&' << out[j - 1].Error << '&' << out[j - 1].No_func_eval;
		//	//myfile <<'&' << out[j - 1].k << '&' << out[j - 1].L << '&' << out[j - 1].time << '&' << out[j - 1].t_CPX << "\\\\" << endl << "\\hline" << endl;
		//}



