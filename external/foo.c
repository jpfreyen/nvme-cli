#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/fs.h>

#include "plugin.h"

#define CREATE_CMD
#include "foo.h"

static int hello_world(struct command *cmd, struct plugin *plugin)
{
	printf("hello, running plug-in %s command %s\n", plugin->name, cmd->name);
	return 0;
}

static int bar(int argc, char **argv, struct command *cmd, struct plugin *plugin)
{
	return hello_world(cmd, plugin);
}

static int baz(int argc, char **argv, struct command *cmd, struct plugin *plugin)
{
	return hello_world(cmd, plugin);
}

static int quz(int argc, char **argv, struct command *cmd, struct plugin *plugin)
{
	return hello_world(cmd, plugin);
}
