/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   args.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/10 14:32:00 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/10 22:20:08 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	get_args(char **argv, t_ctx *ctx)
{
	ctx->coders = atoi(argv[1]);
	ctx->burnout_time = atoi(argv[2]);
	ctx->compile_time = atoi(argv[3]);
	ctx->debug_time = atoi(argv[4]);
	ctx->refactor_time = atoi(argv[5]);
	ctx->max_compiles = atoi(argv[6]);
	ctx->dongle_cooldown = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		ctx->scheduler = FIFO;
	else if (!strcmp(argv[8], "edf"))
		ctx->scheduler = EDF;
	else
		return (1);
	while (argv++ && *(argv + 1) != NULL)
		if (!atoi(*argv))
			return (1);
	return (0);
}
