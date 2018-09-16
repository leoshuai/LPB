#include "stdafx.h"
template <typename T>// Print out a vector; only used in tests.
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
	if ( !v.empty() ) {
		out << '[';
		std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
		out << "\b\b]";
	}
	return out;
}
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
