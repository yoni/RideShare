<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php

	if(isset($_COOKIE['user_id'])) {
		$query = 'SELECT users.user_id FROM users WHERE users.user_id = \'' . $_COOKIE['user_id'] . '\' AND users.password = \'' . $_COOKIE['password'] . '\'';
		$result = mysql_query($query);
		if(mysql_num_rows($result) > 0) {
			header("Location: member.php");
			die();
		}
	}

	if(isset($_POST['login_attempt'])) {
		if($_POST['emailaddr'] != '' && $_POST['password'] != '') {
			$query = 'SELECT users.user_id, users.password FROM users WHERE users.email_addr = \'' . $_POST['emailaddr'] . '\' AND users.password = PASSWORD(\'' . $_POST['password'] .'\')';
			$result = mysql_query($query);
			if(!$result or mysql_num_rows($result) == 0) {
				$error_msg .= 'Invalid email address or password.';
			} else {
				$row = mysql_fetch_assoc($result);
				session_regenerate_id();
				$error_msg .= " - " . $row['user_id'] . " - ";
				setcookie("user_id", $row['user_id'], time() + 1800);
				setcookie("password", $row['password'], time() + 1800);
				session_write_close();
				header('Location: member.php');
				die();
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
?>

  <div class="bigbox" style="margin-bottom: 100px;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <form action="<?=$_SERVER['PHP_SELF']?>" method="post" onsubmit="return form_check();">
    <div class="content">
     Welcome to Rideshare<br />Please log in to your account:<br />
     <input type="text" class="text" name="emailaddr" value="Email Address" onfocus="acceptInput(this, 'Email Address', 'text');" onblur="setIfEmpty(this, 'Email Address');" style="text-align: left" /><br />
     <input type="text" class="text" name="password" value="Password" onfocus="acceptInput(this, 'Password', 'password');" onblur="setIfEmpty(this, 'Password');" style="text-align: left" /><br />
     <input type="submit" class="button" name="login_attempt" value="Submit" /><br />
    </div>
   </form>
   <div class="cornerImage bl">&nbsp;</div><div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&copy; Copyright 2008</div>
  </div>

  <div style="width: 33%; float: left;">
  <div class="box" style="float: left;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content"><a href="about.php">About Rideshare</a></div>
   <div class="cornerImage bl">&nbsp;</div><div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&nbsp;</div>
  </div>
  </div>

  <div style="width: 33%; float: left;">
  <div class="box" style="margin-left: auto; margin-right: auto;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content"><a href="forgotpw.php">Forgot My Password</a></div>
   <div class="cornerImage bl">&nbsp;</div><div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&nbsp;</div>
  </div>
  </div>

  <div style="width: 33%; float: right;">
  <div class="box" style="float: right;">
   <div class="cornerImage tl">&nbsp;</div><div class="cornerImage tr">&nbsp;</div>
   <div class="content"><a href="create_account.php">Create Account</a></div>
   <div class="cornerImage bl">&nbsp;</div><div class="cornerImage br">&nbsp;</div>
   <div class="fineprint">&nbsp;</div>
  </div>
  </div>

 </body>
</html>
<?php require_once 'closedb.inc'; ?>
