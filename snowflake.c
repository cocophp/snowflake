/* snowflake extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "snowflake.h"
#include "ext/standard/info.h"
#include "php_snowflake.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void uuid()
 */
PHP_FUNCTION(uuid) {
	RETURN_LONG( getUniqueId() );
}
/* }}} */
/* {{{ string set_work_id( [ string $var ] )
 */
PHP_FUNCTION(set_work_id){
	zend_long workID = 0;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG( workID )
	ZEND_PARSE_PARAMETERS_END();
	RETURN_LONG( setWorkID( workID ) );
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(snowflake)
{
#if defined(ZTS) && defined(COMPILE_DL_SNOWFLAKE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(snowflake)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "snowflake support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_uuid, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_set_work_id, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ snowflake_functions[]
 */
static const zend_function_entry snowflake_functions[] = {
	PHP_FE(uuid,        arginfo_uuid)
	PHP_FE(set_work_id, arginfo_set_work_id)
	PHP_FE_END
};
/* }}} */

/* {{{ snowflake_module_entry
 */
zend_module_entry snowflake_module_entry = {
	STANDARD_MODULE_HEADER,
	"snowflake",					/* Extension name */
	snowflake_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(snowflake),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(snowflake),			/* PHP_MINFO - Module info */
	PHP_SNOWFLAKE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SNOWFLAKE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(snowflake)
#endif
