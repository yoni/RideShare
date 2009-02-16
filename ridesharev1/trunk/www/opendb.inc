<?php
$username = 'bmesh_rideshare';
$password = 'PAqvwd853zBe';
$database = 'bmesh_rideshare';

$db_connection = mysql_connect('localhost', $username, $password) or die('Error connecting to mysql');
mysql_select_db($database);
?>
