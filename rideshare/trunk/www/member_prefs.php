<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'validate.inc'; ?>
<?php
	if(isset($_POST['save_prefs'])) {
		if($_POST['age_min'] != "" and (!ctype_digit($_POST['age_min']) or intval($_POST['age_min']) > 80)) {
			unset($_POST['age_min']);
			$error_msg .= 'Minimum Age must be a positive whole number less than 80<br />';
		}
		if(intval($_POST['age_min']) == 0) {
			unset($_POST['age_min']);
			$warning_msg .= 'Notice: A minimum age of zero is the same as no minimum age restriction.<br />';
		}
		if($_POST['age_max'] != "" and !ctype_digit($_POST['age_max'])) {
			unset($_POST['age_max']);
			$error_msg .= 'Maximum Age must be a positive whole number<br />';
		}
		if(intval($_POST['age_max']) > 80) {
			unset($_POST['age_max']);
			$warning_msg .= 'Notice: A maximum age above 80 is nearly the same as no maximum age restriction.<br />';
		}
		if(intval($_POST['age_max']) < intval($_POST['age_min'])) {
			unset($_POST['age_max'], $_POST['age_min']);
			$error_msg .= 'Minimum age must be less than or equal to maximum age<br />';
		}
		if($_POST['rating_min'] != "") {
			if(!preg_match('/^([0-9]+\.?[0-9]*)|([0-9]*\.?[0-9]+)$/', $_POST['rating_min'])) {
				unset($_POST['rating_min']);
				$error_msg .= 'Minimum Rating must be a positive real number<br />';
			}
			elseif(round(floatval($_POST['rating_min']),2) == 0.0) {
				unset($_POST['rating_min']);
				$warning_msg .= 'Notice: A minimum rating requirement of 0.0 is the same as having no rating requirement.<br />';
			}
			elseif(round(floatval($_POST['rating_min']),2) > 5.0) {
				unset($_POST['rating_min']);
				$error_msg .= 'Rating must be between 0.0 and 5.0<br />';
			}
		}
		if($_POST['gender_id'] != "") {
			if(!ctype_digit($_POST['gender_id'])) {
				unset($_POST['gender_id']);
				$error_msg .= 'Invalid gender selection in preferences<br />';
			}
			else {
				$query = "SELECT gender_id FROM genders WHERE gender_id = '" . mysql_real_escape_string($_POST['gender_id']) . "'";
				$result = mysql_query($query);
				if(!$result or mysql_num_rows($result) == 0) {
					unset($_POST['gender_id']);
					$error_msg .= 'Invalid gender selection in preferences<br />';
				}
			}
		}

		$query = 'SELECT user_id FROM user_prefs WHERE user_id = ' . $user_id;
		$result = mysql_query($query);
		if($_POST['age_min'] == "" and $_POST['age_max'] == "" and $_POST['gender_id'] == "" and $_POST['rating_min'] == "") {
			if($result and mysql_num_rows($result) > 0) {
				$query = 'DELETE FROM user_prefs WHERE user_id = ' . $user_id . ' LIMIT 1';
				$result = mysql_query($query);
			}
		}
		else {
			// create a new entry
			if(!$result or mysql_num_rows($result) == 0) {
				$query = 'INSERT user_prefs SET user_id = ' . $user_id;
				if($_POST['age_min'] != "")
					$query .= ', age_min = \'' . $_POST['age_min'] . '\'';
				if($_POST['age_max'] != "")
					$query .= ', age_max = \'' . $_POST['age_max'] . '\'';
				if($_POST['gender_id'] != "")
					$query .= ', gender_id = \'' . $_POST['gender_id'] . '\'';
				if($_POST['rating_min'] != "")
					$query .= ', rating_min = \'' . $_POST['rating_min'] .'\'';
			}
			// update the entry
			else {
				$query = 'UPDATE user_prefs SET age_min = ';
				if($_POST['age_min'] == "")
					$query .= 'NULL, ';
				else
					$query .= '\'' . $_POST['age_min'] . '\', ';
				$query .= 'age_max = ';
				if($_POST['age_max'] == "")
					$query .= 'NULL, ';
				else
					$query .= '\'' . $_POST['age_max'] . '\', ';
				$query .= 'gender_id = ';
				if($_POST['gender_id'] == "")
					$query .= 'NULL, ';
				else
					$query .= '\'' . $_POST['gender_id'] . '\', ';
				$query .= 'rating_min = ';
				if($_POST['rating_min'] == "")
					$query .= 'NULL ';
				else
					$query .= '\'' . $_POST['rating_min'] . '\' ';
				$query .= 'WHERE user_id = ' . $user_id . ' LIMIT 1';
			}
			$result = mysql_query($query);
			if($result)
				$message .= "Preferences saved.<br />";
		}
	}
	elseif(isset($_POST['save_prof'])) {
		// password checking stuff
		if($_POST['user_old_pass'] != "") {
			$query = 'SELECT * FROM users WHERE user_id=\'' . $user_id . '\' AND password=PASSWORD(\'' . $_POST['user_old_pass'] . '\')';
			$result = mysql_query($query);
			if($result and mysql_num_rows($result) > 0) {
				if($_POST['user_new_pass'] != $_POST['user_confirm_pass'])
					$error_msg .= "New Password and Confirmation are not the same. Please re-enter them.<br />";
				elseif($_POST['user_new_pass'] == "")
					$error_msg .= "Empty passwords are not allowed.<br />";
				else {
					$query = 'UPDATE users SET password = PASSWORD(\'' . $_POST['user_new_pass'] . '\') WHERE user_id = \'' . $user_id .'\'';
					$result = mysql_query($query);
				}
			}
			else
				$error_msg .= "Old Password does not match<br />";
		}


		if($_POST['user_age'] != "" and (!ctype_digit($_POST['user_age']) or intval($_POST['user_age']) > 120)) {
			unset($_POST['user_age']);
			$error_msg .= 'Age must be a positive whole number less than 120.<br />';
		}
		if($_POST['user_gender_id'] != "" and !ctype_digit($_POST['user_gender_id'])) {
			$error_msg .= 'Invalid gender selection in profile<br />';
			unset($_POST['user_gender_id']);
		}

		$query = 'UPDATE users SET age = ';
		if($_POST['user_age'] == "")
			$query .= 'NULL, ';
		else
			$query .= '\'' . $_POST['user_age'] . '\', ';
		$query .= 'gender_id = ';
		if($_POST['user_gender_id'] == "")
			$query .= 'NULL, ';
		else
			$query .= '\'' . $_POST['user_gender_id'] . '\' ';
		$query .= 'WHERE user_id = ' . $user_id . ' LIMIT 1';
		$result = mysql_query($query);

		if($result)
			$message .= "Profile saved.<br />";

		$query = 'SELECT * FROM users WHERE user_id = \'' . $user_id . '\' LIMIT 1';
		$result = mysql_query($query);
		$row = mysql_fetch_assoc($result);
		$user_age = $row['age'];
		$user_gender_id = $row['gender_id'];
	}

	$query = 'SELECT age_min, age_max, gender_id, rating_min FROM user_prefs WHERE user_id = ' . $user_id;
	$result = mysql_query($query);
	if($result and mysql_num_rows($result) > 0) {
		$row = mysql_fetch_assoc($result);
		$age_min = $row['age_min'];
		$age_max = $row['age_max'];
		$gender_id = $row['gender_id'];
		$rating_min = $row['rating_min'];
	}
	else {
		unset($age_min, $GLOBALS['age_min'], $age_max, $GLOBALS['age_max'], $gender_id, $GLOBALS['gender_id'], $rating_min, $GLOBALS['rating_min']);
	}
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

<?php
	if(isset($error_msg)) {
?>
  <div class="errorbox"><?=$error_msg?></div>
<?php
	}
	elseif(isset($warning_msg)) {
?>
  <div class="warningbox"><?=$warning_msg?></div>
<?php
	}
	elseif(isset($message)) {
?>
  <div class="messagebox"><?=$message?></div>
<?php
	}
?>

  <div class="bigbox">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content">
    Your Profile<br />
    <form action="<?=$_SERVER['PHP_SELF']?>" method="post">
     <table cellpadding="0" cellspacing="0" style="width: 80%; margin-left: auto; margin-right: auto;">
      <tr>
       <td class="normaltext">Name: </td><td class="normaltext" style="text-align: center; padding-bottom: 5px;"><?=$user_name?></td>
      </tr>
      <tr>
       <td class="normaltext">Email Address: </td><td class="normaltext" style="text-align: center;"><?=$user_email?></td>
      </tr>
      <tr>
       <td id="pass_text" class="normaltext">Password: </td>
       <td>
        <input type="button" class="button" name="user_old_pass" value="New Password" onclick="this.type='password';this.className='text';this.style.color='black';this.value='';var showme = document.getElementById('newPass'); showme.style.display=''; showme = document.getElementById('confirmPass'); showme.style.display=''; showme = document.getElementById('pass_text');showme.innerHTML='Old Password:';" />
       </td>
      </tr>
      <tr id="newPass" style="display: none;">
       <td class="normaltext">New Password: </td><td><input type="password" class="text" name="user_new_pass" style="color: black;" /></td>
      </tr>
      <tr id="confirmPass" style="display: none;">
       <td class="normaltext">Confirm New Password: </td><td><input type="password" class="text" name="user_confirm_pass" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Age: </td><td><input type="text" class="text" name="user_age" value="<?=$user_age?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Gender: </td>
       <td>
        <select name="user_gender_id">
         <option value="" <?php if(!isset($user_gender_id) or $user_gender_id == "") { echo 'selected="selected"'; }?>>Unspecified</option>
<?php
	$query = 'SELECT gender_id, gender FROM genders';
	$result = mysql_query($query);
	while($row = mysql_fetch_assoc($result)) {
		echo '         <option value="' . $row['gender_id'] . '"';
		if($user_gender_id == $row['gender_id']) {
			echo ' selected="selected"';
		}
		echo '>' . $row['gender'] . "</option>\n";
	}
?>
        </select>
       </td>
      </tr>
     </table>
     <input type="submit" class="button" name="save_prof" value="Update Profile" />
    </form>
   </div>
   <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&nbsp;</div>
  </div>

  <div class="bigbox">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content">
    Matching Preferences<br />
    <form action="<?=$_SERVER['PHP_SELF']?>" method="post">
     <table cellpadding="0" cellspacing="0" style="margin-left: auto; margin-right: auto; width: 80%;">
      <tr>
       <td class="normaltext">Minimum Age: </td><td><input type="text" class="text" name="age_min" value="<?=$age_min?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Maximum Age: </td><td><input type="text" class="text" name="age_max" value="<?=$age_max?>" style="color: black;" /></td>
      </tr>
      <tr>
       <td class="normaltext">Gender: </td>
       <td>
        <select name="gender_id">
         <option value="" <?php if(!isset($gender_id) or $gender_id == "") { echo 'selected="selected"'; }?>>Any</option>
<?php
	$query = 'SELECT gender_id, gender FROM genders';
	$result = mysql_query($query);
	while($row = mysql_fetch_assoc($result)) {
		echo '         <option value="' . $row['gender_id'] . '"';
		if($gender_id == $row['gender_id']) {
			echo ' selected="selected"';
		}
		echo '>' . $row['gender'] . "</option>\n";
	}
?>
        </select>
       </td>
      </tr>
      <tr>
       <td class="normaltext">Minimum Rating: </td><td><input type="text" class="text" name="rating_min" value="<?=$rating_min?>" style="color: black;" /></td>
      </tr>
     </table>
     <input type="submit" class="button" name="save_prefs" value="Update Preferences" />
    </form>
   </div>
   <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&copy; Rideshare 2008</div>
  </div>
 </body>
</html>
