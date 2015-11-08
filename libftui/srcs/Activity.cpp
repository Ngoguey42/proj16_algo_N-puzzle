// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:14:27 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/08 15:58:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <algorithm>
#include <iostream>

#include "ft/utils.hpp"
#include "ftlua/ftlua.hpp"
#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/Canvas.hpp"
#include "ftui/XmlParser.hpp"

namespace ftui
{

/*
** ************************************************************************** **
** Init-time / End-time -> instance.CTOR / instance.DTOR
*/

Activity::Activity(ft::Vec2<int> size) :
	_rootView(NULL),
	_eventMap(),
	_size(size),
	_l(nullptr)
{
	return ;
}

Activity::~Activity(void)
{
	if (_l != nullptr)
		lua_close(_l);
	// TODO: release views
	return ;
}

/*
** ************************************************************************** **
** Init-time -> instance.inflate
*/

static lua_State	*new_lua_env(void)
{
	lua_State *const	l = luaL_newstate();

	if (l == nullptr)
		throw std::runtime_error("Error while creating lua state");
	luaL_openlibs(l);
	// TODO: rpath in binary to write utils in .lua file
	ftlua::pushUtils(l);
	Canvas::pushTemplate(l);
	AView::pushViewTemplates(l);
	return l;
}

static void			load_views_scripts(
	lua_State *l, std::vector<std::string> &scripts_paths)
{
	for (auto const &fname : scripts_paths)
	{
		if (luaL_dofile(l, fname.c_str()))
			throw std::runtime_error(
				ft::f("error loading '%': '%'"
					  , fname, luaL_checkstring(l, -1)));
	}
	scripts_paths.clear();
	scripts_paths.shrink_to_fit();
	return ;
}

void			Activity::inflate(std::istream &stream)
{
	XmlParser			xml(stream);
	AView				*v;
	XmlParser::State	state;

	FTASSERT(_l == nullptr, "Activity.inflate called again");
	_l = new_lua_env();
	if (!xml.next(state))
		throw std::runtime_error("Activity should own at least 1 view");
	FTASSERT(state == XmlParser::State::START, "Cannot fail");
	v = AView::getFactory(xml.getMarkupName())(xml, *this);
	this->_rootView = new Activity::RootViewHolder(xml, v, this->_size);
	v->inflate(xml, *this);
	v->setViewHolder(this->_rootView);
	if (xml.next(state))
		throw std::runtime_error("Activity should not own more than 1 view");
	load_views_scripts(_l, _scriptsPaths);
	FTASSERT(lua_gettop(_l) == 0, "Something went wrong...");
	return ;
}

void			Activity::saveScriptPath(std::string const &str)
{
	std::stringstream	ss(str);
	char				buf[64];

	// TODO accept folder as parameter
	while (ss.getline(buf, sizeof(buf), ';'))
		_scriptsPaths.push_back(buf);
	return ;
}

/*
** ************************************************************************** **
** Render-time -> internal functions
*/

lua_State		*Activity::getLuaState(void) const
{
	return (_l);
}

AView			*Activity::getRoot(void)
{
	if (_rootView == NULL)
		return (NULL);
	return (_rootView->getView());
}

AView const		*Activity::getRoot(void) const
{
	if (_rootView == NULL)
		return (NULL);
	return (_rootView->getView());
}

/*
** ************************************************************************** **
** Render-time -> instance.render
*/

void			Activity::render(Canvas &canvas)
{
	AView		*rv;

	if (!canvas.isInLua(_l))
		canvas.pushLua(_l);
	rv = this->_rootView == nullptr ? nullptr : this->_rootView->getView();
	if (rv == nullptr)
		return ;
	if (rv->isUpdateQueried())
		rv->onUpdate();
	if (rv->isMeasureQueried())
	{
		rv->onMeasure();
		_rootView->setSize(_size);
	}
	if (rv->isRedrawQueried())
	{
		std::cout << "REDRAW REQ" << std::endl;
		rv->onDraw(canvas);
	}
	return ;
}

void			Activity::queryRedrawAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryRedraw();
}

void			Activity::queryMeasureAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryMeasure();
}

void			Activity::queryUpdateAll(void)
{
	if (_rootView != NULL)
		_rootView->getView()->queryUpdate();
}

/*
** ************************************************************************** **
** Render-time -> key/mouse entry point 'window event'->'activity event'
*/

bool			Activity::onKeyUp(int key_code)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyUp(key_code));
	return (false);
}

bool			Activity::onKeyDown(int key_code)
{
	if (_rootView != NULL && _rootView->getView()->isKeyboardTargeted())
		return (_rootView->getView()->onKeyDown(key_code));
	return (false);
}

/*
** ************************************************************************** **
** Render-time -> instance.*Event		(more in Activity.tpp)
*/

void			Activity::unregisterEvent(std::string const &event, AView *v)
{
	auto			it = this->_eventMap.find(event);
	auto const		ite = this->_eventMap.cend();

	while (it != ite)
	{
		if (it->second->getView() == v)
		{
			delete it->second;
			it = this->_eventMap.erase(it);
		}
		else
			it++;
	}
	return ;
}

/*
** ************************************************************************** **
** Render-time -> register 'c' function for 'lua->c' callback
*/

void			Activity::registerLuaCFun_global(
	std::string const &funName, lua_CFunction f)
{
	lua_register(_l, funName.c_str(), f);
	return ;
}

void			Activity::registerLuaCFun_table(
	std::string const &tabName
	, std::string const &funName
	, lua_CFunction f)
{
	ftlua::registerLuaCFunTable(_l, tabName, funName, f);
	return ;
}

};
