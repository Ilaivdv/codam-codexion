/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/18 17:19:10 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coder.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static void	state_process(t_coder *coder);

void	*wait_for_dongle(void *p)
{
	t_coder	*coder;

	coder = (t_coder *)p;
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	pthread_mutex_lock(&coder->dongles[1]->mutex);
	if (coder->dongles[0][0].is_available && coder->dongles[0][1].is_available)
	{
		printf("%d has taken a dongle\n", coder->id);
		coder->dongles[0]->is_available = false;
		printf("%d has taken a dongle\n", coder->id);
		coder->dongles[1]->is_available = false;
		state_process(coder);
	}
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	pthread_mutex_unlock(&coder->dongles[1]->mutex);
	return (0);
}

static void	state_process(t_coder *coder)
{
	printf("%d is compiling\n", coder->id);
	usleep(coder->ctx->compile_time);
	printf("%d is debugging\n", coder->id);
	usleep(coder->ctx->debug_time);
	printf("%d is refactoring\n", coder->id);
	usleep(coder->ctx->refactor_time);
}
