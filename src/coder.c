/* ************************************************************************** */
/*                                                                            */
/*                                                      ::::    :::           */
/*   coder.c                                           :+:+:   :+:            */
/*                                                    :+:+:+  +:+             */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+ +:+ +#+              */
/*                                                  +#+  +#+#+#               */
/*   Created: 2026/08/16 15:20:31 by ivan-der      #+#   #+#+#                */
/*   Updated: 2026/08/21 16:11:01 by ivan-der     ###    #### orminette :(    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

void	*action_process(void *c)
{
	t_coder				*coder;

	coder = (t_coder *)c;
	request_dongles(coder);
	// TODO make compile function
	// debug and refactor action can possibly happen here
	//
	// DEBUG
	// printf("coder %d, <-%d, %d->\n", coder->id, coder->dongles[0]->is_available, coder->dongles[1]->is_available);
	// usleep(1000);
	// printf("%lld ms\n", get_elapsed_time());

	return (0);
}
