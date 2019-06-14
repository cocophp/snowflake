--TEST--
snowflake_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = snowflake_test1();

var_dump($ret);
?>
--EXPECT--
The extension snowflake is loaded and working!
NULL
