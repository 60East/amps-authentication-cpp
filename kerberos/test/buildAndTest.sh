#!/bin/bash

EXIT_CODE=0

cd "$(dirname "$0")"
make clean
make
if [ $? -ne 0 ] ; then
    exit 1
fi

TESTS="AMPSKerberosAuthenticatorTest AMPSKerberosUtilsTest"

for test_name in $TESTS ; do
    eval "./$test_name"
    if [ $? -ne 0 ] ; then
        EXIT_CODE=1
    fi
done

exit $EXIT_CODE
