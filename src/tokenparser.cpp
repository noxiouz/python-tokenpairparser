/*
 * tokenparser.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: noxiouz
 */


#include <Python.h>
#include <tokenparser.hpp>
#include <iostream>

using namespace boost::spirit;

std::map<std::string, std::string> DICT;

PyObject* token_parser_t::construct(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	token_parser_t * self = reinterpret_cast<token_parser_t*>(type->tp_alloc(type, 0));
	self->parser_rule = eps_p;
	return reinterpret_cast<PyObject*>(self);
}

void token_parser_t::destruct(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	;
}

PyObject * token_parser_t::skip(token_parser_t * self, PyObject * args){
	char c;
	if (!PyArg_ParseTuple(args, "c", &c)){
		return NULL;
	}
	self->parser_rule = self->parser_rule.copy()>>ch_p(c);
	return Py_BuildValue("i",0);
}

PyObject * token_parser_t::upTo(token_parser_t * self, PyObject * args){
	char c;
	const char * key;
	if (!PyArg_ParseTuple(args, "sc",&key, &c)){
		return NULL;
	}
	//std::cout<<key<<std::endl;
	std::string str(key);

	self->parser_rule = self->parser_rule.copy()>>(*~ch_p(c)>>ch_p(c))[insert_at_a(DICT, key)];
	return Py_BuildValue("i",1);
}

PyObject * token_parser_t::Parse(token_parser_t * self, PyObject * args){
	const char * input_string = NULL;
	if (!PyArg_ParseTuple(args, "s", &input_string)){
		return NULL;
	}
	bool result;
	result = parse(input_string, self->parser_rule, space_p).full;
	std::map<std::string, std::string>::iterator it;
	for(it = DICT.begin(); it != DICT.end(); it++){
	std::cout << "Key: " << (*it).first << " Value: " << (*it).second <<std::endl;
	}
	return Py_BuildValue("i", result);
}



//==================================================================================

static PyMethodDef token_parse_methods[] = {
	{"skip", (PyCFunction)token_parser_t::skip, METH_VARARGS, "Test"},
	{"upTo", (PyCFunction)token_parser_t::upTo, METH_VARARGS, "upTo"},
	{"Parse",(PyCFunction)token_parser_t::Parse, METH_VARARGS, "Parsing"},
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
    "TokenParser", /* tp_doc */
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
