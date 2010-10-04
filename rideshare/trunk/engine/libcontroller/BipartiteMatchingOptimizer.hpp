#ifndef _BIPARTITE_MATCHING_OPTIMIZER_HPP
#define _BIPARTITE_MATCHING_OPTIMIZER_HPP

#include "Optimizer.hpp"
#include "Solution.hpp"
#include <vector>

namespace optimizer
{

struct Edge{
	uint32_t match_id;
	uint32_t rider_id;
};

typedef vector<Edge> Edges;

class BipartiteMatchingOptimizer : public Optimizer
{
	public:
		BipartiteMatchingOptimizer(Solution solution)
			: Optimizer(solution)
		{
			mySolution.setOptimizeType(BIPARTITE);
			best_score = score(mySolution);
		}

		BipartiteMatchingOptimizer(Drivers drivers, Riders riders)
			: Optimizer(drivers, riders, NO_FLUSH)
		{
			mySolution.setOptimizeType(BIPARTITE);
			best_score = score(mySolution);
		}
		
		BipartiteMatchingOptimizer(Drivers drivers, Riders riders, Matches matches)
			: Optimizer(drivers, riders, matches)
		{
			mySolution.setOptimizeType(BIPARTITE);
			best_score = score(mySolution);
		}

		/* Implementation of Optimizer abstract functions */
		void optimize();//calls single_optimize 10 times, takes the best result
		void single_optimize();//runs maximal bipatrite matching algorithm
		double getBestScore() const { return best_score; }
		const Solution & getBestSolution() const { return best_solution; }

	private:
		double best_score;
		Solution best_solution;
		
		/* Functions for Implementing the Algorithm:
		 * Maximal Matching on Bipartite Graph
		 * TODO: insert algorithm pseudo-code here
		 */
		void iterate();
		bool getAugmentingPath(Edges& augmentingPath);
		void updateSolution();
		void updateEdges(Edges& augmentingPath);
		void initEdges();
		bool riderIterate(const Rider& rider, Edges& augmentingPath);
		bool matchIterate(Match& match, Edges& augmentingPath);

};

}
#endif // #ifndef _BRUTEFORCEOPTIMIZER_HPP
