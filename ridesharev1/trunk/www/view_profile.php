<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'validate.inc'; ?>
<?php
	$query = "SELECT DISTINCT matches.solution_id, matches.match_id FROM users, route_submissions, matches WHERE matches.route_submission_id = route_submissions.route_submission_id AND route_submissions.user_id = users.user_id AND users.user_id = '" . $user_id . "'";
	$result = mysql_query($query);
	if(!$result or mysql_num_rows($result) == 0) {
		header("Location: member.php");
		die();
	}

	if(!isset($_GET['user_id']) or $_GET['user_id'] == '' or !ctype_digit($_GET['user_id'])) {
		header("Location: member.php");
		die();
	}
	$looking_at_uid = $_GET['user_id'];

	if($looking_at_uid == $user_id) {
		header("Location: member_prefs.php");
		die();
	}

	$found_it = false;

	while($row = mysql_fetch_assoc($result)) {
		$solution_id = $row['solution_id'];
		$match_id = $row['match_id'];
		$query = "SELECT DISTINCT route_submissions.user_id FROM route_submissions, matches WHERE matches.route_submission_id = route_submissions.route_submission_id AND matches.match_id = $match_id AND matches.solution_id = $solution_id AND route_submissions.user_id = $looking_at_uid";
		$uid_result = mysql_query($query);
		if($uid_result and mysql_num_rows($uid_result > 0)) {
			$found_it = true;
			break;
		}
	}

	// Invalid look
	if($found_it == false) {
		header("Location: member.php");
		die();
	}

	$query = "SELECT users.first_name, users.last_name, users.email_addr, genders.gender, users.age FROM users, genders WHERE users.gender_id = genders.gender_id AND users.user_id = $looking_at_uid";
	$result = mysql_query($query);

	// Invalid UID..
	if(!$result or mysql_num_rows($result) == 0) {
		header("Location: member.php");
		die();
	}

	$row = mysql_fetch_assoc($result);
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>Ride Share</title>
  <link rel="Stylesheet" href="style.css" />
  <script type="text/javascript" src="form.js"></script>
 </head>
 <body>

  <?php require 'topmenu.inc'; ?>

  <div class="bigbox">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content">
    Member Profile<br />
    <table cellpadding="0" cellspacing="0" style="width: 80%; margin-left: auto; margin-right: auto;">
     <tr>
      <td class="normaltext">Name: </td><td class="normaltext" style="text-align: center; padding-bottom: 5px;"><?=$row['first_name']." ".$row['last_name']?></td>
     </tr>
     <tr>
      <td class="normaltext">Email Address: </td><td class="normaltext" style="text-align: center;"><?=$row['email_addr']?></td>
     </tr>
     <tr>
      <td class="normaltext">Age: </td><td class="normaltext" style="text-align: center;"><?=$row['age']?></td>
     </tr>
     <tr>
      <td class="normaltext">Gender: </td><td class="normaltext" style="text-align: center;"><?=$row['gender']?></td>
     </tr>
    </table>
    <input type="button" value="Go Back" onclick="javascript: history.go(-1)" />
   </div>
   <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&copy; Rideshare 2008</div>
  </div>
 </body>
</html>
