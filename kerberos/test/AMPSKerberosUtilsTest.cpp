////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012-2019 60East Technologies Inc., All Rights Reserved.
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
#include "../include/AMPSKerberosUtils.hpp"

class AMPSKerberosUtilsTestSuite : public ::testing::Test
{
public:

  AMPSKerberosUtilsTestSuite()
  {
  }

  static void done(void)
  {
  }

  ~AMPSKerberosUtilsTestSuite()
  {
  }

  void SetUp() override
  {
    _validSPNs.push_back("AMPS/localhost");
    _validSPNs.push_back("AMPS/localhost:1234");
    _validSPNs.push_back("AMPS/localhost.localdomain");
    _validSPNs.push_back("AMPS/localhost.localdomain:1234");
    _validSPNs.push_back("AMPS/ac-1234.localhost.com");
    _validSPNs.push_back("AMPS/ac-1234.localhost.com:1234");

    _validSPNsWithRealm.push_back("AMPS/localhost@SOMEREALM");
    _validSPNsWithRealm.push_back("AMPS/localhost@SOMEREALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost@SOME.REALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost:1234@SOMEREALM");
    _validSPNsWithRealm.push_back("AMPS/localhost:1234@SOMEREALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost:1234@SOME.REALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain@SOMEREALM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain@SOMEREALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain@SOME.REALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain:1234@SOMEREALM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain:1234@SOMEREALM.COM");
    _validSPNsWithRealm.push_back("AMPS/localhost.localdomain:1234@SOME.REALM.COM");

    _invalidSPNs.push_back("FOO");
    _invalidSPNs.push_back("localhost.localdomain");
    _invalidSPNs.push_back("AMPS@localhost");
    _invalidSPNs.push_back("AMPS@localhost.localdomain");
    _invalidSPNs.push_back("AMPS@localhost.localdomain");
    _invalidSPNs.push_back("AMPS@localhost.localdomain/FOO");
  }

  std::string getCurrentTestName(void) const
  {
    const ::testing::TestInfo* pTestInfo = ::testing::UnitTest::GetInstance()->current_test_info();
    return std::string(pTestInfo->test_case_name()) + "-" + std::string(pTestInfo->name());
  }

protected:

  std::vector<std::string> _validSPNs;
  std::vector<std::string> _validSPNsWithRealm;
  std::vector<std::string> _invalidSPNs;

};

TEST_F(AMPSKerberosUtilsTestSuite, TestValidateSPN)
{
  for (auto validSPN : _validSPNs)
  {
    AMPS::AMPSKerberosUtils::validateSPN(validSPN);
  }
}

TEST_F(AMPSKerberosUtilsTestSuite, TestValidateSPNWithRealm1)
{
  for (auto validSPN : _validSPNs)
  {
    AMPS::AMPSKerberosUtils::validateSPNWithRealm(validSPN);
  }
}

TEST_F(AMPSKerberosUtilsTestSuite, TestValidateSPNWithRealm2)
{
  for (auto validSPN : _validSPNsWithRealm)
  {
    AMPS::AMPSKerberosUtils::validateSPNWithRealm(validSPN);
  }
}

TEST_F(AMPSKerberosUtilsTestSuite, TestInvalidSPNs1)
{
  for (auto invalidSPN : _validSPNsWithRealm)
  {
    bool exceptionRaised = false;

    try
    {
      AMPS::AMPSKerberosUtils::validateSPN(invalidSPN);
    }
    catch (const AMPS::AMPSException& e)
    {
      exceptionRaised = true;
    }

    EXPECT_TRUE(exceptionRaised);
  }
}

TEST_F(AMPSKerberosUtilsTestSuite, TestInvalidSPNs2)
{
  for (auto invalidSPN : _invalidSPNs)
  {
    bool exceptionRaised = false;

    try
    {
      AMPS::AMPSKerberosUtils::validateSPN(invalidSPN);
    }
    catch (const AMPS::AMPSException& e)
    {
      exceptionRaised = true;
    }

    EXPECT_TRUE(exceptionRaised);
  }
}

TEST_F(AMPSKerberosUtilsTestSuite, TestInvalidSPNs3)
{
  for (auto invalidSPN : _invalidSPNs)
  {
    bool exceptionRaised = false;

    try
    {
      AMPS::AMPSKerberosUtils::validateSPNWithRealm(invalidSPN);
    }
    catch (const AMPS::AMPSException& e)
    {
      exceptionRaised = true;
    }

    EXPECT_TRUE(exceptionRaised);
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  AMPSKerberosUtilsTestSuite::done();
  return RUN_ALL_TESTS();
}

