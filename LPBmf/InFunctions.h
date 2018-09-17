#pragma once
void CB2(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void CB3(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void DEM(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void LQ(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void QL(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void Mifflin1(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void Wolfe(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void Chained_LQ(const Eigen::VectorXd &  x,double &y,Eigen::VectorXd& s);
void GenMXHILB(const Eigen::VectorXd& x, double& y, Eigen::VectorXd& s);
void smallProbs7();
void GenMXH();