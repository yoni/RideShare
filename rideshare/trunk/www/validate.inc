<?php
	if(!isset($_COOKIE['user_id'])) {
		header('Location: index.php');
		die();
	}

	// Make sure they're a real user
	$query = 'SELECT * FROM users WHERE users.user_id = \'' . $_COOKIE['user_id'] . '\' AND users.password = \'' . $_COOKIE['password'] . '\' LIMIT 1';
	$result = mysql_query($query);
	if(!$result or mysql_num_rows($result) == 0) {
		header("Location: index.php");
		die();
	}

	$row = mysql_fetch_assoc($result);
	setcookie("user_id", $row['user_id'], time() + 1800);
	setcookie("password", $row['password'], time() + 1800);
	$user_id = $row['user_id'];
	$user_name = $row['first_name'] . ' ' . $row['last_name'];
	$user_email = $row['email_addr'];
	$user_age = $row['age'];
	$user_gender_id = $row['gender_id'];
?>
