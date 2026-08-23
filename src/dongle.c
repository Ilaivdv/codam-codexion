/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongle.c                                          :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:42:06 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/23 11:54:14 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>

#include <stdio.h>

void	take_dongles(t_coder *coder);

int	request_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	pthread_mutex_lock(&coder->dongles[1]->mutex);
	dongle_heap_push(coder, coder->dongles[0]);
	dongle_heap_push(coder, coder->dongles[1]);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	pthread_mutex_unlock(&coder->dongles[1]->mutex);
	while (coder->ctx->process + 0 * usleep(UPDATE_TICKS))
	{
		if (coder->dongles[0]->queue[0].id == coder->id
				&& coder->dongles[1]->queue[0].id == coder->id)
		{
			take_dongles(coder);
			return (0);
		}
	}
	return (1);
}

void	take_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	pthread_mutex_lock(&coder->dongles[1]->mutex);
	pthread_mutex_lock(&coder->ctx->coder_action_mutex);
	dongle_heap_pop(coder->dongles[0]);
	printf("%d has taken a dongle\n", coder->id);
	dongle_heap_pop(coder->dongles[1]);
	printf("%d has taken a dongle\n", coder->id);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	pthread_mutex_unlock(&coder->dongles[1]->mutex);
	pthread_mutex_unlock(&coder->ctx->coder_action_mutex);
}
