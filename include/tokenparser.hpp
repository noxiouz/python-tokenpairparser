/*
 * tokenparser.hpp
 *
 *  Created on: Sep 16, 2012
 *      Author: noxiouz
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <map>

#include <Python.h>
#include <boost/spirit/core.hpp>
#include <boost/spirit/dynamic/stored_rule.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
#include <boost/spirit/actor/insert_at_actor.hpp>

extern PyTypeObject token_parser_type;

using namespace boost::spirit;

class token_parser_t {
	public:
		PyObject_HEAD

		static PyObject * construct(PyTypeObject * type, PyObject * args, PyObject * kwargs);
		static void destruct(PyTypeObject * type, PyObject * args, PyObject * kwargs);
		static PyObject * skip(token_parser_t * self, PyObject * args);
		static PyObject * Parse(token_parser_t * self, PyObject * args);
		static PyObject * upTo(token_parser_t * self, PyObject * args);
	private:
		stored_rule<> parser_rule;
		//std::string key;
};



#endif /* PARSER_HPP_ */
