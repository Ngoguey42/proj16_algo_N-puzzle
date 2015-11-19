// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cpp_utils.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/13 07:59:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 15:59:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/utils.hpp"

#include "ftlua/ftlua.hpp"

#include <iostream>
#include <functional>

namespace ftlua
{

std::string	stacktostring(lua_State *l)
{
	int const               top = lua_gettop(l);
	int                     i;
	std::string				ret;
	std::function<void()>   funcs[] =
	{
	[=,&i,&ret](){ret += "  none" "\n";},
	[=,&i,&ret](){ret += "   nil" "\n";},
	[=,&i,&ret](){ret += ft::f("  bool: %\n", lua_toboolean(l, i));},
	[=,&i,&ret](){ret += " lusrd" "\n";},
	[=,&i,&ret](){ret += ft::f("   nbr: %\n", lua_tonumber(l, i)); },
	[=,&i,&ret](){ret += ft::f("   str: %\n", lua_tostring(l, i)); },
	[=,&i,&ret](){ret += ft::f("   tab: %\n", (void*)lua_topointer(l, i)); },
	[=,&i,&ret](){ret += ft::f("  func: %\n", (void*)lua_tocfunction(l, i)); },
	[=,&i,&ret](){ret += "  usrd" "\n";},
	[=,&i,&ret](){ret += "thread" "\n";},
	};
	ret += ft::f("Stack dump: % Elements\n", top);
	for (i = 1; i <= top; i++)
	{
		ret += ft::f("[%]", i);
		funcs[lua_type(l, i) + 1]();
	}
	return ret;
}

void		stackdump(lua_State *l)
{
	std::cout << stacktostring(l);
	// int const               top = lua_gettop(l);
	// int                     i;
	// std::function<void()>   funcs[] =
	// {
	// 	[=, &i](){std::cout << "  none" << "\n";},
	// 	[=, &i](){std::cout << "   nil" << "\n";},
	// 	[=, &i](){std::cout << "  bool: " << lua_toboolean(l, i) << "\n";},
	// 	[=, &i](){std::cout << " lusrd" << "\n";},
	// 	[=, &i](){std::cout << "   nbr: " << lua_tonumber(l, i) <<  "\n";},
	// 	[=, &i](){std::cout << "   str: " << lua_tostring(l, i) << "\n";},
	// 	[=, &i](){std::cout << "   tab: "<<(void*)lua_topointer(l, i) << "\n";},
	// 	[=, &i](){std::cout << "  func: "<<(void*)lua_tocfunction(l, i) << "\n";},
	// 	[=, &i](){std::cout << "  usrd" << "\n";},
	// 	[=, &i](){std::cout << "thread" << "\n";},
	// };
	// std::cout << "Stack dump: " << top << " Elements" << std::endl;
	// for (i = 1; i <= top; i++)
	// {
	// 	std::cout << "[" << i << "]";
	// 	funcs[lua_type(l, i) + 1]();
	// }
	return ;
}

void		registerLuaCFunTable(
	lua_State *l
	, std::string const &tabName
	, std::string const &funName
	, lua_CFunction f)
{
	int     t;

	t = lua_getglobal(l, tabName.c_str());
	if (t != LUA_TTABLE)
		throw std::runtime_error(ft::f("Lua: Corrupted table (%)", tabName));
	(void)lua_pushstring(l, funName.c_str());
	(void)lua_pushcfunction(l, f);
	lua_settable(l, -3);
	lua_setglobal(l, tabName.c_str());
	return ;
}

};
