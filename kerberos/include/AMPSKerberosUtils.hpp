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
// is subject to the restrictions set forth by 60East Technologies Inc..
//
////////////////////////////////////////////////////////////////////////////

#ifndef _AMPS_KERBEROS_UTILS_HPP_
#define _AMPS_KERBEROS_UTILS_HPP_

#include <regex>
#include <ampsplusplus.hpp>

#define AMPS_KERBEROS_AUTHENTICATION_HOST_PATTERN "(([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\\-]*[a-zA-Z0-9])"
#define AMPS_KERBEROS_AUTHENTICATION_REALM_PATTERN "@[\\w\\d]+([\\.\\w\\d]*)?"
#define AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_PATTERN "^(\\w+/)(" AMPS_KERBEROS_AUTHENTICATION_HOST_PATTERN ")(:\\d+)?"
#define AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_FORMAT "<service>/<host>[:<port>]"
#define AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_PATTERN_WITH_REALM AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_PATTERN "(" AMPS_KERBEROS_AUTHENTICATION_REALM_PATTERN ")?"
#define AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_FORMAT_WITH_REALM AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_FORMAT "[@REALM]"

namespace AMPS
{

  class AMPSKerberosUtils
  {

  public:

    static void validateSPN(const std::string& spn_)
    {
      std::regex spnRegex(AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_PATTERN);
      if (!std::regex_match(spn_, spnRegex))
      {
        throw AMPS::AuthenticationException("The specified SPN '" + spn_ + "' does not match the format " +
                                            AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_FORMAT);
      }
    }

    static void validateSPNWithRealm(const std::string& spn_)
    {
      std::regex spnRegex(AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_PATTERN_WITH_REALM);
      if (!std::regex_match(spn_, spnRegex))
      {
        throw AMPS::AuthenticationException("The specified SPN '" + spn_ + "' does not match the format " +
                                            AMPS_KERBEROS_AUTHENTICATION_UTILS_SPN_FORMAT_WITH_REALM);
      }
    }

  };

} // end namespace AMPS

#endif

