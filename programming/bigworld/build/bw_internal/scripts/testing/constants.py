
OK_STATE		= "OK"
FAIL_STAT		= "FAIL"
SUCCESS_STATE = [ OK_STATE, FAIL_STAT ]

BUILD_WIN32		= "WIN32"
BUILD_WIN64		= "WIN64"
BUILD_CONFIGS = [ BUILD_WIN32, BUILD_WIN64 ]

EXE_DEBUG		= "Debug"
EXE_RELEASE		= "Hybrid"
EXE_CONSUMER 	= "Consumer_Release"
EXE_TYPES = [ EXE_DEBUG, EXE_RELEASE, EXE_CONSUMER ]

DB_MEMORY = "MEMORY"
DB_PRODUCTION = "MYSQL"
DB_TYPES = [ DB_MEMORY, DB_PRODUCTION ]
DB_DEFAULT = DB_MEMORY

MYSQL_USER = 'perf'
MYSQL_PWD = 'p3rf'
MYSQL_HOST = 'db01'
MYSQL_DB = 'perf'
