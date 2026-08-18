/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   args.c                                            :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:27:50 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/18 16:11:06 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

int	get_args(char **argv, t_ctx *ctx)
{
	ctx->coders = atoi(argv[1]);
	ctx->burnout_time = atoi(argv[2]) * 1000;
	ctx->compile_time = atoi(argv[3]) * 1000;
	ctx->debug_time = atoi(argv[4]) * 1000;
	ctx->refactor_time = atoi(argv[5]) * 1000;
	ctx->max_compiles = atoi(argv[6]);
	ctx->dongle_cooldown = atoi(argv[7]) * 1000;
	if (!strcmp(argv[8], "fifo"))
		ctx->scheduler = FIFO;
	else if (!strcmp(argv[8], "edf"))
		ctx->scheduler = EDF;
	else
		return (1);
	while (argv++ && *(argv + 1) != NULL)
		if (atoi(*argv) <= 0)
			return (1);
	return (0);
}
