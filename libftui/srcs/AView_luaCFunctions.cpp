// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView_luaCFunctions.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/04 11:52:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/10 15:25:45 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/AView.hpp"
#include "ftui/IViewHolder.hpp"
#include "ftui/luaCFunctions_helpers.hpp"

namespace ftui
{

#define DEF_LUACFUN_GSUFFIX(NAME, NUMIN, NUMOUT)			\
int			AView::NAME##G(lua_State *l)					\
{															\
	return luaCFunHelper<NUMIN, NUMOUT>(l, &AView::NAME);	\
}

// DEF_LUACFUN_GSUFFIX(setRequestedSize, 3, 0) //NYI
DEF_LUACFUN_GSUFFIX(setAlpha, 2, 0)
DEF_LUACFUN_GSUFFIX(setVisibility, 2, 0)
DEF_LUACFUN_GSUFFIX(setParam, 3, 0)
DEF_LUACFUN_GSUFFIX(hookMouseScroll, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseClick, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseMove, 2, 0)
DEF_LUACFUN_GSUFFIX(hookMouseCapture, 2, 0)
DEF_LUACFUN_GSUFFIX(hookKeyboard, 2, 0)
DEF_LUACFUN_GSUFFIX(queryUpdate, 1, 0)
DEF_LUACFUN_GSUFFIX(queryMeasure, 1, 0)
DEF_LUACFUN_GSUFFIX(queryRedraw, 1, 0)

// DEF_LUACFUN_GSUFFIX(getRequestedSize, 1, 2) //NYI
// DEF_LUACFUN_GSUFFIX(getPos, 1, 2) //NYI
// DEF_LUACFUN_GSUFFIX(getSize, 1, 2) //NYI
int			AView::getIdG(lua_State *l)
{
	AView *const				i = luaCFunRetreiveSelf<AView>(l, -1);
	std::string const *const	s = i->getId();

	if (s == nullptr)
		lua_pushnil(l);
	else
		lua_pushstring(l, s->c_str());
	return (1);
}

DEF_LUACFUN_GSUFFIX(getParent, 1, 1) //TODO untested
// int			AView::getParentG(lua_State *l)
// {
// 	AView *const	i = luaCFunRetreiveSelf<AView>(l, -1);
// 	ALayout *const	p = i->getParent();

// 	if (p == nullptr)
// 		lua_pushnil(l);
// 	else
// 	{
// 		lua_pushglobaltable(l);
// 		lua_pushlightuserdata(l, p);
// 		lua_gettable(l, -2);
// 	}
// 	return (1);
// }

DEF_LUACFUN_GSUFFIX(getAlpha, 1, 1)
DEF_LUACFUN_GSUFFIX(isVisible, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseOver, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseScrollTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseClickTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isMouseCaptureTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isKeyboardTargeted, 1, 1)
DEF_LUACFUN_GSUFFIX(isUpdateQueried, 1, 1)
DEF_LUACFUN_GSUFFIX(isMeasureQueried, 1, 1)
DEF_LUACFUN_GSUFFIX(isRedrawQueried, 1, 1)

int			AView::getRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getRequestedSize();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::getPosG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getPos();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::getSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -1)->getViewHolder();
	ft::Vec2<int>		s;

	if (h == nullptr)
		return (0);
	s = h->getSize();
	lua_pushinteger(l, s.x);
	lua_pushinteger(l, s.y);
	return (2);
}

int			AView::setRequestedSizeG(lua_State *l)
{
	IViewHolder *const	h = luaCFunRetreiveSelf<AView>(l, -3)->getViewHolder();
	ft::Vec2<int>		s;

	s.x = luaL_checkinteger(l, -1);
	s.y = luaL_checkinteger(l, -2);
	lua_pop(l, 2);
	if (h == nullptr)
		h->setRequestedSize(s);
	return (0);
}

};
