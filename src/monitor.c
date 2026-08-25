/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 09:36:05 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	coder_burnout(t_ctx *ctx);

void	*monitor_process(void *c)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)c;
	ctx->process = true;
	usleep(UPDATE_TICKS);
	while (ctx->process || 0 * usleep(UPDATE_TICKS))
	{
		if (coder_burnout(ctx))
			break ;
	}
	ctx->process = false;
	return (NULL);
}

int	coder_burnout(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
	{
		if (get_elapsed_time() >= ctx->coders[i].deadline
			&& ctx->coders[i].deadline >= 0)
		{
			print_action(&ctx->coders[i], "burned out", RED);
			return (1);
		}
	}
	return (0);
}

int64_t	get_elapsed_time(void)
{
	static int64_t	epoch = -1;
	struct timeval	tv;
	int64_t			current_time;

	gettimeofday(&tv, NULL);
	if (epoch == -1)
		epoch = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time - epoch);
}
