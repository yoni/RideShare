<?php require_once 'opendb.inc'; ?>
<?php require_once 'input_clean.inc'; ?>
<?php require_once 'rsa.php'; ?>
<?php
/*
 * This script will go through all users and assign them a new rsa keypair and rssurl
 * DANGEROUS!
 */
/*
for ($i=1; $i<=26; $i++) 
{
	$keys = generate_keys(1);
	$n = $keys[0];
	$e = $keys[1];
	$d = $keys[2];
	$rssUrl = getUsersRssUrl($i, $keys);
	$userId = getDecryptUserId($rssUrl, $keys);
	echo "rssurl: " .$rssUrl . "\n";
	echo "rssurl: " .base64_decode($rssUrl) . "\n";

	echo "userId: " .$userId . "\n";
	$query = sprintf("UPDATE users SET "
		. " rsaN=%u, rsaE=%u, rsaD=%u, rssurl='%s'"
		. " WHERE user_id=%u",
		mysql_real_escape_string($n),
		mysql_real_escape_string($e),
		mysql_real_escape_string($d),
		$rssUrl,
		mysql_real_escape_string($i));
		
	$submission_result = mysql_query($query);
}
 */
		

?>

