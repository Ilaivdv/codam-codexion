/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/24 18:13:35 by ivan-der     ###    #### orminette :(    */
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
	if (coder->ctx->process)
	{
		coder_action(coder, coder->ctx->params->debug_time, "is debugging");
		coder_action(coder, coder->ctx->params->refactor_time, "is refactoring");
	}
	if (++coder->compiles < coder->ctx->params->max_compiles
			&& coder->ctx->process)
		action_process(coder);
	else
		print_action(coder, "		has finished compiles! REMOVE THIS MESSAGE LATER", GREEN);
	return (0);
}

void	coder_compile(t_coder *coder)
{
	int64_t	end_time;

	if (coder->ctx->process)
	{
		print_action(coder, "is compiling", GREY);
		if ((coder->compiles + 1) < coder->ctx->params->max_compiles)
			coder->deadline = get_elapsed_time() + \
							  coder->ctx->params->burnout_time + \
							  coder->ctx->params->compile_time;
		else
			coder->deadline = -1;
	}
	end_time = get_elapsed_time() + coder->ctx->params->compile_time;
	while (coder->ctx->process || 0 * usleep(UPDATE_TICKS))
	{
		if (get_elapsed_time() >= end_time)
			break;
	}
}

void	coder_action(t_coder *coder, int64_t len, char *msg)
{
	int64_t	end_time;

	if (coder->ctx->process)
		print_action(coder, msg, GREY);
	end_time = get_elapsed_time() + len;
	while (coder->ctx->process || 0 * usleep(UPDATE_TICKS))
	{
		if (get_elapsed_time() >= end_time)
			break;
	}
}
