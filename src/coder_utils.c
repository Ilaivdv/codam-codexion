/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coder_utils.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: ivan-der <ivan-der@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2026/08/11 14:44:37 by ivan-der     #+#    #+#                  */
/*   Updated: 2026/08/11 20:39:50 by ivan-der     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "../include/coder.h"
#include <stdio.h>

void	*init_coder(void *p)
{
	printf("Hi %p\n", p);
	return (0);
}
