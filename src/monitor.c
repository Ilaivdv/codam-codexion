/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/21 22:32:16 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int	check_coder_burnout(t_ctx *ctx);

void	*monitor_process(void *c)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)c;
	ctx->process = true;
	while (ctx->process + 0 * usleep(UPDATE_TICKS))
	{
		ctx->process = check_coder_burnout(ctx);
	}
	return (NULL);
}

int	check_coder_burnout(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
		if (get_elapsed_time() >= ctx->coders[i].deadline)
		{
			//DEBUG
			printf("burnout from coder %d, time: %ld\n", ctx->coders[i].id, get_elapsed_time());
			return (0);
		}
	return (1);
}
