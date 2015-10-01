// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   assert.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/29 07:32:08 by ngoguey           #+#    #+#             //
//   Updated: 2015/09/30 08:17:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASSERT_H
# define ASSERT_H
# include <string>

namespace ft
{

namespace Assert
{
// # define FTASSERT_IGNORE
# define FTASSERT_REPORT
// # define FTASSERT_HALT

# if (defined(FTASSERT_IGNORE) &&							\
	  (defined(FTASSERT_REPORT) || defined(FTASSERT_HALT)))
static_assert(false, "Too many FTASSERT options");
# elif !defined(FTASSERT_IGNORE) && !defined(FTASSERT_REPORT) &&	\
	!defined(FTASSERT_HALT)
static_assert(false, "Not enough FTASSERT options");
# endif

# ifdef FTASSERT_HALT
#  define FTASSERT_HALT_IMPL(MSG) throw std::logic_error(MSG)
# else
#  define FTASSERT_HALT_IMPL(MSG) do { (void)sizeof(MSG); } while (0)
# endif

# ifdef FTASSERT_IGNORE
#  define FTASSERT(X, ...) do{(void)sizeof(static_cast<size_t>(X));}while(0)
# else
#  define FTAARGS(X, ...) #X, __LINE__, __FILE__, __FUNCTION__, #__VA_ARGS__
#  define FTASSERT(X, ...)											\
	do {															\
		if (!(X))													\
		{															\
			ft::Assert::report(FTAARGS(X, ##__VA_ARGS__));			\
			FTASSERT_HALT_IMPL(										\
				ft::Assert::reportStr(FTAARGS(X, ##__VA_ARGS__)));	\
		}															\
	} while (0)
# endif

void		report(std::string const &condition,
				   int line,
				   std::string const &file,
				   std::string const &function,
				   std::string const &msg = "");
std::string	reportStr(std::string const &condition,
					  int line,
					  std::string const &file,
					  std::string const &function,
					  std::string const &msg = "");

};

};

#endif