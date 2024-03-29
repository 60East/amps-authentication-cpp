OPTIMIZER=-O3
DEBUGOPTS=-g
ifeq ("$(PROCESSOR)","")
PROCESSOR = $(shell uname -i)
endif
ifeq ("$(PROCESSOR)","unknown")
PROCESSOR = x86_64
endif

ifeq ($(PROCESSOR),x86)
ARCH=-m32
else
ARCH=-m64
endif

GFS_DIR?=$(realpath ../../../../../../gfs)
GTEST_DIR?=$(GFS_DIR)/oss/gtest-1.6.0

CLIENT_DIR?=$(GFS_DIR)/sixty/amps-client-cpp/wip
CLIENT_LIB_DIR?=$(CLIENT_DIR)/lib/$(PROCESSOR)/release
KRB5_DIR?=$(GFS_DIR)/oss/krb5/1.16.1

GTEST_LIB=./lib/$(PROCESSOR)/gtest-all.o

LDLIBS=-lamps -lpthread -lrt -ldl -lgssapi_krb5 -lkrb5 -lkrb5support -lk5crypto -lcom_err
CXXFLAGS=$(OPTIMIZER) $(DEBUGOPTS) $(ARCH) -I$(GTEST_DIR)/include -I$(CLIENT_DIR)/include -I$(KRB5_DIR)/include -Wall -std=c++11
LDFLAGS=-L$(CLIENT_LIB_DIR) -L$(KRB5_DIR)/lib
TESTS = AMPSKerberosAuthenticatorTest AMPSKerberosUtilsTest

.PHONY: all

all: $(TESTS)
$(TESTS):
clean:
	rm -rf $(TESTS) ./lib

$(GTEST_LIB): $(GTEST_DIR)/src/gtest-all.cc
	mkdir -p lib/$(PROCESSOR)
	g++ $(CXXFLAGS) -I$(GTEST_DIR) -c $< -o $@

AMPSKerberosAuthenticatorTest: AMPSKerberosAuthenticatorTest.cpp $(GTEST_LIB)
	g++ AMPSKerberosAuthenticatorTest.cpp $(LDLIBS) $(LDFLAGS) $(CXXFLAGS) $(GTEST_LIB) -o AMPSKerberosAuthenticatorTest

AMPSKerberosUtilsTest: AMPSKerberosUtilsTest.cpp $(GTEST_LIB)
	g++ AMPSKerberosUtilsTest.cpp $(LDLIBS) $(LDFLAGS) $(CXXFLAGS) $(GTEST_LIB) -o AMPSKerberosUtilsTest

