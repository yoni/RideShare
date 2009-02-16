<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'validate.inc'; ?>
<?php require_once 'googlemaps.inc'; ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>Ride Share</title>
  <link rel="Stylesheet" href="style.css" />
  <script type="text/javascript">
    //<![CDATA[
    var map = null;
    var map_canvas = null;
    var gdir = null;
    var ride_details = null;

    function handleErrors() {
    }

    function clearRideDetails() {
      while(ride_details.hasChildNodes())
        ride_details.removeChild(ride_details.firstChild);
    }

    function onGDirectionsLoad(){ 
      var place;
      var bold_text;
      if(gdir.getNumGeocodes() == 2) {
        var title = ride_details.firstChild;
        ride_details.removeChild(ride_details.firstChild);
        
        ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
        ride_details.insertBefore(document.createTextNode(gdir.getDuration().html.replace(/&nbsp;/g, " ")), ride_details.firstChild);
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('Duration: '));
        ride_details.insertBefore(bold_text, ride_details.firstChild);
        ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
        ride_details.insertBefore(document.createTextNode(gdir.getDistance().html.replace(/&nbsp;/g, " ")), ride_details.firstChild);
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('Distance: '));
        ride_details.insertBefore(bold_text, ride_details.firstChild);
        var num_points;
        for(num_points = gdir.getNumGeocodes()-1; num_points > 0; num_points--) {
          place = gdir.getGeocode(num_points);
          ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
          ride_details.insertBefore(document.createTextNode(place.address), ride_details.firstChild);
          bold_text = document.createElement('b');
          bold_text.appendChild(document.createTextNode('To: '));
          ride_details.insertBefore(bold_text, ride_details.firstChild);
        }

        place = gdir.getGeocode(0);
        ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
        ride_details.insertBefore(document.createTextNode(place.address), ride_details.firstChild);
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('From: '));
        ride_details.insertBefore(bold_text, ride_details.firstChild);
        ride_details.insertBefore(title, ride_details.firstChild);
      }
      else {
        var cur_line;
      
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('Distance: '));
        ride_details.appendChild(document.createElement('br'));
        ride_details.appendChild(bold_text);
        ride_details.appendChild(document.createTextNode(gdir.getDistance().html.replace(/&nbsp;/g, " ")));
        ride_details.appendChild(document.createElement('br'));
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('Duration: '));
        ride_details.appendChild(document.createElement('br'));
        ride_details.appendChild(bold_text);
        ride_details.appendChild(document.createTextNode(gdir.getDuration().html.replace(/&nbsp;/g, " ")));
        ride_details.appendChild(document.createElement('br'));


        place = gdir.getGeocode(0);
        cur_line = ride_details.firstChild.nextSibling;
        cur_line.insertBefore(document.createTextNode(place.address), cur_line.firstChild);
        bold_text = document.createElement('b');
        bold_text.appendChild(document.createTextNode('From: '));
        cur_line.insertBefore(bold_text, cur_line.firstChild);

        var cur_point;
        for(cur_point = 1; cur_point < gdir.getNumGeocodes(); cur_point++) {
          place = gdir.getGeocode(cur_point);
          cur_line = ride_details.firstChild;
          for(var i=0; i<cur_point + 1; i++)
            cur_line = cur_line.nextSibling;
          cur_line.insertBefore(document.createTextNode(place.address), cur_line.firstChild);
          bold_text = document.createElement('b');
          bold_text.appendChild(document.createTextNode('To: '));
          cur_line.insertBefore(bold_text, cur_line.firstChild);
        }

      }

      ride_details.style.display = '';
      map_canvas.style.height = '80%';
    }

    var selected = null;
    function highlight(listentry) {
      if(listentry != selected)
        listentry.style.backgroundColor='#f8e4d4';
    }
    function dehighlight(listentry) {
      if(listentry != selected)
        listentry.style.backgroundColor='#f8d6ba';
    }
    function select(listentry, points, driver_or_rider, timewindows, title, actions) {
      if(selected != null && selected != listentry)
        selected.style.backgroundColor='#f8d6ba';
      listentry.style.backgroundColor='#f8e4d4';
      selected = listentry;
      map_canvas.style.height = '85%';
      gdir.load(points);
      clearRideDetails();
      if(title) {
        var title_div = document.createElement('div');
        title_div.style.textAlign = 'center';
        title_div.setAttribute("class", "headingtext");
        title_div.appendChild(document.createTextNode(title));
        ride_details.appendChild(title_div);
      }
      if(timewindows) {
        if(timewindows.length == 2) {
          var bold_text;
          bold_text = document.createElement('b');
          bold_text.appendChild(document.createTextNode('Departing between: '));
          ride_details.appendChild(bold_text);
          ride_details.appendChild(document.createTextNode(timewindows[0][0] + ' and ' + timewindows[0][1]));
          ride_details.appendChild(document.createElement('br'));
          bold_text = document.createElement('b');
          bold_text.appendChild(document.createTextNode('Arriving between: '));
          ride_details.appendChild(bold_text);
          ride_details.appendChild(document.createTextNode(timewindows[timewindows.length-1][0] + ' and ' + timewindows[timewindows.length-1][1]));
          ride_details.appendChild(document.createElement('br'));
          bold_text = document.createElement('b');
          bold_text.appendChild(document.createTextNode('Role: '));
          ride_details.appendChild(bold_text);
          ride_details.appendChild(document.createTextNode(driver_or_rider));
          ride_details.appendChild(document.createElement('br'));
        }
        else {
          var num_points = timewindows.length;
          for(var cur_point = 0; cur_point < num_points; cur_point++) {
            var new_div = document.createElement('div');
            var text_string = ' between ' + timewindows[cur_point][0] + ' and ' + timewindows[cur_point][1];
            if(cur_point > 0 && cur_point < num_points - 1)
              text_string += ' to ' + actions[cur_point][0] + ' ';
            new_div.appendChild(document.createTextNode(text_string));
            if(cur_point > 0 && cur_point < num_points - 1) {
              var new_link = document.createElement('a');
              new_link.appendChild(document.createTextNode(actions[cur_point][1]));
              new_link.setAttribute("href", "view_profile.php?user_id=" + actions[cur_point][2]);
              new_link.setAttribute("style", "text-decoration: underline;");
              new_div.appendChild(new_link);
            }
            ride_details.appendChild(new_div);
          }
        }
      }
    }

    function initialize() {
      if (GBrowserIsCompatible()) {
        map_canvas = document.getElementById('map_canvas');
        map = new GMap2(map_canvas);
        map.setCenter(new GLatLng(30.288160408911523, -97.7351501584053), 13);
        map.addControl(new GLargeMapControl());
        map.addControl(new GMapTypeControl());
        gdir = new GDirections(map, document.getElementById("directions"));
        GEvent.addListener(gdir, "load", onGDirectionsLoad);
        GEvent.addListener(gdir, "error", handleErrors);
      }
      ride_details = document.getElementById('ride_details');
      
      var first_ride = document.getElementById('first_ride_in_list');
      if(first_ride) {
        var click_event = document.createEvent('MouseEvents');
        click_event.initMouseEvent('click', true, true, document.defaultView, 1, 0, 0, 0, 0, false, false, false, false, 0, null);
        first_ride.dispatchEvent(click_event);
      }
    }

    //]]>
  </script>
 </head>
 <body onload="initialize()" onunload="GUnload()">

  <?php require 'topmenu.inc'; ?>

  <div class="bigbox" style="float: left; width: 350px;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content">
<?php
	$query = 'SELECT rssurl FROM users WHERE user_id='.$_COOKIE['user_id'];
	$submission_result = mysql_query($query);

	if($submission_result and mysql_num_rows($submission_result) > 0) 
	{
		$row = mysql_fetch_assoc($submission_result);
		$usersRssUrl = 'rss.php?x='.$row['rssurl'].'&u='.$_COOKIE['user_id'];
    echo 'My Rides <a class="normaltext" href="'.$usersRssUrl.'">(Subscribe)</a><br />';
	}
	else
	{
		echo 'My Rides <br />';
	}
?>
    <a class="normaltext" href="new_route.php">New Route</a><br />
    <br />
    <div class="normaltext" style="max-height: 600px; overflow-y: auto">
<?php
	$query = "SELECT route_submission_id, start_addr, end_addr, leave_time_earliest, leave_time_latest, arrive_time_earliest, arrive_time_latest, start_location_lat, start_location_lon, end_location_lat, end_location_lon, driver_or_rider, title FROM route_submissions WHERE user_id = '" . mysql_real_escape_string($user_id) . "' ORDER BY arrive_time_latest ASC";
	$submission_result = mysql_query($query);
	if($submission_result and mysql_num_rows($submission_result) > 0) {
		$have_labeled_first_child = false;
		while($row = mysql_fetch_assoc($submission_result)) {
			$route_submission_id = $row['route_submission_id'];
			$route_start_addr = $row['start_addr'];
			$route_end_addr = $row['end_addr'];
			$route_driver_or_rider = $row['driver_or_rider'];
			$route_title = $row['title'];
			$query = "SELECT DISTINCT match_id, solution_id FROM matches WHERE route_submission_id = '" . mysql_real_escape_string($route_submission_id) . "'";
			$match_result = mysql_query($query);
			if($match_result and mysql_num_rows($match_result) > 0) {
				$row = mysql_fetch_assoc($match_result);
				$match_id = $row['match_id'];
				$solution_id = $row['solution_id'];
				echo '     <div class="listbox" onmouseover="highlight(this)" onmouseout="dehighlight(this)" onclick="select(this, \'from: ';
				$query = "SELECT route_submissions.route_submission_id, route_submissions.start_addr, route_submissions.end_addr, route_submissions.driver_or_rider, matches.earliest, matches.latest, matches.sequence_num, users.user_id, users.first_name, users.last_name FROM matches, route_submissions, users WHERE matches.solution_id = '" . mysql_real_escape_string($solution_id) . "' AND matches.match_id = '" . mysql_real_escape_string($match_id) . "' AND route_submissions.route_submission_id = matches.route_submission_id AND users.user_id = route_submissions.user_id ORDER BY matches.sequence_num";
				$result = mysql_query($query);
				$row = mysql_fetch_assoc($result);
				echo $row['start_addr'];
				$time_window_string = "[['" . $row['earliest'] . "', '" . $row['latest'] . "'],";
				$action_string = "[['pick up','" . $row['first_name'] . " " . $row['last_name'] . "','" . $row['user_id'] . "'],";
				unset($seen);
				$seen[$row['route_submission_id']] = true;
				while($row = mysql_fetch_assoc($result)) {
					echo " to: ";
					if($seen[$row['route_submission_id']]) {
						echo $row['end_addr'];
						$action_string .= "['drop off'";
					}
					else {
						$seen[$row['route_submission_id']] = true;
						echo $row['start_addr'];
						$action_string .= "['pick up'";
					}
					if($row['user_id'] == $user_id)
						$action_string .= ",'You','$user_id'],";
					else
						$action_string .= ",'" . addslashes($row['first_name'] . " " . $row['last_name']) . "','" . $row['user_id'] . "'],";
					$time_window_string .= "['".$row['earliest']."','".$row['latest'].".'],";
				}
				$time_window_string = substr($time_window_string, 0, -1) . "]";
				$action_string = substr($action_string, 0, -1) . "]";
				echo "', '" . $route_driver_or_rider . "', $time_window_string, '" . $route_title . "', $action_string)\"";
				unset($seen);
				if(!$have_labeled_first_child) {
					echo ' id="first_ride_in_list"';
					$have_labeled_first_child = true;
				}
				echo '>';
				//echo "Solution: $solution_id, Match: $match_id<br />";
				if($route_driver_or_rider == 'driver')
					echo "We have found candidates for a rideshare<br />";
				else
					echo "Your request for a ride has been matched!<br />";
/*				echo "From: ";
				if(strlen($route_start_addr) > 20)
					echo substr($route_start_addr, 0, 20) . "...";
				else
					echo $route_start_addr;
				echo "<br />To: ";
				if(strlen($route_end_addr) > 20)
					echo substr($route_end_addr, 0, 20) . "...";
				else
					echo $route_end_addr;*/
				echo $route_title;
				echo "<br />";

				$query = "SELECT DISTINCT route_submissions.driver_or_rider, users.first_name, users.last_name FROM matches, route_submissions, users WHERE matches.solution_id = '" . mysql_real_escape_string($solution_id) . "' AND matches.match_id = '" . mysql_real_escape_string($match_id) . "' AND route_submissions.route_submission_id = matches.route_submission_id AND users.user_id = route_submissions.user_id AND matches.route_submission_id != '" . mysql_real_escape_string($route_submission_id) . "' ORDER BY route_submissions.driver_or_rider, matches.sequence_num";
				$result = mysql_query($query);
				while($row = mysql_fetch_assoc($result)) {
					if($row['driver_or_rider'] == 'driver')
						echo 'Driver: ';
					else
						echo '(Other) Rider: ';
					echo $row['first_name'] . " " . $row['last_name'] . "<br />";
				}
//				echo "Solution: $solution_id, Match: $match_id<br />";
				echo "</div>\n";
			}
			else {
				echo '     <div class="listbox" onmouseover="highlight(this)" onmouseout="dehighlight(this)" onclick="select(this, \'from: ' . $row['start_addr'] . ' to: ' . $row['end_addr'] . '\', \'' . $route_driver_or_rider . '\', [[\'' . $row['leave_time_earliest'] . '\',\'' . $row['leave_time_latest'] . '\'], [\'' . $row['arrive_time_earliest'] . '\',\'' . $row['arrive_time_latest'] . '\']], \'' . $row['title'] . '\')"';
				if(!$have_labeled_first_child) {
					echo ' id="first_ride_in_list"';
					$have_labeled_first_child = true;
				}
				echo '>';
/*				echo 'From: ';
				if(strlen($row['start_addr']) > 20)
					echo substr($row['start_addr'], 0, 20) . "...";
				else
					echo $row['start_addr'];
				echo "<br />To: ";
				if(strlen($row['start_addr']) > 20)
					echo substr($row['end_addr'], 0, 20) . "...";
				else
					echo $row['end_addr'];
 */
				echo $route_title;
				echo '<br />Departure: ' . $row['leave_time_earliest'] . "</div>\n";
			}
		}
	}
?>
    </div>
   </div>
   <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&nbsp;</div>
  </div>
  <div id="ride_details" style="border: 1px solid #f8a560; background-color: #f8d6ba; margin-left: 370px; margin-right: 20px; margin-top: 20px; display: none;"></div>
  <div id="map_canvas" style="border: 1px solid black; height: 90%; margin-left: 370px; margin-right: 20px; margin-top: 20px;"></div>
  <div id="directions" style="display: none;"></div>
 </body>
</html>
