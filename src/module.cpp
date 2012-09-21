/*
 * Copyright (c) 2012 Anton Tyurin <noxiouz@yandex.ru>
 *
 * This file is part of TokenPairParser.
 *
 * TokenPairParser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * TokenPairParser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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





