#include <iostream>
#include <string>
#include "DBAccess.hpp"
#include "BruteForceOptimizer.hpp"
#include "BipartiteMatchingOptimizer.hpp"
#include "GeneticOptimizer.hpp"
#include "Solution.hpp"

using optimizer::BruteForceOptimizer;
using optimizer::BipartiteMatchingOptimizer;
using optimizer::GeneticOptimizer;
using optimizer::Solution;
using controller::dba::DBAccess;
using namespace std;

bool useLocalMatrix = true;
namespace scorer
{
	const bool CSV_OUTPUT = true;
	const bool CONSOLE_OUTPUT = true;
#define CSV_FILENAME "score_results_test_time_stamp"
	
	ofstream csvFile;
	
	Solution::Riders  testRiders;
	Solution::Drivers testDrivers;
	Solution::Matches testMatches;
	
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
	vector<string> uShip_1_prefs;
	vector<string> uShip_2_prefs;
	vector<string> uShip_3_prefs;
	vector<string> uPrefs_1;
	vector<string> uPrefs_2;
	vector<string> uPrefs_3;
	vector<string> uPrefs_4;
	vector<string> uPrefs_5;
	vector<string> uPrefs_6;
	vector<string> uPrefs_7;
	vector<string> uPrefs_8;
	vector<string> uPrefs_9;
	vector<string> uPrefs_10;
	vector<string> uPrefs_11;
	vector<string> uPrefs_12;
	vector<string> uPrefs_13;
	vector<string> uPrefs_14;
	vector<string> uPrefs_15;
	vector<string> uPrefs_16;
	vector<string> uPrefs_17;
	vector<string> uPrefs_18;
	vector<string> uPrefs_19;
	vector<string> uPrefs_20;

	vector< vector<string> > bf_test_cases;
	vector< vector<string> > g_test_cases;
	vector< vector<string> > bm_test_cases;

	string host = "rideshare.ece.utexas.edu";
	string user = "jonas";
	string pw   = "letmein2";
	string db   = "rideshare";
	DBAccess::ptr dba;
	
	void init_DBAccess()
	{
		dba.reset(new DBAccess(host, db, user, pw));
	}

	void init_test_cases()
	{
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
		uShip_1_prefs.push_back("uShip_1_prefs");
		uShip_2_prefs.push_back("uShip_2_prefs");
		uShip_3_prefs.push_back("uShip_3_prefs");
		uPrefs_1.push_back("uPrefs_1");
		uPrefs_2.push_back("uPrefs_2");
		uPrefs_3.push_back("uPrefs_3");
		uPrefs_4.push_back("uPrefs_4");
		uPrefs_5.push_back("uPrefs_5");
		uPrefs_6.push_back("uPrefs_6");
		uPrefs_7.push_back("uPrefs_7");
		uPrefs_8.push_back("uPrefs_8");
		uPrefs_9.push_back("uPrefs_9");
		uPrefs_10.push_back("uPrefs_10");
		uPrefs_11.push_back("uPrefs_11");
		uPrefs_12.push_back("uPrefs_12");
		uPrefs_13.push_back("uPrefs_13");
		uPrefs_14.push_back("uPrefs_14");
		uPrefs_15.push_back("uPrefs_15");
		uPrefs_16.push_back("uPrefs_16");
		uPrefs_17.push_back("uPrefs_17");
		uPrefs_18.push_back("uPrefs_18");
		uPrefs_19.push_back("uPrefs_19");
		uPrefs_20.push_back("uPrefs_20");
		
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
		//bf_test_cases.push_back(uPrefs_1);
		//bf_test_cases.push_back(uPrefs_2);
		//bf_test_cases.push_back(uPrefs_3);
		//bf_test_cases.push_back(uPrefs_4);
		//bf_test_cases.push_back(uPrefs_5);
		//bf_test_cases.push_back(uPrefs_6);
		//bf_test_cases.push_back(uPrefs_7);
		//bf_test_cases.push_back(uPrefs_8);
		//bf_test_cases.push_back(uPrefs_9);
		//bf_test_cases.push_back(uPrefs_10);
		//bf_test_cases.push_back(uPrefs_11);
		//bf_test_cases.push_back(uPrefs_12);
		//bf_test_cases.push_back(uPrefs_13);
		//bf_test_cases.push_back(uPrefs_14);
		//bf_test_cases.push_back(uPrefs_15);
		//bf_test_cases.push_back(uPrefs_16);
		//bf_test_cases.push_back(uPrefs_17);
		//bf_test_cases.push_back(uPrefs_18);
		//bf_test_cases.push_back(uPrefs_19);
		//bf_test_cases.push_back(uPrefs_20);
     
		//bm_test_cases.push_back(test_1);
		//bm_test_cases.push_back(test_2);
		//bm_test_cases.push_back(test_3);
		//bm_test_cases.push_back(test_4);
		//bm_test_cases.push_back(test_5);
		//bm_test_cases.push_back(test_6);
		//bm_test_cases.push_back(test_7);
		//bm_test_cases.push_back(test_8);
		//bm_test_cases.push_back(test_9);
		//bm_test_cases.push_back(test_10);
		//bm_test_cases.push_back(test_11);
		//bm_test_cases.push_back(uShip_1);
		//bm_test_cases.push_back(uShip_2);
		//bm_test_cases.push_back(uShip_3);
		//bm_test_cases.push_back(uShip_1_prefs);
		//bm_test_cases.push_back(uShip_2_prefs);
		//bm_test_cases.push_back(uShip_3_prefs);
		//bm_test_cases.push_back(raw);
		//bm_test_cases.push_back(uPrefs_1);
		//bm_test_cases.push_back(uPrefs_2);
		//bm_test_cases.push_back(uPrefs_3);
		//bm_test_cases.push_back(uPrefs_4);
		//bm_test_cases.push_back(uPrefs_5);
		//bm_test_cases.push_back(uPrefs_6);
		//bm_test_cases.push_back(uPrefs_7);
		//bm_test_cases.push_back(uPrefs_8);
		//bm_test_cases.push_back(uPrefs_9);
		//bm_test_cases.push_back(uPrefs_10);
		//bm_test_cases.push_back(uPrefs_11);
		//bm_test_cases.push_back(uPrefs_12);
		//bm_test_cases.push_back(uPrefs_13);
		//bm_test_cases.push_back(uPrefs_14);
		//bm_test_cases.push_back(uPrefs_15);
		//bm_test_cases.push_back(uPrefs_16);
		//bm_test_cases.push_back(uPrefs_17);
		//bm_test_cases.push_back(uPrefs_18);
		//bm_test_cases.push_back(uPrefs_19);
		//bm_test_cases.push_back(uPrefs_20);


		//g_test_cases.push_back(test_1);
		//g_test_cases.push_back(test_2);
		//g_test_cases.push_back(test_3);
		//g_test_cases.push_back(test_4);
		//g_test_cases.push_back(test_5);
		//g_test_cases.push_back(test_6);
		//g_test_cases.push_back(test_7);
		//g_test_cases.push_back(test_8);
		//g_test_cases.push_back(test_9);
		//g_test_cases.push_back(test_10);
		//g_test_cases.push_back(test_11);
		//g_test_cases.push_back(uShip_1);
		//g_test_cases.push_back(uShip_2);
		//g_test_cases.push_back(uShip_3);
		//g_test_cases.push_back(uShip_1_prefs);
		//g_test_cases.push_back(uShip_2_prefs);
		//g_test_cases.push_back(uShip_3_prefs);
		//g_test_cases.push_back(raw);
		//g_test_cases.push_back(uPrefs_1);
		//g_test_cases.push_back(uPrefs_2);
		//g_test_cases.push_back(uPrefs_3);
		//g_test_cases.push_back(uPrefs_4);
		//g_test_cases.push_back(uPrefs_5);
		//g_test_cases.push_back(uPrefs_6);
		//g_test_cases.push_back(uPrefs_7);
		//g_test_cases.push_back(uPrefs_8);
		//g_test_cases.push_back(uPrefs_9);
		//g_test_cases.push_back(uPrefs_10);
		//g_test_cases.push_back(uPrefs_11);
		//g_test_cases.push_back(uPrefs_12);
		//g_test_cases.push_back(uPrefs_13);
		//g_test_cases.push_back(uPrefs_14);
		//g_test_cases.push_back(uPrefs_15);
		//g_test_cases.push_back(uPrefs_16);
		//g_test_cases.push_back(uPrefs_17);
		//g_test_cases.push_back(uPrefs_18);
		//g_test_cases.push_back(uPrefs_19);
		//g_test_cases.push_back(uPrefs_20);
	}

	void output_time_stamp()
	{
		if(CSV_OUTPUT) csvFile.open(CSV_FILENAME,fstream::app);
		time_t ltime; /* calendar time */
		ltime = time(NULL); /* get local cal time */
		cout << asctime(localtime(&ltime)) <<endl;
		if(CSV_OUTPUT) csvFile << asctime(localtime(&ltime))<<endl;
		if(CSV_OUTPUT) csvFile.close();
	}

	void score_brute_force_optimizer()
	{
		if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
		if(CONSOLE_OUTPUT) cout<<"* Results for Brute Force Optimizer "<<endl;
		if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
		for(size_t i =0; i < bf_test_cases.size(); i++)
		{
			if(CONSOLE_OUTPUT) csvFile.open(CSV_FILENAME,fstream::app);
			vector<string> test_data_to_include = bf_test_cases[i];
			
			if(CSV_OUTPUT) csvFile << "brute force" << "," << "test_" << i+1 << ",";
			if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
			if(CONSOLE_OUTPUT) cout<< "*    Running test_" << i+1 <<": ";
			for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
			{
				if(CONSOLE_OUTPUT) 				cout << test_data_to_include[jj] << ",";
				if(CSV_OUTPUT && jj !=0) 	csvFile << ";";
				if(CSV_OUTPUT) csvFile << test_data_to_include[jj];
			}
			if(CONSOLE_OUTPUT) cout<<endl;
			if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
			
			/* retrieve test data from the database */
			testDrivers = dba->getDriverSubmissions(test_data_to_include);
			testRiders = dba->getRiderSubmissions(test_data_to_include);
			
			if(CONSOLE_OUTPUT) cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
			if(CONSOLE_OUTPUT) cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
			if(CSV_OUTPUT) csvFile << "," << testDrivers.size() << "," << testRiders.size() 
				<< "," << testDrivers.size()+testRiders.size();
			
			BruteForceOptimizer bfOptimizer(testDrivers, testRiders);
			if(CONSOLE_OUTPUT) cout << "Score before optimization: " << bfOptimizer.getBestScore() << endl;
			if(CSV_OUTPUT) csvFile << "," << bfOptimizer.getBestScore();
			//clock_t start = clock();
			time_t start;
			time(&start);
			bfOptimizer.optimize();
			time_t end;
			time(&end);
			//clock_t end = clock();
			//double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
			double runTime = difftime(end,start);
			if(CONSOLE_OUTPUT) cout<< "Score after optimization: " << bfOptimizer.getBestScore() << endl;
			if(CONSOLE_OUTPUT) cout<< "Runtime in seconds: " << runTime << endl;
			if(CSV_OUTPUT) csvFile << "," << bfOptimizer.getBestScore();
			if(CSV_OUTPUT) csvFile << "," << runTime << endl;
			if(CONSOLE_OUTPUT) csvFile.close();
		}
	}
	void score_genetic_optimizer()
	{
		cout<<"****************************************"<<endl;
		cout<<"* Results for Genetic Optimizer "<<endl;
		cout<<"****************************************"<<endl;
		for(size_t i =0; i < g_test_cases.size(); i++)
		{
			if(CONSOLE_OUTPUT) csvFile.open(CSV_FILENAME,fstream::app);
			vector<string> test_data_to_include = g_test_cases[i];
			if(CSV_OUTPUT) csvFile << "genetic" << "," << "test_" << i+1 << ",";
			
			if(CONSOLE_OUTPUT)	cout<<"****************************************"<<endl;
			if(CONSOLE_OUTPUT)	cout<< "*    Running test_" << i+1 <<": ";
			for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
			{
				if(CONSOLE_OUTPUT) cout << test_data_to_include[jj] << ",";
				if(CSV_OUTPUT && jj !=0) csvFile << ";";
				if(CSV_OUTPUT) csvFile << test_data_to_include[jj];
			}
			if(CONSOLE_OUTPUT) cout<<endl;
			if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
			/* retrieve test data from the database */
			testDrivers = dba->getDriverSubmissions(test_data_to_include);
			testRiders = dba->getRiderSubmissions(test_data_to_include);
			
			if(CONSOLE_OUTPUT) cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
			if(CONSOLE_OUTPUT) cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
			if(CSV_OUTPUT) csvFile << "," << testDrivers.size() << "," << testRiders.size()
				<< "," << testDrivers.size()+testRiders.size();
			
			GeneticOptimizer gOptimizer(testDrivers, testRiders);
			cout << "Score before optimization: " << gOptimizer.getBestScore() << endl;
			if(CSV_OUTPUT) csvFile << "," << gOptimizer.getBestScore();
			//clock_t start = clock();
			time_t start;
			time(&start);
			gOptimizer.optimize();
			time_t end;
			time(&end);
			//clock_t end = clock();
			//double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
			double runTime = difftime(end,start);
			if(CONSOLE_OUTPUT) cout<< "Score after optimization: " << gOptimizer.getBestScore() << endl;
			if(CONSOLE_OUTPUT) cout<< "Runtime in seconds: " << runTime << endl;
			if(CSV_OUTPUT) csvFile << "," << gOptimizer.getBestScore();
			if(CSV_OUTPUT) csvFile << "," << runTime << endl;
			if(CONSOLE_OUTPUT) csvFile.close();
		}
	}

	void score_bipartite_matching_optimizer()
	{
		cout<<"****************************************"<<endl;
		cout<<"* Results for Bipartite Matching Optimizer "<<endl;
		cout<<"****************************************"<<endl;
		for(size_t i =0; i < bm_test_cases.size(); i++)
		{
			if(CONSOLE_OUTPUT) csvFile.open(CSV_FILENAME,fstream::app);
			vector<string> test_data_to_include = bm_test_cases[i];
			if(CSV_OUTPUT) csvFile << "bipartite matching" << "," << "test_" << i+1 << ",";
			
			if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
			if(CONSOLE_OUTPUT) 	cout<< "*    Running test_" << i+1 <<": ";
			for(size_t jj =  0; jj < test_data_to_include.size(); jj++)
			{
				if(CONSOLE_OUTPUT) cout << test_data_to_include[jj] << ",";
				if(CSV_OUTPUT && jj !=0) csvFile << ";";
				if(CSV_OUTPUT) csvFile << test_data_to_include[jj];
			}
			if(CONSOLE_OUTPUT) cout<<endl;
			if(CONSOLE_OUTPUT) cout<<"****************************************"<<endl;
			/* retrieve test data from the database */
			testDrivers = dba->getDriverSubmissions(test_data_to_include);
			testRiders = dba->getRiderSubmissions(test_data_to_include);
			
			if(CONSOLE_OUTPUT) cout<< "testDrivers.size() = "<<testDrivers.size()<<endl; 
			if(CONSOLE_OUTPUT) cout<< "testRiders.size() = "<<testRiders.size()<<endl; 
			if(CSV_OUTPUT) csvFile << "," << testDrivers.size() << "," << testRiders.size()
				<< "," << testDrivers.size()+testRiders.size();

			BipartiteMatchingOptimizer bmOptimizer(testDrivers, testRiders);
			
			if(CONSOLE_OUTPUT) cout << "Score before optimization: " << bmOptimizer.getBestScore() << endl;
			if(CSV_OUTPUT) csvFile << "," << bmOptimizer.getBestScore();
			//clock_t start = clock();
			time_t start;
			time(&start);
			bmOptimizer.optimize();
			time_t end;
			time(&end);
			//clock_t end = clock();
			//double runTime = (end - start)/((CLOCKS_PER_SEC)/1000);
			double runTime = difftime(end,start);
			if(CONSOLE_OUTPUT) cout<< "Score after optimization: " << bmOptimizer.getBestScore() << endl;
			if(CONSOLE_OUTPUT) cout<< "Runtime in seconds: " << runTime << endl;
			if(CSV_OUTPUT) csvFile << "," << bmOptimizer.getBestScore();
			if(CSV_OUTPUT) csvFile << "," << runTime << endl;
			if(CONSOLE_OUTPUT) csvFile.close();
		}
	}

	void score_all_optimizers()
	{
		if(CSV_OUTPUT) csvFile.open(CSV_FILENAME);
		if(CSV_OUTPUT) csvFile << "optimizer,test number,test cases,num drivers,num riders,total requests,initial score,final score,time in seconds"<<endl;
		score_genetic_optimizer();
		score_bipartite_matching_optimizer();
		score_brute_force_optimizer();
		if(CSV_OUTPUT) csvFile.close();
	}
}//end namespace scorer


using namespace scorer;


int main()
{
	if(CONSOLE_OUTPUT) cout<<"Generating scores for optimizers."<<endl;
	if(CSV_OUTPUT) csvFile.open(CSV_FILENAME);
	output_time_stamp();
	init_DBAccess();
	init_test_cases();
	score_all_optimizers();
	
	if(CSV_OUTPUT) csvFile.close();
	return 0;
}


