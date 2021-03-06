/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpham <mpham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:41:25 by mpham             #+#    #+#             */
/*   Updated: 2018/02/01 12:48:18 by mpham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
# include "math3D.h"

// 3D Vectors

vec3_t  vec3(float x, float y, float z)
{
    vec3_t  vec3;

    vec3.x = x;
    vec3.y = y;
    vec3.z = z;
    return (vec3);
}

vec3_t	vec3_add(vec3_t a, vec3_t b)
{
    vec3_t  vec3;

    vec3.x = a.x + b.x;
    vec3.y = a.y + b.y;
    vec3.z = a.z + b.z;
    return (vec3);
}

vec3_t	vec3_sub(vec3_t a, vec3_t b)
{
    vec3_t  vec3;
    
        vec3.x = a.x - b.x;
        vec3.y = a.y - b.y;
        vec3.z = a.z - b.z;
        return (vec3);
}

vec3_t	vec3_mult(vec3_t a, vec3_t b)
{
    vec3_t vec3;

    vec3.x = a.x * b.x;
    vec3.y = a.y * b.y;
    vec3.z = a.z * b.z;
    return (vec3);
}

vec3_t	vec3_div(vec3_t a, vec3_t b)
{
    vec3_t vec3;

    vec3.x = a.x / b.x;
    vec3.y = a.y / b.y;
    vec3.z = a.z / b.z;
    return (vec3);
}

void  ft_print_vec3(vec3_t vec3)
{
    ft_putchar('|');
    ft_putnbr(vec3.x);
    ft_putchar('|');
    ft_putchar('\n');
    ft_putchar('|');
    ft_putnbr(vec3.y);
    ft_putchar('|');
    ft_putchar('\n');
    ft_putchar('|');
    ft_putnbr(vec3.z);
    ft_putchar('|');
}

// 4D Vectors

vec4_t  vec4(float x, float y, float z, float w)
{
    vec4_t  vec4;

    vec4.x = x;
    vec4.y = y;
    vec4.z = z;
    vec4.w = w;
    return (vec4);
}

// Matrice 4 x 4

mat4_t  mat4(t_matrix m) 
{
    return (mat4_t)
    {
        {{m.m00, m.m01, m.m02, m.m03},
         {m.m10, m.m11, m.m12, m.m13},
         {m.m20, m.m21, m.m22, m.m23},
         {m.m30, m.m31, m.m32, m.m33}}
    };
}

void    ft_print_mat4(mat4_t matrice)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 4)
    {
        while (j < 4)
        {
            ft_putnbr(matrice.m[i][j]);
            ft_putchar('|');
            j++;
        }
        if (i < 3)
            ft_putchar('\n');
        j = 0;
        i++;
    }
}

mat4_t  m4_identity(void)
{
    return mat4((t_matrix)
		{1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1}
    );
}

mat4_t  ft_mult_mat4(mat4_t m1, mat4_t m2)
{
    int     i;
    int     j;
    int     k;
    mat4_t  result;
    
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

mat4_t  m4_translation(vec3_t offset)
{
    return mat4((t_matrix)
		{1, 0, 0, offset.x,
		 0, 1, 0, offset.y,
		 0, 0, 1, offset.z,
		 0, 0, 0, 1}
    );
}

mat4_t	m4_scaling(vec3_t scale)
{
    return mat4((t_matrix)
		{scale.x, 0, 0, 0,
		 0, scale.y, 0, 0,
		 0, 0, scale.z, 0,
		 0, 0, 0, 1}
    );
}

mat4_t	m4_rotationx(float angle)
{
    return mat4((t_matrix)
		{1, 0, 0, 0,
		 0, cos(angle), -sin(angle), 0,
		 0, sin(angle), cos(angle), 0,
		 0, 0, 0, 1}
    );
}

mat4_t	m4_rotationy(float angle)
{
    return mat4((t_matrix)
		{cos(angle), 0, sin(angle), 0,
		 0, 1, 0, 0,
		 -sin(angle), 0, cos(angle), 0,
		 0, 0, 0, 1}
    );
}

mat4_t	m4_rotationz(float angle)
{
    return mat4((t_matrix)
		{cos(angle), -sin(angle), 0, 0,
		 sin(angle), cos(angle), 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1}
    );
}

mat4_t  m4_rotation(float angle, vec3_t e)
{
    float x;
    float y;
    float z;
    float c;
    float s;

    x = e.x;
    y = e.y;
    z = e.z;
    c = cos(angle);
    s = sin(angle);

    return mat4((t_matrix)
        {(x * x * (1 - c)) + c, (x * y * (1 - c)) - (z * s) , (x * z * (1 - c)) + (y * s), 0,
         (x * y * (1 - c)) + (z * s), (y * y * (1- c)) + c, (y * z * (1 - c )) - (x * s), 0,
         (x * z * (1 - c)) - (y * s), (y * z * (1 - c)) + (x * s), (z * z * (1 - c)) + c, 0,
         0, 0, 0, 1}
    );
}

vec4_t m4_mult_pos(mat4_t matrix, vec4_t position) 
{
	vec4_t result = vec4(
		matrix.m[0][0] * position.x + matrix.m[0][1] * position.y + matrix.m[0][2] * position.z + matrix.m[0][3] * position.w,
		matrix.m[1][0] * position.x + matrix.m[1][1] * position.y + matrix.m[1][2] * position.z + matrix.m[1][3] * position.w,
        matrix.m[2][0] * position.x + matrix.m[2][1] * position.y + matrix.m[2][2] * position.z + matrix.m[2][3] * position.w,
        matrix.m[3][0] * position.x + matrix.m[3][1] * position.y + matrix.m[3][2] * position.z + matrix.m[3][3] * position.w
	);	
	return result;
}


mat4_t m4_perspective(float vertical_field_of_view_in_deg, float aspect_ratio, float near_view_distance, float far_view_distance) 
{
	float fovy_in_rad = vertical_field_of_view_in_deg / 180 * PI;
	float f = 1 / tan(fovy_in_rad / 2);
	float ar = aspect_ratio;
	float nd = near_view_distance, fd = far_view_distance;
	
	return mat4((t_matrix)
		 {f / ar,          0,                0,                0,
		 0,                f,                0,                0,
		 0,                0,               (-fd-nd)/(nd-fd),  (2*fd*nd)/(nd-fd),
		 0,                0,               1,                0}
	);
}

float  vec3_length(vec3_t v)                    { return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);          }
float  vec3_dot   (vec3_t a, vec3_t b)          { return a.x*b.x + a.y*b.y + a.z*b.z;                 }
vec3_t vec3_muls  (vec3_t a, float s)           { return (vec3_t){ a.x * s,   a.y * s,   a.z * s   }; }
vec3_t vec3_norm(vec3_t v) {
	float len = vec3_length(v);
	if (len > 0)
		return (vec3_t){ v.x / len, v.y / len, v.z / len };
	else
		return (vec3_t){ 0, 0, 0};
}
vec3_t vec3_cross(vec3_t a, vec3_t b) {
	return (vec3_t){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

mat4_t m4_look_at(vec3_t from, vec3_t to, vec3_t up) {
	vec3_t z = vec3_muls(vec3_norm(vec3_sub(to, from)), -1);
	vec3_t x = vec3_norm(vec3_cross(up, z));
	vec3_t y = vec3_cross(z, x);
	
	return mat4((t_matrix)
		{x.x, x.y, x.z, -vec3_dot(from, x),
		y.x, y.y, y.z, -vec3_dot(from, y),
		z.x, z.y, z.z, -vec3_dot(from, z),
		0,   0,   0,    1}
	);
}

