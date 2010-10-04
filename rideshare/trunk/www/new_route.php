<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'validate.inc'; ?>
<?php require_once 'googlemaps.inc'; ?>
<?php

	if(isset($_POST['driver_or_rider']) and (strtolower($_POST['driver_or_rider']) == 'driver' or strtolower($_POST['driver_or_rider']) == 'rider')) {
		if(!isset($_POST['route_title']) or $_POST['route_title'] == '')
			$error_msg .= 'Please provide a title for this route.<br />';
		elseif(!preg_match('/^[a-zA-Z0-9 ]+$/', $_POST['route_title']))
			$error_msg .= 'Please use only alphanumeric characters in the title.<br />';

		/* Validate starting coordinates */
		if(!isset($_POST['start_addr']) or $_POST['start_addr'] == '')
			$error_msg .= 'A starting location is required.  Please fill one in and resubmit your ride.<br />';
		if(!isset($error_msg) and (!isset($_POST['start_lat']) or !isset($_POST['start_long']) or !preg_match('/^-?(\d{1,3})(?:\.\d+)?$/', $_POST['start_lat'], $lat_matches) or !preg_match('/^-?(\d{1,3})(?:\.\d+)?$/', $_POST['start_long'], $long_matches)))
			$error_msg .= 'The starting location is invalid.  Please make sure javascript is enabled in your browser<br />';
		if(!isset($error_msg) and intval($lat_matches[1]) > 90)
			$error_msg .= 'Coordinate (latitude) specified as starting location is out of range.<br />';
		if(!isset($error_msg) and intval($long_matches[1]) > 180)
			$error_msg .= 'Coordinate (longitude) specified as starting location is out of range.<br />';

		/* Validate ending coordinates */
		if(!isset($_POST['end_addr']) or $_POST['end_addr'] == '')
			$error_msg .= 'An ending location is required.  Please fill one in and resubmit your ride.<br />';
		if(!isset($error_msg) and (!isset($_POST['end_lat']) or !isset($_POST['end_long']) or !preg_match('/^-?(\d{1,3})(?:\.\d+)?$/', $_POST['end_lat'], $lat_matches) or !preg_match('/^-?(\d{1,3})(?:\.\d+)?$/', $_POST['end_long'], $long_matches)))
			$error_msg .= 'The ending location is invalid.  Please make sure javascript is enabled in your browser<br />';
		if(!isset($error_msg) and intval($lat_matches[1]) > 90)
			$error_msg .= 'Coordinate (latitude) specified as ending location is out of range.<br />';
		if(!isset($error_msg) and intval($long_matches[1]) > 180)
			$error_msg .= 'Coordinate (longitude) specified as ending location is out of range.<br />';

		/* Look for missing times */
		if(!isset($_POST['route_leave_time_earliest']) or $_POST['route_leave_time_earliest'] == '')
			$error_msg .= 'The earliest departure field is required.  Please fill it in (in YYYY-MM-DD HH:MM:SS format).<br />';
		if(!isset($_POST['route_leave_time_latest']) or $_POST['route_leave_time_latest'] == '')
			$error_msg .= 'The latest departure field is required.  Please fill it in (in YYYY-MM-DD HH:MM:SS format).<br />';
		if(!isset($_POST['route_arrive_time_earliest']) or $_POST['route_arrive_time_earliest'] == '')
			$error_msg .= 'The earliest arrival field is required.  Please fill it in (in YYYY-MM-DD HH:MM:SS format).<br />';
		if(!isset($_POST['route_arrive_time_latest']) or $_POST['route_arrive_time_latest'] == '')
			$error_msg .= 'The latest arrival field is required.  Please fill it in (in YYYY-MM-DD HH:MM:SS format).<br />';

		/* Check for invalid format */
		$acceptable_datetime_format = '/^\s*(\d{4})[-\/]([01]?\d)[-\/]([0-3]?\d)\s+([0-2]?\d)(?:\:([0-5]?\d)(?:\:([0-5]?\d))?)?(?:\s*([aApP](?:\.[mM]\.|[mM])))?\s*$/';

		if(isset($_POST['route_leave_time_earliest']) and $_POST['route_leave_time_earliest'] != '') {
			if(!preg_match($acceptable_datetime_format, $_POST['route_leave_time_earliest'], $datetimeinfo))
				$error_msg .= 'Earliest departure time is in an incorrect format.  Please rewrite it in YYYY-MM-DD HH:MM:SS format.<br />';
			else {
				$year = $datetimeinfo[1];
				$month = sprintf('%02d',$datetimeinfo[2]);
				$day = sprintf('%02d',$datetimeinfo[3]);
				$hour = sprintf('%02d',$datetimeinfo[4]);
				$min = sprintf('%02d',isset($datetimeinfo[5])?$datetimeinfo[5]:0);
				$sec = sprintf('%02d',isset($datetimeinfo[6])?$datetimeinfo[6]:0);
				$ampm = $datetimeinfo[7];
				if(isset($ampm)) {
					if (intval($hour) > 12 and preg_match('/^[aA]/', $ampm))
						$error_msg .= "In earliest departure time: $hour $ampm is not a valid time, please correct it.<br />";
					elseif(preg_match('/^[pP]/', $ampm) and intval($hour) < 12)
						$hour = sprintf('%02d',intval($hour)+12);
					unset($ampm);
				}
				$leave_time_earliest = strtotime("$year$month$day, $hour$min");
				if($leave_time_earliest === false)
					$error_msg .= "Earliest departure date/time is invalid.<br />";
				elseif($leave_time_earliest < strtotime("-1 day"))
					$error_msg .= 'Earliest departure time is far in the past; please adjust it to be current.<br />';
				else
					$_POST['route_leave_time_earliest'] = "$year-$month-$day $hour:$min:$sec";
			}
		}
		else
			unset($_POST['route_leave_time_earliest']);

		if(isset($_POST['route_leave_time_latest']) and $_POST['route_leave_time_latest'] != '') {
			if(!preg_match($acceptable_datetime_format, $_POST['route_leave_time_latest'], $datetimeinfo))
				$error_msg .= 'Latest departure time is in an incorrect format.  Please rewrite it in YYYY-MM-DD HH:MM:SS format.<br />';
			else {
				$year = $datetimeinfo[1];
				$month = sprintf('%02d',$datetimeinfo[2]);
				$day = sprintf('%02d',$datetimeinfo[3]);
				$hour = sprintf('%02d',$datetimeinfo[4]);
				$min = sprintf('%02d',isset($datetimeinfo[5])?$datetimeinfo[5]:0);
				$sec = sprintf('%02d',isset($datetimeinfo[6])?$datetimeinfo[6]:0);
				$ampm = $datetimeinfo[7];
				if(isset($ampm)) {
					if(intval($hour) > 12 and preg_match('/^[aA]/', $ampm))
						$error_msg .= "In latest departure time: $hour $ampm is not a valid time, please correct it.<br />";
					elseif(preg_match('/^[pP]/', $ampm) and intval($hour) < 12)
						$hour = sprintf('%02d',intval($hour)+12);
					unset($ampm);
				}
				$leave_time_latest = strtotime("$year$month$day, $hour$min");
				if($leave_time_latest === false)
					$error_msg .= "Latest departure date/time is invalid.<br />";
				elseif($leave_time_latest < strtotime("-1 day"))
					$error_msg .= 'Latest departure time is far in the past; please adjust it to be current.<br />';
				else
					$_POST['route_leave_time_latest'] = "$year-$month-$day $hour:$min:$sec";
			}
		}
		else
			unset($_POST['route_leave_time_latest']);

		if(isset($_POST['route_arrive_time_earliest']) and $_POST['route_arrive_time_earliest'] != '') {
			if(!preg_match($acceptable_datetime_format, $_POST['route_arrive_time_earliest'], $datetimeinfo))
				$error_msg .= 'Earliest arrival time is in an incorrect format.  Please rewrite it in YYYY-MM-DD HH:MM:SS format.<br />';
			else {
				$year = $datetimeinfo[1];
				$month = sprintf('%02d',$datetimeinfo[2]);
				$day = sprintf('%02d',$datetimeinfo[3]);
				$hour = sprintf('%02d',$datetimeinfo[4]);
				$min = sprintf('%02d',isset($datetimeinfo[5])?$datetimeinfo[5]:0);
				$sec = sprintf('%02d',isset($datetimeinfo[6])?$datetimeinfo[6]:0);
				$ampm = $datetimeinfo[7];
				if(isset($ampm)) {
					if(intval($hour) > 12 and preg_match('/^[aA]/', $ampm))
						$error_msg .= "In earliest arrival time: $hour $ampm is not a valid time, please correct it.<br />";
					elseif(preg_match('/^[pP]/', $ampm) and intval($hour) < 12)
						$hour = sprintf('%02d',intval($hour)+12);
					unset($ampm);
				}
				$arrive_time_earliest = strtotime("$year$month$day, $hour$min");
				if($arrive_time_earliest === false)
					$error_msg .= "Earliest arrival date/time is invalid.<br />";
				elseif($arrive_time_earliest < strtotime("-1 day"))
					$error_msg .= 'Earliest arrival time is far in the past; please adjust it to be current.<br />';
				else
					$_POST['route_arrive_time_earliest'] = "$year-$month-$day $hour:$min:$sec";
			}
		}
		else
			unset($_POST['route_arrive_time_earliest']);

		if(isset($_POST['route_arrive_time_latest']) and $_POST['route_arrive_time_latest'] != '') {
			if(!preg_match($acceptable_datetime_format, $_POST['route_arrive_time_latest'], $datetimeinfo))
				$error_msg .= 'Latest arrival time is in an incorrect format.  Please rewrite it in YYYY-MM-DD HH:MM:SS format.<br />';
			else {
				$year = $datetimeinfo[1];
				$month = sprintf('%02d',$datetimeinfo[2]);
				$day = sprintf('%02d',$datetimeinfo[3]);
				$hour = sprintf('%02d',$datetimeinfo[4]);
				$min = sprintf('%02d',isset($datetimeinfo[5])?$datetimeinfo[5]:0);
				$sec = sprintf('%02d',isset($datetimeinfo[6])?$datetimeinfo[6]:0);
				$ampm = $datetimeinfo[7];
				if(isset($ampm)) {
					if(intval($hour) > 12 and preg_match('/^[aA]/', $ampm))
						$error_msg .= "In latest arrival time: $hour $ampm is not a valid time, please correct it.<br />";
					elseif(preg_match('/^[pP]/', $ampm) and intval($hour) < 12)
						$hour = sprintf('%02d',intval($hour)+12);
					unset($ampm);
				}
				$arrive_time_latest = strtotime("$year$month$day, $hour$min");
				if($arrive_time_latest === false)
					$error_msg .= "Latest arrival date/time is invalid.<br />";
				elseif($arrive_time_latest < strtotime("-1 day"))
					$error_msg .= 'Latest arrival time is far in the past; please adjust it to be current.<br />';
				else
					$_POST['route_arrive_time_latest'] = "$year-$month-$day $hour:$min:$sec";
			}
		}
		else
			unset($_POST['route_arrive_time_latest']);

		/* Make sure it's possible */
		if(!isset($error_msg) and (!isset($_POST['route_optimal_duration']) or !isset($_POST['route_optimal_distance'])))
			$error_msg .= 'Missing route information.  Please make sure you have Javascript enabled in your browser.<br />';

		if(!isset($_POST['route_optimal_duration']) or !ctype_digit($_POST['route_optimal_duration']) or !isset($_POST['route_optimal_distance']) or !ctype_digit($_POST['route_optimal_distance']))
			$error_msg .= 'Please make sure javascript is turned on in your browser.<br />';
		else {
			$route_duration = intval($_POST['route_optimal_duration']);
			if(isset($leave_time_earliest) and isset($leave_time_latest) and $leave_time_earliest > $leave_time_latest)
				$error_msg .= 'Earliest departure time is after latest departure time. Please correct.<br />';
			if(isset($arrive_time_earliest) and isset($arrive_time_latest) and $arrive_time_earliest > $arrive_time_latest)
				$error_msg .= 'Earliest arrival time is after latest arrival time. Please correct.<br />';
			if(isset($leave_time_earliest) and isset($arrive_time_latest) and $leave_time_earliest + $route_duration > $arrive_time_latest)
				$error_msg .= 'Sorry but it is not possible to satisfy both your earliest departure and latest arrival times for the addresses given.<br />';
		}

		/* Preferences */
		if($_POST['route_pref_age_min'] != "" and (!ctype_digit($_POST['route_pref_age_min']) or intval($_POST['route_pref_age_min']) > 80)) {
			unset($_POST['route_pref_age_min']);
			$error_msg .= 'Minimum Age must be a positive whole number less than 80<br />';
		}
		if(intval($_POST['route_pref_age_min']) == 0)
			unset($_POST['route_pref_age_min']);
		if($_POST['route_pref_age_max'] != "" and !ctype_digit($_POST['route_pref_age_max'])) {
			unset($_POST['route_pref_age_max']);
			$error_msg .= 'Maximum Age must be a positive whole number<br />';
		}
		if(intval($_POST['route_pref_age_max']) > 80 or intval($_POST['route_pref_age_max']) == 0)
			unset($_POST['route_pref_age_max']);
		if(intval($_POST['route_pref_age_max']) < intval($_POST['route_pref_age_min'])) {
			unset($_POST['route_pref_age_max'], $_POST['route_pref_age_min']);
			$error_msg .= 'Minimum age must be less than or equal to maximum age<br />';
		}
		if($_POST['route_pref_rating_min'] != "") {
			if(!preg_match('/^([0-9]+\.?[0-9]*)|([0-9]*\.?[0-9]+)$/', $_POST['route_pref_rating_min'])) {
				unset($_POST['route_pref_rating_min']);
				$error_msg .= 'Minimum Rating must be a positive real number<br />';
			}
			elseif(round(floatval($_POST['route_pref_rating_min']),2) == 0.0)
				unset($_POST['route_pref_rating_min']);
			elseif(round(floatval($_POST['route_pref_rating_min']),2) > 5.0) {
				unset($_POST['route_pref_rating_min']);
				$error_msg .= 'Rating must be between 0.0 and 5.0<br />';
			}
		}
		if($_POST['route_comment'] != '') {
			if(strlen($_POST['route_comment']) > 110) {
				unset($_POST['route_comment']);
				$error_msg .= 'Comment is too large.  Please try to keep it less than 100 characters.<br />';
			}
		}
		if($_POST['route_pref_gender_id'] != "") {
			if(!ctype_digit($_POST['route_pref_gender_id'])) {
				unset($_POST['route_pref_gender_id']);
				$error_msg .= 'Invalid gender selection in preferences<br />';
			}
			else {
				$query = "SELECT gender_id FROM genders WHERE gender_id = '" . mysql_real_escape_string($_POST['route_pref_gender_id']) . "'";
				$result = mysql_query($query);
				if(!$result or mysql_num_rows($result) == 0) {
					unset($_POST['route_pref_gender_id']);
					$error_msg .= 'Invalid gender selection in preferences<br />';
				}
			}
		}
		else
			unset($_POST['route_pref_gender_id']);

		/* occupation specific parameters */
		if(strtolower($_POST['driver_or_rider']) == 'driver') {
			if($_POST['route_pref_capacity'] == "" or !ctype_digit($_POST['route_pref_capacity'])) {
				unset($_POST['route_pref_capacity']);
				$error_msg .= 'Invalid capacity specified<br />';
			}
		}
		else
			unset($_POST['route_pref_capacity']);

		if(!isset($error_msg)) {
			$query = "INSERT route_submissions SET user_id = '$user_id', start_location_lat = '" . mysql_real_escape_string($_POST['start_lat']) . "', start_location_lon = '" . mysql_real_escape_string($_POST['start_long']) . "', end_location_lat = '" . mysql_real_escape_string($_POST['end_lat']) . "', end_location_lon = '" . mysql_real_escape_string($_POST['end_long']) . "', optimal_route_length = '" . mysql_real_escape_string(floatval($_POST['route_optimal_distance'])/1609.344) . "', driver_or_rider = '" . mysql_real_escape_string(strtolower($_POST['driver_or_rider'])) . "', start_addr = '" . mysql_real_escape_string($_POST['start_addr']) . "', end_addr = '" . mysql_real_escape_string($_POST['end_addr']) . "', optimal_route_time = '" . mysql_real_escape_string($_POST['route_optimal_duration']) . "', title = '" . mysql_real_escape_string($_POST['route_title']) . "'";
			if(isset($_POST['route_leave_time_earliest']))
				$query .= ", leave_time_earliest = '" . mysql_real_escape_string($_POST['route_leave_time_earliest']) . "'";
			if(isset($_POST['route_leave_time_latest']))
				$query .= ", leave_time_latest = '" . mysql_real_escape_string($_POST['route_leave_time_latest']) . "'";
			if(isset($_POST['route_arrive_time_earliest']))
				$query .= ", arrive_time_earliest = '" . mysql_real_escape_string($_POST['route_arrive_time_earliest']) . "'";
			if(isset($_POST['route_arrive_time_latest']))
				$query .= ", arrive_time_latest = '" . mysql_real_escape_string($_POST['route_arrive_time_latest']) . "'";
			if(isset($_POST['route_comment']))
				$query .= ", comment = '" . mysql_real_escape_string($_POST['route_comment']) . "'";

			$result = mysql_query($query);
			if($result) {
				$route_id = mysql_insert_id();
				if($_POST['route_pref_age_min'] != "" or $_POST['route_pref_age_max'] != "" or $_POST['route_pref_gender_id'] != "" or $_POST['route_pref_rating_min']) {
					$query = "INSERT route_prefs SET route_submission_id = '" . mysql_real_escape_string($route_id) . "'";
					if($_POST['route_pref_age_min'] != "")
						$query .= ", age_min = '" . mysql_real_escape_string($_POST['route_pref_age_min']) . "'";
					if($_POST['route_pref_age_max'] != "")
						$query .= ", age_max = '" . mysql_real_escape_string($_POST['route_pref_age_max']) . "'";
					if($_POST['route_pref_gender_id'] != "")
						$query .= ", gender_id = '" . mysql_real_escape_string($_POST['route_pref_gender_id']) . "'";
					if($_POST['route_pref_rating_min'] != "")
						$query .= ", rating_min = '" . mysql_real_escape_string($_POST['route_pref_rating_min']) . "'";
					mysql_query($query);
				}
				if(strtolower($_POST['driver_or_rider']) == 'driver' and $_POST['route_pref_capacity'] != "") {
					$query = "INSERT route_driver_options SET route_submission_id = '" . mysql_real_escape_string($route_id) . "', capacity = '" . mysql_real_escape_string($_POST['route_pref_capacity']) . "'";
					mysql_query($query);
				}
				header("Location: member.php");
				die();
			}
		}
		/*foreach (array_keys($_POST) as $key) {
			$error_msg .= $key . ' = ' . $_POST[$key] . '<br />';
		}*/
	}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>Ride Share</title>
  <link rel="Stylesheet" href="style.css" />
  <script type="text/javascript" src="form.js"></script>
  <script type="text/javascript">
    //<![CDATA[
    var map = null;
    var gdir = null;
    var geocoder = null;

    var is_real_submit = false;
    var initialized = false;

    var from_address_input = null;
    var to_address_input = null;

    function handleErrors() {
      var error_text;
      var errorbox = document.getElementById('errorbox');

      // we don't have to handle unknown address error here, because it's handled when we look up their lat/longs
      if (gdir.getStatus().code == G_GEO_UNKNOWN_ADDRESS) {
/*        var start_lat = document.getElementById('start_lat').value;
        var end_lat = document.getElementById('end_lat').value;
        if(start_lat != '' && end_lat != '') {
          error_text = "There was a problem locating at least one of the addresses provided.  Please double check that they are correct (try entering them in one at a time)";
	  }*/
      }
      else if (gdir.getStatus().code == G_GEO_UNKNOWN_DIRECTIONS) {
        error_text = "A route could not be computed between the two specified addresses. Please select different starting and ending locations.";
      }

      else if (gdir.getStatus().code == G_GEO_SERVER_ERROR)
        error_text = "Error " + gdir.getStatus().code + ": The map servers could not process your request at this time. Please try again shortly.";
  
      else if (gdir.getStatus().code == G_GEO_MISSING_QUERY || gdir.getStatus().code == G_GEO_BAD_KEY || gdir.getStatus().code == G_GEO_BAD_REQUEST)
        error_text = "Error " + gdir.getStatus().code + ": There was an internal error processing your ride request.  Please report this event to us.";

      else
        error_text = "An unknown error occured.  Please report this event to us.";

      if(error_text) {
        errorbox.appendChild(document.createTextNode(error_text));
        errorbox.appendChild(document.createElement('br'));
        errorbox.style.display='';
      }
    }

    function updateStartingLocation(response, add_marker) {
      if (!response || response.Status.code != 200) {
        var error_text = 'Sorry but that starting address is not valid.';
        var errorbox = document.getElementById('errorbox');
        errorbox.appendChild(document.createTextNode(error_text));
        errorbox.appendChild(document.createElement('br'));
        errorbox.style.display='';
      }
      else {
        place = response.Placemark[0];
        point = new GLatLng(place.Point.coordinates[1], place.Point.coordinates[0]);
        from_address_input.value = place.address;
 
        // update the hidden fields that are passed to the database
        document.getElementById('start_lat').value = place.Point.coordinates[1];
        document.getElementById('start_long').value = place.Point.coordinates[0];

        if(add_marker) {
          map.clearOverlays();
          marker = new GMarker(point);
          map.addOverlay(marker);
          map.setCenter(point);
        }
      }
    }
    function updateAddStartingLocation(response) {
      updateStartingLocation(response, true);
    }

    function updateEndingLocation(response, add_marker) {
      if (!response || response.Status.code != 200) {
        var error_text = 'Sorry but that ending address is not valid.';
        var errorbox = document.getElementById('errorbox');
        errorbox.appendChild(document.createTextNode(error_text));
        errorbox.appendChild(document.createElement('br'));
        errorbox.style.display='';
      }
      else {
        place = response.Placemark[0];
        point = new GLatLng(place.Point.coordinates[1], place.Point.coordinates[0]);
        to_address_input.value = place.address;
 
        // update the hidden fields that are passed to the database
        document.getElementById('end_lat').value = place.Point.coordinates[1];
        document.getElementById('end_long').value = place.Point.coordinates[0];

        if(add_marker) {
          map.clearOverlays();
          marker = new GMarker(point);
          map.addOverlay(marker);
          map.setCenter(point);
        }
      }
    }
    function updateAddEndingLocation(response) {
      updateEndingLocation(response, true);
    }

    function setDirections() {
      map.clearOverlays();
      var from_address_input = document.getElementById('from_address');
      var from_address = from_address_input.value;
      var to_address_input = document.getElementById('to_address');
      var to_address = to_address_input.value;
      document.getElementById('route_optimal_duration_gui').style.display = 'none';
      document.getElementById('route_optimal_distance_gui').style.display = 'none';
      
      // clear out old values
      document.getElementById('start_lat').value = '';
      document.getElementById('start_long').value = '';
      document.getElementById('end_lat').value = '';
      document.getElementById('end_long').value = '';
      if(initialized) {
        var error_box = document.getElementById('errorbox');
        while(error_box.hasChildNodes()) {
          error_box.removeChild(error_box.firstChild);
        }
        error_box.style.display = 'none';
      }

      if(
        (from_address != 'Starting Address' && from_address != '') &&
        (to_address != 'Ending Address' && to_address != '') 
      ) {
        // just making sure...
        from_address_input.style.color = 'black';
        to_address_input.style.color = 'black';

        geocoder.getLocations(from_address, updateStartingLocation);
        geocoder.getLocations(to_address, updateEndingLocation);

        var load_string = '';
        load_string += "from: " + from_address;
        load_string += " to: " + to_address;
        gdir.load(load_string);
      }
      else if(from_address != 'Starting Address' && from_address != '') {
        from_address_input.style.color = 'black';
        geocoder.getLocations(from_address, updateAddStartingLocation);
      }
      else if(to_address != 'Ending Address' && to_address != '') {
        to_address_input.style.color = 'black';
        geocoder.getLocations(to_address, updateAddEndingLocation);
      }
      else {
        map.setCenter(new GLatLng(30.28815462, -97.7351001), 13);
      }

    }

    function onGDirectionsLoad(){ 
      document.getElementById('route_optimal_duration_gui').style.display = '';
      document.getElementById('route_optimal_duration_display').value = gdir.getDuration().html.replace(/&nbsp;/g, " ");
      document.getElementById('route_optimal_duration').value = gdir.getDuration().seconds;
      document.getElementById('route_optimal_distance_gui').style.display = '';
      document.getElementById('route_optimal_distance_display').value = gdir.getDistance().html.replace(/&nbsp;/g, " ");
      document.getElementById('route_optimal_distance').value = gdir.getDistance().meters;
    }
  
    function initialize() {
      from_address_input = document.getElementById('from_address');
      to_address_input = document.getElementById('to_address');
      if (GBrowserIsCompatible()) {
        map = new GMap2(document.getElementById("map_canvas"));
        map.setCenter(new GLatLng(30.288160408911523, -97.7351501584053), 13);
        map.addControl(new GLargeMapControl());
        map.addControl(new GMapTypeControl());
        geocoder = new GClientGeocoder();
        gdir = new GDirections(map, document.getElementById("directions"));
        GEvent.addListener(gdir, "load", onGDirectionsLoad);
        GEvent.addListener(gdir, "error", handleErrors);

        GEvent.addDomListener(from_address_input, "change", function() { document.getElementById('start_lat').value = ''; document.getElementById('start_long').value = ''; setDirections(); });
        GEvent.addDomListener(to_address_input, "change", function() { document.getElementById('end_lat').value = ''; document.getElementById('end_long').value = ''; setDirections(); });
      }
      if(document.getElementById('driver_radio').checked == true) {
        document.getElementById('driver_options').style.display = '';
      }
      
      if(from_address_input.value != 'Starting Address' && from_address_input.value != '')
        from_address_input.style.color = 'black';
      if(to_address_input.value != 'Ending Address' && to_address_input.value != '')
        to_address_input.style.color = 'black';

      setDirections();
      initialized = true;
    }

    function handleSubmit() {

      if(!is_real_submit) {
        setDirections();
        return false;
      }

      var error_text = '';
      // check if the inputs are valid;
      if(document.getElementById('start_lat').value == '') {
        var from_address = from_address_input.value;
        if(from_address == 'Starting Address' || from_address == '')
          error_text += 'Please provide a valid starting address. (Make sure you have pressed the "Look Up" button).\n';
        else {
          setDirections();
          return false;
        }
      }

      if(document.getElementById('end_lat').value == '') {
        var to_address = to_address_input.value;
        if(to_address == 'Ending Address' || to_address == '')
          error_text += 'Please provide a valid ending address. (Make sure you have pressed the "Look Up" button).\n';
        else {
          setDirections();
          return false;
        }
      }

      // FIXME: Add checks for time windows and other required fields

      if(error_text == '')
        return true;

      // if there were errors, update the errorbox
      var errorbox = document.getElementById('errorbox');
      while(errorbox.hasChildNodes())
        errorbox.removeChild(errorbox.firstChild);

      while(error_text != null && error_text != '') {
        var this_error;
        if(error_text.indexOf('\n') == -1) {
          this_error = error_text;
          error_text = null;
        }
        else {
          this_error = error_text.substring(0, error_text.indexOf('\n'));
          error_text = error_text.substring(error_text.indexOf('\n') + 1);
        }
        errorbox.appendChild(document.createTextNode(this_error));
        errorbox.appendChild(document.createElement('br'));
        errorbox.style.display = '';
      }
      return false;
    }

    function setIfEmpty(input, text) {
      if(input.value == '') {
        input.value = text;
        input.style.color = '#7F7F7F';
        input.type = 'text';
        if(text == 'Starting Address') {
          document.getElementById('start_lat').value = '';
          document.getElementById('start_long').value = '';
          setDirections();
        }
        else if(text == 'Ending Address') {
          document.getElementById('end_lat').value = '';
          document.getElementById('end_long').value = '';
          setDirections();
        }
      }
    }
    //]]>
  </script>
 </head>
 <body onload="initialize()" onunload="GUnload()">

  <?php require 'topmenu.inc'; ?>

  <form action="<?=$_SERVER['PHP_SELF']?>" method="post" id="new_ride_form" onsubmit="return handleSubmit();">
   <div class="bigbox" style="float: left; width: 350px; margin-bottom: 10px;">
    <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
    <div class="content">
     New Ride<br />
     <span class="normaltext">
      <input type="radio" value="Rider" name="driver_or_rider" id="rider_radio" <?php if(!isset($_POST['driver_or_rider']) or $_POST['driver_or_rider'] == 'Rider') { ?>checked="checked" <?php } ?> onclick="var driver_opts = document.getElementById('driver_options'); if(this.checked == true) { driver_opts.style.display = 'none'; } else { driver_opts.style.display = ''; }" />
      <label for="rider_radio">Rider</label>
      <input type="radio" value="Driver" name="driver_or_rider" <?php if(isset($_POST['driver_or_rider']) and $_POST['driver_or_rider'] == 'Driver') { ?> checked="checked" <?php } ?> onclick="var driver_opts = document.getElementById('driver_options');  if(this.checked == true) { driver_opts.style.display = ''; } else { driver_opts.style.display = 'none'; }" id="driver_radio" />
      <label for="driver_radio">Driver</label>
     </span>
     <br />
     <input type="text" class="text" name="start_addr" <?php if(isset($_POST['start_lat']) and $_POST['start_lat'] != '') { ?> style="color: black; text-align: left;" value="<?=$_POST['start_addr']?>" <?php } else { ?> value="Starting Address" <?php } ?> size="30" onfocus="acceptInput(this, 'Starting Address', 'text');" onblur="setIfEmpty(this, 'Starting Address');" id="from_address" style="text-align: left" /><br />
     <input type="hidden" id="start_lat" name="start_lat" value="<?=$_POST['start_lat']?>" />
     <input type="hidden" id="start_long" name="start_long" value="<?=$_POST['start_long']?>" />
     <input type="text" class="text" name="end_addr" <?php if(isset($_POST['end_lat']) and $_POST['end_lat'] != '') { ?> style="color: black; text-align: left;" value="<?=$_POST['end_addr']?>" <?php } else { ?> value="Ending Address" <?php } ?> size="30" onfocus="acceptInput(this, 'Ending Address', 'text');" onblur="setIfEmpty(this, 'Ending Address');" id="to_address" style="text-align: left" /><br />
     <input type="hidden" id="end_lat" name="end_lat" value="<?=$_POST['end_lat']?>" />
     <input type="hidden" id="end_long" name="end_long" value="<?=$_POST['end_long']?>" />
     <input type="submit" class="button" value="Look Up" /><br />
     <br />
     <table cellpadding="0" cellspacing="0" style="width: 100%;">
      <tr>
       <td class="normaltext">Route Title:</td>
       <td><input type="text" class="text" name="route_title" id="route_title" value="<?=$_POST['route_title']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td colspan="2" class="headingtext" style="padding-top: 15px;">Date/Time Preferences</td>
      </tr>
      <tr id="route_optimal_distance_gui">
       <td class="normaltext">Est. Route Distance: </td>
       <td>
        <input class="label" readonly="readonly" id="route_optimal_distance_display" />
        <input type="hidden" id="route_optimal_distance" name="route_optimal_distance" />
       </td>
      </tr>
      <tr id="route_optimal_duration_gui">
       <td class="normaltext">Est. Route Duration: </td>
       <td>
        <input class="label" readonly="readonly" id="route_optimal_duration_display" />
        <input type="hidden" id="route_optimal_duration" name="route_optimal_duration" />
       </td>
      </tr>
      <tr>
       <td class="normaltext" colspan="2" style="text-align: center; padding-top: 5px;">I want to leave sometime between:</td>
      </tr>
      <tr>
       <td class="normaltext">Earliest Departure: </td><td><input type="text" class="text" name="route_leave_time_earliest" value="<?=$_POST['route_leave_time_earliest']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Latest Departure: </td><td><input type="text" class="text" name="route_leave_time_latest" value="<?=$_POST['route_leave_time_latest']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext" colspan="2" style="text-align: center; padding-top: 5px;">I want to arrive sometime between:</td>
      </tr>
      <tr>
       <td class="normaltext">Earliest Arrival: </td><td><input type="text" class="text" name="route_arrive_time_earliest" value="<?=$_POST['route_arrive_time_earliest']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Latest Arrival: </td><td><input type="text" class="text" name="route_arrive_time_latest" value="<?=$_POST['route_arrive_time_latest']?>" style="color: black;" /></td>
      </tr>
     </table>
     <br />
     <input type="hidden" name="optional_prefs_input" id="optional_prefs_input" <?php if(isset($_POST['optional_prefs_input']) and $_POST['optional_prefs_input'] == 'open') { ?> value="open" <?php } else { ?> value="closed" <?php } ?> />
     <input type="button" class="button" onclick="var prefs_input = document.getElementById('optional_prefs_input'); var prefs = document.getElementById('optional_prefs'); if(optional_prefs_input.value =='open') { prefs.style.display='none'; prefs_input.value = 'closed'; } else { prefs.style.display=''; prefs_input.value = 'open'; }" value="Optional Preferences" /><br />
     <table cellpadding="0" cellspacing="0" style="width: 100%; <?php if(!isset($_POST['optional_prefs_input']) or $_POST['optional_prefs_input'] == 'closed') { ?> display: none; <?php } ?>" id="optional_prefs">
      <tr>
       <td class="normaltext">Minimum Age: </td><td><input type="text" class="text" name="route_pref_age_min" value="<?=$_POST['route_pref_age_min']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Maximum Age: </td><td><input type="text" class="text" name="route_pref_age_max" value="<?=$_POST['route_pref_age_max']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Gender: </td>
       <td>
        <select name="route_pref_gender_id">
         <option value="" <?php if(!isset($_POST['route_pref_gender_id']) or $_POST['route_pref_gender_id'] == "") { echo 'selected="selected"'; }?>>Any</option>
<?php
	$query = 'SELECT gender_id, gender FROM genders';
	$result = mysql_query($query);
	while($row = mysql_fetch_assoc($result)) {
		echo '         <option value="' . $row['gender_id'] . '"';
		if($_POST['route_pref_gender_id'] == $row['gender_id']) {
			echo 'selected="selected"';
		}
		echo '>' . $row['gender'] . "</option>\n";
	}
?>
        </select>
       </td>
      </tr>
      <tr>
       <td class="normaltext">Minimum Rating: </td><td><input type="text" class="text" name="route_pref_rating_min" value="<?=$_POST['route_pref_rating_min']?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Comment: </td><td><textarea class="text" name="route_comment" style="color: black;"><?=$_POST['route_comment']?></textarea></td>
      </tr>
     </table>
     <br />
     <input type="button" class="button" value="Confirm Ride" onclick="var theform = document.getElementById('new_ride_form'); is_real_submit = true; if(handleSubmit()) { theform.submit(); } is_real_submit = false;" name="new_route_submit" />
    </div>
    <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
    <div class="fineprint"> </div>
   </div>

   <div class="bigbox" style="clear: both; float: left; width: 350px; display: none;" id="driver_options">
    <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
    <div class="content">
     Driver Options<br />
     <table cellpadding="0" cellspacing="0" style="width: 80%;">
      <tr><td style="height: 15px;"></td></tr>
      <tr>
       <td class="normaltext">Passenger Capacity: </td><td><input type="text" class="text" name="route_pref_capacity" value="<?=$_POST['route_pref_capacity']?>" style="color: black;" /></td>
      </tr>
     </table>
    </div>
    <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
    <div class="fineprint"> </div>
   </div>
  </form>
  <div style="margin-left: 370px; margin-right: 20px; <?php if(!isset($error_msg)) { ?> display: none; <?php } ?>" class="errorbox" id="errorbox"><?=$error_msg?></div>
  <div id="map_canvas" style="border: 1px solid black; height: 90%; margin-left: 370px; margin-right: 20px; margin-top: 20px;"></div>
  <div id="directions" style="display: none;"></div>
 </body>
</html>
