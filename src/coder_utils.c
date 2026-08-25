/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:26:18 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 16:23:31 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

static int	process_threads(t_ctx *ctx);

int	init_coders(t_ctx *ctx)
{
	ssize_t	i;

	ctx->coders = malloc(sizeof(t_coder) * ctx->params->n_coders);
	memset(ctx->coders, 0, sizeof(t_coder) * ctx->params->n_coders);
	ctx->dongles = malloc(sizeof(t_dongle) * ctx->params->n_coders);
	memset(ctx->dongles, 0, sizeof(t_coder) * ctx->params->n_coders);
	if (!ctx->coders || !ctx->dongles || init_dongles(ctx))
		return (1);
	i = -1;
	while (++i < ctx->params->n_coders)
	{
		if (pthread_mutex_init(&ctx->coders[i].deadline_mutex, NULL))
			return (1);
		ctx->coders[i] = (t_coder){.ctx = ctx, .id = i + 1,
			.compiles = 0, .dongles = {ctx->dongles + i,
			ctx->dongles + ((i + 1) % ctx->params->n_coders)}};
		set_coder_deadline(&ctx->coders[i],
			get_elapsed_time(ctx) + ctx->params->burnout_time);
	}
	return (process_threads(ctx));
}

static int	process_threads(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
		if (pthread_create(&ctx->coders[i].thread, NULL,
				&action_process, &ctx->coders[i]))
			return (1);
	i = -1;
	while (++i < ctx->params->n_coders)
		if (pthread_join(ctx->coders[i].thread, NULL))
			return (2);
	return (0);
}

void	print_action(t_coder *coder, char *msg, char *color)
{
	pthread_mutex_lock(&coder->ctx->coder_action_mutex);
	if (get_process(coder->ctx))
		printf("%5ld %5d %s%s%s\n", get_elapsed_time(coder->ctx), coder->id,
			color, msg, COLOR_RESET);
	pthread_mutex_unlock(&coder->ctx->coder_action_mutex);
}

int64_t	get_coder_deadline(t_coder *coder)
{
	int64_t	res;

	pthread_mutex_lock(&coder->deadline_mutex);
	res = coder->deadline;
	pthread_mutex_unlock(&coder->deadline_mutex);
	return (res);
}

void	set_coder_deadline(t_coder *coder, int64_t deadline)
{
	pthread_mutex_lock(&coder->deadline_mutex);
	coder->deadline = deadline;
	pthread_mutex_unlock(&coder->deadline_mutex);
}
