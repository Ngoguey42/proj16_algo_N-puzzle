// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rect.tpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/05 14:06:16 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/11 17:49:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

namespace ft
{

template<typename T>
Rect<T>::Rect(void) :
	left(0),
	top(0),
	right(0),
	bottom(0)
{
}

template<typename T>
Rect<T>::Rect(Rect<T> const &src) :
	left(src.left),
	top(src.top),
	right(src.right),
	bottom(src.bottom)
{
}

template<typename T>
Rect<T>::Rect(T left, T top, T right, T bottom) :
	left(left),
	top(top),
	right(right),
	bottom(bottom)
{
}

template<typename T>
Rect<T>::Rect(Vec2<T> pos, Vec2<T> size) :
	left(pos.x),
	top(pos.y),
	right(pos.x + size.x),
	bottom(pos.y + size.y)
{
}

template<typename T>
Rect<T>::~Rect(void)
{
}

template<typename T>
T			Rect<T>::getWidth(void) const
{
	return (right - left);
}

template<typename T>
T			Rect<T>::getHeight(void) const
{
	return (bottom - top);
}

template<typename T>
void		Rect<T>::setPos(Vec2<T> pos)
{
	right = pos.x + getWidth();
	bottom = pos.y + getHeight();
	left = pos.x;
	top = pos.y;
}

template<typename T>
Vec2<T>		Rect<T>::getPos(void) const
{
	return (Vec2<T>(top, left));
}

template<typename T>
void		Rect<T>::setSize(Vec2<T> size)
{
	right = left + size.x;
	bottom = top + size.y;
}

template<typename T>
Vec2<T>		Rect<T>::getSize(void) const
{
	return (Vec2<T>(getWidth(), getHeight()));
}

template<typename T>
void		Rect<T>::expand(T expand)
{
	left -= expand;
	top -= expand;
	right += expand;
	bottom += expand;
}

template<typename T>
bool		Rect<T>::collides(Rect<T> const &rect) const
{
//TODO: check, j'ai remove les >=/<= en >/<
	if (rect.left < right && rect.right > left
		&& rect.top < bottom && rect.bottom > top)
		return (true);
	return (false);
}

template<typename T>
bool		Rect<T>::collides(Rect<T> const &rect, Rect<T> &res) const
{
	if (!collides(rect))
		return (false);
	res.left = std::max(left, rect.left);
	res.top = std::max(top, rect.top);
	res.right = std::min(right, rect.right);
	res.bottom = std::min(bottom, rect.bottom);
	return (true);
}

template<typename T>
bool		Rect<T>::contains(Rect<T> const &rect) const
{
//TODO: check, j'ai remove les >=/<= en >/<
	if (rect.left > left && rect.top > top
		&& rect.right < right && rect.bottom < bottom)
		return (true);
	return (false);
}

template<typename T>
bool		Rect<T>::contains(Vec2<T> pt) const
{
//TODO: check, j'ai remove les >=/<= en >/<
	if (pt.x > left && pt.x < right
		&& pt.y > top && pt.y < bottom)
		return (true);
	return (false);
}

template<typename T>
void		Rect<T>::merge(Rect<T> const &rect)
{
	if (rect.left < left)
		left = rect.left;
	if (rect.top < top)
		top = rect.top;
	if (rect.right > right)
		right = rect.right;
	if (rect.bottom > bottom)
		bottom = rect.bottom;
}

template<typename T>
void		Rect<T>::merge(Vec2<T> pt)
{
	if (pt.x < left)
		left = pt.x;
	else if (pt.x > right)
		right = pt.x;
	if (pt.y < top)
		top = pt.y;
	else if (pt.y > bottom)
		bottom = pt.y;
}

template<typename T>
Rect<T>		Rect<T>::operator+(Vec2<T> offset) const
{
	return (Rect<T>(left + offset.x, top + offset.y,
		right + offset.x, bottom + offset.y));
}

template<typename T>
Rect<T>		&Rect<T>::operator+=(Vec2<T> offset)
{
	left += offset.x;
	top += offset.y;
	right += offset.x;
	bottom += offset.y;
	return (*this);
}

template<typename T>
Rect<T>		Rect<T>::operator-(Vec2<T> offset) const
{
	return (Rect<T>(left - offset.x, top - offset.y,
		right - offset.x, bottom - offset.y));
}

template<typename T>
Rect<T>		&Rect<T>::operator-=(Vec2<T> offset)
{
	left -= offset.x;
	top -= offset.y;
	right -= offset.x;
	bottom -= offset.y;
	return (*this);
}

template<typename T>
Rect<T>		Rect<T>::operator*(T scale) const
{
	return (ft::make_rect(left * scale, top * scale, right * scale,
		bottom * scale));
}

template<typename T>
Rect<T>		&Rect<T>::operator*=(T scale)
{
	left *= scale;
	top *= scale;
	right *= scale;
	bottom *= scale;
	return (*this);
}

template<typename T>
Rect<T>		&Rect<T>::operator=(Rect<T> const &rhs)
{
	left = rhs.left;
	top = rhs.top;
	right = rhs.right;
	bottom = rhs.bottom;
	return (*this);
}

template<typename T>
bool		Rect<T>::operator==(Rect<T> const &rhs) const
{
	return (left == rhs.left && top == rhs.top
		&& right == rhs.right && bottom == rhs.bottom);
}

template<typename T>
template<typename C>
Rect<T>::operator Rect<C>(void) const
{
	return (ft::make_rect(
		static_cast<C>(left),
		static_cast<C>(top),
		static_cast<C>(right),
		static_cast<C>(bottom)
	));
}

template<typename T>
Rect<T>		make_rect(T left, T top, T right, T bottom)
{
	return (Rect<T>(left, top, right, bottom));
}

template<typename T>
Rect<T>		make_rect(Vec2<T> pos, Vec2<T> size)
{
	return (Rect<T>(pos, size));
}

static_assert(!std::is_polymorphic<Rect<int>>(), "It shouldn't be!");

};
