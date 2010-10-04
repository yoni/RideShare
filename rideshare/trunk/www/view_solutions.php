<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'validate.inc'; ?>
<?php require_once 'admin.inc'; ?>
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
      
      place = gdir.getGeocode(gdir.getNumGeocodes()-1);
      ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
      ride_details.insertBefore(document.createTextNode(place.address), ride_details.firstChild);
      bold_text = document.createElement('b');
      bold_text.appendChild(document.createTextNode('To: '));
      ride_details.insertBefore(bold_text, ride_details.firstChild);

      place = gdir.getGeocode(0);
      ride_details.insertBefore(document.createElement('br'), ride_details.firstChild);
      ride_details.insertBefore(document.createTextNode(place.address), ride_details.firstChild);
      bold_text = document.createElement('b');
      bold_text.appendChild(document.createTextNode('From: '));
      ride_details.insertBefore(bold_text, ride_details.firstChild);

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
    function select(listentry, points, timewindows) {
      if(selected != null && selected != listentry)
        selected.style.backgroundColor='#f8d6ba';
      listentry.style.backgroundColor='#f8e4d4';
      selected = listentry;
      map_canvas.style.height = '85%';
      gdir.load(points);
      clearRideDetails();
      var bold_text;
      bold_text = document.createElement('b');
      bold_text.appendChild(document.createTextNode('Departing between: '));
      ride_details.appendChild(bold_text);
      ride_details.appendChild(document.createTextNode(timewindows[0] + ' and ' + timewindows[1]));
      ride_details.appendChild(document.createElement('br'));
      bold_text = document.createElement('b');
      bold_text.appendChild(document.createTextNode('Arriving between: '));
      ride_details.appendChild(bold_text);
      ride_details.appendChild(document.createTextNode(timewindows[2] + ' and ' + timewindows[3]));
      ride_details.appendChild(document.createElement('br'));
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
    Solutions<br />
    <div class="normaltext" style="max-height: 600px; overflow-y: auto">
<?php
	$query = "SELECT solution_id, optimizer, calculated FROM solutions ORDER BY calculated DESC";
	$result = mysql_query($query);
	if($result) {
		$have_labeled_first_child = false;
		while($row = mysql_fetch_assoc($result)) {
			echo '     <div class="listbox" onmouseover="highlight(this)" onmouseout="dehighlight(this)" onclick="select(this)"';
			if(!$have_labeled_first_child) {
				echo ' id="first_ride_in_list"';
				$have_labeled_first_child = true;
			}
			echo '>Created: ' . $row['calculated'] . '<br />';
			echo "Algorithm: " . $row['optimizer'] . '<br />';
			echo '<a href="view_solution.php?solution_id=' . $row['solution_id'] . '" style="text-align: center; text-decoration: underline; display: block; margin-top: 5px;">Explore Solution</a>';
			echo "</div>\n";
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
