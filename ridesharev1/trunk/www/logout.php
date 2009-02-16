<?php
	setcookie('user_id', -1, time() - 100);
	setcookie('password', -1, time() - 100);
	header("Location: index.php");
	die();
?>
