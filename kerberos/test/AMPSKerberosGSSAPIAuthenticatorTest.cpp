////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012-2018 60East Technologies Inc., All Rights Reserved.
//
// This computer software is owned by 60East Technologies Inc. and is
// protected by U.S. copyright laws and other laws and by international
// treaties.  This computer software is furnished by 60East Technologies
// Inc. pursuant to a written license agreement and may be used, copied,
// transmitted, and stored only in accordance with the terms of such
// license agreement and with the inclusion of the above copyright notice.
// This computer software or any other copies thereof may not be provided
// or otherwise made available to any other person.
//
// U.S. Government Restricted Rights.  This computer software: (a) was
// developed at private expense and is in all respects the proprietary
// information of 60East Technologies Inc.; (b) was not developed with
// government funds; (c) is a trade secret of 60East Technologies Inc.
// for all purposes of the Freedom of Information Act; and (d) is a
// commercial item and thus, pursuant to Section 12.212 of the Federal
// Acquisition Regulations (FAR) and DFAR Supplement Section 227.7202,
// Government's use, duplication or disclosure of the computer software
// is subject to the restrictions set forth by 60East Technologies Inc.
//
////////////////////////////////////////////////////////////////////////////

#include <ampsplusplus.hpp>
#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "../include/AMPSKerberosGSSAPIAuthenticator.hpp"

class AMPSKerberosGSSAPIAuthenticatorTestSuite : public ::testing::Test
{
public:

  AMPSKerberosGSSAPIAuthenticatorTestSuite()
  {
    char const* host = getenv("AMPS_HOST");
    if (host == NULL)
    {
      //TODO: It is probably better to use setUp and then FAIL()
      fprintf(stderr, "The AMPS_HOST environment variable must be set to run the tests\n");
      std::exit(1);
    }

    int port;
    char const* portStr = getenv("AMPS_PORT");
    port = (portStr == NULL) ? 6666 : std::stoi(portStr);

    char const* user = getenv("AMPS_USER");
    if (user == NULL)
    {
      user = "60east";
    }

    _spn = std::string("AMPS/") + host;

    std::ostringstream uriOss;
    uriOss << "tcp://" << user << "@" << host << ":" << port << "/amps/json";
    _uri = uriOss.str();
  }

  static void done(void)
  {
  }

  ~AMPSKerberosGSSAPIAuthenticatorTestSuite()
  {
  }

  std::string getCurrentTestName(void) const
  {
    const ::testing::TestInfo* pTestInfo = ::testing::UnitTest::GetInstance()->current_test_info();
    return std::string(pTestInfo->test_case_name()) + "-" + std::string(pTestInfo->name());
  }

protected:

  std::string _spn;
  std::string _uri;

};

TEST_F(AMPSKerberosGSSAPIAuthenticatorTestSuite, TestObtainToken)
{
  AMPS::AMPSKerberosGSSAPIAuthenticator authenticator(_spn);
  std::string token = authenticator.authenticate("", "");
  ASSERT_NE(token.length(), 0U);
  ASSERT_EQ(token.find("YII"), 0U);
}

TEST_F(AMPSKerberosGSSAPIAuthenticatorTestSuite, TestPublish)
{
  AMPS::AMPSKerberosGSSAPIAuthenticator authenticator(_spn);
  AMPS::Client client("KerberosTestPublisher");
  client.connect(_uri);
  client.logon(10000, authenticator);
  client.publish("/topic", R"({"foo": "bar"})");
}

TEST_F(AMPSKerberosGSSAPIAuthenticatorTestSuite, TestUndefinedSPN)
{
  bool errorThrown = false;

  AMPS::AMPSKerberosGSSAPIAuthenticator authenticator("AMPS/foo.com");
  try
  {
    authenticator.authenticate("", "");
  }
  catch (const AMPS::AMPSException& e)
  {
    errorThrown = true;
  }

  ASSERT_TRUE(errorThrown);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  AMPSKerberosGSSAPIAuthenticatorTestSuite::done();
  return RUN_ALL_TESTS();
}
