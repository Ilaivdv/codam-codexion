/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/24 13:19:24 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

void	coder_compile(t_coder *coder);
void	coder_action(t_coder *coder, int64_t len, char *msg);

void	*action_process(void *c)
{
	t_coder				*coder;

	coder = (t_coder *)c;
	if (request_dongles(coder))
		return (0); // TODO wait for condition here
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
		pthread_mutex_lock(&coder->dongles[1]->mutex);
	if (coder->ctx->process)
	{
		take_dongles(coder);
		coder_compile(coder);
	}
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
		pthread_mutex_unlock(&coder->dongles[1]->mutex);

	coder_action(coder, coder->ctx->params->debug_time, "is debugging");
	coder_action(coder, coder->ctx->params->refactor_time, "is refactoring");
	coder->deadline = (get_elapsed_time(false) + \
					  coder->ctx->params->burnout_time) % 1000000;
	if (++coder->compiles < coder->ctx->params->max_compiles
			&& coder->ctx->process)
		action_process(coder);
	else
		print_action(coder, "		has finished compiles!");
	return (0);
}

// #include <stdio.h>
void	coder_compile(t_coder *coder)
{
	int64_t	end_time;

	if (coder->ctx->process)
		print_action(coder, "is compiling");
	end_time = get_elapsed_time(false) + coder->ctx->params->compile_time;
	while (coder->ctx->process || 0 * usleep(UPDATE_TICKS))
	{
		if (get_elapsed_time(false) >= end_time)
			break;
	}
	// printf("coder %d deadline: %ld, time: %ld\n", coder->id, end_time, get_elapsed_time(false));
}

void	coder_action(t_coder *coder, int64_t len, char *msg)
{
	int64_t	end_time;

	if (coder->ctx->process)
		print_action(coder, msg);
	end_time = get_elapsed_time(false) + len;
	while (coder->ctx->process || 0 * usleep(UPDATE_TICKS))
	{
		if (get_elapsed_time(false) >= end_time)
			break;
	}
	// printf("%ld coder %d finished action\n", get_elapsed_time(true), coder->id);
}
