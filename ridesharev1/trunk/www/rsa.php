<?
/* 
 *
 * *v.1.3 [2 Sep 2002]
 *
 * * Rivest/Shamir/Adelman (RSA) compatible functions
 * * to generate keys and encode/decode plaintext messages.  
 * * Plaintext must contain only ASCII(32) - ASCII(126) characters.
 *
 * *Send questions and suggestions to Ilya Rudev <www <at> polar-lights <dot> com> (Polar Lights Labs)
 *
 * *most part of code ported from different
 * *C++,  JS and Flash
 * *RSA examples found in books and in the net :)
 *
 * *supplied with Hacker Hunter authentication system.
 * *http://www.polar-lights.com/hackerhunter/
 *
 * *It is distributed in the hope that it will be useful,  but
 * *WITHOUT ANY WARRANTY; without even the implied warranty of
 * *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * *See the GNU General Public License for more details.
 *
 * *With a great thanks to:
 * *Glenn Haecker <ghaecker <at> idworld <dot> net>
 * *Segey Semenov <sergei2002 <at> mail <dot> ru>
 * *Suivan <ssuuii <at> gmx <dot> net>
 * */

/*random generator seed */
mt_srand((double)microtime()*1000000);

/*
 * * Prime numbers table
 * * 570 prime numbers (Array can not be be enlarged)
 * * 4507, 4513 is the smallest and 9521, 9533 is the largest pair
 * * Still have no time to find why 9521, 9533 is the largest - sorry :)
 * */
$primes = array (4507,  4513,  4517,  4519,  4523,  4547,  4549,  4561,  4567,  4583,  4591,  4597,
	4603,  4621,  4637,  4639,  4643,  4649,  4651,  4657,  4663,  4673,  4679,  4691,  4703,  4721,  4723,  4729,  4733,  4751,
	4759,  4783,  4787,  4789,  4793,  4799,  4801,  4813,  4817,  4831,  4861,  4871,  4877,  4889,  4903,  4909,  4919,  4931,
	4933,  4937,  4943,  4951,  4957,  4967,  4969,  4973,  4987,  4993,  4999,  5003,  5009,  5011,  5021,  5023,  5039,  5051,
	5059,  5077,  5081,  5087,  5099,  5101,  5107,  5113,  5119,  5147,  5153,  5167,  5171,  5179,  5189,  5197,  5209,  5227,
	5231,  5233,  5237,  5261,  5273,  5279,  5281,  5297,  5303,  5309,  5323,  5333,  5347,  5351,  5381,  5387,  5393,  5399,
	5407,  5413,  5417,  5419,  5431,  5437,  5441,  5443,  5449,  5471,  5477,  5479,  5483,  5501,  5503,  5507,  5519,  5521,
	5527,  5531,  5557,  5563,  5569,  5573,  5581,  5591,  5623,  5639,  5641,  5647,  5651,  5653,  5657,  5659,  5669,  5683,
	5689,  5693,  5701,  5711,  5717,  5737,  5741,  5743,  5749,  5779,  5783,  5791,  5801,  5807,  5813,  5821,  5827,  5839,
	5843,  5849,  5851,  5857,  5861,  5867,  5869,  5879,  5881,  5897,  5903,  5923,  5927,  5939,  5953,  5981,  5987,  6007,
	6011,  6029,  6037,  6043,  6047,  6053,  6067,  6073,  6079,  6089,  6091,  6101,  6113,  6121,  6131,  6133,  6143,  6151,
	6163,  6173,  6197,  6199,  6203,  6211,  6217,  6221,  6229,  6247,  6257,  6263,  6269,  6271,  6277,  6287,  6299,  6301,
	6311,  6317,  6323,  6329,  6337,  6343,  6353,  6359,  6361,  6367,  6373,  6379,  6389,  6397,  6421,  6427,  6449,  6451,
	6469,  6473,  6481,  6491,  6521,  6529,  6547,  6551,  6553,  6563,  6569,  6571,  6577,  6581,  6599,  6607,  6619,  6637,
	6653,  6659,  6661,  6673,  6679,  6689,  6691,  6701,  6703,  6709,  6719,  6733,  6737,  6761,  6763,  6779,  6781,  6791,
	6793,  6803,  6823,  6827,  6829,  6833,  6841,  6857,  6863,  6869,  6871,  6883,  6899,  6907,  6911,  6917,  6947,  6949,
	6959,  6961,  6967,  6971,  6977,  6983,  6991,  6997,  7001,  7013,  7019,  7027,  7039,  7043,  7057,  7069,  7079,  7103,
	7109,  7121,  7127,  7129,  7151,  7159,  7177,  7187,  7193,  7207,  7211,  7213,  7219,  7229,  7237,  7243,  7247,  7253,
	7283,  7297,  7307,  7309,  7321,  7331,  7333,  7349,  7351,  7369,  7393,  7411,  7417,  7433,  7451,  7457,  7459,  7477,
	7481,  7487,  7489,  7499,  7507,  7517,  7523,  7529,  7537,  7541,  7547,  7549,  7559,  7561,  7573,  7577,  7583,  7589,
	7591,  7603,  7607,  7621,  7639,  7643,  7649,  7669,  7673,  7681,  7687,  7691,  7699,  7703,  7717,  7723,  7727,  7741,
	7753,  7757,  7759,  7789,  7793,  7817,  7823,  7829,  7841,  7853,  7867,  7873,  7877,  7879,  7883,  7901,  7907,  7919,
	7927,  7933,  7937,  7949,  7951,  7963,  7993,  8009,  8011,  8017,  8039,  8053,  8059,  8069,  8081,  8087,  8089,  8093,
	8101,  8111,  8117,  8123,  8147,  8161,  8167,  8171,  8179,  8191,  8209,  8219,  8221,  8231,  8233,  8237,  8243,  8263,
	8269,  8273,  8287,  8291,  8293,  8297,  8311,  8317,  8329,  8353,  8363,  8369,  8377,  8387,  8389,  8419,  8423,  8429,
	8431,  8443,  8447,  8461,  8467,  8501,  8513,  8521,  8527,  8537,  8539,  8543,  8563,  8573,  8581,  8597,  8599,  8609,
	8623,  8627,  8629,  8641,  8647,  8663,  8669,  8677,  8681,  8689,  8693,  8699,  8707,  8713,  8719,  8731,  8737,  8741,
	8747,  8753,  8761,  8779,  8783,  8803,  8807,  8819,  8821,  8831,  8837,  8839,  8849,  8861,  8863,  8867,  8887,  8893,
	8923,  8929,  8933,  8941,  8951,  8963,  8969,  8971,  8999,  9001,  9007,  9011,  9013,  9029,  9041,  9043,  9049,  9059,
	9067,  9091,  9103,  9109,  9127,  9133,  9137,  9151,  9157,  9161,  9173,  9181,  9187,  9199,  9203,  9209,  9221,  9227,
	9239,  9241,  9257,  9277,  9281,  9283,  9293,  9311,  9319,  9323,  9337,  9341,  9343,  9349,  9371,  9377,  9391,  9397,
	9403,  9413,  9419,  9421,  9431,  9433,  9437,  9439,  9461,  9463,  9467,  9473,  9479,  9491,  9497,  9511,  9521,  9533);

$maxprimes = count($primes) - 1;

/*Function for generating keys. Return array where
 * $array[0] -> modulo N
 * $array[1] -> public key E
 * $array[2] -> private key D
 * Public key pair is N and E
 * Private key pair is N and D
 * */
function generate_keys ($show_debug=0){

	global $primes,  $maxprimes;
	while (empty($e) || empty($d)) {
		/*finding 2 small prime numbers $p and $q 
		 *         $p and $q must be different*/
		$p = $primes[mt_rand(0,  $maxprimes)];
		while (empty($q) || ($p==$q)) $q = $primes[mt_rand(0,  $maxprimes)];
		//second part of public and private pairs - N
		$n = $p*$q;
		
		//$pi (we need it to calculate D and E) 
		$pi = ($p - 1) * ($q - 1);

		// Public key  E 
		$e = tofindE($pi,  $p,  $q);

		// Private key D
		$d = extend($e, $pi);

		$keys = array ($n,  $e,  $d);
		if ($show_debug) {
			//echo "P = $p<br>Q = $q<br><b>N = $n</b> - modulo<br>PI = $pi<br><b>E = $e</b> - public key<br><b>D = $d</b> - private key<p>";
		}
	}
	return $keys;
}

/* modulus function */
function mo ($g,  $l) {
	return $g - ($l * floor ($g/$l));
}

/* 
 * Standard method of calculating D
 * D = E-1 (mod N)
 * It's presumed D will be found in less then 16 iterations 
 */
function extend ($Ee, $Epi) {
	$u1 = 1;
	$u2 = 0;
	$u3 = $Epi;
	$v1 = 0;
	$v2 = 1;
	$v3 = $Ee;
	while ($v3 != 0) {
		$qq = floor($u3/$v3);
		$t1 = $u1 - $qq * $v1;
		$t2 = $u2 - $qq * $v2;
		$t3 = $u3 - $qq * $v3;
		$u1 = $v1;
		$u2 = $v2;
		$u3 = $v3;
		$v1 = $t1;
		$v2 = $t2;
		$v3 = $t3;
		$z = 1;
	}
	$uu = $u1;
	$vv = $u2;
	if ($vv < 0) {
		$inverse = $vv + $Epi;
	} else {
		$inverse = $vv;
	}
	return $inverse;
}

/* This function return Greatest Common Divisor for $e and $pi numbers */
function GCD($e, $pi) {
	$y = $e;
	$x = $pi;
	while ($y != 0) {
		$w =  mo($x ,  $y);
		$x = $y;
		$y = $w;

	}
	return $x;
}

/*function for calculating E under conditions:
 If each test E is prime,  there will be much less loops in that fuction
 and smaller E means less JS calculations on client side */
/*
 * Calculating E under conditions:
 * GCD(N, E) = 1 and 1<E<N
 * If E is prime,  there will be fewer loops in the function.
 * Smaller E also means reduced JS calculations on client side. 
 */
function tofindE($pi) {
	global $primes,  $maxprimes;
	$great = 0;
	$cc = mt_rand (0, $maxprimes);
	$startcc = $cc;
	while ($cc >= 0) {
		$se = $primes[$cc];
		$great = GCD($se, $pi);
		$cc--;
		if ($great == 1) break;
	}
	if ($great == 0) {
		$cc = $startcc + 1;
		while ($cc <= $maxprimes) {
			$se = $primes[$cc];
			$great = GCD($se, $pi);
			$cc++;
			if ($great == 1) break;
		}
	}
	return $se;
}

/*
 * ENCRYPT function returns
 *,  X = M^E (mod N)
 * Please check http://www.ge.kochi-ct.ac.jp/cgi-bin-takagi/calcmodp
 * and Flash5 RSA .fla by R.Vijay <rveejay0 <at> hotmail <dot> com> at
 * http://www.digitalillusion.co.in/lab/rsaencyp.htm
 * It is one of the simplest examples for binary RSA calculations 
 *
 * Each letter in the message is represented as its ASCII code number - 30
 * 3 letters in each block with 1 in the beginning and end.
 * For example string
 *,  AAA
 * will become
 *,  13535351 (A = ASCII 65-30 = 35)
 * we can build these blocks because the smalest prime available is 4507
 *,  4507^2 = 20313049 
 * This means that 
 *,  1. Modulo N will always be < 19999991
 *,  2. Letters > ASCII 128 must not occur in plain text message
 */

function rsa_encrypt ($m,  $e,  $n) {
	$asci = array ();
	for ($i=0; $i<strlen($m); $i+=3) {
		$tmpasci="1";
		for ($h=0; $h<3; $h++) {
			if ($i+$h <strlen($m)) {
				$tmpstr = ord (substr ($m,  $i+$h,  1)) - 30;
				if (strlen($tmpstr) < 2) {
					$tmpstr ="0".$tmpstr;
				}
			} else {
				break;
			}
			$tmpasci .=$tmpstr;
		}
		array_push($asci,  $tmpasci."1");
	}

	//Each number is then encrypted using the RSA formula: block ^E mod N
	for ($k=0; $k< count ($asci); $k++) {
		$resultmod = powmod($asci[$k],  $e,  $n);
		$coded .= $resultmod." ";
	}
	return trim($coded);
}

/*Russian Peasant method for exponentiation */
function powmod ($base,  $exp,  $modulus) {
	$accum = 1;
	$i = 0;
	$basepow2 = $base;
	while (($exp >> $i)>0) {
		if ((($exp >> $i) & 1) == 1) {
			$accum = mo(($accum * $basepow2) ,  $modulus);
		}
		$basepow2 = mo(($basepow2 * $basepow2) ,  $modulus);
		$i++;
	}
	return $accum;
}

/*
ENCRYPT function returns
M = X^D (mod N)
*/
function rsa_decrypt ($c,  $d,  $n) {
	//Strip the blank spaces from the ecrypted text and store it in an array
	$decryptarray = split(" ",  $c);
	for ($u=0; $u<count ($decryptarray); $u++) {
		if ($decryptarray[$u] == "") {
			array_splice($decryptarray,  $u,  1);
		}
	}
	//Each number is then decrypted using the RSA formula: block ^D mod N
	for ($u=0; $u< count($decryptarray); $u++) {
		$resultmod = powmod($decryptarray[$u],  $d,  $n);
		//remove leading and trailing '1' digits
		$deencrypt.= substr ($resultmod, 1, strlen($resultmod)-2);
	}
	//Each ASCII code number + 30 in the message is represented as its letter
	for ($u=0; $u<strlen($deencrypt); $u+=2) {
		$resultd .= chr(substr ($deencrypt,  $u,  2) + 30);
	}
	return $resultd;
}

/*
 * Generates a unique URL for the email by
 * encrypting email with users public key
 *
 * keys[0] -> modulo N
 * keys[1] -> public key E
 * Public key pair is N and E
 */
function getUsersRssUrl($user_id, $keys)
{
	$url = rsa_encrypt($user_id, $keys[1], $keys[0]);
	$url = str_replace(" ","", $url);
	$url = base64_encode($url);
	return $url;
}

/*
 * Returns user_id decrypted from xid
 *
 * keys[0] -> modulo N
 * keys[1] -> public key E
 * Public key pair is N and E
 */
function getDecryptUserId($xid, $keys)
{
	$xid = base64_decode($xid);
	$top = 8;
	$spacedXid = "";
	while($top <= strlen($xid))
	{
		$spacedXid .= substr($xid, $top - 8, $top) . " ";
		$top += 8;
	}

	$xid = rsa_decrypt($spacedXid, $keys[2], $keys[0]);
	return $xid;
}

$encoded = rsa_encrypt ($message,  $keys[1],  $keys[0]);
$decoded = rsa_decrypt($encoded,  $keys[2],  $keys[0]);

/* Example */
/*

echo"<i>Keys:</i><br>";
$keys = generate_keys (1);
//or just
//$keys = generate_keys ();
$message="";
//for ($i=32;$i<127;$i++) $message.=chr($i);
$message="435456666";
$encoded = rsa_encrypt ($message,  $keys[1],  $keys[0]);
$decoded = rsa_decrypt($encoded,  $keys[2],  $keys[0]);
echo "<pre><br><i>Test ASCII(32) - ASCII(126):</i>\n";
echo "Message: <b>$message</b>\n";
echo "Encoded: <b>$encoded</b>\n";
echo "Decoded: <b>$decoded</b>\n";
echo "Success: ".(($decoded == $message) ? "True" : "False")."</pre>\n";
 */
?>
