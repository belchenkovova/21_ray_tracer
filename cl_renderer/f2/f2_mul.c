/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f2_mul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:27:57 by ashari            #+#    #+#             */
/*   Updated: 2019/09/29 12:27:59 by ashari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f2.h"

RT_F2_API			f2_mul_components(RT_F2_API a, RT_F2_API b)
{
	return ((RT_F2_API){a.x * b.x, a.y * b.y});
}

RT_F2_API			f2_mul(const RT_F2_API a, double value)
{
	return ((RT_F2_API){a.x * value, a.y * value});
}
