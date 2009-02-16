<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php
	if(isset($_POST['new_user_post'])) {
		if($_POST['user_first_name'] == "") {
			$error_msg .= 'Please fill in your first name.<br />';
		}
		if($_POST['user_last_name'] == "") {
			$error_msg .= 'Please fill in your last name.<br />';
		}
		if($_POST['user_email'] == "") {
			$error_msg .= 'Please fill in your E-Mail Address.<br />';
		}
		if($_POST['password'] == "") {
			$error_msg .= 'Please fill in your desired password.<br />';
		}
		if($_POST['confirm_password'] == "") {
			$error_msg .= 'Please confirm your password.<br />';
		}

		if(!isset($error_msg)) {
			if(strlen($_POST['user_first_name']) > 20 || strlen($_POST['user_last_name']) > 20) {
				$error_msg .= 'Sorry, names are restricted to twenty characters or fewer.<br />';
			}
			else if(!eregi('^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4})$', $_POST['user_email'])) {
				$error_msg .= $_POST['user_email'] . ' does not appear to be a valid email address.  Please use a different one.<br />';
			}
			else if($_POST['password'] != $_POST['confirm_password']) {
				$error_msg .= 'Passwords do not match. Please re-enter them.<br />';
			}
		}

		if(!isset($error_msg)) {
			$query = 'SELECT user_id FROM users WHERE email_addr = \'' . $_POST['user_email'] . '\'';
			$result = mysql_query($query);
			if($result and mysql_num_rows($result) != 0) {
				$error_msg .= 'A user with that email address has already registered.<br />';
			}

			if(!isset($error_msg)) {
				$query = 'SELECT user_id FROM users_pending_validation WHERE email_addr = \'' . $_POST['user_email'] . '\'';
				$result = mysql_query($query);
				if($result and mysql_num_rows($result) != 0) {
					$row = mysql_fetch_assoc($result);

					// if the key has expired, delete it
					if(strtotime($row['key_sent_date']) + 3600*48 < time()) {
						$query = 'DELETE FROM users_pending_validation WHERE email_addr = \'' . $row['email_addr'] . '\'';
						mysql_query($query);
					}
					else {
						$error_msg .= 'A user with that email address has already registered.<br />';
					}
				}
			}

			if(!isset($error_msg)) {
				list($usec1, $sec) = explode(" ", microtime());
				list($usec2, $sec) = explode(" ", microtime());
				$query = 'INSERT INTO users_pending_validation (validation_key, key_sent_date, first_name, last_name, email_addr, password) VALUES (SHA1(\'' . $usec1 . $_POST['user_email'] . $usec2 . '\'), NOW(), \'' . $_POST['user_first_name'] . '\', \'' . $_POST['user_last_name'] . '\', \'' . $_POST['user_email'] . '\', PASSWORD(\'' . $_POST['password'] . '\'))';
				if(!mysql_query($query)) {
					$error_msg .= 'There was an internal error creating your account.  Please try again soon.<br />';
				}
				else {
					// Grab the validation key to email them with
					$query = 'SELECT validation_key FROM users_pending_validation WHERE email_addr = \'' . $_POST['user_email'] . '\'';
					$result = mysql_query($query);
					$row = mysql_fetch_assoc($result);
					$valkey = $row['validation_key'];

					// Construct the email message
					$email_message = "Thank you for joining the rideshare community.<BR><BR>Please do not respond to this email.<BR>Please click the following link to validate your account: <a href=\"http://{$_SERVER['SERVER_NAME']}/account_validation.php?valkey=$valkey\">Validate your account</a>";
					$email_address = $_POST['user_email'];
					$email_subject = "Rideshare account validation";
					$email_header = "From: account_management@rideshare.ece.utexas.edu\n";
					$email_header .= "Content-Type: text/html; charset=iso-8859-1\nContent-Transfer-Encoding: 8bit";
					mail($email_address, $email_subject, $email_message, $email_header);

					// Notify the user the message has been sent
					$message .= 'A confirmation email has been sent to the specified email address.  It will expire after two days.<br />';
				}
			}
		}
	}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
 <head>
  <title>Rideshare - Create Account</title>
  <link rel="Stylesheet" href="style.css" />
 </head>
 <body>
  <div class="logo">
   <img src="images/rideshare.png" alt="Rideshare" />
  </div>

<?php
	if(isset($error_msg)) {
?>
  <div class="errorbox"><?=$error_msg?></div>
<?php
	}
	else if(isset($message)) {
?>
  <div class="messagebox"><?=$message?></div>
<?php
	}
?>

  <div class="bigbox" style="margin-bottom: 100px;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <form action="<?=$_SERVER['PHP_SELF']?>" method="post">
    <div class="content">
     New Account Creation<br />
     <span class="normaltext">Please fill in the fields below:</span><br />
     <table cellpadding="0" cellspacing="0" style="width: 80%; margin-left: auto; margin-right: auto;">
      <tr>
       <td class="normaltext">First Name: </td><td class="normaltext" style="text-align: center; padding-bottom: 5px;"><input type="text" class="text" style="color: black;" name="user_first_name" value="<?=$_POST['user_first_name']?>" /></td>
      </tr>
      <tr>
       <td class="normaltext">Last Name: </td><td class="normaltext" style="text-align: center; padding-bottom: 5px;"><input type="text" class="text" style="color: black;" name="user_last_name" value="<?=$_POST['user_last_name']?>" /></td>
      </tr>
      <tr>
       <td class="normaltext">Email Address: </td><td class="normaltext" style="text-align: center;"><input type="text" class="text" style="color: black;" name="user_email" value="<?=$_POST['user_email']?>" /></td>
      </tr>
      <tr>
       <td id="pass_text" class="normaltext">Password: </td>
       <td><input type="password" class="text" style="color: black;" name="password" /></td>
      </tr>
      <tr>
       <td id="pass_text" class="normaltext">Confirm Password: </td>
       <td><input type="password" class="text" style="color: black;" name="confirm_password" /></td>
      </tr>
     </table>
     <input type="submit" value="Submit" class="button" name="new_user_post" />
    </div>
   </form>
   <div class="cornerImage bl" style="clear: both">&nbsp;</div> <div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&copy; Rideshare 2008</div>
  </div>

 </body>
</html>
