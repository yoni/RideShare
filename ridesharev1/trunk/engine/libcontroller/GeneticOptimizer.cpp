#include "GeneticOptimizer.hpp"
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include "RouteClient.hpp"

namespace optimizer
{
using controller::routes::RouteClient;
#if 1
#define INITIAL_POPULATION_SIZE 1
#define INTERMEDIATE_POPULATION_SIZE 5
#define FINAL_POPULATION_SIZE 1
#define NUMBER_OF_GENERATIONS 5
#define NUMBER_OF_BEST_TO_KEEP_EACH_GENERATION 1

#else

//TODO: the values below should be used in production
#define INITIAL_POPULATION_SIZE 20
#define INTERMEDIATE_POPULATION_SIZE 20
#define FINAL_POPULATION_SIZE 1

#define NUMBER_OF_GENERATIONS 20
#define NUMBER_OF_BEST_TO_KEEP_EACH_GENERATION 3
#endif


using controller::routes::RouteClient;
using std::map;
using std::vector;
using std::random_shuffle;
using std::sort;

GeneticOptimizer::GeneticOptimizer(Solution solution)
			: Optimizer(solution, defaultFlush)
{
	init();
}

GeneticOptimizer::GeneticOptimizer(Drivers drivers, Riders riders)
			: Optimizer(drivers, riders, defaultFlush)
{
	init();
}

GeneticOptimizer::GeneticOptimizer(Drivers drivers, Riders riders, Matches matches)
	: Optimizer(drivers, riders, matches, defaultFlush)
{
	init();
}

void GeneticOptimizer::init()
{
	mySolution.setOptimizeType(GENETIC);
	mySolution.setFlushType(NO_FLUSH);
	generatePopulation(INITIAL_POPULATION_SIZE);
}

void GeneticOptimizer::generatePopulation(const unsigned int num_to_create)
{
	for(unsigned char i = 0; i < num_to_create; i++)
	{
		Solution newSolution(mySolution);

		// Build a list of riders to iterate through them in random order
		vector<RidersMap::iterator> rider_iterators;
		for(RidersMap::iterator i = newSolution.myRiders.begin(); i != newSolution.myRiders.end(); i++)
			rider_iterators.push_back(i);
		random_shuffle(rider_iterators.begin(), rider_iterators.end());

		// Iterate through the riders in random order.  For each, build a list of matches they could be placed in, then pick one at random and add them to that one.
		vector<RidersMap::iterator> added_riders;
		while(!rider_iterators.empty())
		{
			RidersMap::iterator cur_rider = rider_iterators.back();
			rider_iterators.pop_back();

			vector<MatchesMap::iterator> match_pool;
			for(MatchesMap::iterator cur_match = newSolution.myMatches.begin(); cur_match != newSolution.myMatches.end(); cur_match++)
			{
				if(cur_match->second.canAddRider(cur_rider->second))
				{
					match_pool.push_back(cur_match);
				}
			}

			if(match_pool.size() > 0)
			{
				// possible FIXME: include the possibility of unassigning them here to make it truely random...
				unsigned int action = rand() % match_pool.size();
				match_pool[action]->second.addRider(cur_rider->second);
				added_riders.push_back(cur_rider);
			}
		}

		while(!added_riders.empty())
		{
			RidersMap::iterator cur_rider = added_riders.back();
			added_riders.pop_back();

			newSolution.myRiders.erase(cur_rider);
		}

		population[Optimizer::score(newSolution)] = newSolution;

		// write generated solution to history of solutions (for later use)
		//static uint32_t cur_generation_num = 0;
		//static const string defaultFile = "genetic_solution_";
		//std::stringstream ss(std::stringstream::in | std::stringstream::out);
		//ss << defaultFile << cur_generation_num++ << ".gif ";
		std::cout<<"Solution generated has score: " << Optimizer::score(newSolution) << std::endl;
		solutionHistory.push_back(newSolution);
	}
}

void GeneticOptimizer::optimize()
{
	solutionHistory.clear();
	RouteClient rClient;
	// can be changed to a time based thing instead...
	string defaultFile = "genetic_solution_";

	for(unsigned char cur_generation_num =0; cur_generation_num < NUMBER_OF_GENERATIONS; cur_generation_num++)
	{
		map<double, Solution>::iterator threshold = population.end();
		for(unsigned int i=0; i<NUMBER_OF_BEST_TO_KEEP_EACH_GENERATION; i++)
			threshold--;
		population.erase(population.begin(), threshold);
		generatePopulation(INTERMEDIATE_POPULATION_SIZE - population.size());

		//solutionHistory.push_back(const_cast<Solution &>(getBestSolution()));
	//	std::cout<<ss.str();
	//	rClient.createRouteImage(const_cast<Solution &>(getBestSolution()), ss.str());
	}
}

double GeneticOptimizer::getBestScore() const
{
	map<double, Solution>::const_iterator best = population.end();
	best--;
	return best->first;
}

const Solution& GeneticOptimizer::getBestSolution() const
{
	map<double, Solution>::const_iterator best = population.end();
	best--;
	return best->second;
}

}
