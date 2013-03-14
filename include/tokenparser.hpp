/*
 * Copyright (c) 2012 Anton Tyurin <noxiouz@yandex.ru>
 *
 * This file is part of Tokenparser.
 *
 * Tokenparser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tokenparser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <Python.h>

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_stored_rule.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
/*
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_stored_rule.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
*/
extern PyTypeObject token_parser_type;

using namespace boost::spirit::classic;

class token_parser_t {
	public:
		PyObject_HEAD

		static PyObject* construct(PyTypeObject * type, PyObject * args, PyObject * kwargs);
		static void destruct(token_parser_t* type);
		static PyObject* skip(token_parser_t* self, PyObject* args);
		static PyObject* skipTo(token_parser_t* self, PyObject* args);
		static PyObject* fromTo(token_parser_t* self, PyObject* args);
		static PyObject* upTo(token_parser_t* self, PyObject* args);
		static PyObject* Parse(token_parser_t* self, PyObject* args);
		static PyObject* MultilineParse(token_parser_t* self, PyObject* args);
		static PyObject* matches(token_parser_t* self);
		static PyObject* clearMatches(token_parser_t* self);
	private:
		stored_rule<> parser_rule;
		std::vector<std::string> _vtr_value;
		std::vector<const char *> _vtr_field;
};



#endif /* PARSER_HPP_ */
