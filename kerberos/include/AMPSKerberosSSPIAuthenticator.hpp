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

#ifndef _AMPS_KERBEROS_SSPI_AUTHENTICATOR_HPP_
#define _AMPS_KERBEROS_SSPI_AUTHENTICATOR_HPP_

#define SECURITY_WIN32

#include <ampsplusplus.hpp>
#include <sspi.h>
#include <windows.h>
#include <Lmcons.h>
#include "AMPSKerberosAuthenticatorBase.hpp"
#include "AMPSKerberosSSPIStatus.hpp"

namespace AMPS
{

  class AMPSKerberosSSPIAuthenticator : public AMPS::AMPSKerberosAuthenticatorBase
  {

  public:

    AMPSKerberosSSPIAuthenticator(const std::string& spn_);
    ~AMPSKerberosSSPIAuthenticator();

  private:

    CredHandle      _credentialsHandle;
    CtxtHandle      _contextHandle;
    TimeStamp       _contextLifetime;
    bool            _contextHandleInitialized;
    unsigned long   _maxTokenSize;

    void sspiCallFailure(const std::string& sspiFuncName_, SECURITY_STATUS ss_) const;
    void acquireCredentials();
    void initializeSecurityContext(const ByteBuffer& inToken_, ByteBuffer& outToken_);
  };

  inline AMPSKerberosSSPIAuthenticator::AMPSKerberosSSPIAuthenticator(const std::string& spn_)
    : AMPS::AMPSKerberosAuthenticatorBase(spn_),
      _contextHandleInitialized(FALSE)
  {
    AMPS::AMPSKerberosUtils::validateSPNWithRealm(spn_);

    SECURITY_STATUS ss;
    PSecPkgInfo pkgInfo;
    ss = QuerySecurityPackageInfo("Kerberos", &pkgInfo);
    if (ss != SEC_E_OK)
    {
      sspiCallFailure("QuerySecurityPackageInfo", ss);
    }
    _maxTokenSize = pkgInfo->cbMaxToken;
    FreeContextBuffer(pkgInfo);

    SecInvalidateHandle(&_credentialsHandle);
    SecInvalidateHandle(&_contextHandle);

    acquireCredentials();
  }

  inline AMPSKerberosSSPIAuthenticator::~AMPSKerberosSSPIAuthenticator()
  {
    DeleteSecurityContext(&_contextHandle);
    SecInvalidateHandle(&_contextHandle);
    FreeCredentialHandle(&_credentialsHandle);
    SecInvalidateHandle(&_credentialsHandle);
  }

  inline void AMPSKerberosSSPIAuthenticator::sspiCallFailure(const std::string& sspiFuncName_, SECURITY_STATUS ss_) const
  {
    throw AMPS::AuthenticationException("A call to " + sspiFuncName_ + " resulted in a failure: " +
                                        AMPS::AMPSKerberosSSPIStatus::getStatusString(ss_));
  }

  inline void AMPSKerberosSSPIAuthenticator::acquireCredentials()
  {
    char username[UNLEN + 1];
    DWORD usernameLen = UNLEN + 1;
    GetUserName(username, &usernameLen);

    TimeStamp credLifetime;

    SECURITY_STATUS ss;

    ss = AcquireCredentialsHandle(username,
                                  "Kerberos",
                                  SECPKG_CRED_BOTH,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  &_credentialsHandle,
                                  &credLifetime);
    if (ss != SEC_E_OK)
    {
      sspiCallFailure("AcquireCredentialsHandle", ss);
    }
  }

  inline void AMPSKerberosSSPIAuthenticator::initializeSecurityContext(const ByteBuffer& inToken_, ByteBuffer& outToken_)
  {
    SECURITY_STATUS ss;

    SecBufferDesc outSecBufDesc;
    SecBuffer     outSecBuf;

    outSecBufDesc.ulVersion = SECBUFFER_VERSION;
    outSecBufDesc.cBuffers  = 1;
    outSecBufDesc.pBuffers  = &outSecBuf;
    outSecBuf.cbBuffer      = _maxTokenSize;
    outSecBuf.BufferType    = SECBUFFER_TOKEN;
    std::vector<unsigned char> outBuf(_maxTokenSize);
    outSecBuf.pvBuffer      = reinterpret_cast<char*>(outBuf.data());

    unsigned long contextAttrs = 0;

    if (_contextHandleInitialized)
    {
      SecBufferDesc inSecBufDesc;
      SecBuffer     inSecBuf;

      inSecBufDesc.ulVersion  = SECBUFFER_VERSION;
      inSecBufDesc.cBuffers   = 1;
      inSecBufDesc.pBuffers   = &inSecBuf;
      inSecBuf.cbBuffer       = (unsigned long)inToken_.size();
      inSecBuf.BufferType     = SECBUFFER_TOKEN;
      std::vector<unsigned char> inBuf(inToken_.size());
      inSecBuf.pvBuffer       = reinterpret_cast<char*>(inBuf.data());

      if (inToken_.size() > 0)
      {
        std::copy(inToken_.begin(), inToken_.end(), inBuf.begin());
      }

      ss = InitializeSecurityContext(&_credentialsHandle,
                                     &_contextHandle,
                                     const_cast<SEC_CHAR*>(_spn.c_str()),
                                     ISC_REQ_MUTUAL_AUTH | ISC_REQ_REPLAY_DETECT | ISC_REQ_SEQUENCE_DETECT | ISC_REQ_CONNECTION,
                                     0,
                                     SECURITY_NATIVE_DREP,
                                     &inSecBufDesc,
                                     0,
                                     &_contextHandle,
                                     &outSecBufDesc,
                                     &contextAttrs,
                                     &_contextLifetime);
    }
    else
    {
      ss = InitializeSecurityContext(&_credentialsHandle,
                                     NULL,
                                     const_cast<SEC_CHAR*>(_spn.c_str()),
                                     ISC_REQ_MUTUAL_AUTH | ISC_REQ_REPLAY_DETECT | ISC_REQ_SEQUENCE_DETECT | ISC_REQ_CONNECTION,
                                     0,
                                     SECURITY_NATIVE_DREP,
                                     NULL,
                                     0,
                                     &_contextHandle,
                                     &outSecBufDesc,
                                     &contextAttrs,
                                     &_contextLifetime);

      _contextHandleInitialized = true;
    }

    if ((ss != SEC_E_OK) && (ss != SEC_I_CONTINUE_NEEDED))
    {
      sspiCallFailure("InitializeSecurityContext", ss);
    }

    if ((ss == SEC_I_COMPLETE_NEEDED) || (ss = SEC_I_COMPLETE_AND_CONTINUE))
    {
      ss = CompleteAuthToken(&_contextHandle, &outSecBufDesc);
      if (ss != SEC_E_OK)
      {
        sspiCallFailure("CompleteAuthToken", ss);
      }
    }

    if (outSecBuf.cbBuffer > 0)
    {
      outToken_.resize(outSecBuf.cbBuffer);
      std::memcpy(&outToken_[0], outSecBuf.pvBuffer, outSecBuf.cbBuffer);
    }
  }

} // end namespace AMPS

#endif

