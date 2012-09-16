/*
 * gil.hpp
 *
 *  Created on: Sep 16, 2012
 *      Author: noxiouz
 */

#ifndef GIL_HPP_
#define GIL_HPP_

#include <Python.h>

class allow_threads_t{
	public:
    	inline allow_threads_t():
    		m_thread_state(PyEval_SaveThread()) {};

    	inline ~allow_threads_t()
    	{
    		PyEval_RestoreThread(m_thread_state);
    		m_thread_state = NULL;
    	}

	private:
    	PyThreadState * m_thread_state;
};



#endif /* GIL_HPP_ */
