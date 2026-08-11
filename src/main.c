/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/07 12:23:34 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/11 11:45:32 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*coder_compile(void *p)
{
	printf("hi %p\n", p);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	th1;
	t_ctx		ctx;

	if (argc != 9 || get_args(argv, &ctx) || ctx.coders > MAX_THREADS)
	{
		fprintf(stderr, "Incorrect arguments!\nSee 'make help'.\n");
		return (1);
	}
	pthread_create(&th1, NULL, &coder_compile, NULL);
	pthread_join(th1, NULL);
	return (0);
}
