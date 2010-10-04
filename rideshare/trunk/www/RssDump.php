<?php
require_once 'opendb.inc';

class RssGenerator
{
	public $userId;
	public $xId;
	public $userName;
	public $ii;

	function RssGenerator($userId, $xId)
	{
		$this->xId        = $xId;
		$this->userId     = $userId;
		$this->userName   = $this->getUserName($this->userId);
		$this->ii = 0;
	}

	function getUsersMatches()
	{
		$query = 'SELECT DISTINCT route_submissions.driver_or_rider, '
		//$query = 'SELECT DISTINCT '
			.' matches.earliest, matches.latest, matches.match_id,matches.solution_id, '
			.' solutions.optimizer, solutions.calculated FROM matches, '
			.' solutions, route_submissions WHERE '
			. 'matches.route_submission_id = route_submissions.route_submission_id AND '
			.' route_submissions.user_id = '.$this->userId
			.' ORDER BY solutions.calculated DESC LIMIT 0,15';

		/*
		$query = 'SELECT * from solutions where solution_id IN '
			. '(SELECT solution_id FROM matches WHERE '
			. 'route_submission_id='.$this->userId. ')'
			. ' ORDER BY calculated DESC';
		 */

		$submission_result = mysql_query($query);

		return $submission_result;
	}

	function getUserName($userId)
	{
		$userName = "";
		$query = 'SELECT first_name,last_name FROM users WHERE user_id='.$userId;

		$submission_result = mysql_query($query);
		if($submission_result and mysql_num_rows($submission_result) > 0) 
		{
			$row = mysql_fetch_assoc($submission_result);
			$firstName = $row['first_name'];
			$lastName  = $row['last_name'];
			$userName = $firstName . " " . $lastName;
		}
		else
		{
			echo "There was no user with user_id: " . $userId;
		}
		return $userName;
	}


	function dumpAllMatches()
	{
		$results = $this->getUsersMatches();

		if($results and mysql_num_rows($results) > 0 )
		{
			//$row = mysql_fetch_assoc($results);
			while($row = mysql_fetch_assoc($results))
			{
				$this->dumpMatch($row);
			}
		}
	}

/*
	<item>
	<title>Title of an item</title>
	<link>http://example.com/item/123</link>
	<guid>http://example.com/item/123</guid>
	<pubDate>Mon, 12 Sep 2005 18:37:00 GMT</pubDate>
	<description>[CDATA[ This is the description. ]]</description>
	</item>

 */
	function getDriverFromMatch($match)
	{
		$matchId = $match['match_id'];
		$solutionId = $match['solution_id'];

		$query = "SELECT users.first_name, users.last_name "
			. " FROM users, route_submissions"
			. " WHERE route_submissions.user_id = users.user_id AND"
			. " route_submissions.route_submission_id"
			. " = ("
			. " SELECT route_submission_id"
			. " FROM matches"
			. " WHERE match_id=".$matchId
			. " AND solution_id=".$solutionId
			. " and sequence_num=0"
			. ")";

		$driversName = "";

		$submission_result = mysql_query($query);
		if($submission_result and mysql_num_rows($submission_result) > 0) 
		{
			$row = mysql_fetch_assoc($submission_result);
			$firstName = $row['first_name'];
			$lastName  = $row['last_name'];
			$driversName = $firstName . " " . $lastName;
		}
		else
		{
			echo "There was no driver in solution_id: " . $solutionId . " and match_id: " . $matchId;
		}
		return $driversName;
	}

	function getLeaveWindowString($match)
	{
		$dtEarliest   = $match['earliest'];
		$dtLatest     = $match['latest'];
		$dayOfTheWeek = date("l", strtotime($dtEarliest));
		$month        = date("F", strtotime($dtEarliest));
		$day          = date("j", strtotime($dtEarliest));
		$timeEarly    = date("g:i a", strtotime($dtEarliest));
		$timeLate     = date("g:i a", strtotime($dtEarliest));

		$returnDate = $dayOfTheWeek .  ', ' . $month
			. ' ' . $day . ' between ' . $timeEarly
			. ' and ' . $timeLate;
		//$returnDate = $match['earliest'] . '.';
		return $returnDate;
	}

	function dumpMatch($match)
	{
		$driverName = $this->getDriverFromMatch($match);
		$pubDate = $this->getRssDate($match['calculated']);
		$time = $this->getLeaveWindowString($match);
		$description = "You have been matched as a " . $match['driver_or_rider'] 
			. " in a Rideshare that is schedule to start on " . $time . " \n\n"
			. 'To view this Rideshare visit http://rideshare.ece.utexas.edu'
			. "\n";
		echo "<item>\n";
		$dtEarliest     = $match['earliest'];
		$dayOfTheWeek = date("l", strtotime($dtEarliest));
		$month        = date("F", strtotime($dtEarliest));
		$day          = date("j", strtotime($dtEarliest));
		echo "<title>New Rideshare on " . $dayOfTheWeek. ', ' . $month .' ' . $day. "</title>\n";
		echo "<pubDate>".$pubDate."</pubDate>\n";
		echo "<link>"."http://rideshare.ece.utexas.edu/member.php?s=".$match['solution_id']
			. "&amp;m=" . $match['match_id'] . $this->ii++ . "</link>\n";
		echo '<guid isPermaLink="false">'."http://rideshare.ece.utexas.edu/member.php?s=".$match['solution_id']
			. "&amp;m=" . $match['match_id'] . $this->ii++ . "</guid>\n";
		echo "<description>".$description."</description>\n";
		echo "</item>";
	}


	function dumpHeader()
	{
		echo '<?xml version="1.0"?>'."\n";
		echo '<rss version="2.0" xmlns:atom="http://www.w3.org/2005/Atom">' . "\n";
		$submission_result  = $this->getUsersMatches();

		if($submission_result and mysql_num_rows($submission_result) > 0 )
		{
			$row          = mysql_fetch_assoc($submission_result);
			$numMatches   = mysql_num_rows($submission_result);
			$freshestDate = $row['calculated'];
		}
		else
		{
			$freshestDate = "No Matches";
		}

		echo "<channel>\n";
		echo '<atom:link href="http://rideshare.ece.utexas.edu/rss.php?u=' . $this->userId . 
			'&amp;x=' . $this->xId . '" rel="self" type="application/rss+xml" />';
		echo "<title>" . $this->userName. " Rideshare Notifications</title>\n";
		echo "<link>http://rideshare.ece.utexas.edu</link>\n";
		echo "<description> &lt;p&gt;You have been matched with ". $numMatches. 
			" rideshare(s)&lt;/p&gt;</description>\n";
		echo "<lastBuildDate>".$this->getRssDate($freshestDate)."</lastBuildDate>\n";
	}

	function getRssDate($dateTime)
	{
		$returnStr = date("D, d M Y H:i:s T", strtotime($dateTime));
		return $returnStr;

	}

	function dumpEpilogue()
	{
		echo "\n" . '</channel>' . "\n";
		echo '</rss>' . "\n";
	}

}

?>
