// Copyright (c) 2017 Stefan Mavrodiev
//
// GNU GENERAL PUBLIC LICENSE
//    Version 3, 29 June 2007
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "Python.h"
#include "libgpio.h"

/**
 * Set output value of GPIO. Pin must be configured as output or else raises
 * exception. For high output level - 1, low - 0.
 *
 * @param self
 * @param args Tuple that holds GPIO number and value
 * @return none
 */
static PyObject *py_output(PyObject *self, PyObject *args)
{
	int gpio;
	int value;

	/* Parse arguments. Two integers are required. */
	if (!PyArg_ParseTuple(args, "kb", &gpio, &value))
		return NULL;

	/* Set output value and check return status. */
	if (sunxi_gpio_output(gpio, value))
		return PyErr_SetFromErrno(PyExc_IOError);

	Py_RETURN_NONE;
}

/**
 * Read value of the pin configured as input. If its output raises exception.
 *
 * @param self
 * @param args GPIO number
 * @return value of the given pin
 */
static PyObject *py_input(PyObject *self, PyObject *args)
{
	int gpio;
	int val;


	/* Parse argument. One integer is required */
	if (!PyArg_ParseTuple(args, "k", &gpio))
		return NULL;

	/* Read value */
	if(sunxi_gpio_input(gpio, (uint8_t *)&val))
		return PyErr_SetFromErrno(PyExc_IOError);

	/* Return read value */
	return Py_BuildValue("b", val);
}

/**
 * Set configuration. See A20 datasheet for correct values.
 *
 * @param self
 * @param args GPIO number and configuration value
 * @return none
 */
static PyObject *py_setcfg(PyObject *self, PyObject *args)
{
	int gpio;
	int cfg;

	/* Parse arguments. Require two integers for GPIO number and configuration */
	if (!PyArg_ParseTuple(args, "kb", &gpio, &cfg))
		return NULL;

	/* Set configuration and check return status */
	if (sunxi_gpio_set_cfgpin(gpio, cfg) != 0)
		return PyErr_SetFromErrno(PyExc_IOError);

	Py_RETURN_NONE;
}

/**
 * Read current configuration of GPIO.
 *
 * @param self
 * @param args GPIO number
 * @return current configuration
 */
static PyObject *py_getcfg(PyObject *self, PyObject *args)
{
	int gpio;
	int cfg;

	/* Parse arguments */
	if (!PyArg_ParseTuple(args, "k", &gpio))
		return NULL;

	/* Read configuration*/
	if(sunxi_gpio_get_cfgpin(gpio, (uint8_t *)&cfg))
		return PyErr_SetFromErrno(PyExc_IOError);

	/* Return configuration */
	return Py_BuildValue("b", cfg);
}

/**
 *
 * Make initial initialization of the extention. This is done by map physical
 * memory to the virtual and thus gaining access to the memory. From there we
 * can do anything.
 *
 * @return none
 */
static PyObject *py_init(PyObject *self, PyObject *args)
{
	if (sunxi_gpio_init())
		return PyErr_SetFromErrno(PyExc_IOError);

	Py_RETURN_NONE;
}

/**
 *  Set pull-up/pull-down on pin defined as input.
 *
 * @param self
 * @param args
 * @return
 */
static PyObject *py_pullup(PyObject *self, PyObject *args)
{
	int gpio;
	int pull;

	/* Parse arguments */
	if (!PyArg_ParseTuple(args, "kb", &gpio, &pull))
		return NULL;

	/* Set pull-up */
	if (sunxi_gpio_pullup(gpio, pull))
		return PyErr_SetFromErrno(PyExc_IOError);

	Py_RETURN_NONE;
}


/* Define module methods */
static PyMethodDef module_methods[] = {
	{ "init",   py_init,   METH_NOARGS,  "Initialize module"     },
	{ "setcfg", py_setcfg, METH_VARARGS, "Set pin function"	     },
	{ "getcfg", py_getcfg, METH_VARARGS, "Get pin function"	     },
	{ "output", py_output, METH_VARARGS, "Set output state"	     },
	{ "pullup", py_pullup, METH_VARARGS, "Set pull-up/pull-down" },
	{ "input",  py_input,  METH_VARARGS, "Get input state"	     },
	{ NULL,	    NULL,      0,	     NULL		     }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef module_def = {
	PyModuleDef_HEAD_INIT,
	"gpio",
	NULL,
	-1,
	module_methods
};
#endif

PyMODINIT_FUNC
#if PY_MAJOR_VERSION >= 3
PyInit_gpio(void)
{
#else
initgpio(void) {
#endif

	PyObject *module = NULL;


#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(&module_def);
#else
	module = Py_InitModule("gpio", module_methods);
#endif


	if (module == NULL)
#if PY_MAJOR_VERSION >= 3
		return NULL;
#else
		return;
#endif

	PyModule_AddObject(module, "HIGH", Py_BuildValue("b", 1));
	PyModule_AddObject(module, "LOW", Py_BuildValue("b", 0));
	PyModule_AddObject(module, "INPUT", Py_BuildValue("b", SUNXI_GPIO_INPUT));
	PyModule_AddObject(module, "OUTPUT", Py_BuildValue("b", SUNXI_GPIO_OUTPUT));

	PyModule_AddObject(module, "PULLUP", Py_BuildValue("b", SUNXI_PULL_UP));
	PyModule_AddObject(module, "PULLDOWN", Py_BuildValue("b", SUNXI_PULL_DOWN));


#if PY_MAJOR_VERSION >= 3
	return module;
#else
	return;
#endif
}
