// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <map>
#include <vector>
#include <cmath>

#include "gnuplot-iostream/gnuplot-iostream.h"

int main() {
	Gnuplot gp;

	std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	gp << "set xrange [0:10]\nset yrange [0:1]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	gp << "plot '-' with lines title 'data'\n";
	gp.send1d(xy_pts_A);
}
