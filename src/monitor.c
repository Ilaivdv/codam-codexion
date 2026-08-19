/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/19 13:10:36 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/time.h>
#include <unistd.h>

unsigned int	get_elapsed_time(t_ctx *ctx)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_usec - ctx->monitor->start) / 1000);
}

int	monitor_process()
{
	return (1);
}
