#include <iostream>
#include <string>
#include <vector>
//libController includes
#include "DBAccess.hpp"
#include "GeneticOptimizer.hpp"
#include "BruteForceOptimizer.hpp"
#include "BipartiteMatchingOptimizer.hpp"
#include "Solution.hpp"
#include "SolutionUtils.hpp"

//controller includes
#include "server_info.hpp"
#include "ArgsHandler.hpp"
#include "Mailer.hpp"

using optimizer::Optimizer;
using optimizer::GeneticOptimizer;
using optimizer::BruteForceOptimizer;
using optimizer::BipartiteMatchingOptimizer;
using optimizer::Solution;
using optimizer::solutions2javascript;
using controller::dba::DBAccess;
using std::string;
using std::vector;
using std::cout;
using std::endl;

bool useLocalMatrix = true;

Solution::Riders getRiders(DBAccess::ptr dba)
{
	vector<string> comments_to_search_for;
	comments_to_search_for.push_back("austinDemo2_6");
	comments_to_search_for.push_back("austinDemo2_5");
	comments_to_search_for.push_back("austinDemo2_4");
	comments_to_search_for.push_back("austinDemo2_3");
	comments_to_search_for.push_back("austinDemo2_2");
	comments_to_search_for.push_back("austinDemo2_1");

	Solution::Riders riders;
	//riders = dba->getRiderSubmissions(comments_to_search_for);
	riders = dba->getRiderSubmissions();
	return riders;
}

Solution::Drivers getDrivers(DBAccess::ptr dba)
{
	vector<string> comments_to_search_for;
	comments_to_search_for.push_back("austinDemo2_6");
	comments_to_search_for.push_back("austinDemo2_5");
	comments_to_search_for.push_back("austinDemo2_4");
	comments_to_search_for.push_back("austinDemo2_3");
	comments_to_search_for.push_back("austinDemo2_2");
	comments_to_search_for.push_back("austinDemo2_1");

	Solution::Drivers drivers;
	//drivers = dba->getDriverSubmissions(comments_to_search_for);
	drivers = dba->getDriverSubmissions();
	return drivers;
}

Optimizer::ptr getOptimizer(string type, Solution::Drivers &drivers, Solution::Riders &riders)
{
	string_tolower(type);
	Optimizer::ptr returnOptimizer;
	if (type == "genetic")
	{
		returnOptimizer.reset(new GeneticOptimizer(drivers, riders));
	}
	else if (type == "bruteforce")
	{
		returnOptimizer.reset(new BruteForceOptimizer(drivers, riders));
	}
	else if (type == "bipartite")
	{
		returnOptimizer.reset(new BipartiteMatchingOptimizer(drivers, riders));
	}
	return returnOptimizer;
}

int main(int argc, char* argv[])
{
	ArgsHandler argsHandler(argc, argv);
	cout << "Algorithm: " <<  argsHandler.getAlgorithm() << endl;
	string calcType = (argsHandler.getCalcType()) ? "Map Quest" : "Local";
	cout << "CalcType: " << calcType << endl;
	string notify = argsHandler.getSendNotifications() ?  "On" : "Off";
	cout << "Send Notifications: " <<  notify << endl;
	string jsFile = (argsHandler.getJSFile() == "") ? "None" : argsHandler.getJSFile();
	cout << "JS File: " <<  jsFile << endl;
	string writesolut = argsHandler.getWriteSolutions() ?  "On" : "Off";
	cout << "Write Solutions: " << writesolut<< endl;

	DBAccess::ptr dba(new DBAccess(host, db, user, pw));
	Solution::Riders riders = getRiders(dba);
	Solution::Drivers drivers = getDrivers(dba);

	if (argsHandler.getCalcType() == LOCAL)
	{
		useLocalMatrix = true;
	}
	else
	{
		useLocalMatrix = false;
	}

	Optimizer::ptr optimizer(getOptimizer(argsHandler.getAlgorithm(), drivers, riders));
	optimizer->optimize();

	Solution bestSolution(optimizer->getBestSolution());
	//std::cout<<"Best score: " << optimizer->getBestScore() << endl;
	//std::cout<<"Should be Best score: " << Optimizer::score(bestSolution) << endl;

	// dump JS file
	if (argsHandler.getJSFile() != "")
	{
		Solution::Solutions solutions;
		solutions.push_back(bestSolution);
		solutions2javascript(optimizer->solutionHistory, argsHandler.getJSFile());
	}

	// write solutions to db
	if (argsHandler.getWriteSolutions())
	{
		dba->writeSolution(bestSolution);
	}

	// send notifications
	if (argsHandler.getSendNotifications())
	{
		Mailer mailer(dba, bestSolution);
		mailer.sendNotifications();
	}
}


