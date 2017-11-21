from distutils.core import setup
from distutils.core import Extension
import pyA64
import sys

modules = [
    Extension('pyA64.gpio.gpio', sources=['pyA64/gpio/libgpio.c', 'pyA64/gpio/gpio.c']),
    Extension('pyA64.gpio.connector', sources=['pyA64/gpio/connector/connector.c']),
    Extension('pyA64.gpio.port', sources=['pyA64/gpio/port/port.c']),
]

setup(
    name='pyA64',
    version=pyA64.__version__,
    author=pyA64.__author__,
    author_email=pyA64.__email__,
    url='https://www.olimex.com/',
    license=pyA64.__license__,
    packages=['pyA64', 'pyA64.gpio'],
    description='Control GPIO ports on A64-OLinuXino',
    long_description=open('README.rst').read(),
    classifiers=['Development Status :: 3 - Alpha',
                 'Environment :: Console',
                 'Intended Audience :: Developers',
                 'Intended Audience :: Education',
                 'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
                 'Operating System :: POSIX :: Linux',
                 'Programming Language :: Python',
                 'Topic :: Home Automation',
                 'Topic :: Software Development :: Embedded Systems'
                 ],
    ext_modules=modules
)
