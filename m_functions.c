/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpham <mpham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:41:25 by mpham             #+#    #+#             */
/*   Updated: 2018/02/12 13:29:25 by mpham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

vec3_t	vec3(float x, float y, float z)
{
	vec3_t	vec3;

	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return (vec3);
}

vec4_t	vec4(float x, float y, float z, float w)
{
	vec4_t	vec4;

	vec4.x = x;
	vec4.y = y;
	vec4.z = z;
	vec4.w = w;
	return (vec4);
}

mat4_t	mat4(t_matrix m)
{
	return (mat4_t)
	{
		{{m.m00, m.m01, m.m02, m.m03},
			{m.m10, m.m11, m.m12, m.m13},
			{m.m20, m.m21, m.m22, m.m23},
			{m.m30, m.m31, m.m32, m.m33}}
	};
}

mat4_t	mult_mat4(mat4_t m1, mat4_t m2)
{
	int		i;
	int		j;
	int		k;
	mat4_t	result;

	i = 0;
	j = 0;
	k = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			result.m[i][j] = 0;
			while (k < 4)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

vec4_t	m4_mult_pos(mat4_t matrix, vec4_t position)
{
	vec4_t result;

	result = vec4(matrix.m[0][0] * position.x + matrix.m[0][1] * position.y +
	matrix.m[0][2] * position.z + matrix.m[0][3] * position.w,
	matrix.m[1][0] * position.x + matrix.m[1][1] * position.y +
	matrix.m[1][2] * position.z + matrix.m[1][3] * position.w,
	matrix.m[2][0] * position.x + matrix.m[2][1] * position.y +
	matrix.m[2][2] * position.z + matrix.m[2][3] * position.w,
	matrix.m[3][0] * position.x + matrix.m[3][1] * position.y +
	matrix.m[3][2] * position.z + matrix.m[3][3] * position.w);
	return (result);
}
