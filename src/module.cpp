/*
 * module.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: noxiouz
 */

#include "tokenparser.hpp"

extern "C" {
    void init_tokenparser(void) {
        PyObject * module = Py_InitModule3(
            "_tokenparser",
            NULL,
            "TokenParser"
        );

        if(PyType_Ready(&token_parser_type) < 0) {
            return;
        }

        Py_INCREF(&token_parser_type);

        PyModule_AddObject(
            module,
            "TokenParser",
            reinterpret_cast<PyObject*>(&token_parser_type)
        );
    }
}





