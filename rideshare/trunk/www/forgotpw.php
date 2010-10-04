<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php
	if(isset($_POST['forgotpw_submit'])) {
		if(!isset($_POST['email_addr'])) {
			$error_msg .= 'Please fill in your email address.<br />';
		}

		if(!isset($error_msg)) {
			$query = 'SELECT user_id, email_addr FROM users WHERE email_addr = \'' . $_POST['email_addr'] . '\'';
			$result = mysql_query($query);
			if(!$result or mysql_num_rows($result) == 0) {
				$error_msg .= 'That email address is not in our database.<br />';
			}
			else {
				$row = mysql_fetch_assoc($result);
				list($usec1, $sec) = explode(" ", microtime());
				list($usec2, $sec) = explode(" ", microtime());
				$new_password = substr(sha1($usec1 . rand() . $usec2), 0, 8);
				$query = 'UPDATE users SET password = PASSWORD(\'' . $new_password . '\') WHERE user_id = \'' . $row['user_id'] . '\'';
				mysql_query($query);

				$email_address = $row['email_addr'];
				$email_subject = "Reset Password";
				$email_header = "From: account_management@rideshare.ece.utexas.edu\n";
				$email_header .= "Content-Type: text/html; charset=iso-8859-1\nContent-Transfer-Encoding: 8bit";
				$email_message = "This message has been automatically generated. Please do not respond to it. <BR><BR>Your password has been reset to $new_password <BR> Please login and change it to something more memorable";
				mail($email_address, $email_subject, $email_message, $email_header);

				$message .= 'An email containing your reset password has been sent to your email address. Please proceed to the <a href="index.php">Login page</a><br />';
			}
		}
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
     Forgotten Password<br />
     <span class="normaltext">Please fill in your E-Mail address below:</span>
     <input type="text" class="text" style="text-align: left;" name="email_addr" value="E-Mail Address" onfocus="acceptInput(this, 'E-Mail Address', 'text');" onblur="setIfEmpty(this, 'E-Mail Address');" /><br />
     <input type="submit" value="Submit" class="button" name="forgotpw_submit" />
    </div>
   </form>
   <div class="cornerImage bl">&nbsp;</div><div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&copy; Copyright 2008</div>
  </div>

 </body>
</html>
<?php require_once 'closedb.inc'; ?>
