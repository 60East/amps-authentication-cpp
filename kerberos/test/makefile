!include platform_test.nmakefile

GFS_DIR=..\..\..\..\..\..\gfs

CLIENT_DIR=$(GFS_DIR)\sixty\amps-client-cpp\wip
CLIENT_LIB_DIR=$(CLIENT_DIR)\lib\$(TARGET_PLATFORM)\Debug

GTEST_DIR=$(GFS_DIR)\oss\gtest-1.6.0

BASE_CPPFLAGS=/Zi /MDd /EHsc /I. /I$(CLIENT_DIR)\include /I$(GTEST_DIR)\include /I$(GTEST_DIR)
CPPFLAGS=$(BASE_CPPFLAGS) $(CLIENT_LIB_DIR)\amps.lib advapi32.lib Secur32.lib gtest.lib

TARGETS=AMPSKerberosAuthenticatorTest.exe AMPSKerberosUtilsTest.exe AMPSKerberosSSPIStatusTest.exe

all: gtest.lib $(TARGETS)

AMPSKerberosAuthenticatorTest.exe: AMPSKerberosAuthenticatorTest.cpp gtest.lib
	$(CPP) /DPSAPI_VERSION=1 $(CPPFLAGS) psapi.lib AMPSKerberosAuthenticatorTest.cpp /FeAMPSKerberosAuthenticatorTest.exe

AMPSKerberosUtilsTest.exe: AMPSKerberosUtilsTest.cpp gtest.lib
	$(CPP) /DPSAPI_VERSION=1 $(CPPFLAGS) psapi.lib AMPSKerberosUtilsTest.cpp /FeAMPSKerberosUtilsTest.exe

AMPSKerberosSSPIStatusTest.exe: AMPSKerberosSSPIStatusTest.cpp gtest.lib
	$(CPP) /DPSAPI_VERSION=1 $(CPPFLAGS) psapi.lib AMPSKerberosSSPIStatusTest.cpp /FeAMPSKerberosSSPIStatusTest.exe

gtest.lib: $(GTEST_DIR)\src\gtest-all.cc
	$(CXX) $(BASE_CPPFLAGS) /c $(GTEST_DIR)\src\gtest-all.cc /Fogtest-all.obj
	LIB /out:$@ gtest-all.obj

clean:
	-del $(TARGETS) *.lib *.pdb *.ilk *.obj 2>nul

