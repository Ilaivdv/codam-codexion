/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   main.c                                            :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/18 15:10:02 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/18 17:19:08 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include "../include/coder.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int	init_coders(t_coder **coders, pthread_t **threads,
				t_dongle **dongles, t_ctx *ctx);

// TODO use compound literals

int	main(int argc, char **argv)
{
	pthread_t	*threads;
	t_coder		*coders;
	t_dongle	*dongles;
	t_ctx		ctx;
	ssize_t		i;

	if (argc != 9 || get_args(argv, &ctx) || ctx.coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'\n");
		return (1);
	}
	threads = malloc(sizeof(pthread_t) * ctx.coders);
	coders = malloc(sizeof(t_coder) * ctx.coders);
	dongles = malloc(sizeof(t_dongle) * ctx.coders);
	if (!threads || !coders
		|| init_coders(&coders, &threads, &dongles, &ctx))
		return (2);
	i = -1;
	while (i++ < (ctx.coders - 1))
		if (pthread_join(threads[i], NULL))
			return (3);
	// DEBUG
	// for (size_t i = 0; i < ctx.coders; i++)
	// 	printf("coder %d, dongles available: %d %d\n", (coders + i)->id, coders->dongles[0][0].is_available, coders->dongles[0][1].is_available);
	free(threads);
	free(coders);
	free(dongles); // TODO: destroy mutexes within dongles
	return (0);
}

static int	init_coders(t_coder **coders, pthread_t **threads,
		t_dongle **dongles, t_ctx *ctx)
{
	ssize_t		i;

	i = -1;
	while (i++ < (ctx->coders - 1))
	{
		pthread_mutex_init(&(*dongles + i)->mutex, NULL);
		(*dongles + i)->is_available = true;
	}
	i = -1;
	while (i++ < (ctx->coders - 1))
	{
		(*coders + i)->id = i;
		(*coders + i)->ctx = ctx;
		(*coders + i)->dongles[0] = (*dongles + i);
		(*coders + i)->dongles[1] = (*dongles + ((i + 1) % ctx->coders));
		if (pthread_create(*threads + i, NULL, &wait_for_dongle, *coders + i))
			return (1);
	}
	return (0);
}
