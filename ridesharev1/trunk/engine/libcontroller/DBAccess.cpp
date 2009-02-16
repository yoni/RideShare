#include <mysql++/mysql++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <exception>

#include "DBAccess.hpp"
#include "Utils.hpp"
#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "PointInfo.hpp"
#include "Match.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace controller
{
namespace dba
{
	using std::string;
	using std::cout;
	using std::set;
	using std::vector;
	using std::stringstream;

	using optimizer::Match;
	using mysqlpp::Query;
	using mysqlpp::Result;
	using mysqlpp::Row;

	string DBAccess::getRouteSubmissionIdsInSolution(const Solution &solution) const
	{
		set<uint32_t> uniqueRouteSubmissionIds;
		for(MatchesMap::const_iterator cur_match = solution.myMatches.begin(); 
				cur_match != solution.myMatches.end();
				cur_match++)
		{
			for(uint32_t pp=0; pp < cur_match->second.myRoute.numPoints(); pp++)
			{
				//cout << "  Wrote solId = " << solutionId << endl;
				const PointInfo<double> &point = cur_match->second.myRoute.at(pp);
				uniqueRouteSubmissionIds.insert(point.routeId);
			}
		}

		stringstream ss;
		//TODO make this a string stream
		ss<<"(";
		vector<uint32_t> rIds(uniqueRouteSubmissionIds.begin(), uniqueRouteSubmissionIds.end());
		for(vector<uint32_t>::iterator iter = rIds.begin();
				iter != rIds.end();
				iter++)
		{
			if (iter != rIds.begin())
				ss << ",";

			ss<<" "<<*iter;
		}
		ss<<")";

		return ss.str();
	}

	vector<string> DBAccess::getUserEmails(const Solution &solu) const
	{
		vector<string> returnVector;
		try
		{
			string rSubmissionSQL = getRouteSubmissionIdsInSolution(solu);
			Query query = getQuery();
			query << "SELECT DISTINCT users.email_addr FROM users,route_submissions WHERE "
				<< " route_submissions.route_submission_id IN "
				<< rSubmissionSQL;

			Result res = query.store();
			for (uint32_t ii = 0; ii < res.num_rows(); ii++)
			{
				Row  userRow = res.at(ii);
				returnVector.push_back(userRow["email_addr"].get_string());
			}

			if (!query.success())
			{
				std::cerr << "Could not get user emails in solution" << std::endl;
				std::cerr << query.error() << std::endl;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return returnVector;
	}

	ReturnCode DBAccess::deleteSolution(uint32_t solutionId )
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();

			query << "DELETE FROM matches WHERE solution_id=" << solutionId;
			res = query.store();
			if (!query.success())
			{
				std::cerr << "Delete Solution in matches table Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

			query << "DELETE FROM solutions WHERE solution_id=" << solutionId;
			res = query.store();
			if (!query.success())
			{
				std::cerr << "Delete Solution in solutions table Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	ReturnCode DBAccess::deleteRouteSubmission(uint32_t routeId )
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "DELETE FROM route_submissions WHERE route_submission_id=" << routeId;
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Delete Route Submission Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		try
		{
			Query query = getQuery();
			query << "DELETE FROM route_driver_options WHERE route_submission_id=" << routeId;
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Delete driver options Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

		} catch (const mysqlpp::Exception& er) 
		
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}

		return retCode;
	}

	ReturnCode DBAccess::deleteUserPreference(uint32_t userId )
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "DELETE FROM user_prefs WHERE user_id=" << userId;
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Delete Route Preference Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	ReturnCode DBAccess::deleteRoutePreference(uint32_t routeId )
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "DELETE FROM route_prefs WHERE route_submission_id=" << routeId;
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Delete Route Preference Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	/**
	 * writeSolution()
	 *   @desc: writes Solution object to matches table if
	 *   there is not already an entry with matching solution_id
	 *   @returns:
	 *   	SUCCESS if the add was successful
	 *   	FAILURE if the add was not successful; if the userId
	 *   	is already in the database
	 **/
	ReturnCode DBAccess::writeSolution(const SolutionPtr solution, uint32_t &solutionId)
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			// first, make entry in solution table
			Query query = getQuery();
			query << "INSERT INTO solutions (optimizer, calculated) VALUES ('"
				<< solution->getOptimizeType()<<"', NOW()"
				<< ")";
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write Solution Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}

			// take new solution_id and write a row into matches table
			solutionId = query.insert_id();
			//cout << "SolutionId = " << solutionId << endl;
			uint32_t mm=0;
			for(MatchesMap::iterator cur_match = solution->myMatches.begin(); 
					cur_match != solution->myMatches.end();
					mm++, cur_match++)
			{
				for(uint32_t pp=0; pp < cur_match->second.myRoute.numPoints(); pp++)
				{
					//cout << "  Wrote solId = " << solutionId << endl;
					const PointInfo<double> &point = cur_match->second.myRoute.at(pp);
					const TimeWindow<ptime> times = cur_match->second.myRoute.timeWindows[pp];
					const TimeWindow<DateTime> dTimes = (convertToDateTime(times));
					writeMatchRow(pp, solutionId, mm, point, dTimes);
					updateRouteSubmission(point, solutionId, mm);
				}
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		return retCode;
	}

	ReturnCode DBAccess::updateRouteSubmission(const PointInfo<> &point, 
			uint32_t solutionId, uint32_t matchId)
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "UPDATE route_submissions SET match_id = " << matchId 
				<< ", solution_id = " << solutionId 
				<< " WHERE route_submission_id=" << point.routeId;
			res = query.store();

			if (!query.success())
			{
				std::cerr << "update Route Submission Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		return retCode;
	}


	ReturnCode DBAccess::writeSolution(const SolutionPtr solution)
	{
		uint32_t returned_solution_id;
		return writeSolution(solution, returned_solution_id);
	}

	ReturnCode DBAccess::writeSolution(const Solution& solution)
	{
		SolutionPtr solptr(new Solution(solution));
		return writeSolution(solptr);
	}

	ReturnCode DBAccess::writeMatchRow(uint32_t seqId, uint32_t solutionId,
			uint32_t matchId, const PointInfo<> &point, const TimeWindow<DateTime> times)
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			//cout << "writing match row with SolId = " << solutionId << endl;
			Query query = getQuery();
			query << "INSERT INTO matches (sequence_num, solution_id, "
				<<"match_id, route_submission_id, earliest, latest) VALUES ("
				<< seqId <<", "<< solutionId <<", " << matchId << ", " << point.routeId << ", '" 
				<< times.startTime <<"', '"<< times.endTime << "')";
			//std::cout << query.str() << std::endl; 
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write PointInfo Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	/**
	 * writeRouteUserPreference()
	 *   @desc: writes UserPreference object to route_prefs table if
	 *   there is not already an entry with matching routeId
	 *   @returns:
	 *   	true if the add was successful
	 *   	false if the add was not successful; if the userId
	 *   	is already in the database
	 **/
	ReturnCode DBAccess::writeRouteUserPreference(const UserPreference &uPref)
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "INSERT INTO route_prefs (age_min, age_max, "
				<< "gender_id, rating_min, route_submission_id) VALUES ("
				<< uPref.ageMin<<", " <<uPref.ageMax<< ", " 
				<< uPref.genderId<<", '"<<uPref.ratingMin<< "', '"<<uPref.routeId<<"'"
				<< ")";
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write RouteUserPreference Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	/**
	 * writeUserPreference()
	 *   @desc: writes UserPreference object to database if 
	 *   there is not already an entry with matching userId
	 *   @returns:
	 *   	true if the add was successful
	 *   	false if the add was not successful; if the userId
	 *   	is already in the database
	 **/
	ReturnCode DBAccess::writeUserPreference(const UserPreference &uPref)
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "INSERT INTO user_prefs (user_id, age_min, age_max, gender_id, rating_min) VALUES ("
				<< uPref.userId<<", "<<uPref.ageMin<<", " <<uPref.ageMax<< ", " 
				<< uPref.genderId<<", '"<<uPref.ratingMin<< "'"
				<< ")";
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write Route Submission Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;

	}

	/* for test cases, with start and end strings */
	ReturnCode DBAccess::writeDriverRouteSubmission(RouteSubmission::ptr rs, 
			string start, string end, double routeLength, double routeTime)
	{
		return writeRouteSubmission(rs, start, end, routeLength, routeTime);
	}

	/* for test cases, with start and end strings */
	ReturnCode DBAccess::writeRouteSubmission(RouteSubmission::ptr rs, 
			string start, string end)
	{
		return writeRouteSubmission(rs, start, end, 0, 0);
	}

	ReturnCode DBAccess::writeDriverRouteSubmission(DriverRouteSubmission::ptr rs)
	{
		return writeRouteSubmission(rs, rs->optimalDistance, rs->capacity);
	}

	ReturnCode DBAccess::writeRouteSubmission(RouteSubmission::ptr rs)
	{
		return writeRouteSubmission(rs, 0, 0);
	}

	/**
	 * writeRouteSubmission()
	 *   @desc: writes RouteSubmission object to database if 
	 *   there is not already an entry with matching routeId
	 *   @returns:
	 *   	true if the add was successful
	 *   	false if the add was not successful; if the routeId
	 *   	is already in the database
	 **/
	ReturnCode DBAccess::writeRouteSubmission(RouteSubmission::ptr rs, double optimalRouteLength, size_t capacity) 
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		// first write capacity, if a driver.
		if (capacity){
			try
			{
				Query query = getQuery();
				query << "INSERT INTO route_driver_options (route_submission_id, capacity) VALUES ("
							<< rs->routeId << ", " << capacity << ")"; 
				res = query.store();
				
				if (!query.success())
				{
					std::cerr << "Write Route Submission Failed (capacity not written)" << std::endl;
					std::cerr << query.error() << std::endl;
					retCode = FAIL;
					return retCode;
				}
			}catch (const mysqlpp::Exception& er)
			{
				// Catch-all for any other MySQL++ exceptions
				retCode = FAIL;
				std::cerr << "Error: " << er.what() << std::endl;
				return retCode;
			}
		}
		// now write the actual route submission
		try
		{
			Query query = getQuery();
			query << "INSERT INTO route_submissions (route_submission_id, user_id, start_location_lat, "
				<< "start_location_lon, end_location_lat, end_location_lon, leave_time_earliest, "
				<< "leave_time_latest, arrive_time_earliest, arrive_time_latest, optimal_route_length, "
				<< "driver_or_rider, comment, start_addr, end_addr"
				<< ") VALUES ("
				<< rs->routeId<<", "<<rs->userId<<", "<<rs->startLoc().lat<<", "<<rs->startLoc().lng<<", "<<rs->endLoc().lat
				<< ", "<<rs->endLoc().lng<<", '"<<rs->routePref.leaveWindow.startTime<<"', '"<<rs->routePref.leaveWindow.endTime
				<< "', '"<<rs->routePref.arriveWindow.startTime<<"', '"<< rs->routePref.arriveWindow.endTime
				<< "', "<<optimalRouteLength<<", '"<<rs->get_type() << "', '" << rs->comment 
				<< "', '"<<rs->startLoc().addr.street<<"', '"<<rs->endLoc().addr.street<< "'"
				<< ")";
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write Route Submission Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	/* for test cases: uses string for starting and ending address */
	ReturnCode DBAccess::writeRouteSubmission(RouteSubmission::ptr rs, string start, string end, 
		double optimalRouteLength, double optimalRouteTime) 
	{
		ReturnCode retCode = SUCCESS;
		Result res;
		try
		{
			Query query = getQuery();
			query << "INSERT INTO route_submissions (route_submission_id, user_id, start_location_lat, "
				<< "start_location_lon, end_location_lat, end_location_lon, leave_time_earliest, "
				<< "leave_time_latest, arrive_time_earliest, arrive_time_latest, optimal_route_length, "
				<< "driver_or_rider, comment, start_addr, end_addr, optimal_route_time"
				<< ") VALUES ("
				<< rs->routeId <<", "<< rs->userId <<", "<< rs->startLoc().lat <<", "<< rs->startLoc().lng <<", "<< rs->endLoc().lat
				<< ", "<< rs->endLoc().lng <<", '"<< rs->routePref.leaveWindow.startTime <<"', '"<<rs->routePref.leaveWindow.endTime
				<< "', '"<< rs->routePref.arriveWindow.startTime <<"', '"<< rs->routePref.arriveWindow.endTime
				<< "', "<< optimalRouteLength <<", '"<< rs->get_type() << "', '" << rs->comment 
				<< "', '" << start << "', '" << end << "', " << optimalRouteTime
				<< ")";
			res = query.store();

			if (!query.success())
			{
				std::cerr << "Write Route Submission Failed" << std::endl;
				std::cerr << query.error() << std::endl;
				retCode = FAIL;
			}
		} catch (const mysqlpp::Exception& er) 
		{
			// Catch-all for any other MySQL++ exceptions
			retCode = FAIL;
			std::cerr << "Error: " << er.what() << std::endl;
		}
		
		return retCode;
	}

	UserPreference DBAccess::getRoutePreference(uint32_t routeId) const
	{
		uint32_t _userId = 0;
		size_t ageMin = 0, ageMax = 0, genderId = 0;
		double  ratingMin = 0.0;

		Query query = myConnection->query();
		query << "SELECT age_min,age_max,gender_id,rating_min "
					<< " FROM route_prefs WHERE route_submission_id=" << routeId;
		Result res = query.store();
		if (res.num_rows() > 0)
		{
			Row    userRow = res.at(0);

			if(userRow["age_min"].is_null())
				ageMin = 0;
			else
				ageMin    = userRow["age_min"];

			if(userRow["age_max"].is_null())
				ageMax = 255;
			else
				ageMax    = userRow["age_max"];

			if(userRow["gender_id"].is_null())
				genderId = 0;
			else
				genderId  = userRow["gender_id"];

			if(userRow["rating_min"].is_null())
				ratingMin = 0.0;
			else
				ratingMin = userRow["rating_min"];
		}
		else
		{
			ageMin = 0;
			ageMax = 255;
			genderId = 0;
			ratingMin = 0.0;
		}

		UserPreference uPref(routeId, _userId, ageMin, ageMax, genderId, ratingMin);
		return uPref;
	}

	/**
	 * getRouteSubmission()
	 *  @param: 
	 *   routeId: Query Route with this routeId
	 *  @desc: returns a Route::ptr with Route indexed by routeId
	 **/
	RouteSubmission::ptr DBAccess::getRouteSubmission(uint32_t routeId) const
	{
		Query query = myConnection->query();
		query << "SELECT * from route_submissions where route_submission_id = " << routeId;
		Result res = query.store();
		RouteSubmission::ptr retRoute;

		if (res.num_rows() > 0)
		{
			retRoute = getRouteSubmissionFromRowFetch( res.at(0) );
		}
		else
		{
			std::cerr << "No route with route_submission_id "<< routeId << std::endl;
		}

		return retRoute;
	}

	/**
	 * getRiderSubmissions()
	 *  @desc: returns a vector<Rider> with all Routes
	 **/
	DBAccess::Riders DBAccess::getRiderSubmissions() const
	{
		Riders retVector;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_submissions where match_id=0 AND solution_id = 0";
			Result res = query.store();
			RouteSubmission::ptr route;

			if (res.num_rows() > 0)
			{
				for(uint32_t ii = 0; ii < res.num_rows(); ii++)
				{
					if (!strcmp(res.at(ii)["driver_or_rider"], "rider"))
					{
						route = getRouteSubmissionFromRowFetch( res.at(ii) );
						retVector.push_back(*(dynamic_cast<Rider *> (route.get())));
					}
				}
			}
			else
			{
				std::cerr << "No route_submissions" << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retVector;
	}
	/**
	 * getDriverSubmission(RouteID)
	 *  @desc: returns a vector<Driver> with all drivers
	 **/
	DBAccess::Driver DBAccess::getDriverRouteSubmission(uint32_t routeId) const
	{
		Driver retDriver;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_driver_options, route_submissions WHERE "
				<< "route_driver_options.route_submission_id = route_submissions.route_submission_id "
				<< "AND route_submissions.route_submission_id = " << routeId;
			Result res = query.store();
			RouteSubmission::ptr route;
			if (res.num_rows() > 0)
			{
				if (!strcmp(res.at(0)["driver_or_rider"], "driver"))
				{
					route = getRouteSubmissionFromRowFetch( res.at(0) );
					retDriver = (*(dynamic_cast<Driver *> (route.get())));
					retDriver.capacity = (res.at(0)["capacity"]);
				}
			}
			else
			{
				std::cerr << "No route_submission with routeId " << routeId << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retDriver;
	}

	/**
	 * getDriverSubmissions()
	 *  @desc: returns a vector<Driver> with all drivers
	 **/
	DBAccess::Drivers DBAccess::getDriverSubmissions() const
	{
		Drivers retVector;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_driver_options, route_submissions WHERE "
				<< "route_driver_options.route_submission_id = route_submissions.route_submission_id "
				<< "AND match_id = 0 AND solution_id = 0";
			Result res = query.store();
			RouteSubmission::ptr route;

			if (res.num_rows() > 0)
			{
				for(uint32_t ii = 0; ii < res.num_rows(); ii++)
				{
					if (!strcmp(res.at(ii)["driver_or_rider"], "driver"))
					{
						route = getRouteSubmissionFromRowFetch( res.at(ii) );
						retVector.push_back(*(dynamic_cast<Driver *> (route.get())));
						retVector[ii].capacity = (res.at(ii)["capacity"]);
					}
				}
			}
			else
			{
				std::cerr << "No route_submissions" << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retVector;
	}

	/**
	 * getDriverSubmissions(string comment)
	 *  @desc: returns a vector<Rider> with all Routes with string comment
	 **/
	DBAccess::Drivers DBAccess::getDriverSubmissions(string comment) const
	{
		Drivers retVector;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_driver_options, route_submissions WHERE "
				<< "route_driver_options.route_submission_id = route_submissions.route_submission_id "
				<< "AND route_submissions.comment LIKE '" << comment << "' "
				<< "AND route_submissions.match_id = 0 AND route_submissions.solution_id = 0";
			Result res = query.store();
			RouteSubmission::ptr route;

			if (res.num_rows() > 0)
			{
				for(uint32_t ii = 0; ii < res.num_rows(); ii++)
				{
					if (!strcmp(res.at(ii)["driver_or_rider"], "driver"))
					{
						route = getRouteSubmissionFromRowFetch( res.at(ii) );
						retVector.push_back(*(dynamic_cast<Driver *> (route.get())));
						retVector[ii].capacity = (res.at(ii)["capacity"]);
					}
				}
			}
			else
			{
				std::cerr << "No route_submissions" << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retVector;
	}
	
	DBAccess::Drivers DBAccess::getDriverSubmissionsNoCapacity(string comment) const
	{
		Drivers retVector;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_submissions WHERE comment LIKE '" << comment << "'";
			Result res = query.store();
			RouteSubmission::ptr route;

			if (res.num_rows() > 0)
			{
				cout << "Got " << res.num_rows() << " drivers.\n";
				for(uint32_t ii = 0; ii < res.num_rows(); ii++)
				{
					if (!strcmp(res.at(ii)["driver_or_rider"], "driver"))
					{
						route = getRouteSubmissionFromRowFetch( res.at(ii) );
						retVector.push_back(*(dynamic_cast<Driver *> (route.get())));
						retVector[ii].capacity = (rand()%4);
					}
				}
			}
			else
			{
				std::cerr << "No route_submissions" << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retVector;
	}


	/**
	 * getRiderSubmissions(string comment)
	 *  @desc: returns a vector<Rider> with all Routes with string comment
	 **/
	DBAccess::Riders DBAccess::getRiderSubmissions(string comment) const
	{
		Riders retVector;
		try
		{
			Query query = myConnection->query();
			query << "SELECT * FROM route_submissions WHERE "
				<< "match_id=0 AND solution_id=0 AND comment LIKE '" << comment  << "'" ;
			Result res = query.store();
			RouteSubmission::ptr route;

			if (res.num_rows() > 0)
			{
				for(uint32_t ii = 0; ii < res.num_rows(); ii++)
				{
					if (!strcmp(res.at(ii)["driver_or_rider"], "rider"))
					{
						route = getRouteSubmissionFromRowFetch( res.at(ii) );
						retVector.push_back(*(dynamic_cast<Rider *> (route.get())));
					}
				}
			}
			else
			{
				std::cerr << "No rider route_submissions" << std::endl;
			}
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}
		return retVector;
	}


	DBAccess::Riders DBAccess::getRiderSubmissions(vector<string> comments) const
	{
		Riders retVector;
		for (size_t ii = 0; ii < comments.size(); ii++){
			Riders tempVector = DBAccess::getRiderSubmissions(comments[ii]);
			for (uint32_t jj = 0; jj < tempVector.size(); jj++){
				retVector.push_back(tempVector[jj]);
			}
		}
		return retVector;
	}

	DBAccess::Drivers DBAccess::getDriverSubmissions(vector<string> comments) const
	{
		Drivers retVector;
		for (size_t ii = 0; ii < comments.size(); ii++){
			Drivers tempVector = DBAccess::getDriverSubmissions(comments[ii]);
			for (uint32_t jj = 0; jj < tempVector.size(); jj++){
				retVector.push_back(tempVector[jj]);
			}
		}
		return retVector;
	}

	UserPreference DBAccess::getUserPreference(uint32_t userId) const
	{
		size_t ageMin = 0, ageMax = 0, genderId = 0;
		double  ratingMin = 0.0;

		Query query = myConnection->query();
		query << "SELECT age_min,age_max,gender_id,rating_min FROM user_prefs WHERE user_id=" << userId;
		Result res = query.store();
		if (res.num_rows() > 0)
		{
			Row    userRow = res.at(0);

			if(userRow["age_min"].is_null())
				ageMin = 0;
			else
				ageMin    = userRow["age_min"];

			if(userRow["age_max"].is_null())
				ageMax = 255;
			else
				ageMax    = userRow["age_max"];

			if(userRow["gender_id"].is_null())
				genderId = 0;
			else
				genderId  = userRow["gender_id"];

			if(userRow["rating_min"].is_null())
				ratingMin = 0.0;
			else
				ratingMin = userRow["rating_min"];
		}
		else
		{
			ageMin = 0;
			ageMax = 255;
			genderId = 0;
			ratingMin = 0.0;
		}

		UserPreference uPref(userId, ageMin, ageMax, genderId, ratingMin);
		return uPref;
	}
	/**
	 * getUserInfo()
	 *  @desc: takes in a user's ID and returns a UserInfo
	 *  @param userId user's ID
	 *  @return UserInfo
	 **/
	UserInfo DBAccess::getUserInfo(uint32_t userId) const
	{
		string firstName, lastName, emailAddr;
		size_t genderId, age;

		Query query = myConnection->query();
		query << "SELECT first_name,last_name,email_addr,gender_id,age "
					<< " FROM users WHERE user_id=" << userId;

		Result res = query.store();
		if (res.num_rows() > 0)
		{
			Row userRow = res.at(0);
			firstName  = userRow["first_name"].get_string();
			lastName   = userRow["last_name"].get_string();
			emailAddr = userRow["email_addr"].get_string();
			if(userRow["gender_id"].is_null())
				genderId = 0;
			else
				genderId  = userRow["gender_id"];

			if(userRow["age"].is_null())
				age = 0;
			else
				age        = userRow["age"];
		}
		else
		{
			std::cerr<<"No user info for userid: "
				<< userId << std::endl;
		}

		UserInfo uInfo(firstName, lastName, emailAddr, genderId, age);
		return uInfo;
	}

	/**
	 * getRouteSubmissionFromRowFetch()
	 *  @desc: helper function that takes a result from a query
	 *         and translates that result into a RouteSubmission object
	 **/
	RouteSubmission::ptr DBAccess::getRouteSubmissionFromRowFetch(const Row& row) const
	{
		uint32_t userId;
		RouteSubmission::ptr retRoute;
		try
		{
			userId = row["user_id"];
			UserPreference  uPrefs = getUserPreference(userId);
			UserInfo        uInfo  = getUserInfo(userId);

			retRoute = createRouteSubmission(row,uPrefs, uInfo);
		} catch (const mysqlpp::BadFieldName& er) 
		{
			std::cerr << "There was an invalid field name for user " 
				<< userId << std::endl;
		} catch (const mysqlpp::Exception& er) 
		{
			std::cerr << "MySQL++ Error: " << er.what() << std::endl;
		} catch (const std::exception& er) 
		{
			std::cerr << "General Error: " << er.what() << std::endl;
		}

		return retRoute;
	}

} //end dba namespace
} //end controller ns
