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

#define SECURITY_WIN32

#include <ampsplusplus.hpp>
#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "../include/AMPSKerberosSSPIStatus.hpp"

class AMPSKerberosSSPIStatusTestSuite : public ::testing::Test
{
public:

  AMPSKerberosSSPIStatusTestSuite()
  {
  }

  static void done(void)
  {
  }

  ~AMPSKerberosSSPIStatusTestSuite()
  {
  }

  std::string getCurrentTestName(void) const
  {
    const ::testing::TestInfo* pTestInfo = ::testing::UnitTest::GetInstance()->current_test_info();
    return std::string(pTestInfo->test_case_name()) + "-" + std::string(pTestInfo->name());
  }

};

TEST_F(AMPSKerberosSSPIStatusTestSuite, TestKnownStatus)
{
  std::string statusString = AMPS::AMPSKerberosSSPIStatus::getStatusString(SEC_E_INVALID_TOKEN);
  ASSERT_EQ(statusString.find("SEC_E_INVALID_TOKEN: "), 0U);
}

TEST_F(AMPSKerberosSSPIStatusTestSuite, TestUnknownStatus)
{
  std::string statusString = AMPS::AMPSKerberosSSPIStatus::getStatusString(42);
  ASSERT_EQ(statusString.find("UNKNOWN SECURITY STATUS: "), 0U);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  AMPSKerberosSSPIStatusTestSuite::done();
  return RUN_ALL_TESTS();
}

