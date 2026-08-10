/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/07 12:23:34 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/10 22:05:11 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*do_thing(void *p)
{
	printf("hi %p\n", p);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	th1;
	t_ctx		ctx;

	if (argc != 9)
	{
		fprintf(stderr,
			"Incorrect arguments!\nSee 'make help' for proper usage.\n");
		return (1);
	}
	get_args(argv, &ctx);
	pthread_create(&th1, NULL, &do_thing, NULL);
	pthread_join(th1, NULL);
	return (0);
}
