/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 18:36:43 by ivan-der     ###    #### orminette :(    */
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
	if (coder->ctx->params->max_compiles <= 0 || request_dongles(coder))
		return (0);
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
		pthread_mutex_lock(&coder->dongles[1]->mutex);
	take_dongles(coder);
	coder_compile(coder);
	release_dongles(coder);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	if (get_process(coder->ctx))
	{
		coder_action(coder, coder->ctx->params->debug_time, "is debugging");
		coder_action(coder, coder->ctx->params->refactor_time,
			"is refactoring");
	}
	if (++coder->compiles < coder->ctx->params->max_compiles
		&& get_process(coder->ctx))
		action_process(coder);
	return (0);
}

void	coder_compile(t_coder *coder)
{
	int64_t	end_time;

	if (get_process(coder->ctx))
		print_action(coder, "is compiling", GREY);
	end_time = get_elapsed_time(coder->ctx) + coder->ctx->params->compile_time;
	while (get_process(coder->ctx))
	{
		if (get_elapsed_time(coder->ctx) >= end_time)
			break ;
		usleep(UPDATE_TICKS);
	}
	if ((coder->compiles + 1) < coder->ctx->params->max_compiles)
		set_coder_deadline(coder, get_elapsed_time(coder->ctx)
			+ coder->ctx->params->burnout_time);
	else
		set_coder_deadline(coder, -1);
}

void	coder_action(t_coder *coder, int64_t len, char *msg)
{
	int64_t	end_time;

	if (get_process(coder->ctx))
		print_action(coder, msg, GREY);
	end_time = get_elapsed_time(coder->ctx) + len;
	while (get_process(coder->ctx))
	{
		if (get_elapsed_time(coder->ctx) >= end_time)
			break ;
		usleep(UPDATE_TICKS);
	}
}
