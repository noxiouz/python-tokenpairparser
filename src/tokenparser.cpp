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

#include <Python.h>
#include <tokenparser.hpp>

using namespace boost::spirit;


PyObject*
token_parser_t::construct(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	token_parser_t * self = reinterpret_cast<token_parser_t*>(type->tp_alloc(type, 0));
	self->parser_rule = eps_p;
	return reinterpret_cast<PyObject*>(self);
}

void token_parser_t::destruct(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	;
}

PyObject*
token_parser_t::skip(token_parser_t * self, PyObject * args){
	char c;
	if (!PyArg_ParseTuple(args, "c", &c)){
		return NULL;
	}
	self->parser_rule = self->parser_rule.copy()>>ch_p(c);
	Py_RETURN_NONE;
}

PyObject*
token_parser_t::skipTo(token_parser_t* self, PyObject* args){
	char c;
	if (!PyArg_ParseTuple(args, "c", &c)){
		return NULL;
	}
	self->parser_rule = self->parser_rule.copy()>>*~ch_p(c);
	Py_RETURN_NONE;
}

PyObject*
token_parser_t::upTo(token_parser_t * self, PyObject * args){
	char c;
	const char * key;
	if (!PyArg_ParseTuple(args, "sc",&key, &c)){
		return NULL;
	}
	self->_vtr_field.push_back(key);
	self->parser_rule = self->parser_rule.copy()>>
			(*~ch_p(c))[push_back_a(self->_vtr_value)];
	Py_RETURN_NONE;
}

PyObject*
token_parser_t::fromTo(token_parser_t* self, PyObject* args){
	char _from, _to;
	const char * key;
	if (!PyArg_ParseTuple(args, "scc",&key, &_from, &_to)){
		return NULL;
	}
	self->_vtr_field.push_back(key);
	self->parser_rule = self->parser_rule.copy()>>
			(ch_p(_from)>>*~ch_p(_to)>>ch_p(_to))[push_back_a(self->_vtr_value)];
	Py_RETURN_NONE;
}

PyObject*
token_parser_t::Parse(token_parser_t * self, PyObject * args){
	const char * input_string = NULL;
	if (!PyArg_ParseTuple(args, "s", &input_string)){
		return NULL;
	}
	if (parse( input_string, self->parser_rule, space_p).full ){
		Py_RETURN_TRUE;
	}
	else {
		Py_RETURN_FALSE;
	}
}

PyObject*
token_parser_t::matches(token_parser_t* self, PyObject *args){
	PyObject * dict = PyDict_New();
	for (int i=0; i<self->_vtr_value.size(); ++i){
		PyDict_SetItem(dict,
						Py_BuildValue("s",self->_vtr_field[i]),
						Py_BuildValue("s", self->_vtr_value[i].c_str())
					);
	}
	//Py_INCREF(dict);
	return dict;
}


PyObject* 
token_parser_t::clearMatches(token_parser_t* self, PyObject* args){
	self->_vtr_value.clear();
	self->_vtr_field.clear();
	Py_RETURN_NONE;
}

//==================================================================================

static PyMethodDef token_parse_methods[] = {
	{"skip",	(PyCFunction)token_parser_t::skip, METH_VARARGS, "skip symbol"},
	{"skipTo",	(PyCFunction)token_parser_t::skipTo, METH_VARARGS, "skipTo"},
	{"fromTo",	(PyCFunction)token_parser_t::fromTo, METH_VARARGS, "fromTo"},
	{"upTo",	(PyCFunction)token_parser_t::upTo, METH_VARARGS, "upTo"},
	{"parse",	(PyCFunction)token_parser_t::Parse, METH_VARARGS, "Parse"},
	{"matches", (PyCFunction)token_parser_t::matches, METH_NOARGS, "matches"},
	{"clearMatches", (PyCFunction)token_parser_t::clearMatches, METH_NOARGS, "clearmatches"},
    { NULL, NULL, 0, NULL }
};

PyTypeObject token_parser_type = {
    PyObject_HEAD_INIT(&PyType_Type)
    0, /* ob_size */
    "Parser", /* tp_name */
    sizeof(token_parser_t), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor)token_parser_t::destruct, /* tp_dealloc */
    0, /* tp_print */
    0, /* tp_getattr */
    0, /* tp_setattr */
    0, /* tp_compare */
    0, /* tp_repr */
    0, /* tp_as_number */
    0, /* tp_as_sequence */
    0, /* tp_as_mapping */
    0, /* tp_hash */
    0, /* tp_call */
    0, /* tp_str */
    0, /* tp_getattro */
    0, /* tp_setattro */
    0, /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "Tokenparser", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    token_parse_methods, /* tp_methods */
    0, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    0,//(initproc)client_object_t::initialize, /* tp_init */
    0, /* tp_alloc */
    token_parser_t::construct /* tp_new */
};
