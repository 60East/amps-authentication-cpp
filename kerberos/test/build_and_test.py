#!/usr/bin/env python

import os
import sys
import platform
from subprocess import call, check_call

OS = platform.system()

if 'Linux' in OS:
    OS = 'linux'
elif 'Windows' in OS:
    OS = 'windows'
else:
    raise RuntimeError('%s is not a supported platform' % OS)

def main():
    os.chdir(os.path.dirname(os.path.realpath(__file__)))

    test_suffix = 'Test'
    if OS == 'linux':
        check_call('make clean')
        check_call('make')
    else:
        check_call('.\win_build.bat')
        test_suffix += '.exe'

    tests = [f for f in os.listdir('.') if os.path.isfile(f) and f.startswith('AMPS') and f.endswith(test_suffix)]
    for test in tests:
        check_call(os.path.join('.', test))

if __name__ == '__main__':
    main()

