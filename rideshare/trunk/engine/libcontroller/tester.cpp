#include <string>
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include "TimeWindow.hpp"
#include "DBAccess.hpp"
#include "RouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include "RoutePreference.hpp"
#include "UserPreference.hpp"
#include "RouteClient.hpp"
#include "Match.hpp"
#include "Solution.hpp"
#include "SolutionUtils.hpp"
#include "TestCases.hpp"
#include "RouteMatrix.hpp"
#include "RouteMatrixLocal.hpp"
#include "Utils.hpp"
#include "CompatibilityMatrix.hpp"
#include "BruteForceOptimizer.hpp"
#include "BipartiteMatchingOptimizer.hpp"
#include "GeneticOptimizer.hpp"

#include "TesterUtil.hpp"

bool useLocalMatrix = true;
namespace UnitTests
{
	using namespace controller;
	using namespace controller::dba;
	using namespace controller::routes;
	using namespace optimizer;
	using namespace UnitTests::TestCases;
	using namespace UnitTests::MatchTests;

	using std::string;
	using std::vector;

	string host = "rideshare.ece.utexas.edu";
	string user = "jonas";
	string pw   = "letmein2";
	string db   = "rideshare";

	Solution::Riders  testRiders;
	Solution::Drivers testDrivers;
	Solution::Matches testMatches;

	void init_riders_and_drivers()
	{
		testDrivers = getSampleDrivers();
		testRiders  = getSampleRiders();
		testMatches = getSampleMatches();
	}

	namespace optimizer_test 
	{
		DBAccess::ptr dba;

		void test_route_matrix_generation()
		{
			cout<<"* test_route_matrix_generation()"<<endl;
			init_riders_and_drivers();
			RouteMatrix<> rMatrix(testDrivers, testRiders, testMatches);
			Match m1 = testMatches[0];
			Match m2 = testMatches[1];
			Driver d1 = testDrivers[0];
			Driver d2 = testDrivers[1];
			Locations locs;
			locs.push_back(d1.startLoc());
			locs.push_back(d2.endLoc());
			RouteClient rc;
			RouteInfo<> rInfo = rc.getRouteInfo(locs, RouteClient::MQ_SERVER);
			double controlDist = rInfo.getRouteDistance();
			uint32_t d1Id = d1.routeId;
			uint32_t d2Id = d2.routeId;
			double testDist = rMatrix.getDistance(d1Id, START, d2Id, END);
			ASSERT_APPROX(controlDist, testDist);

			Rider r1 = testRiders[0];
			Rider r2 = testRiders[1];

			locs.clear();
			locs.push_back(r1.startLoc());
			locs.push_back(r2.endLoc());
			rInfo = rc.getRouteInfo(locs, RouteClient::MQ_SERVER);
			controlDist = rInfo.getRouteDistance();
			uint32_t r1Id = r1.routeId;
			uint32_t r2Id = r2.routeId;
			testDist = rMatrix.getDistance(r1Id, START, r2Id, END);
			ASSERT_APPROX(controlDist, testDist);

			r1 = testRiders[2];
			d1 = m2.myDriver;

			locs.clear();
			locs.push_back(r1.endLoc());
			locs.push_back(d1.startLoc());
			rInfo = rc.getRouteInfo(locs, RouteClient::MQ_SERVER);
			controlDist = rInfo.getRouteDistance();
			r1Id = r1.routeId;
			d1Id = d1.routeId;
			testDist = rMatrix.getDistance(r1Id, END, d1Id, START);
			ASSERT_APPROX(controlDist, testDist);
		}

		void test_local_matrix()
		{
			cout<<"* test_local_matrix()"<<endl;
			init_riders_and_drivers();
			RouteMatrix<> rMatrix(testDrivers, testRiders, testMatches);
			RouteMatrixLocal rMatrixLocal(testDrivers, testRiders, testMatches);

			Match m1 = testMatches[0];
			Match m2 = testMatches[1];
			Driver d1 = testDrivers[0];
			Driver d2 = testDrivers[1];
			Locations locs;
			locs.push_back(d1.startLoc());
			locs.push_back(d2.endLoc());
			uint32_t d1Id = d1.routeId;
			uint32_t d2Id = d2.routeId;
			double testDist = rMatrix.getDistance(d1Id, START, d2Id, END);
			double localDist = rMatrixLocal.getDistance(d1Id, START, d2Id, END);

			std::cout << "local distance: " << localDist << "\tmq distance: " << testDist << std::endl;

			Rider r1 = testRiders[0];
			Rider r2 = testRiders[1];

			locs.clear();
			locs.push_back(r1.startLoc());
			locs.push_back(r2.endLoc());
			uint32_t r1Id = r1.routeId;
			uint32_t r2Id = r2.routeId;
			testDist = rMatrix.getDistance(r1Id, START, r2Id, END);
			localDist = rMatrixLocal.getDistance(r1Id, START, r2Id, END);

			std::cout << "local distance: " << localDist << "\tmq distance: " << testDist << std::endl;

			r1 = testRiders[2];
			d1 = m2.myDriver;

			locs.clear();
			locs.push_back(r1.endLoc());
			locs.push_back(d1.startLoc());
			r1Id = r1.routeId;
			d1Id = d1.routeId;
			testDist = rMatrix.getDistance(r1Id, END, d1Id, START);
			localDist = rMatrixLocal.getDistance(r1Id, END, d1Id, START);
			std::cout << "local distance: " << localDist << "\tmq distance: " << testDist << std::endl;

			testDist = rMatrixLocal.getDistance( r1Id, END, d1Id, START);
			double expectedDist = rMatrixLocal.getDistance( d1Id, START, r1Id, END);
			ASSERT_APPROX(expectedDist, testDist);

			testDist = rMatrixLocal.getDistance( r1Id, START, r1Id, START);
			expectedDist = rMatrixLocal.getDistance( r1Id, START, r1Id, START);
			ASSERT_APPROX(expectedDist, testDist);

			testDist = rMatrixLocal.getDistance( r2Id, START, r1Id, END);
			expectedDist = rMatrixLocal.getDistance( r1Id, END, r2Id, START);
			ASSERT_APPROX(expectedDist, testDist);
		}

		void test_match()
		{
			cout<<"* test_match()"<<endl;
			Riders riders;
			riders.clear();
			riders.push_back(r1); riders.push_back(r2); riders.push_back(r3);
			Match m1(d1);
			Match m2(d2, riders);
			ASSERT(m1.getMyMaxAge(),d1Info.age);
			ASSERT(m1.getMyMinAge(),d1Info.age);
			ASSERT(m1.getHasMale(),true);
			ASSERT(m1.getHasFemale(),false);
			ASSERT(m2.getMyMaxAge(),r3Info.age);
			ASSERT(m2.getMyMinAge(),r2Info.age);
			ASSERT(m2.getHasMale(),true);
			ASSERT(m2.getHasFemale(),true);
		}

		void test_canAddRider()
		{
			cout<<"* test_canAddRider()"<<endl;
			
			Match m1(d1);
			Match m2(d2);
			Drivers drivers;
			drivers.push_back(d1);
			drivers.push_back(d2);
			Riders riders;
			riders.push_back(r1);
			riders.push_back(r2);
			riders.push_back(r3);
			riders.push_back(r4);
			riders.push_back(r5);
			Match m3(d1);
			Matches matches;
			matches.push_back(m3);

			RouteInfo<> rInfo;
			//cout<<"d1 time windows are: "<<endl;
			//cout<<"leave = ("<<d1.routePref.leaveWindow.startTime<<" , "
			//	<< d1.routePref.leaveWindow.endTime<<")"<<endl;
			//cout<<"arrive = ("<<d1.routePref.arriveWindow.startTime<<" , "
			//	<< d1.routePref.arriveWindow.endTime<<")"<<endl;
			
			Solution s1(drivers, riders);
			//cout<<endl<<"Testing m1 (d1) with r1: " <<endl;
			ASSERT_EQ(s1.myMatches[m1.myDriver.routeId].canAddRider(r1,rInfo));
			//cout<<endl<<"Testing m1 (d1) with r2: " <<endl;
			ASSERT_EQ(!s1.myMatches[m1.myDriver.routeId].canAddRider(r2,rInfo));
			//cout<<endl<<"Testing m1 (d1) with r3: " <<endl;
			ASSERT_EQ(!s1.myMatches[m1.myDriver.routeId].canAddRider(r3,rInfo));
			//cout<<endl<<"Testing m1 (d1) with r4: " <<endl;
			ASSERT_EQ(!s1.myMatches[m1.myDriver.routeId].canAddRider(r4,rInfo));
			//cout<<endl<<"Testing m1 (d1) with r5: " <<endl;
			ASSERT_EQ(!s1.myMatches[m1.myDriver.routeId].canAddRider(r5,rInfo));

			//cout<<endl<<"Testing m2 (d2) with r1: " <<endl;
			ASSERT_EQ(s1.myMatches[m1.myDriver.routeId].canAddRider(r1,rInfo));
			//cout<<endl<<"Testing m2 (d2) with r2: " <<endl;
			ASSERT_EQ(s1.myMatches[m2.myDriver.routeId].canAddRider(r2,rInfo));
			//cout<<endl<<"Testing m2 (d2) with r3: " <<endl;
			ASSERT_EQ(!s1.myMatches[m2.myDriver.routeId].canAddRider(r3,rInfo));
			//cout<<endl<<"Testing m2 (d2) with r4: " <<endl;
			ASSERT_EQ(!s1.myMatches[m2.myDriver.routeId].canAddRider(r4,rInfo));
			//cout<<endl<<"Testing m2 (d2) with r5: " <<endl;
			ASSERT_EQ(!s1.myMatches[m2.myDriver.routeId].canAddRider(r5,rInfo));

			drivers.clear();
			Solution s2(drivers,riders,matches);
			//cout<<endl<<"Testing m3 (d1,r1) with r6: " <<endl;
			ASSERT_EQ(s2.myMatches[m3.myDriver.routeId].canAddRider(r6,rInfo));
			//cout<<endl<<"Testing m3 (d1,r1) with r7: " <<endl;
			ASSERT_EQ(s2.myMatches[m3.myDriver.routeId].canAddRider(r7,rInfo));
		}

		void test_brute_force_optimizer()
		{
			cout<<"* test_brute_force_optimizer()"<<endl;
			dba.reset(new DBAccess(host, db, user, pw));
			testDrivers = dba->getDriverSubmissions("austinDemo");
			testRiders = dba->getRiderSubmissions("austinDemo");
			//cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
			//cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
			//cout << "Testing Brute Force Optimizer" << endl;
			BruteForceOptimizer optimizer(testDrivers,testRiders);
			//ASSERT_APPROX(optimizer.getBestScore(), 0.0606914563502);
			ASSERT_APPROX(optimizer.getBestScore(), 0.0749681385411);
			optimizer.optimize();
			//ASSERT_APPROX(optimizer.getBestScore(), 4.02776);
			ASSERT_APPROX(optimizer.getBestScore(), 3.07343);
		//	ReturnCode testCode = dba->writeSolution(optimizer.getBestSolution());
		//	ASSERT(testCode, SUCCESS);
		}

		void test_genetic_optimizer()
		{
			cout<<"* test_genetic_optimizer()"<<endl;
			dba.reset(new DBAccess(host, db, user, pw));
			vector<string> comments_to_search_for;
			//comments_to_search_for.push_back("austinDemo2_1");
			//comments_to_search_for.push_back("austinDemo2_2");
			//comments_to_search_for.push_back("austinDemo2_3");
			//comments_to_search_for.push_back("austinDemo2_4");
			//comments_to_search_for.push_back("austinDemo2_5");
			comments_to_search_for.push_back("austinDemo2_6");
			testDrivers = dba->getDriverSubmissions(comments_to_search_for);
			testRiders = dba->getRiderSubmissions(comments_to_search_for);
			GeneticOptimizer optimizer(testDrivers,testRiders);
			//ASSERT_APPROX(optimizer.getBestScore(), 0.0606914563502);
			//ASSERT_APPROX(optimizer.getBestScore(), 0.0749681385411);
			optimizer.optimize();
			//ASSERT_APPROX(optimizer.getBestScore(), 5.01321);
			//ASSERT_APPROX(optimizer.getBestScore(), 5.01667);
			//
			//ASSERT_APPROX(optimizer.getBestScore(), 4.02776);
			//ASSERT_APPROX(optimizer.getBestScore(), 3.07343);
		}

		void test_bipartite_matching_optimizer()
		{
			cout<<"* test_bipartite__optimizer()"<<endl;
			dba.reset(new DBAccess(host, db, user, pw));
			/*
			 * austin Demo2_6 Test
			 */
			cout<<"austinDemo2_6 Test"<<endl;
			testDrivers = dba->getDriverSubmissions("austinDemo2_6");
			testRiders = dba->getRiderSubmissions("austinDemo2_6");
			/* Test Bipartite over same data set with different orders of riders of Riders and matches */
			BipartiteMatchingOptimizer optimizer(testDrivers, testRiders);
			//cout << "The score before optimization is: " << optimizer.getBestScore() << endl;
			ASSERT_APPROX(optimizer.getBestScore(), 0.0767585);//austinDemo2_6 initial result

			optimizer.optimize();
			//cout << "The score after optimization is: " << optimizer.getBestScore() << endl;
			ASSERT_APPROX(optimizer.getBestScore(), 8.07676);//austinDemo2_6 final score
			
		}

		void test_solution2_javascript()
		{
			dba.reset(new DBAccess(host, db, user, pw));
			cout<<"* test_solution2_javascript()"<<endl;
			vector<string> comments_to_search_for;
			comments_to_search_for.push_back("austinDemo2_1");
			comments_to_search_for.push_back("austinDemo2_2");
			comments_to_search_for.push_back("austinDemo2_3");
			comments_to_search_for.push_back("austinDemo2_4");
			comments_to_search_for.push_back("austinDemo2_5");
			comments_to_search_for.push_back("austinDemo2_6");
			testDrivers = dba->getDriverSubmissions(comments_to_search_for);
			testRiders = dba->getRiderSubmissions(comments_to_search_for);

			GeneticOptimizer optimizer(testDrivers,testRiders);
			optimizer.optimize();

			Solution::Solutions solutions;
			solutions.push_back(optimizer.getBestSolution());

			solutions2javascript(optimizer.solutionHistory, "test_java_script.js");
		}

		void test_all_optimizers()
		{
			cout<<"* run_optimizers()"<<endl;
			dba.reset(new DBAccess(host, db, user, pw));
			vector<string> test_1;
			vector<string> test_2;
			vector<string> test_3;
			vector<string> test_4;
			vector<string> test_5;
			vector<string> test_6;
			vector<string> test_7;
			vector<string> test_8;
			vector<string> test_9;
			vector<string> test_10;
			vector<string> test_11;
			vector<string> raw;
			vector<string> uShip_1;
			vector<string> uShip_2;
			vector<string> uShip_3;

			test_1.push_back("austinDemo2_1");
			test_2.push_back("austinDemo2_2");
			test_3.push_back("austinDemo2_3");
			test_4.push_back("austinDemo2_4");
			test_5.push_back("austinDemo2_5");
			test_6.push_back("austinDemo2_6");
			/* test 7 */
				test_7.push_back("austinDemo2_1"); 
				test_7.push_back("austinDemo2_2");
			/* test_8 */
				test_8.push_back("austinDemo2_1"); 
				test_8.push_back("austinDemo2_2");
				test_8.push_back("austinDemo2_3");
			/* test_9 */
				test_9.push_back("austinDemo2_1"); 
				test_9.push_back("austinDemo2_2");
				test_9.push_back("austinDemo2_3");
				test_9.push_back("austinDemo2_4");
			/* test_10 */
				test_10.push_back("austinDemo2_1"); 
				test_10.push_back("austinDemo2_2");
				test_10.push_back("austinDemo2_3");
				test_10.push_back("austinDemo2_4");
				test_10.push_back("austinDemo2_5");
			/* test_11 */
				test_11.push_back("austinDemo2_1"); 
				test_11.push_back("austinDemo2_2");
				test_11.push_back("austinDemo2_3");
				test_11.push_back("austinDemo2_4");
				test_11.push_back("austinDemo2_5");
				test_11.push_back("austinDemo2_6");

			raw.push_back("Raw");
			uShip_1.push_back("uShip_1");
			uShip_2.push_back("uShip_2");
			uShip_3.push_back("uShip_3");

			vector< vector<string> > bf_test_cases;
			vector< vector<string> > g_test_cases;
			vector< vector<string> > bm_test_cases;
			
			//bf_test_cases.push_back(test_1);
			//bf_test_cases.push_back(test_2);
			//bf_test_cases.push_back(test_3);
			//bf_test_cases.push_back(test_4);
			//bf_test_cases.push_back(test_5);
			//bf_test_cases.push_back(test_6);
			//bf_test_cases.push_back(test_7);
			//bf_test_cases.push_back(test_8);
			//bf_test_cases.push_back(test_9);
			//bf_test_cases.push_back(test_10);

			bm_test_cases.push_back(test_1);
			bm_test_cases.push_back(test_2);
			bm_test_cases.push_back(test_3);
			bm_test_cases.push_back(test_4);
			bm_test_cases.push_back(test_5);
			bm_test_cases.push_back(test_6);
			bm_test_cases.push_back(test_7);
			bm_test_cases.push_back(test_8);
			bm_test_cases.push_back(test_9);
			bm_test_cases.push_back(test_10);
			bm_test_cases.push_back(test_11);
			//bm_test_cases.push_back(raw);
			//bm_test_cases.push_back(uShip_1);
			//bm_test_cases.push_back(uShip_2);
			//bm_test_cases.push_back(uShip_3);
	
			g_test_cases.push_back(test_1);
			g_test_cases.push_back(test_2);
			g_test_cases.push_back(test_3);
			g_test_cases.push_back(test_4);
			g_test_cases.push_back(test_5);
			g_test_cases.push_back(test_6);
			g_test_cases.push_back(test_7);
			g_test_cases.push_back(test_8);
			g_test_cases.push_back(test_9);
			g_test_cases.push_back(test_10);
			g_test_cases.push_back(test_11);
			//g_test_cases.push_back(uShip_1);
			//g_test_cases.push_back(uShip_2);
			//g_test_cases.push_back(uShip_3);
			
			cout<<"****************************************"<<endl;
			cout<<"* Results for Brute Force Optimizer "<<endl;
			cout<<"****************************************"<<endl;
			for(size_t i =0; i < bf_test_cases.size(); i++)
			{
				vector<string> test_data_to_include = bf_test_cases[i];
				cout<< "***************************************"<<endl;
				cout<< "* Running test_" << i+1 <<": ";
				for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
				{
					cout << test_data_to_include[jj] << ",";
				}
				cout<<endl;
				cout<< "***************************************"<<endl;
				/* retrieve test data from the database */
				testDrivers = dba->getDriverSubmissions(test_data_to_include);
				testRiders = dba->getRiderSubmissions(test_data_to_include);
				
				cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
				cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
				
				BruteForceOptimizer bfOptimizer(testDrivers, testRiders);
				cout << "Score before optimization: " << bfOptimizer.getBestScore() << endl;
				clock_t start = clock();
				bfOptimizer.optimize();
				clock_t end = clock();
				double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
				cout<< "Score after optimization: " << bfOptimizer.getBestScore() << endl;
				cout<< "Runtime in milliseconds: " << runTime << endl;
			}
			cout<<"****************************************"<<endl;
			cout<<"* Results for Bipartite Matching Optimizer "<<endl;
			cout<<"****************************************"<<endl;
			for(size_t i =0; i < bm_test_cases.size(); i++)
			{
				vector<string> test_data_to_include = bm_test_cases[i];
				cout<<"****************************************"<<endl;
				cout<< "*    Running test_" << i+1 <<": ";
				for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
				{
					cout << test_data_to_include[jj] << ",";
				}
				cout<<endl;
				cout<<"****************************************"<<endl;
				/* retrieve test data from the database */
				testDrivers = dba->getDriverSubmissions(test_data_to_include);
				testRiders = dba->getRiderSubmissions(test_data_to_include);
				
				cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
				cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
				
				BipartiteMatchingOptimizer bmOptimizer(testDrivers, testRiders);
				cout << "Score before optimization: " << bmOptimizer.getBestScore() << endl;
				clock_t start = clock();
				bmOptimizer.optimize();
				clock_t end = clock();
				double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
				cout<< "Score after optimization: " << bmOptimizer.getBestScore() << endl;
				cout<< "Runtime in milliseconds: " << runTime << endl;
			}
			cout<<"****************************************"<<endl;
			cout<<"* Results for Genetic Optimizer "<<endl;
			cout<<"****************************************"<<endl;
			for(size_t i =0; i < g_test_cases.size(); i++)
			{
				vector<string> test_data_to_include = g_test_cases[i];
				cout<<"****************************************"<<endl;
				cout<< "*    Running test_" << i+1 <<": ";
				for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
				{
					cout << test_data_to_include[jj] << ",";
				}
				cout<<endl;
				cout<<"****************************************"<<endl;
				/* retrieve test data from the database */
				testDrivers = dba->getDriverSubmissions(test_data_to_include);
				testRiders = dba->getRiderSubmissions(test_data_to_include);
				
				cout<< "      testDrivers.size() = "<<testDrivers.size()<<endl; 
				cout<< "      testRiders.size() = "<<testRiders.size()<<endl; 
				
				GeneticOptimizer gOptimizer(testDrivers, testRiders);
				cout << "Score before optimization: " << gOptimizer.getBestScore() << endl;
				clock_t start = clock();
				gOptimizer.optimize();
				clock_t end = clock();
				double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
				cout<< "Score after optimization: " << gOptimizer.getBestScore() << endl;
				cout<< "Runtime in milliseconds: " << runTime << endl;
			}
		}

		void test_cases()
		{
			typedef map<uint32_t,Match> MatchesMap;
			typedef map<uint32_t,Rider> RidersMap;
			
			#define use_All 1 // if false, disregard next two defines
			// and just use what you get
				size_t num_drivers = 50;
				size_t num_riders = 100;
			#define useBruteForce 0

			vector<string> comments;
			//comments.push_back("Raw");
			//comments.push_back("austinDemo");
			comments.push_back("austinDemo2_1");
			comments.push_back("austinDemo2_2");
			comments.push_back("austinDemo2_3");
			comments.push_back("austinDemo2_4");
			comments.push_back("austinDemo2_5");
			comments.push_back("austinDemo2_6");
			//comments.push_back("FinalDemo");

			cout << "* test_cases()" << endl;
			dba.reset(new DBAccess(host, db, user, pw));
			
			cout << " - Input: \n";
			cout << " - Comment Queried: " << comments[0] << " and more..." << endl;
			
			Drivers drivers;
			drivers = dba->getDriverSubmissions(comments);
			cout << " --- Got Drivers: " << drivers.size() << endl;
			Drivers smalld;
			if (use_All) { num_drivers = drivers.size(); }
			for (size_t ii = 0; ii < num_drivers; ii++){
				smalld.push_back(drivers[ii]);
			}
			ASSERT(smalld.size(), num_drivers);
			cout << " ---- Using Drivers: " << num_drivers << endl;


			Riders riders;
			riders = dba->getRiderSubmissions(comments);
			cout << " --- Got Riders: " << riders.size() << endl;
			Riders smallr;
			if (use_All) { num_riders = riders.size(); }
			for (size_t ii = 0; ii < num_riders; ii++){
				smallr.push_back(riders[ii]);
			}
			ASSERT(smallr.size(), num_riders);
			cout << " ---- Using Riders: " << num_riders << endl;
			
			
#if useBruteForce
			BruteForceOptimizer optimizer(smalld, smallr);
			cout << " - Creating Brute Force Optimizer...";
#else
			GeneticOptimizer optimizer(smalld, smallr);
			cout << " - Creating Genetic Optimizer...";
#endif
			
			cout << "done.\n - Optimizing...";
			cout.flush(); 
			optimizer.optimize();
			cout << "done.\n";
			
			double score = optimizer.getBestScore();
			cout << " - Output: \n"; 
			cout << " --- Score: " << score << endl;
			
			Solution solution = optimizer.getBestSolution();
			
			size_t matched_riders = 0;
			size_t unused_capacity = 0;
			for(MatchesMap::iterator cur_match = solution.myMatches.begin(); 
					cur_match != solution.myMatches.end(); cur_match++)
			{
				matched_riders += cur_match->second.myRiders.size();
				matched_riders += cur_match->second.confirmedRiders.size(); // no one uses this now but we might later
				unused_capacity += cur_match->second.myDriver.capacity;
			}
			size_t num_matches = solution.myMatches.size();
			
			cout << " --- Matches (Drivers): " << num_matches << endl;
			cout << " --- Matched Riders: " << matched_riders
				<< ", Unmatched: " << (num_riders - matched_riders) << endl;
			cout << " --- Unused Capacity: " << unused_capacity << endl;
			
			ASSERT(num_matches, num_drivers);
			ASSERT_APPROX(score, 20.02);
			//ReturnCode testCode = dba->writeSolution(solution);
			//ASSERT(testCode, SUCCESS);
		}

		void run_all()
		{
			cout<<"****************************************"<<endl;
			cout<<"*            Running optimizer tests."<<endl;
			cout<<"****************************************"<<endl;
			test_local_matrix();
			test_route_matrix_generation();
			test_canAddRider();
			test_brute_force_optimizer(); 
			test_genetic_optimizer(); 
			test_solution2_javascript();
			//test_bipartite_matching_optimizer();
			//test_all_optimizers();
			//test_cases();
		}
	}

	namespace routes_tests
	{
		RouteClient::Locations locs;

		void init_test_locations()
		{
			locs.clear();
			Location<double> loc1(29.387870, -98.511960, "san antonio");
			Location<double> loc2(40.706440, -74.252990,"new york");
			Location<double> loc3(35.079920, -90.070220,"memphis");
			Location<double> loc4(29.691960, -95.325730,"houston");
			//Location<double> loc5(29.691960, -95.325730,"houston");
			Location<double> loc5(34.182600, -118.172220, "los angeles");
			locs.push_back(loc1);
			locs.push_back(loc3);
			locs.push_back(loc4);
			locs.push_back(loc2);
			locs.push_back(loc5);
		}

		void test_get_largest_rectangle()
		{
			Match m1(d1);

			m1.getLargestRectangle();
			vector< Location<> > rectangle = m1.getLargestRectangle();

			/* Check Top Left Location */
			ASSERT(rectangle[0].lat,m1.myDriver.endLoc().lat);
			ASSERT(rectangle[0].lng,m1.myDriver.startLoc().lng);
			/* Check Bottom Right Location */
			ASSERT(rectangle[1].lat,m1.myDriver.startLoc().lat);
			ASSERT(rectangle[1].lng,m1.myDriver.endLoc().lng);
			
			m1.addRider(r1);
			/* Check Top Left Location */
			ASSERT(rectangle[0].lat, r1.endLoc().lat);
			ASSERT(rectangle[0].lng, r1.endLoc().lng);
			/* Check Bottom Right Location */
			ASSERT(rectangle[1].lat, m1.myDriver.startLoc().lat);
			ASSERT(rectangle[1].lng, m1.myDriver.endLoc().lng);
		//Location<> d1StartLoc(30.260180, -97.745700, "Congress Ave S");
		//Location<> d1EndLoc(30.352747, -97.643664, "Cameron Rd");
		//Location<> r1StartLoc(30.380146, -97.716339, "Metric Blvd");
		//Location<> r1EndLoc(30.353078, -97.797554, "W Courtyard Dr");



		}
		
		void test_route_info_getRouteDistance()
		{
			cout<<"* test_route_info_getRouteDistance()"<<endl;
			init_test_locations();
			RouteClient rClient;
			RouteInfo<double> rInfo = rClient.getRouteInfo(locs, RouteClient::MQ_SERVER);
			//sum up parts and compare to total.  should be the same
			double testSum = 0;
			for (size_t ii = 0; ii < rInfo.size(); ii++)
			{
				testSum += rInfo[ii].distanceMiles;
			}
			ASSERT(rInfo.getRouteDistance(), testSum);
			//rInfo.printAllPoints();
		}

		void test_route_info_getRouteTime()
		{
			cout<<"* test_route_info_getRouteTime()"<<endl;
			init_test_locations();
			RouteClient rClient;
			RouteInfo<double> rInfo = rClient.getRouteInfo(locs, RouteClient::MQ_SERVER);
			//sum up parts and compare to total.  should be the same
			double testSum = 0;
			for (size_t ii = 0; ii < rInfo.size(); ii++)
			{
				testSum += rInfo[ii].timeMinutes;
			}
			ASSERT(rInfo.getRouteTime(), testSum);
			//rInfo.printAllPoints();
		}

		void test_get_route_matrix()
		{
			cout<<"* test_get_route_matrix()"<<endl;
			init_test_locations();
			RouteClient rc;
			RouteMatrix<double> rMatrix = rc.getRouteMatrix(locs, RouteClient::MQ_SERVER);
		}

		void test_get_route_1()
		{
			cout<<"* test_get_route_1()"<<endl;
			init_test_locations();
			RouteClient rc;
			string resultStr(rc.getRouteDirections(locs));
			//std::cout<<resultStr<<std::endl;
		}

		void test_generate_route_image()
		{
			cout<<"* test_generate_route_image()"<<endl;
			init_test_locations();
			RouteClient rClient;
			rClient.setLocations(locs);
			CMQRouteResults results = rClient.getMQRouteResults();
			rClient.createRouteImage(results, "map_test.gif");
		}

		void test_geocode_addr()
		{
			cout<<"* test_geocode_addr()"<<endl;
			RouteClient rClient;
			Address addr("1600 wickersham ln", "Austin", "TX");
			Location<> loc = rClient.getLocationFromAddress(addr);
			ASSERT_EQ(loc.lat != 0.0);
			ASSERT_EQ(loc.lng != 0.0);
		}

		void test_create_route_image_from_solution()
		{
			cout<<"* test_create_route_image_from_solution()"<<endl;
			DBAccess::ptr dba(new DBAccess(host, db, user, pw));
			testDrivers = dba->getDriverSubmissions("austinDemo");
			testRiders = dba->getRiderSubmissions("austinDemo");
			BruteForceOptimizer optimizer(testDrivers,testRiders);
			optimizer.optimize();
			Solution solution = const_cast<Solution &> (optimizer.getBestSolution());

			RouteClient rClient;
			rClient.createRouteImage(solution, "test_map_generate.gif");
#if 0
			
			rClient.setLocations((solution.myMatches.begin())->second.myRoute);
			CMQRouteResults results = rClient.getMQRouteResults();
			rClient.createRouteImage(results, "test_map_generate2.gif");
#endif

		}
		void run_all()
		{
			cout<<"****************************************"<<endl;
			cout<<"*            Running route tests."<<endl;
			cout<<"****************************************"<<endl;
			//test_get_route_1();
			//test_route_info_getRouteDistance();
			//test_route_info_getRouteTime();
			//test_generate_route_image();
			//test_create_route_image_from_solution();
			//test_get_route_matrix();
			//test_geocode_addr();
			test_get_largest_rectangle();
		}

	}

	namespace dba_tests
	{
		DBAccess::ptr dba;
		// make sure we can at least connect to the database and request a row
		void test_connect_and_query()
		{
			cout<<"* test_connect_and_query()"<<endl;
			try 
			{
				mysqlpp::Query query = dba->getQuery();
				query << "SELECT route_submission_id FROM route_submissions";
				Result test     = query.store();
				ASSERT_GT(test.num_rows(),1);
			} catch (const mysqlpp::Exception& er) 
			{
				// Catch-all for any other MySQL++ exceptions
				std::cerr << "Error: " << er.what() << std::endl;
			}
		}
		
		// get fake route of route_submission_id: 123456
		// N.b. this route_submission_id must remain unmodified for this test to work
		void test_get_fake_route()
		{
			cout<<"* test_get_fake_route()"<<endl;
			RouteSubmission::ptr testRoute = dba->getRouteSubmission(123456);

			ASSERT(testRoute->routeId, 123456);
			ASSERT(testRoute->userId, 654321);
			ASSERT(testRoute->startLoc().lat, 34.4);
			ASSERT(testRoute->endLoc().lng, -60.3456);
			ASSERT(testRoute->routePref.leaveWindow.startTime, "2008-02-12 00:00:00");
			ASSERT(testRoute->routePref.arriveWindow.endTime, "2008-02-27 00:00:00");
			ASSERT(testRoute->optimalDistance, 3444.56);
		}

		// test get All routes in DB
		// test only checks if there is more than 2 entries
		void test_get_all_route_submissions()
		{
			cout<<"* test_get_all_route_submissions()"<<endl;
			DBAccess::Riders submissions = dba->getRiderSubmissions();
			ASSERT_GT(submissions.size(), 2);
		}

		void test_get_all_commented_route_submissions()
		{
			cout<<"* test_get_all_commented_route_submissions()"<<endl;
			DBAccess::Riders submissions = dba->getRiderSubmissions("TestComment");
			ASSERT_EQ(submissions.size() == 1);
		}
		
		void test_get_all_list_comments_route_submissions()
		{
			cout<<"* test_get_all_list_comments_route_submissions()"<<endl;
			vector<string> comments;
			comments.push_back("TestComment");
			comments.push_back("TestComment2");
			DBAccess::Riders submissions = dba->getRiderSubmissions(comments);
			ASSERT(submissions.size(), 1);
		}
		
		// test writeRouteSubmission.  We create a new RouteSubmission, add it DB,
		// and query and compare submission objects
		void test_write_submission_1()
		{
			cout<<"* test_write_submission()"<<endl;
			Location<double> start(123.45, -123.45);
			Location<double> end(123.45, -123.45);
			TimeWindow<DateTime> leave(DateTime("2008-01-30 03:30:00"), DateTime("2008-01-30 10:30:00"));
			TimeWindow<DateTime> arrive(DateTime("2009-02-28 05:30:00"), DateTime("2009-02-28 06:30:00"));

			RoutePreference rPref(leave, arrive);
			UserPreference  uPref(18, 21, 1, 4.00);

			size_t capacity = 10;
			RouteSubmission::ptr rSubmission( new DriverRouteSubmission
						(0xDEAD, 0xBEEF, start, end, uPref, rPref, 42.52, capacity)
						);

			rSubmission->setComment("test this comment...");
			ReturnCode success = dba->writeRouteSubmission(rSubmission);
			ASSERT(success, SUCCESS);

			// check values were inserted
			RouteSubmission::ptr testRoute = dba->getRouteSubmission(0xDEAD);

			ASSERT(testRoute->routeId, 0xDEAD);
			ASSERT(testRoute->routePref.arriveWindow.startTime.hour, 5);
			ASSERT(testRoute->routePref.arriveWindow.endTime.hour, 6);
			ASSERT(testRoute->routePref.leaveWindow.startTime.hour, 3);
			ASSERT(testRoute->routePref.leaveWindow.endTime.hour, 10);
			ASSERT(testRoute->userId, 0xBEEF);
			ASSERT(testRoute->comment, "test this comment...");
			ASSERT(testRoute->startLoc().lat, 123.45);
			ASSERT(testRoute->endLoc().lng, -123.45);
			ASSERT(testRoute->endLoc().lng, -123.45);
			
			// cleanup
			success = dba->deleteRouteSubmission(0xDEAD);
			ASSERT(success, SUCCESS);
		}

		// test writeDriverRouteSubmission. new driver, add to db, test it, delete.
		void test_write_driver_submissions()
		{
			cout<<"* test_write_driver_submissions()"<<endl;

			Location<double> start(123.45, -123.45);
			Location<double> end(123.45, -123.45);
			TimeWindow<DateTime> leave(DateTime("2008-01-30 03:30:00"), DateTime("2008-01-30 10:30:00"));
			TimeWindow<DateTime> arrive(DateTime("2009-02-28 05:30:00"), DateTime("2009-02-28 06:30:00"));
			RoutePreference rPref(leave, arrive);
			UserPreference  uPref(18, 21, 1, 4.00);
			size_t capacity = 10;
			DriverRouteSubmission::ptr driverX(new DriverRouteSubmission(
						0xDEAD, 0xBEEF, start, end, uPref, rPref, 45.52, capacity));
			driverX->setComment("test this comment...");
			DriverRouteSubmission::ptr driverY(new DriverRouteSubmission(
						0xDEAE, 0xBEF0, start, end, uPref, rPref, 45.52, (capacity-1)));
			driverY->setComment("test this comment...");
			
			ReturnCode success = dba->writeDriverRouteSubmission(driverX);
				ASSERT(success, SUCCESS);
			success = dba->writeDriverRouteSubmission(driverY);
				ASSERT(success, SUCCESS);

			Driver testRoute = dba->getDriverRouteSubmission(0xDEAD);
				ASSERT(testRoute.routeId, 0xDEAD);
				ASSERT(testRoute.routePref.arriveWindow.startTime.hour, 5);
				ASSERT(testRoute.routePref.arriveWindow.endTime.hour, 6);
				ASSERT(testRoute.routePref.leaveWindow.startTime.hour, 3);
				ASSERT(testRoute.routePref.leaveWindow.endTime.hour, 10);
				ASSERT(testRoute.userId, 0xBEEF);
				ASSERT(testRoute.comment, "test this comment...");
				ASSERT(testRoute.startLoc().lat, 123.45);
				ASSERT(testRoute.endLoc().lng, -123.45);
				ASSERT(testRoute.endLoc().lng, -123.45);
				ASSERT(testRoute.capacity, 10); 
			
			Drivers drivers = dba->getDriverSubmissions("test this comment...");
				ASSERT(drivers.size(), 2); // if this assert fails, check the comments
				
				Driver driver(drivers[0]);
			if (drivers[0].routeId != 0xDEAE)
				driver = drivers[1];
				
				ASSERT(driver.routeId, 0xDEAE);
				ASSERT(driver.routePref.arriveWindow.startTime.hour, 5);
				ASSERT(driver.routePref.arriveWindow.endTime.hour, 6);
				ASSERT(driver.routePref.leaveWindow.startTime.hour, 3);
				ASSERT(driver.routePref.leaveWindow.endTime.hour, 10);
				ASSERT(driver.userId, 0xBEF0);
				ASSERT(driver.comment, "test this comment...");
				ASSERT(driver.startLoc().lat, 123.45);
				ASSERT(driver.endLoc().lng, -123.45);
				ASSERT(driver.endLoc().lng, -123.45);
				ASSERT(driver.capacity, (capacity-1)); 

			// cleanup
			success = dba->deleteRouteSubmission(0xDEAD);
				ASSERT(success, SUCCESS);
			success = dba->deleteRouteSubmission(0xDEAE);
				ASSERT(success, SUCCESS);
		}

		void test_user_info()
		{
			cout<<"* test_user_info()"<<endl;
			UserInfo expectedInfo("Derrick","Huhn","derrickhuhn@mail.utexas.edu"
					, 1, 22);
			UserInfo testInfo = dba->getUserInfo(2);
			ASSERT(expectedInfo,  testInfo);
		}

		void test_write_solution()
		{
			cout<<"* test_write_solution()"<<endl;
/*			// FIXME: TODO: add dates to the solution before writing it, or it will fail
			init_riders_and_drivers();
			Solution::ptr solution(new Solution(testDrivers, testRiders, testMatches));
			uint32_t solutionId = 0;
			ReturnCode testCode = dba->writeSolution(solution, solutionId);
			ASSERT(testCode, SUCCESS);

			testCode = dba->deleteSolution(solutionId);
			ASSERT(testCode, SUCCESS);
*/

			// now write solution generated by brute force algorithm
			DBAccess::ptr dba(new DBAccess(host, db, user, pw));
			testDrivers = dba->getDriverSubmissions("austinDemo");
			testRiders = dba->getRiderSubmissions("austinDemo");

			Solution::ptr solution(new Solution( testDrivers, testRiders ));
			uint32_t solutionId = 0;
			ReturnCode testCode;

			testCode = dba->writeSolution(solution, solutionId);
			ASSERT(testCode, SUCCESS);

			testCode = dba->deleteSolution(solutionId);
			ASSERT(testCode, SUCCESS);
		}

		void test_time_windows()
		{
			cout<<"* test_time_windows()"<<endl;
			DateTime start("2008-01-30 08:30:00");
			DateTime end("2008-01-30 10:30:00");
#if 0			
			cout<<"DateTime start = "<< start << endl;
			cout<<"DateTime end = "  << end   << endl;
			
			cout<<"Raw DateTime from str constructor: " 
				<< DateTime("2008-01-30 08:30:00")<<"     "<<DateTime("2008-01-30 10:30:00")<<endl;
			cout<<"Originals: 2008-01-30 08:30:00 , 2008-01-30 10:30:00"<<endl;
			cout<<"DateTimes using TimeWindow constructor: "<<dt1.startTime<<" , "<<dt1.endTime<<endl;
#endif
			TimeWindow<DateTime> dt1(start,end);
			
			TimeWindow<ptime> pt1 = convertToPtime(dt1);
			cout<<"ptimes using conversion method: "<<pt1.startTime<<" , "<<pt1.endTime<<endl;
			
			TimeWindow<DateTime> dt2 = convertToDateTime(pt1);
			cout<<"DateTimes using conversion method: "<<dt2.startTime<<" , "<<dt2.endTime<<endl;
		}

		void test_update_route_submission()
		{
			cout<<"* test_update_route_submission()" << endl;
			DBAccess::ptr dba(new DBAccess(host, db, user, pw));
			uint32_t solutionId = 0xFF;
			uint32_t matchId = 0xFF;
			PointInfo<> point(2222);
			ReturnCode ret = dba->updateRouteSubmission(point, solutionId, matchId);
			ASSERT(ret, SUCCESS);

		}
		void run_all()
		{
			cout<<"****************************************"<<endl;
			cout<<"*            Running dba tests."<<endl;
			cout<<"****************************************"<<endl;
			dba.reset(new DBAccess(host, db, user, pw));
			test_connect_and_query();
			//test_get_fake_route(); //currently broken - run time error
			//test_get_all_route_submissions();//currently broken - run time error
			test_get_all_commented_route_submissions();
			test_get_all_list_comments_route_submissions();
			test_get_all_commented_route_submissions();
			test_write_submission_1();
			test_write_driver_submissions();
			test_user_info();
			test_write_solution();
			test_time_windows();
			test_update_route_submission();
		}
	}

	namespace Preference_tests
	{
		void test_create_simple_pref_1()
		{
			cout<<"* test_create_simple_pref_1()"<<endl;
			DBAccess::ptr dba(new DBAccess(host, db, user, pw));
			UserPreference expectedPref(0xdead, 21, 30, 1, 10.0);
			dba->writeUserPreference(expectedPref);
			UserPreference testPref = dba->getUserPreference(0xdead);
			ASSERT(testPref.userId, expectedPref.userId);
			ASSERT(testPref.ratingMin, expectedPref.ratingMin);
			ASSERT(testPref.ageMin, expectedPref.ageMin);
			ASSERT(testPref.ageMax, expectedPref.ageMax);
			ASSERT(testPref.genderId, expectedPref.genderId);
			ReturnCode success = dba->deleteUserPreference(0xdead);
			ASSERT(success, SUCCESS);
		}

		void test_create_simple_pref_2()
		{
			cout<<"* test_create_simple_pref_2()"<<endl;
			DBAccess::ptr dba(new DBAccess(host, db, user, pw));
			UserPreference expectedPref(44, 55, 21, 30, 1, 10.0);

			dba->writeRouteUserPreference(expectedPref);
			UserPreference testPref = dba->getRoutePreference(44);

			ASSERT(testPref.ratingMin, expectedPref.ratingMin);
			ASSERT(testPref.ageMin, expectedPref.ageMin);
			ASSERT(testPref.ageMax, expectedPref.ageMax);
			ASSERT(testPref.genderId, expectedPref.genderId);
			ReturnCode success = dba->deleteRoutePreference(44);
			ASSERT(success, SUCCESS);
			success = dba->deleteRouteSubmission(0xBEEF);
			ASSERT(success, SUCCESS);
		}

		typedef vector< UserPreference > UserPreferences;
		void test_getCommonPrefs()
		{
			cout<<"* test_getCommonPrefs()"<<endl;
			UserPreference uPref1(18, 40, DONT_CARE, 3.00);
			UserPreference uPref2(18, 30, DONT_CARE, 4.00);
			UserPreference uPref3(18, 25, MALE_ONLY, 5.00);
			UserPreference uPref4(18, 21, FEMALE_ONLY, 6.00);
			UserPreferences prefs;
			UserPreference commonPrefs;
			prefs.push_back(uPref1);
			prefs.push_back(uPref2);
			commonPrefs =  UserPreference::getCommonUserPreference(prefs);
			
			ASSERT(commonPrefs.ageMin,18);
			ASSERT(commonPrefs.ageMax,30);
			ASSERT(commonPrefs.ratingMin,4.00);
			ASSERT(commonPrefs.genderId,DONT_CARE);
			prefs.push_back(uPref3);
			commonPrefs =  UserPreference::getCommonUserPreference(prefs);
			ASSERT(commonPrefs.ageMin,18);
			ASSERT(commonPrefs.ageMax,25);
			ASSERT(commonPrefs.ratingMin,5.00);
			ASSERT(commonPrefs.genderId,MALE_ONLY);
		}

		void run_all()
		{
			cout<<"****************************************"<<endl;
			cout<<"*            Running preference tests."<<endl;
			cout<<"****************************************"<<endl;
			test_create_simple_pref_1();
			//test_create_simple_pref_2(); //currently broken - run time error
			test_getCommonPrefs();
		}
	}//end Preference_tests namespace

	namespace Route_tests
	{
		// create a fake route and assert all its members
		void test_create_route_submission()
		{
			cout<<"* test_create_route_submission()"<<endl;
			Location<double> start(123.456789, -123.456789);
			Location<double> end(123.456789, -123.456789);
			TimeWindow<DateTime> leave(DateTime("2008-1-30 3:30:00"), 
																 DateTime("2008-1-30 4:30:00"));
			TimeWindow<DateTime> arrive(DateTime("2008-1-29 3:30:00"), 
																 DateTime("2008-1-29 4:30:00"));

			RoutePreference rPref(leave, arrive);
			UserPreference  uPref(18, 21, 1, 4.00);

			RouteSubmission testRoute(0xDEAD, 0xBEEF, start, end, 
																uPref, rPref, 42.52);

			ASSERT(testRoute.routeId, 0xDEAD);
			ASSERT(testRoute.userId, 0xBEEF);
			ASSERT(testRoute.startLoc().lat, 123.456789);
			ASSERT(testRoute.endLoc().lng, -123.456789);
			ASSERT_EQ(!testRoute.routePref.leaveWindow.startTime.compare(leave.startTime));
			ASSERT_EQ(!testRoute.routePref.arriveWindow.startTime.compare(arrive.startTime));
			ASSERT(testRoute.optimalDistance, 42.52);
		}

		void run_all()
		{
			cout<<"****************************************"<<endl;
			cout<<"*            Running Route tests."<<endl;
			cout<<"****************************************"<<endl;
			test_create_route_submission();
		}
	}
}

using namespace UnitTests;
int main() 
{
	std::cout<<"Starting unit tests...\n";

	//dba_tests::run_all();

	//Route_tests::run_all();
	//Preference_tests::run_all();
	routes_tests::run_all();
	//optimizer_test::run_all();

	std::cout<<"...Tests Completed.  Number of Assertions: " << numAssertions << std::endl;
	return 0;
}

