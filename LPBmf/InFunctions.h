#pragma once
typedef Eigen::Ref<Eigen::VectorXd> Vec;
typedef const Eigen::Ref<const Eigen::VectorXd> cVec;
void CB2(cVec &  x,double &y,Vec s);
void CB3(cVec &  x,double &y,Vec s);
void DEM(cVec &  x,double &y,Vec s);
void LQ(cVec &  x,double &y,Vec s);
void QL(cVec &  x,double &y,Vec s);
void Mifflin1(cVec &  x,double &y,Vec s);
void Wolfe(cVec &  x,double &y,Vec s);
void Chained_LQ(cVec &  x,double &y,Vec s);
void GenMXHILB(const VectorXd& x, double& y, VectorXd& s);
//template <typename Derived, typename OtherDerived> void GenMXHILB(const MatrixBase<Derived>& x, double &y, MatrixBase<OtherDerived> const & s)
//{
//	int n = x.size();
//	const_cast<MatrixBase<OtherDerived>&>(s).setZero;
//	double temp, t4, t5;
//	int k = 1;o
//	VectorXd J(n);
//	J = VectorXd::LinSpaced(n, 1, n);
//	VectorXd t1(n), I(n), t2(n), t3(n);
//	I.setOnes();
//	t1 = x.array() / J.array();
//	temp = t1.sum();
//	y = abs(temp);
//	for (int i = 2; i < n + 1; i++)
//	{
//		t2 = J + i * I - I;
//		t1 = x.array() / t2.array();
//		temp = t1.sum();
//		if (abs(temp) > y)
//		{
//			y = abs(temp);
//			k = i;
//		}
//	}
//	t2 = J + k * I - I;
//	t1 = I.array() / t2.array();
//	t3 = x.array() / t2.array();
//	t4 = t3.sum();
//	if (t4 >= 0)
//		t5 = 1;
//	else
//		t5 = -1;
//	const_cast<MatrixBase<OtherDerived>&>(s) = t5 * t1;
//
//}
//template void GenMXHILB<VectorXd,VectorXd>(const Ref<const VectorXd>& x, double & y, Ref<const VectorXd>& s); // explicit instantiation.
