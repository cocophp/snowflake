/* snowflake extension for PHP */

#ifndef PHP_SNOWFLAKE_H
# define PHP_SNOWFLAKE_H

extern zend_module_entry snowflake_module_entry;
# define phpext_snowflake_ptr &snowflake_module_entry

# define PHP_SNOWFLAKE_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_SNOWFLAKE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_SNOWFLAKE_H */

