/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:26:18 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/24 15:33:16 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
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
		ctx->coders[i] = (t_coder){.ctx = ctx, .id = i + 1,
			.compiles = 0, .dongles = {ctx->dongles + i,
			ctx->dongles + ((i + 1) % ctx->params->n_coders)},
			.deadline = get_elapsed_time() + ctx->params->burnout_time};
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

void	print_action(t_coder *coder, char *msg)
{
	if (!coder->ctx->process)
		return;
	pthread_mutex_lock(&coder->ctx->coder_action_mutex);
	printf("%ld %d %s\n", get_elapsed_time(), coder->id, msg);
	pthread_mutex_unlock(&coder->ctx->coder_action_mutex);
}
