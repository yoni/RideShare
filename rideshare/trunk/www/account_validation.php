<?php require_once 'rsa.php'; ?>
<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php
	if(isset($_GET['valkey'])) {
		$query = 'SELECT * FROM users_pending_validation WHERE validation_key = \'' . $_GET['valkey'] . '\'';
		$result = mysql_query($query);
		if(!$result or mysql_num_rows($result) == 0) {
			$error_msg .= 'Sorry that validation key must have expired. Please go to the <a href="create_account.php">create new account page</a><br />';
		}

		if(!isset($error_msg)) {
			$row = mysql_fetch_assoc($result);

			if(strtotime($row['key_sent_date']) + (3600*48) < time()) {
				$error_msg .= 'Sorry that validation key must have expired.  Please go to the <a href="create_account.php">create new account page</a><br />';
			}

			// THIS MUST BE DONE EVEN IF ERROR_MSG IS SET (flush expired key)
			// Delete info from pending user table
			$query = 'DELETE FROM users_pending_validation WHERE email_addr = \'' . $row['email_addr'] . '\'';
			mysql_query($query);

			if(!isset($error_msg)) {
				// Insert into users table
				$newKeys = generate_keys(1);
				// rss' private key below
				$rsaN = $newKeys[0];
				$rsaE = $newKeys[1];
				$rsaD = $newKeys[2];
				$query = 'INSERT INTO users (first_name, last_name, email_addr, password, rsaN, rsaE, rsaD) VALUES (\'' . 
					$row['first_name'] . '\', \'' . $row['last_name'] . '\', \'' . $row['email_addr'] . '\', \'' . $row['password'] . '\','
					. "'" . $rsaN. "','" . $rsaE . "','" . $rsaD . "')";
				if(mysql_query($query)) {
					$userId = mysql_insert_id();
					$usersRssUrl = getUsersRssUrl($userId, $newKeys);
					$query = sprintf("UPDATE users SET "
						. " rssurl='%s'"
						. " WHERE user_id=%u",
						$usersRssUrl,
						$userId);
					mysql_query($query);
					$message .= 'Your account has been activated. You may now proceed to the <a href="index.php">login page</a>.<br />';
				}
			}
		}
	}
	else {
		$error_msg .= 'Sorry, this page is for users validating their email addresses. Perhaps you meant to go to the <a href="index.php">login page</a><br />';
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
	elseif(isset($message)) {
?>
	<div class="messagebox"><?=$message?></div>
<?php
	}
?>
 </body>
</html>
