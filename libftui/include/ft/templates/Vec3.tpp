/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 14:45:49 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 17:29:45 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{

template <typename T>
Vec3<T>::Vec3(void) :
	x(0),
	y(0),
	z(0)
{
}

template <typename T>
Vec3<T>::Vec3(Vec2<T> const &src, T z) :
	x(src.x),
	y(src.y),
	z(z)
{
}

template <typename T>
Vec3<T>::Vec3(Vec3<T> const &src) :
	x(src.x),
	y(src.y),
	z(src.z)
{
}

template <typename T>
Vec3<T>::Vec3(T v) :
	x(v),
	y(v),
	z(v)
{
}

template <typename T>
Vec3<T>::Vec3(T x, T y, T z) :
	x(x),
	y(y),
	z(z)
{
}

template <typename T>
Vec3<T>::~Vec3(void)
{
}

template <typename T>
Vec3<T>		&Vec3<T>::operator=(Vec3<T> const &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

template <typename T>
bool		Vec3<T>::operator==(Vec3<T> const &rhs) const
{
	return (rhs.x == x && rhs.y == y && rhs.z == z);
}

# define DECLARE_OPERATOR(OP) \
template <typename T>											\
Vec3<T>		&Vec3<T>::operator OP##=(Vec3<T> const &rhs)		\
{																\
	x OP##= rhs.x;												\
	y OP##= rhs.y;												\
	z OP##= rhs.z;												\
	return (*this);												\
}																\
template <typename T>											\
Vec3<T>		&Vec3<T>::operator OP##=(T v)						\
{																\
	x OP##= v;													\
	y OP##= v;													\
	z OP##= v;													\
	return (*this);												\
}																\
template <typename T>											\
Vec3<T>		Vec3<T>::operator OP(Vec3<T> const &rhs) const		\
{																\
	return (Vec3<T>(x OP rhs.x, y OP rhs.y, z OP rhs.z));		\
}																\
template <typename T>											\
Vec3<T>		Vec3<T>::operator OP(T v) const						\
{																\
	return (Vec3<T>(x OP v, y OP v, z OP v));					\
}

DECLARE_OPERATOR(+)
DECLARE_OPERATOR(-)
DECLARE_OPERATOR(*)
DECLARE_OPERATOR(/)

# undef DECLARE_OPERATOR

};
