--TEST--
Check if snowflake is loaded
--SKIPIF--
<?php
if (!extension_loaded('snowflake')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "snowflake" is available';
?>
--EXPECT--
The extension "snowflake" is available
