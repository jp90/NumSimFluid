/*
 * computation.cpp
 *
 *  Created on: 12.11.2013
 *      Author: David
 */

#include "computation.h"
#include <iostream>

using namespace std;

Computation::Computation(IO& SimIO) :
		SimIO(SimIO) {
}

RealType Computation::computeTimesstep(RealType uMax, RealType vMax,
		const PointType& h, RealType Re, RealType tau) {

	return 0.0;
}

void Computation::computeNewVelocities(GridFunction& u, GridFunction& v,
		GridFunction& f, GridFunction& g, GridFunctionType& p,
		const PointType& delta, RealType deltaT) {
//	GridFunction branch_1(p.griddimension);
//	Px(branch_1,p,SimIO.para.alpha,h);

	u.A
}
;

void Computation::computeMomentumEquations(GridFunction& f, GridFunction& g,
		GridFunction& u, GridFunction& v, GridFunction& gx, GridFunction& gy,
		const PointType& h, RealType& deltaT) {

	RealType alpha = SimIO.para.alpha;
	RealType re = 0.5;
	MultiIndexType begin, end, dim;
	dim = u.griddimension;
	begin[0] = 0;
	end[0] = u.griddimension[0] - 1;
	begin[1] = 0;
	end[1] = u.griddimension[1] - 1;

	// Term F

	Uxx(f, u, alpha, h);

	GridFunction branch_2(u.griddimension);
	Uyy(branch_2, u, alpha, h);
	f.AddToGridFunction(begin, end, 1.0, branch_2);
	f.ScaleGridFunction(begin, end, 1.0 / re);
	GridFunction branch_3(u.griddimension);
	UUx(branch_3, u, alpha, h);
	GridFunction branch_4(u.griddimension);
	UVy(branch_4, u, v, alpha, h);
	branch_3.AddToGridFunction(begin, end, 1.0, branch_4);

	f.AddToGridFunction(begin, end, -1.0, branch_3);
	// KILL branch 2-4

	//MISSING g_x

	f.ScaleGridFunction(begin, end, deltaT);
	f.AddToGridFunction(begin, end, 1.0, u);

	//Term G

	Vxx(g, v, alpha, h);
	GridFunction branch_6(u.griddimension);
	Vyy(branch_6, v, alpha, h);
	g.AddToGridFunction(begin, end, 1.0, branch_6);
	g.ScaleGridFunction(begin, end, 1.0 / re);

	GridFunction branch_7(u.griddimension);
	UVx(branch_7, u, v, alpha, h);
	GridFunction branch_8(u.griddimension);
	VVy(branch_8, v, alpha, h);
	branch_7.AddToGridFunction(begin, end, 1.0, branch_8);

	g.AddToGridFunction(begin, end, -1.0, branch_7);

	//MISSING g_y term

	g.ScaleGridFunction(begin, end, deltaT);
	g.AddToGridFunction(begin, end, 1.0, v);

}

void Computation::setBoundaryU(GridFunction& u) {
	MultiIndexType begin, end;
	begin[0] = 0;
	begin[1] = 0;
	end[0] = u.griddimension[0] - 1;
	end[1] = 0;
	u.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = 0;
	end[0] = 0;
	end[1] = u.griddimension[1] - 1;
	u.SetGridFunction(begin, end, 0.0);


	begin[0] = u.griddimension[0] - 1;
	begin[1] = 0;
	end[0] = u.griddimension[0] - 1;
	end[1] = u.griddimension[1] - 1;
	u.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = u.griddimension[1] - 1;
	end[0] = u.griddimension[1] -1;
	end[1] = u.griddimension[1] -1;
	u.SetGridFunction(begin, end, SimIO.para.ui);
}
void Computation::setBoundaryV(GridFunction& v) {
	MultiIndexType begin, end;
	begin[0] = 0;
	begin[1] = 0;
	end[0] = v.griddimension[0] - 1;
	end[1] = 0;
	v.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = 0;
	end[0] = 0;
	end[1] = v.griddimension[1] - 1;
	v.SetGridFunction(begin, end, 0.0);


	begin[0] = v.griddimension[0] - 1;
	begin[1] = 0;
	end[0] = v.griddimension[0] - 1;
	end[1] = v.griddimension[1] - 1;
	v.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = v.griddimension[1] - 1;
	end[0] = v.griddimension[1] -1;
	end[1] = v.griddimension[1] -1;
	v.SetGridFunction(begin, end, 0.0);
}
void Computation::setBoundaryP(GridFunction& p) {
	MultiIndexType begin, end;
	begin[0] = 0;
	begin[1] = 0;
	end[0] = p.griddimension[0] - 1;
	end[1] = 0;
	p.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = 0;
	end[0] = 0;
	end[1] = p.griddimension[1] - 1;
	p.SetGridFunction(begin, end, 0.0);


	begin[0] = p.griddimension[0] - 1;
	begin[1] = 0;
	end[0] = p.griddimension[0] - 1;
	end[1] = p.griddimension[1] - 1;
	p.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = p.griddimension[1] - 1;
	end[0] = p.griddimension[1] -1;
	end[1] = p.griddimension[1] -1;
	p.SetGridFunction(begin, end, SimIO.para.pi);
}
void Computation::setBoundaryF(GridFunction& f) {
	MultiIndexType begin, end;
	begin[0] = 0;
	begin[1] = 0;
	end[0] = f.griddimension[0] - 1;
	end[1] = 0;
	f.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = 0;
	end[0] = 0;
	end[1] = f.griddimension[1] - 1;
	f.SetGridFunction(begin, end, 0.0);


	begin[0] = f.griddimension[0] - 1;
	begin[1] = 0;
	end[0] = f.griddimension[0] - 1;
	end[1] = f.griddimension[1] - 1;
	f.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = f.griddimension[1] - 1;
	end[0] = f.griddimension[1] -1;
	end[1] = f.griddimension[1] -1;
	f.SetGridFunction(begin, end, 0.0);
}
void Computation::setBoundaryG(GridFunction& g) {
	MultiIndexType begin, end;
	begin[0] = 0;
	begin[1] = 0;
	end[0] = g.griddimension[0] - 1;
	end[1] = 0;
	g.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = 0;
	end[0] = 0;
	end[1] = g.griddimension[1] - 1;
	g.SetGridFunction(begin, end, 0.0);


	begin[0] = g.griddimension[0] - 1;
	begin[1] = 0;
	end[0] = g.griddimension[0] - 1;
	end[1] = g.griddimension[1] - 1;
	g.SetGridFunction(begin, end, 0.0);

	begin[0] = 0;
	begin[1] = g.griddimension[1] - 1;
	end[0] = g.griddimension[1] -1;
	end[1] = g.griddimension[1] -1;
	g.SetGridFunction(begin, end, 0.0);
}

void Computation::computeRighthandSide(const MultiIndexType& griddimension,
		GridFunctionType& rhs, GridFunctionType& f, GridFunctionType& g,
		const PointType& delta, RealType deltaT) {

}

