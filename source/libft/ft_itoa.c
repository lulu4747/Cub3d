/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lfourage <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/16 11:46:49 by lfourage     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 18:30:53 by lfourage    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_buflen(unsigned long int nb, int len)
{
	int ret;

	ret = 1;
	if (nb >= (unsigned long int)len)
	{
		ret += (ft_buflen((nb / len), len));
	}
	return (ret);
}

char		*ft_uitoa_base(unsigned long long int nb, char *base)
{
	int		len;
	int		blen;
	char	*buffer;

	buffer = NULL;
	len = ft_strlen(base);
	blen = ft_buflen(nb, len);
	if (!(buffer = malloc(sizeof(char) * (blen + 1))))
		return (NULL);
	buffer[blen] = 0;
	while (--blen >= 0)
	{
		buffer[blen] = base[(nb % len)];
		nb = nb / len;
	}
	return (buffer);
}

char		*ft_itoa_base(long long int nb, char *base)
{
	int		len;
	int		blen;
	int		neg;
	char	*buffer;

	buffer = NULL;
	blen = (nb < 0) ? 1 : 0;
	neg = (nb < 0) ? -1 : 1;
	len = ft_strlen(base);
	blen += ft_buflen((long int)(nb * neg), len);
	if (!(buffer = ft_calloc(sizeof(char), (blen + 1))))
		return (NULL);
	buffer[blen] = 0;
	(nb < 0) ? buffer[0] = '-' : 0;
	nb = nb * neg;
	while (--blen >= 0 && buffer[blen] != '-')
	{
		buffer[blen] = base[(nb % len)];
		nb = nb / len;
	}
	return (buffer);
}
