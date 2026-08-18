/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder_utils.c                                     :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/18 11:14:55 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coder.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void	*coder_get_dongle(void *c)
{
	t_coder	*coder;

	coder = (t_coder *)c;
	coder->state = WAITING;
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	pthread_mutex_lock(&coder->dongles[1]->mutex);
	if (coder->dongles[0][0].is_available && coder->dongles[0][1].is_available)
	{
		printf("coder %d has taken a dongle\n", coder->id);
		coder->dongles[0]->is_available = false;
		printf("coder %d has taken a dongle\n", coder->id);
		coder->dongles[1]->is_available = false;
	}
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	pthread_mutex_unlock(&coder->dongles[1]->mutex);
	return (0);
}
