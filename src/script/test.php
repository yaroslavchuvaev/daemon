<?php
	$sock = fsockopen('unix:///var/run/reader.socket', NULL, $errno, $errstr, 0.5);
	$data = "input string";
	fwrite($sock,$data);  
	echo fread($sock, 4096)."=".md5($data.'BD341CF62EDC9470DA377ED2')."\n";
	echo '';
?>