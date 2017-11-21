pyA64
=====

|Build Status|

Description
-----------

The package provide methods for controlling GPIO pins via memory access. It's written for
`A64-OLinuXino <https://www.olimex.com/Products/OLinuXino/A64/A64-OLinuXino/open-source-hardware>`__,
but it can be used with other boards. In this case proper operation is
not guaranteed.

**Notes**:

	* When using GPIO make sure that the desired gpio is not used by another periphery.
	* Using this library requires root access.
	* Currently (0.1.0) port L is not supported, because the memory cannot be accessed from userspace.

GPIO methods
------------

The following methods are available:

* **init()** - Make initialization of the module. Must be called first.
* **getcfg()** - Read current configuration of gpio.
* **setcfg()** - Write configuration to gpio.
* **input()** - Return current value of gpio.
* **output()** - Set output value.
* **pullup()** - Set pull-up/pull-down.

The available constants are:

* **HIGH** - 1
* **LOW** - 0
* **INPUT** - 0
* **OUPTUT** - 1
* **PULLUP** - 1
* **PULLDOWN** - 2

The gpio are named two ways:

* By port name: PH0, PG2, PE10, etc. These can be imported from port module:

.. code:: python

	>>> from pyA64.gpio import port
	>>> dir(port)

* By connector name and pin number: gpio2p12, gpio3p8, lcdp18, uext1p3 and etc:

.. code:: python

	>>> from pyA64.gpio import connector
	>>> dir(connector)

Generally these constants are just an offset in the memory from the base
GPIO address, so they can be assigned to a number type variable.

.. code:: python

	>>> led = port.PE17
	>>> print led
	226

Changelog
---------

-  pyA64 0.1.0 (21 NOV 2017)

	- Initial release


.. |Build Status| image:: https://travis-ci.org/StefanMavrodiev/pyA64.svg?branch=master
   :target: https://travis-ci.org/StefanMavrodiev/pyA64
