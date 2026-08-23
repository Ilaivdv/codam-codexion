/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 21:08:01 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

void	coder_compile(t_coder *coder);

void	*action_process(void *c)
{
	t_coder				*coder;

	coder = (t_coder *)c;
	if (request_dongles(coder))
		return ((int *)1); // TODO wait for condition here
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
	// TODO debug and refactor action
	// TODO make loop until compilation quota
	return (0);
}

void	coder_compile(t_coder *coder)
{
	int64_t	end_time;

	print_action(coder, "is compiling");
	end_time = get_elapsed_time(false) + coder->ctx->params->compile_time;
	while (coder->ctx->process + 0 * usleep(UPDATE_TICKS))
		if (get_elapsed_time(false) >= end_time)
			break;
}
