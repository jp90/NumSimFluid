/*
 * computation.h
 *
 *  Created on: 12.11.2013
 *      Author: David
 */

#include "gridfunction.h"
#include "derivatives.h"
#include "IO.hpp"

#ifndef COMPUTATION_H_
#define COMPUTATION_H_

#include "IO.hpp"


class Computation {
public:

	Computation(IO& SimIO);

	RealType computeTimesstep(RealType uMax, RealType vMax, const PointType& h,
			RealType Re, RealType tau);
	void computeNewVelocities(GridFunction& u, GridFunction& v,
			GridFunction& f, GridFunction& g, GridFunction& p,
			const PointType& delta, RealType deltaT);


	void computeMomentumEquations(GridFunction& f, GridFunction& g, GridFunction& u,
									 GridFunction& v, GridFunction& gx, GridFunction& gy,
									 const PointType& h, RealType& deltaT );


	void setBoundaryU(GridFunction& u);
	void setBoundaryV(GridFunction& v);
	void setBoundaryP(GridFunction& p);
	void setBoundaryF(GridFunction& f);
	void setBoundaryG(GridFunction& g);




	void computeRighthandSide(const MultiIndexType& griddimension,
			GridFunctionType& rhs, GridFunctionType& f, GridFunctionType& g,
			const PointType& delta, RealType deltaT);


    IO SimIO;

};

#endif /* COMPUTATION_H_ */
