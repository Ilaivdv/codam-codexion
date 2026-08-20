/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/20 15:51:13 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include <unistd.h>

// TODO add and update time stats for coders
int	wait_for_dongle(t_coder *coder);

void	*action_process(void *c)
{
	t_coder	*coder;

	coder = (t_coder *)c;
	wait_for_dongle(coder);

	// TODO make compile function
	// debug and refactor action can possibly happen here

	// DEBUG
	// printf("coder %d, <-%d, %d->\n", coder->id, coder->dongles[0]->is_available, coder->dongles[1]->is_available);
	// usleep(1000);
	// printf("%lld ms\n", get_elapsed_time());

	return (0);
}

int	wait_for_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->dongles[0]->mutex);
	if (*(&coder->dongles[0]) != *(&coder->dongles[1]))
		pthread_mutex_lock(&coder->dongles[1]->mutex);
	if (coder->dongles[0]->is_available && coder->dongles[1]->is_available)
	{
		printf("%d has taken a dongle\n", coder->id);
		coder->dongles[0]->is_available = false;
		if (coder->dongles[1]->is_available)
		{
			printf("%d has taken a dongle\n", coder->id);
			coder->dongles[1]->is_available = false;
		}
	}
	pthread_mutex_unlock(&coder->dongles[0]->mutex);
	if (*(&coder->dongles[0]) != *(&coder->dongles[1]))
		pthread_mutex_unlock(&coder->dongles[1]->mutex);
	return (0);
}
