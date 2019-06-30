/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashari <ashari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 19:11:07 by ashari            #+#    #+#             */
/*   Updated: 2019/06/30 19:11:08 by ashari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"

typedef struct				s_material
{
	t_vector3				color;
	float					diffuse;
	float					specular;
	float					reflect;
}							t_material;

#endif
