#ifndef _BRUTEFORCEOPTIMIZER_HPP
#define _BRUTEFORCEOPTIMIZER_HPP

#include "Optimizer.hpp"

namespace optimizer
{


class BruteForceOptimizer : public Optimizer
{
	public:
		BruteForceOptimizer(Solution solution)
			: Optimizer(solution)
			, best_score(Optimizer::score(solution))
			, best_solution(solution)
		{
			if(!best_solution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
			if(!mySolution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
		}

		BruteForceOptimizer(Drivers drivers, Riders riders)
			: Optimizer(drivers, riders)
			, best_solution(drivers, riders)
		{
			if(!best_solution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
			if(!mySolution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
			best_score = Optimizer::score(mySolution);
		}

		BruteForceOptimizer(Drivers drivers, Riders riders, Matches matches)
			: Optimizer(drivers, riders, matches)
			, best_solution(drivers, riders, matches)
		{
			if(!best_solution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
			if(!mySolution.setOptimizeType(BRUTE_FORCE))
				cout << "Could not set optimizer type to brute force" << endl;
			best_score = Optimizer::score(mySolution);
		}

		void optimize();
		double getBestScore() const { return best_score; }
		const Solution & getBestSolution() const { return best_solution; }

	private:
		double best_score;
		Solution best_solution;
		double iterate();
};

}
#endif // #ifndef _BRUTEFORCEOPTIMIZER_HPP
