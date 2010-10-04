<?php 
require_once 'RssDump.php';
require_once 'opendb.inc';
require_once 'rsa.php';

if(isset($_GET['u']) && isset($_GET['x']))
{
	$uId   = $_GET['u'];
	$xId   = $_GET['x'];
	$query = 'SELECT rsaN,rsaE,rsaD FROM users WHERE user_id='.$uId;
	$submission_result = mysql_query($query);

	if($submission_result and mysql_num_rows($submission_result) > 0) 
	{
		$row = mysql_fetch_assoc($submission_result);
		$n = $row['rsaN'];
		$e = $row['rsaE'];
		$d = $row['rsaD'];
		$key = array($n, $e, $d);
		$decryptedUserId = getDecryptUserId($xId, $key);

		if ($decryptedUserId == $uId)
		{
			dumpRssFeed($uId,$xId);
		}
		else 
		{
			echo "Invalid Feed";
		}
	}
}
else 
{
	echo "Invalid Feed";
}

function dumpRssFeed($userId, $xId)
{
	$rssGen = new RssGenerator($userId, $xId); 

	$rssGen->dumpHeader();
	$rssGen->dumpAllMatches();
	$rssGen->dumpEpilogue();
}

?>
