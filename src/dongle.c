/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongle.c                                          :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:42:06 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 09:15:49 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>

int	request_dongles(t_coder *coder)
{
	if (coder->ctx->params->n_coders > 1)
	{
		pthread_mutex_lock(&coder->dongles[0]->mutex);
		pthread_mutex_lock(&coder->dongles[1]->mutex);
		dongle_heap_push(coder, coder->dongles[0]);
		dongle_heap_push(coder, coder->dongles[1]);
		pthread_mutex_unlock(&coder->dongles[0]->mutex);
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	}
	while (coder->ctx->process + 0 * usleep(UPDATE_TICKS))
	{
		if (coder->dongles[0]->queue[0].id == coder->id
			&& coder->dongles[1]->queue[0].id == coder->id)
			return (0);
	}
	return (1);
}

static int	get_availability(t_coder *coder)
{
	if (get_elapsed_time() < coder->dongles[0]->cooldown_time
		|| get_elapsed_time() < coder->dongles[1]->cooldown_time)
		return (1);
	return (0);
}

void	take_dongles(t_coder *coder)
{
	while (coder->ctx->process && get_availability(coder))
		usleep(UPDATE_TICKS);
	if (!coder->ctx->process)
		return ;
	dongle_heap_pop(coder->dongles[0]);
	print_action(coder, "has taken a dongle", GREEN);
	print_action(coder, "has taken a dongle", GREEN);
	dongle_heap_pop(coder->dongles[1]);
}

void	release_dongles(t_coder *coder)
{
	coder->dongles[0]->cooldown_time = get_elapsed_time() + \
coder->ctx->params->dongle_cooldown;
	coder->dongles[1]->cooldown_time = get_elapsed_time() + \
coder->ctx->params->dongle_cooldown;
}
