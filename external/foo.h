#undef CMD_INC_FILE
#define CMD_INC_FILE external/foo

#if !defined(FOO) || defined(CMD_HEADER_MULTI_READ)
#define FOO

#include "cmd.h"

PLUGIN_EXT(NAME("foo", "Example external plugin"),
	COMMAND_LIST(
		ENTRY("bar", "Example 1", bar)
		ENTRY("baz", "Example 2", baz)
		ENTRY("qux", "Example 3", quz)
	)
);

#endif

#include "define_cmd.h"
