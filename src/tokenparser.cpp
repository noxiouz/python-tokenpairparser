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
#include <gil.hpp>


using namespace boost::spirit;


PyObject*
token_parser_t::construct(PyTypeObject * type, PyObject *args, PyObject * kwargs) {
    (void) args;
    (void) kwargs;
 	token_parser_t * self = reinterpret_cast<token_parser_t*>(type->tp_alloc(type, 0));
	self->parser_rule = eps_p;
	return reinterpret_cast<PyObject*>(self);
}

void token_parser_t::destruct(token_parser_t* self) {
	self->ob_type->tp_free(self);
}


PyDoc_STRVAR(skip__doc__,
"skip(char)\n\n\
:param char: skiping char\n\n\
Skip giving symbol");

PyObject*
token_parser_t::skip(token_parser_t * self, PyObject * args) {
	char c;
	if (!PyArg_ParseTuple(args, "c:skip", &c)){
		return NULL;
	}
	self->parser_rule = self->parser_rule.copy()>>ch_p(c);
	Py_RETURN_NONE;
}


PyDoc_STRVAR(skipTo__doc__,
"skipTo(char)\n\n\
:param char: letter to the occurrence of which skipping characters \n\n\
Skip all characters until the occurrence of ``char`` (excludes ``char``)");

PyObject*
token_parser_t::skipTo(token_parser_t* self, PyObject* args){
	char c;
	if (!PyArg_ParseTuple(args, "c:skipTo", &c)){
		return NULL;
	}
	self->parser_rule = self->parser_rule.copy()>>*~ch_p(c);
	Py_RETURN_NONE;
}


PyDoc_STRVAR(upTo__doc__,
"upTo(field, char)\n\n\
:param field: field's name\n\
:param char: letter to the occurrence of which capturing characters \n\n\
Capture all characters until the occurrence of ``char`` (include ``char``)");

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


PyDoc_STRVAR(fromTo__doc__,
"fromTo(field, from, to)\n\n\
:param field: string\n\
:param from: char\n\
:param to: char\n\n\
Capture all characters from ``from`` to ``to`` (include ``to``) into ``field``");

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

PyDoc_STRVAR(Parse__doc__,
"parse(input) -> bool\n\n\
:param input: input string for parsing \n\n\
Parse giving input string. In the case of full compliance with the rules\n\
return ``True``, otherwise - ``False``");

PyObject*
token_parser_t::Parse(token_parser_t * self, PyObject * args){
    clearMatches(self);
	const char * input_string = NULL;
	if (!PyArg_ParseTuple(args, "s", &input_string)){
		return NULL;
	}
	if (parse(input_string, self->parser_rule).full ){
		Py_RETURN_TRUE;
	}
	else {
		Py_RETURN_FALSE;
	}
}



PyObject*
token_parser_t::matches(token_parser_t* self){
	PyObject * dict = PyDict_New();
	for (size_t i=0; i < self->_vtr_value.size(); ++i){
        PyObject* value = Py_BuildValue("s", self->_vtr_value[i].c_str());
		PyDict_SetItemString(dict,
						self->_vtr_field[i],
						value
					);
        Py_DECREF(value);
	}
	return dict;
}


PyObject* 
token_parser_t::clearMatches(token_parser_t* self){
	self->_vtr_value.clear();
	self->_vtr_field.clear();
	Py_RETURN_NONE;
}


PyObject* 
token_parser_t::MultilineParse(token_parser_t *self, PyObject *args){
    PyObject* input_lines;
    if (!PyArg_ParseTuple(args, "O", &input_lines)){
        return NULL;
    }
    PyObject* iterator = PyObject_GetIter(input_lines);
    if (iterator == NULL){
        return NULL;
    }

    clearMatches(self);
    PyObject *list = PyList_New(0);
    PyObject* item;
    // http://docs.python.org/2/c-api/iter.html?highlight=pyiter_next#PyIter_Next
    while (item = PyIter_Next(iterator)) { 
        const char* tm = NULL; 
        tm = PyString_AS_STRING(item);
	if (parse(tm, self->parser_rule).full) {
            PyObject* value = matches(self);
            PyList_Append(list, value);
            Py_DECREF(value);
        }
        clearMatches(self);
        Py_DECREF(item);
    }
    if (PyErr_Occurred()) {
            Py_DECREF(list);
            return NULL;
        }
    Py_DECREF(iterator);
    return list;
}

//==================================================================================

static PyMethodDef token_parse_methods[] = {
	{"skip",	(PyCFunction)token_parser_t::skip, METH_VARARGS, skip__doc__},
	{"skipTo",	(PyCFunction)token_parser_t::skipTo, METH_VARARGS, skipTo__doc__},
	{"fromTo",	(PyCFunction)token_parser_t::fromTo, METH_VARARGS, fromTo__doc__},
	{"upTo",	(PyCFunction)token_parser_t::upTo, METH_VARARGS, upTo__doc__},
	{"parse",	(PyCFunction)token_parser_t::Parse, METH_VARARGS, Parse__doc__},
	{"multilinesParse",	(PyCFunction)token_parser_t::MultilineParse, METH_VARARGS, "Parse multilines like tuple or list of strings"},
	{"matches", (PyCFunction)token_parser_t::matches, METH_NOARGS, "Return result as dict"},
	{"clearMatches", (PyCFunction)token_parser_t::clearMatches, METH_NOARGS, "Clear result"},
    { NULL, NULL, 0, NULL }
};

PyTypeObject token_parser_type = {
    PyObject_HEAD_INIT(&PyType_Type)
    0, /* ob_size */
    "Tokenparser", /* tp_name */
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
