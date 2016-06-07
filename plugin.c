#include <stdio.h>
#include <stdlib.h>

#include "plugin.h"
#include "argconfig.h"

void usage(struct plugin *plugin)
{
	struct program *prog = plugin->parent;

	printf("usage: %s %s\n", prog->name, prog->usage);
}

void general_help(struct plugin *plugin)
{
	struct program *prog = plugin->parent;
	unsigned i = 0;
	struct plugin *extension;

	printf("%s-%s\n", prog->name, prog->version);

	usage(plugin);

	printf("\n");
	print_word_wrapped(plugin->desc, 0, 0);

	printf("The following are all implemented sub-commands:\n");
	while (plugin->commands[i]) {
		printf("  %-*s %s\n", 15, plugin->commands[i]->name,
					plugin->commands[i]->help);
		i++;
	}

	printf("\n");

	if (plugin->name)
		printf("See '%s %s help <command>' for more information on a specific command\n",
			prog->name, plugin->name);
	else
		printf("See '%s help <command>' for more information on a specific command\n",
			prog->name);

	extension = prog->extensions->next;

	/* The first plugin is the built-in. If we're not showing help for the
	 * built-in, don't show the program's other extensions */
	if (!extension || plugin != prog->extensions)
		return;
	
	printf("\nThe following are all installed plugin extensions:\n");
	while (extension) {
		printf("  %-*s %s\n", 15, extension->name, extension->desc);
		extension = extension->next;
	}
	printf("\nSee '%s <plugin> help' for more information on a plugin\n",
			prog->name);
}

int handle_plugin(int argc, char **argv, struct plugin *plugin)
{
	unsigned i = 0;
	struct command *cmd;
	char *str = argv[0];
	char usage[0x100];

	struct plugin *extension;

	sprintf(usage, "%s %s <device> [OPTIONS]", plugin->name, str);
	argconfig_append_usage(usage);

	/* translate --help and --version into commands */
	while (*str == '-')
		str++;

	while (plugin->commands[i]) {
		cmd = plugin->commands[i];
		i++;

		if (strcmp(str, cmd->name))
			continue;

		return (cmd->fn(argc, argv, cmd, plugin));
	}

	/* check extensions */
	extension = plugin->next;

	while (extension) {
		if (strcmp(str, extension->name)) {
			extension = extension->next;
			continue;
		}
		return handle_plugin(argc - 1, &argv[1], extension);
		extension = extension->next;
	}
	return -1;
}
