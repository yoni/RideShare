<?php
	function array_clean(&$value) {
		if (ini_get('magic_quotes_gpc')) {
			$value = stripslashes($value);
		}
		mysql_real_escape_string($value);
	}
	array_walk_recursive($_POST, 'array_clean');
	array_walk_recursive($_GET, 'array_clean');
	array_walk_recursive($_COOKIE, 'array_clean');
	unset($error_msg, $GLOBALS['error_msg'], $warning_msg, $GLOBALS['warning_msg'], $message, $GLOBALS['message']);
?>
