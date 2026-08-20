/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   monitor.c                                         :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/19 12:13:09 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/20 12:29:57 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

// TODO change this to use a static var for start time for reusability
long long	get_elapsed_time(void)
{
	static long long	epoch = -1;
	struct timeval		tv;
	long long			current_time;

	gettimeofday(&tv, NULL);
	if (epoch == -1)
		epoch = tv.tv_usec;
	current_time = tv.tv_usec;
	return ((current_time - epoch) / 1000);
}
