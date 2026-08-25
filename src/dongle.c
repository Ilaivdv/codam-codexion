/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongle.c                                          :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 21:42:06 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/25 22:44:07 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <unistd.h>

int	request_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	dongle_heap_push(coder, coder->dongles[0]);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
	{
		pthread_mutex_lock(&coder->dongles[1]->mutex);
		dongle_heap_push(coder, coder->dongles[1]);
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	}
	while (get_process(coder->ctx))
	{
		if (check_queue_front(coder->dongles[0], coder->id)
			&& check_queue_front(coder->dongles[1], coder->id))
			return (0);
		usleep(UPDATE_TICKS);
	}
	return (1);
}

static int	get_available(t_coder *coder)
{
	if (coder->ctx->params->n_coders <= 1)
		return (1);
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	if (get_elapsed_time(coder->ctx) < coder->dongles[0]->cooldown_time
		|| !coder->dongles[0]->is_available)
	{
		pthread_mutex_unlock(&coder->dongles[0]->mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
	{
		pthread_mutex_lock(&coder->dongles[1]->mutex);
		if (get_elapsed_time(coder->ctx) < coder->dongles[1]->cooldown_time
			|| !coder->dongles[1]->is_available)
		{
			pthread_mutex_unlock(&coder->dongles[1]->mutex);
			return (1);
		}
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	}
	return (0);
}

void	take_dongles(t_coder *coder)
{
	while (get_process(coder->ctx) && get_available(coder))
		usleep(UPDATE_TICKS);
	if (!get_process(coder->ctx))
		return ;
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	coder->dongles[0]->is_available = false;
	dongle_heap_pop(coder->dongles[0]);
	print_action(coder, "has taken a dongle", GREEN);
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
	{
		pthread_mutex_lock(&coder->dongles[1]->mutex);
		coder->dongles[1]->is_available = false;
		print_action(coder, "has taken a dongle", GREEN);
		dongle_heap_pop(coder->dongles[1]);
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	}
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	coder->dongles[0]->cooldown_time = get_elapsed_time(coder->ctx) + \
coder->ctx->params->dongle_cooldown;
	coder->dongles[0]->is_available = true;
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (coder->ctx->params->n_coders > 1)
	{
		pthread_mutex_lock(&coder->dongles[1]->mutex);
		coder->dongles[1]->cooldown_time = get_elapsed_time(coder->ctx) + \
coder->ctx->params->dongle_cooldown;
		coder->dongles[1]->is_available = true;
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	}
}
