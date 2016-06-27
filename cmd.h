#ifndef _CMD_H
#define _CMD_H

#undef PLUGIN_EXT
#define PLUGIN_EXT(n, c) PLUGIN(n, c)

#undef PLUGIN
#define PLUGIN(n, c)

#undef COMMAND_LIST
#define COMMAND_LIST(args...)

#endif
