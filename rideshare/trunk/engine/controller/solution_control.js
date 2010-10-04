var timer;
var solutionId = 0

function getNumberRiders(solution_id)
{
	var total = 0;
	// for each solution
	for(mm = 0; mm < solutions[solution_id]['matches'].length; mm ++)
	{
		total += solutions[solution_id]['matches'][mm]['riders'].length;
	}
	return total;
}

function setImage(image)
{
	eval("document['map_image'].src = '" + image + "'" );
	//document['map_image'].src = "'" + image + "'";
}

function getMatches(solution_id)
{
	// for each match get riders
	returnStr = "" ;
	for(mm = 0; mm < solutions[solution_id]['matches'].length; mm ++)
	{
		returnStr += "<br> Match " + (mm+1) + " with Driver: <b>" + solutions[solution_id]['matches'][mm]['driver_id'] + "</b>";
		for(rr = 0; rr < solutions[solution_id]['matches'][mm]['riders'].length; rr ++)
		{
			returnStr += "<br>     Rider #" + (rr + 1 ) + "<b>" + solutions[solution_id]['matches'][mm]['riders'][rr] + "</b>";
		}
	}
	return returnStr;
	//return "hello<br /> world <br/> testing<br />";

}

function getDriverNames(solution_id)
{
	// for each match get riders
	returnStr = "" ;
	for(mm = 0; mm < solutions[solution_id]['matches'].length; mm ++)
	{
		returnStr += "<br> " + solutions[solution_id]['matches'][mm]['driver_id'];
	}
	return returnStr;
	//return "hello<br /> world <br/> testing<br />";

}

function getRiderNames(solution_id)
{
	// for each match get riders
	returnStr = "" ;
	for(mm = 0; mm < solutions[solution_id]['matches'].length; mm ++)
	{
		for(rr = 0; rr < solutions[solution_id]['matches'][mm]['riders'].length; rr ++)
		{
			returnStr += "<br> " + solutions[solution_id]['matches'][mm]['riders'][rr];
		}
	}
	return returnStr;
	//return "hello<br /> world <br/> testing<br />";

}

function setSolutionInfo()
{
	document.getElementById("txt").value = "Solution: " + solutionId;
	document.getElementById("num_matches").value = "# Matches: " + solutions[solutionId]['matches'].length;
	document.getElementById("num_riders").value = "# Riders: " + getNumberRiders(solutionId);
	//document.getElementById("riders").value = "";
	//document.getElementById("riders").innerHTML = getRiderNames(solutionId);
	//document.getElementById("drivers").innerHTML = getDriverNames(solutionId);
	document.getElementById("matches").innerHTML = getMatches(solutionId);
	document.getElementById("score").value = "Score: " + solutions[solutionId]['score'];
}

function updateDisplay()
{
	setImage(solutions[solutionId]['map'].src);
	setSolutionInfo();

}

function prevSolution()
{
	solutionId = --solutionId % solutions.length;
	updateDisplay();
}

function nextSolution()
{
	solutionId = ++solutionId % solutions.length;
	updateDisplay();
}

function startVisualization()
{
	nextSolution();
	timer = setTimeout("startVisualization()", 800);
}

function stopVisualization()
{
	clearTimeout(timer);
}

function load()
{
	sortSolutions();
}

function solution_compare(a, b)
{
	return a['score'] - b['score'];
}

function sortSolutions()
{
	solutions.sort(solution_compare);
}

