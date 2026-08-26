/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   dongle_utils.c                                    :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/21 16:06:22 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/26 11:33:50 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/types.h>
#include <stdbool.h>

static void	dongle_queue_swap(t_dongle *dongle);

int	init_dongles(t_ctx *ctx)
{
	ssize_t	i;

	i = -1;
	while (++i < ctx->params->n_coders)
	{
		if (pthread_mutex_init(&(ctx->dongles + i)->mutex, NULL)
			|| pthread_mutex_init(&(ctx->dongles + i)->queue_mutex, NULL))
			return (1);
		ctx->dongles[i] = (t_dongle){.is_available = true, .queue_size = 0};
	}
	return (0);
}

void	dongle_heapify(t_dongle *dongle)
{
	t_queue	tmp;

	if (dongle->queue_size == 1)
		return ;
	dongle->queue[0].cmp = get_cmp(dongle->queue[0].coder);
	dongle->queue[1].cmp = get_cmp(dongle->queue[1].coder);
	if (dongle->queue[1].cmp < dongle->queue[0].cmp)
	{
		tmp = dongle->queue[0];
		dongle->queue[0] = dongle->queue[1];
		dongle->queue[1] = tmp;
	}
}

void	dongle_heap_push(t_coder *coder, t_dongle *dongle, int64_t cmp)
{
	pthread_mutex_lock(&dongle->queue_mutex);
	dongle->queue_size++;
	if (dongle->queue_size == 1)
		dongle->queue[0] = (t_queue){.cmp = cmp,
			.id = coder->id, .coder = coder};
	else
	{
		if (dongle->queue[0].cmp < cmp)
			dongle->queue[1] = (t_queue){.cmp = cmp,
				.id = coder->id, .coder = coder};
		else
		{
			dongle->queue[1] = dongle->queue[0];
			dongle->queue[0] = (t_queue){.cmp = cmp,
				.id = coder->id, .coder = coder};
		}
		if (coder->ctx->params->scheduler == EDF)
		{
			dongle_heapify(dongle);
			if (coder->dongles[0]->queue[0].id
				!= coder->dongles[1]->queue[0].id)
				dongle_queue_swap(coder->dongles[1]);
		}
	}
	pthread_mutex_unlock(&dongle->queue_mutex);
}

void	dongle_heap_remove(t_dongle *dongle, int id)
{
	pthread_mutex_lock(&dongle->queue_mutex);
	if (dongle->queue[0].id == id)
		dongle->queue[0] = dongle->queue[1];
	dongle->queue[1] = (t_queue){.cmp = 0, .id = 0};
	dongle->queue_size--;
	pthread_mutex_unlock(&dongle->queue_mutex);
}

static void	dongle_queue_swap(t_dongle *dongle)
{
	t_queue	tmp;

	if (dongle->queue_size <= 1)
		return ;
	tmp = dongle->queue[0];
	dongle->queue[0] = dongle->queue[1];
	dongle->queue[1] = tmp;
}
