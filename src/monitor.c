/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 16:14:10 by ivan-der     ###    #### orminette :(    */
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
	set_process(ctx, true);
	usleep(UPDATE_TICKS);
	while (get_process(ctx) || 0 * usleep(UPDATE_TICKS))
	{
		if (coder_burnout(ctx))
			break ;
	}
	set_process(ctx, false);
	return (NULL);
}

int	coder_burnout(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
	{
		if (get_elapsed_time(ctx) >= get_coder_deadline(&ctx->coders[i])
			&& get_coder_deadline(&ctx->coders[i]) >= 0)
		{
			print_action(&ctx->coders[i], "burned out", RED);
			return (1);
		}
	}
	return (0);
}

int64_t	get_elapsed_time(t_ctx *ctx)
{
	static int64_t	epoch = -1;
	struct timeval	tv;
	int64_t			current_time;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&ctx->time_mutex);
	if (epoch == -1)
		epoch = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(&ctx->time_mutex);
	return (current_time - epoch);
}

bool	get_process(t_ctx *ctx)
{
	bool	res;

	pthread_mutex_lock(&ctx->process_mutex);
	if (ctx->process)
		res = true;
	else
		res = false;
	pthread_mutex_unlock(&ctx->process_mutex);
	return (res);
}

void	set_process(t_ctx *ctx, bool process)
{
	pthread_mutex_lock(&ctx->process_mutex);
	ctx->process = process;
	pthread_mutex_unlock(&ctx->process_mutex);
}
