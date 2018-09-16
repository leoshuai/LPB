// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
void copyUpperTriangularPart(MatrixXf& dst, const MatrixXf& src)
{
	dst.triangularView<Upper>() = src.triangularView<Upper>();
}
int main()
{
	MatrixXf m1 = MatrixXf::Ones(4, 4);
	MatrixXf m2 = MatrixXf::Random(4, 4);
	std::cout << "m2 before copy:" << std::endl;
	std::cout << m2 << std::endl << std::endl;
	copyUpperTriangularPart(m2, m1);
	std::cout << "m2 after copy:" << std::endl;
	std::cout << m2 << std::endl << std::endl;
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
