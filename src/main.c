/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/07 12:23:34 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/10 12:42:24 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void*	do_thing()
{
	printf("hi\n");
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t th1;
	argc = 0;
	argv = NULL;
	pthread_create(&th1, NULL, &do_thing, NULL); 
	pthread_join(th1, NULL);
	return (0);
}

