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
// is subject to the restrictions set forth by 60East Technologies Inc..
//
////////////////////////////////////////////////////////////////////////////

#ifndef _AMPS_KERBEROS_AUTHENTICATOR_BASE_HPP_
#define _AMPS_KERBEROS_AUTHENTICATOR_BASE_HPP_

#include <ampsplusplus.hpp>
#include "AMPSBase64.hpp"
#include "AMPSKerberosUtils.hpp"

namespace AMPS
{

  typedef std::vector<uint8_t> ByteBuffer;

  class AMPSKerberosAuthenticatorBase : public AMPS::Authenticator
  {

  public:

    AMPSKerberosAuthenticatorBase(const std::string& spn_);

    std::string authenticate(const std::string& username_, const std::string& token_);
    std::string retry(const std::string& username_, const std::string& token_);
    void        completed(const std::string& username_, const std::string& token_, const std::string& reason_);

  protected:

    std::string  _spn;

    virtual void initializeSecurityContext(const ByteBuffer& inToken_, ByteBuffer& outToken_) = 0;
    virtual void dispose() = 0;

  };

  inline AMPSKerberosAuthenticatorBase::AMPSKerberosAuthenticatorBase(const std::string& spn_)
    : _spn(spn_)
  {
  }

  inline std::string AMPSKerberosAuthenticatorBase::authenticate(const std::string& username_, const std::string& token_)
  {
    ByteBuffer inTokenBuf;
    ByteBuffer outTokenBuf;

    if (!token_.empty())
    {
      std::string decodedToken = AMPS::Base64::decode(token_);
      inTokenBuf.assign(decodedToken.begin(), decodedToken.end());
    }

    initializeSecurityContext(inTokenBuf, outTokenBuf);

    if (!outTokenBuf.empty())
    {
      std::string outToken(outTokenBuf.begin(), outTokenBuf.end());
      std::string encodedToken = AMPS::Base64::encode(outToken);
      return encodedToken;
    }

    return "";
  }

  inline std::string AMPSKerberosAuthenticatorBase::retry(const std::string& username_, const std::string& token_)
  {
    return authenticate(username_, token_);
  }

  inline void AMPSKerberosAuthenticatorBase::completed(const std::string& username_, const std::string& token_,
                                                       const std::string& reason_)
  {
    if (reason_ == AMPS::Reason::authDisabled())
    {
      dispose();
      return;
    }
    authenticate(username_, token_);
    dispose();
  }

} // end namespace AMPS

#endif

