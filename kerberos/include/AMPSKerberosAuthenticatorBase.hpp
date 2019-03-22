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
#include "amps_base64.hpp"
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
    virtual void init() = 0;
    virtual void dispose() = 0;

  private:

    ByteBuffer   _inTokenBuf;
    ByteBuffer   _outTokenBuf;
    bool         _completing;
    std::string  _encodedToken;

    std::string _authenticate(const std::string& username_, const std::string& token_, bool completing_);

  };

  inline AMPSKerberosAuthenticatorBase::AMPSKerberosAuthenticatorBase(const std::string& spn_)
    : _spn(spn_)
  {
  }

  inline std::string AMPSKerberosAuthenticatorBase::_authenticate(const std::string& username_, const std::string& token_, bool completing_)
  {
    if (!completing_)
    {
      dispose();
      init();
    }
    _inTokenBuf.clear();
    _outTokenBuf.clear();
    _encodedToken.clear();

    if (!token_.empty())
    {
      size_t inputLength = token_.size();
      const unsigned char* pInput = reinterpret_cast<const unsigned char*>(token_.data());
      _inTokenBuf.resize(inputLength);
      char* pOutput = reinterpret_cast<char*>(const_cast<unsigned char*>(_inTokenBuf.data()));
      size_t outputLength = 0;

      amps::base64::decode(pInput, inputLength, pOutput, &outputLength);
      _inTokenBuf.resize(outputLength);
    }

    initializeSecurityContext(_inTokenBuf, _outTokenBuf);

    if (!_outTokenBuf.empty())
    {
      // C++11 guarantees contiguous storage of strings
      size_t max_encoded_size = 5 + ( (4 * (_outTokenBuf.size() + 2)) / 3 );
      _encodedToken.resize(max_encoded_size);
      char* pPassword = const_cast<char*>(&_encodedToken.front());
      _encodedToken.resize(amps::base64::encode(_outTokenBuf.data(), _outTokenBuf.size(), pPassword) - 1);
      return _encodedToken;
    }

    return "";
  }

  inline std::string AMPSKerberosAuthenticatorBase::authenticate(const std::string& username_, const std::string& token_)
  {
    return _authenticate(username_, token_, false);
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
    _authenticate(username_, token_, true);
    dispose();
  }

} // end namespace AMPS

#endif

