#include "BipartiteMatchingOptimizer.hpp"
#include "SolutionUtils.hpp"
#include <iostream>

#define debug_optimize false
#define debug_optimize_2 false
#define debug_augmenting_path false
#define debug_get_augmenting_path false
#define debug_init_edges false
#define debug_update_solution false

namespace optimizer
{

using std::vector;
typedef uint32_t id;
static const uint32_t UNMATCHED = 0;
static const size_t SAMPLES = 8;
/*
 * Function:		optimize()
 * Comments:		Runs SAMPLES instances of iterated bipartite matching.
 * 							Sets mySolution to the best result
 * 							Since each instance runs through a random order of 
 * 							riders and matches, this will ensure we attempt 
 * 							significantly different scenarios
 */
void BipartiteMatchingOptimizer::optimize() 
{
	Solution oldSolution = mySolution;
#if debug_optimize
	cout<< "Running bipartite optimizer: ";
#endif
	for(size_t i = 0; i < SAMPLES; i++)
	{
#if debug_optimize
		if(i < SAMPLES - 1) cout<< i << ",";
#endif
		BipartiteMatchingOptimizer optimizer(oldSolution);
		optimizer.single_optimize();
		if(optimizer.getBestScore() > best_score)
		{
			best_score = optimizer.getBestScore();
			best_solution = optimizer.getBestSolution();
			solutionHistory.push_back(best_solution);
			cout << "Generated BP Solution with score: " << best_score << endl;
		}
	}
#if debug_optimize
	cout<<endl;
#endif
}

/*
 * Function:		single_optimize()
 * Comments:		Runs iterated bipartite matching algorithm on solution
 * 							Runs it once.
 */
void BipartiteMatchingOptimizer::single_optimize() 
{
	bool run = true;
	best_solution = mySolution;
	best_score = score(mySolution);
	size_t iterationNumber = 0;
#if debug_optimize
	mySolution.printRouteIds(); 
#endif
	while(run)
	{
#if debug_optimize
		cout<<"*********************************"<<iterationNumber<<endl;
		cout<<"* Maximal matching iteration #"<<iterationNumber<<endl;
		cout<<"*********************************"<<iterationNumber<<endl;
#endif
		iterate();
		double cur_score = Optimizer::score(mySolution);
		if(cur_score == best_score)
			run = false;
		if(cur_score > best_score)
		{
			best_score = cur_score;
			best_solution = mySolution;
		}
		iterationNumber++;
	}
#if debug_optimize
	cout<< "Final score: " << best_score << endl;
#endif
}

/*
 * Function:		iterate()
 * Comments:		Run one iteration of the maximal matching algorithm,
 * 							i.e. find a maximal matching for the bipartite graph:
 * 								G = (V,E), where V = {unmatched riders} union {matches}
 * 								E = the set of compatible (rider,match) pairs
 */
void BipartiteMatchingOptimizer::iterate()
{
	initEdges(); 
	Edges augmentingPath;
	augmentingPath.clear();
	//find maximal matching for this iteration
	while(getAugmentingPath(augmentingPath))
	{
#if debug_augmenting_path
		cout<< "  Augmenting path found: " <<endl;
		for(size_t i = 0; i < augmentingPath.size(); i++)
		{
			cout<<"    "<< i <<"   match: " << augmentingPath[i].match_id << " rider: " << augmentingPath[i].rider_id << endl;
		}
#endif
		/*
		 * Set edges to matched/unmatched, according to augmenting path
		 */
		updateEdges(augmentingPath); 
	}
	/*
	 * Use maximal matching result to update Solution
	 * complete matching process by adding riders to their matches
	 */
	updateSolution();
}

/*
 * Function:		getAugmentingPath()
 * Arguments:		Path reference
 * Return:			true if there exists an augmenting path in the solution
 * 								reference argument will hold the augmenting path
 * 							false if there doen't exist an augmenting path
 * Comments:		Implements depth-first-search (DFS) by calling the recursive
 * 							function riderIterate()
 */
bool BipartiteMatchingOptimizer::getAugmentingPath(Edges& augmentingPath)
{
	/*  Algorithm:
	 *  1. Mark nodes as matched or unmatched (already done in other functions)
	 *  2. For each unmatched rider, chosen in random order do:
	 *  3.	Start a search from each of the unmatched rider nodes.
	 *  4.		Traverse unmatched edges from right to left.
	 *  5.		Traverse matched edges from left to right.
	 *  6.		Stop successfully if an unmatched left node is reached. 
	 *  7.		Stop with failure if search terminates without finding 
	 *  				an unmatched left node. 
	 */
#if debug_get_augmenting_path
	cout<<"  Getting Augmenting Path."<<endl;
#endif

	/* Build a list of riders to iterate through in random order */
	vector<Solution::RidersMap::iterator> 	rider_iterators = 
																mySolution.getRandomRiderIteratorVector();
	while(rider_iterators.size())
	{
		RidersMap::iterator rider = rider_iterators.back();
		rider_iterators.pop_back();

		augmentingPath.clear();
		/* Check if this rider leads to an augmenting path */
		if(rider->second.match_id == UNMATCHED) //only try unmatched riders
		{
			if(riderIterate(rider->second, augmentingPath))
				return true;
		}
	}
	return false;
}

/*
 * Function:		riderIterate()
 * Arguments:		Unmatched Rider, path reference
 * Return:			true if this rider leads to an augmenting path
 * 								reference argument will hold the augmenting path
 * 							false if this rider doesn't lead to an augmenting path
 */
bool BipartiteMatchingOptimizer::riderIterate(const Rider& rider, Edges& augmentingPath)
{
	for(size_t i = 0; i < rider.unmatched.size(); i++)
	{
		//traverse the unmatched edge, check if it leads to an augmenting path
		Edge e; 
		e.match_id = rider.unmatched[i]; 
		e.rider_id = rider.routeId;
		augmentingPath.push_back(e);
		if( matchIterate(mySolution.myMatches[rider.unmatched[i]] , augmentingPath) )
		{
			return true;
		}
		augmentingPath.pop_back(); //this edge doesn't lead to an augmenting path
	}
	return false;//this rider doesn't lead to an augmenting path
}

/*
 * Function:		matchIterate()
 * Arguments:		Match, path reference
 * Return:			true if this match leads to an augmenting path
 * 								reference argument will hold the augmenting path
 * 							false if this match doesn't lead to an augmenting path
 */
bool BipartiteMatchingOptimizer::matchIterate(Match& match, Edges& augmentingPath)
{
	if(match.matched_rider_id == UNMATCHED)
		return true; //match unmatched. found an augmenting path.
	if(match.visited == true)
		return false; //found a cycle
	match.visited = true;

	//traverse the matched edge, check if it leads to an augmenting path
	Rider& rider = mySolution.myRiders[match.matched_rider_id];
	Edge e;
	e.match_id = match.myDriver.routeId; e.rider_id = rider.routeId;
	augmentingPath.push_back(e);
	if(riderIterate(rider,augmentingPath))
	{
		return true;
	}else
	{
		augmentingPath.pop_back();
		return false;
	}
}

/*
 * Function:		updateEdges()
 * Arguments:		reference to augmenting path
 * Comments:		Adds odd edges to augmenting path, 
 * 							removes even edges from augmenting path
 */
void BipartiteMatchingOptimizer::updateEdges(Edges& augmentingPath)
{
#if debug_optimize
	cout<<"  Updating edges for augmenting path."<<endl;
#endif
	if(augmentingPath.size()%2 == 0)
	{
		cout<< "    Error: augmenting path is even, should be odd." <<endl;
	}
	for(size_t i = 0; i < augmentingPath.size(); i++)
	{
		uint32_t rider_id = augmentingPath[i].rider_id;
		uint32_t match_id = augmentingPath[i].match_id;
		if((i+1)%2)
		{
			/*
			 * for newly matched (odd) edges: 
			 * 		for the rider: 
			 * 			set match_id to this edge's match_id
			 * 		for the match:
			 * 			set the matched_rider_id to this edge's rider_id
			 */
			mySolution.myRiders[rider_id].match_id = match_id;
			mySolution.myMatches[match_id].matched_rider_id = rider_id;
#if debug_optimize
			cout<<"    Added edge to matching: ("<<match_id<<","<<rider_id<<")"<<endl;
#endif
		}
	}
	//book keeping: update visited field to false for all matches
	//todo:move the following functionality to a separate function
	for(Solution::MatchesMap::iterator 	match = mySolution.myMatches.begin();
																			match != mySolution.myMatches.end(); 
																			match++)
	{
		match->second.visited = false;
	}
}

/*
 * Function:					initEdges()
 * Comments:					Adds an unmatched edge to each rider that is 
 * 											compatible with a match
 * 										Sets up matches for matching algorithm
 */
void BipartiteMatchingOptimizer::initEdges()
{
#if debug_init_edges
	cout<<"  Initializing edges:"<<endl;
#endif
	Matches matches;
	for(Solution::RidersMap::iterator rider = mySolution.myRiders.begin();
																	rider != mySolution.myRiders.end(); 
																	rider++)
	{
		rider->second.unmatched.clear();
		rider->second.match_id = UNMATCHED;
	}
	/* Build a list of matches to iterate through in random order */
	vector<Solution::MatchesMap::iterator> 	match_iterators = 
																mySolution.getRandomMatchIteratorVector();

	while(match_iterators.size())
	{
		MatchesMap::iterator match = match_iterators.back();
		match_iterators.pop_back();

#if debug_init_edges
		cout<<"    Checking compatibilities for match: "<<
						match->second.myDriver.routeId << endl;
#endif
		match->second.visited = false;//set up match for augmenting path algorithm
		match->second.matched_rider_id = UNMATCHED;//initially, all are unmatched

		/* Build a list of riders to iterate through in random order */
		vector<Solution::RidersMap::iterator> 	rider_iterators = 
																	mySolution.getRandomRiderIteratorVector();
		while(rider_iterators.size())
		{
			RidersMap::iterator rider = rider_iterators.back();
			rider_iterators.pop_back();
			if(match->second.canAddRider(rider->second))
			{
				rider->second.unmatched.push_back(match->second.myDriver.routeId);
#if debug_init_edges
				cout<<"    Added unmatched edge: ("<< match->second.myDriver.routeId << "," << 
					rider->second.routeId << ")" <<endl;
#endif
			}
		}
	}
}

/*
 * Function:			updateSolution()
 * Comments:			Adds all matched riders to their corresponding matches
 */
void BipartiteMatchingOptimizer::updateSolution()
{
#if debug_update_solution
	cout<<"  Updating solution"<<endl;
#endif
	vector<uint32_t> matched_rider_ids;
	// TODO: reset the matched_rider_id values for each match.
	for(Solution::RidersMap::iterator rider = mySolution.myRiders.begin();
																	rider != mySolution.myRiders.end(); 
																	rider++)
	{
		rider->second.unmatched.clear();
		if(rider->second.match_id != UNMATCHED)
		{
#if debug_update_solution
			cout<<"    Adding the rider: " <<rider->second.routeId <<
									" to the match: "<<rider->second.match_id<<endl;
#endif
			bool compatibilityError = 
				!mySolution.myMatches[rider->second.match_id].addRider(rider->second);
			matched_rider_ids.push_back(rider->second.routeId);//mark this rider for removal
			if(compatibilityError)
			{
#if debug_update_solution
				cout<<"    Error: tried to add a rider that's incompatible."<<endl;
				cout<<"      Details:  match: "<< rider->second.match_id << 
						" rider: " << rider->second.routeId << endl;
				cout<<"      canAddRider returns: "<< 
					mySolution.myMatches[rider->second.match_id].canAddRider(rider->second)<<endl;
#endif
			}
		}
	}
	//remove matched riders from myRiders
	for(size_t j = 0; j < matched_rider_ids.size(); j++)
	{
		mySolution.myRiders.erase(matched_rider_ids[j]);
	}
}

}//end optimizer namespace
