#ifndef _GENETICOPTIMIZER_HPP
#define _GENETICOPTIMIZER_HPP

#include "Optimizer.hpp"
#include <map>

namespace optimizer
{

class GeneticOptimizer : public Optimizer
{
	// N.B. we init the RouteMatrix with FLUSH on and then turn it off in init()
	// This is so we don't create copies of the RouteMatrix inside Genetic.optimize()
	// but we get a new RouteMatrix rather than use old Matricies from old optimizers
	static const RouteMatrixInitType defaultFlush = FLUSH;

	public:
		GeneticOptimizer(Solution solution);
		GeneticOptimizer(Drivers drivers, Riders riders);
		GeneticOptimizer(Drivers drivers, Riders riders, Matches matches);
		void init();
		void optimize();
		double getBestScore() const;
		const Solution& getBestSolution() const;

	private:
		map<double, Solution> population;
		void generatePopulation(const unsigned int num_to_create);
};

}
#endif // #ifndef _GENETICOPTIMIZER_HPP
