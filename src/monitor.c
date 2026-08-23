/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 16:44:59 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	coder_burnout(t_ctx *ctx);

void	*monitor_process(void *c)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)c;
	ctx->process = true;
	while (ctx->process + 0 * usleep(UPDATE_TICKS))
	{
		ctx->process = coder_burnout(ctx);
	}
	return (NULL);
}

int	coder_burnout(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
		if (get_elapsed_time(false) >= ctx->coders[i].deadline)
		{
			//DEBUG
			printf("burnout from coder %d, time: %ld\n", ctx->coders[i].id, get_elapsed_time(false));
			return (0);
		}
	return (1);
}
