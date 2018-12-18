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

#ifndef _AMPS_KERBEROS_GSSAPI_AUTHENTICATOR_HPP_
#define _AMPS_KERBEROS_GSSAPI_AUTHENTICATOR_HPP_

#include <ampsplusplus.hpp>
#include <gssapi/gssapi.h>
#include <gssapi/gssapi_generic.h>
#include <gssapi/gssapi_krb5.h>
#include "AMPSKerberosAuthenticatorBase.hpp"

#define MAX_TOKEN_SIZE 65535

namespace AMPS
{

  class AMPSKerberosGSSAPIAuthenticator : public AMPS::AMPSKerberosAuthenticatorBase
  {

  public:

    AMPSKerberosGSSAPIAuthenticator(const std::string& spn_);
    ~AMPSKerberosGSSAPIAuthenticator();

  private:

    gss_ctx_id_t  _contextHandle;
    gss_cred_id_t _credentialsHandle;
    gss_name_t    _targetName;

    void        importServiceName();
    void        initializeSecurityContext(const ByteBuffer& inToken_, ByteBuffer& outToken_);
    void        releaseName(gss_name_t& name_) const;
    void        releaseContextHandle();
    void        releaseCredentialsHandle();
    void        gssCallFailure(const std::string& gssFuncName_, OM_uint32 majorStatus_, OM_uint32 minorStatus_) const;
    std::string getStatusString(OM_uint32 majorStatus_, OM_uint32 minorStatus_) const;
    std::string convertStatusToString(OM_uint32 status_, int statusCodeType_) const;
    std::string convertNameToString(const gss_name_t& name_) const;
  };

  inline AMPSKerberosGSSAPIAuthenticator::AMPSKerberosGSSAPIAuthenticator(const std::string& spn_)
    : AMPS::AMPSKerberosAuthenticatorBase(spn_),
      _contextHandle(GSS_C_NO_CONTEXT),
      _credentialsHandle(GSS_C_NO_CREDENTIAL)
  {
    AMPS::AMPSKerberosUtils::validateSPN(spn_);
    std::replace(_spn.begin(), _spn.end(), '/', '@');
    importServiceName();
  }

  inline AMPSKerberosGSSAPIAuthenticator::~AMPSKerberosGSSAPIAuthenticator()
  {
    releaseName(_targetName);
    releaseContextHandle();
    releaseCredentialsHandle();
  }

  inline void AMPSKerberosGSSAPIAuthenticator::initializeSecurityContext(const ByteBuffer& inToken_,
                                                                         ByteBuffer& outToken_)
  {
    gss_buffer_desc inTokenBuf;
    inTokenBuf.value = (void*)&inToken_[0];
    inTokenBuf.length = inToken_.size();

    gss_buffer_desc outTokenBuf = GSS_C_EMPTY_BUFFER;

    OM_uint32 majorStatus = 0U;
    OM_uint32 minorStatus = 0U;

    majorStatus = gss_init_sec_context(&minorStatus,
                                       _credentialsHandle,
                                       &_contextHandle,
                                       _targetName,
                                       GSS_C_NO_OID,
                                       GSS_C_MUTUAL_FLAG | GSS_C_REPLAY_FLAG,
                                       0,
                                       GSS_C_NO_CHANNEL_BINDINGS,
                                       &inTokenBuf,
                                       0,
                                       &outTokenBuf,
                                       0,
                                       0);

    if ((majorStatus == GSS_S_COMPLETE) || (majorStatus == GSS_S_CONTINUE_NEEDED))
    {
      outToken_.resize(outTokenBuf.length);
      memcpy(&outToken_[0], outTokenBuf.value, outTokenBuf.length);
      gss_release_buffer(&minorStatus, &outTokenBuf);
    }
    else
    {
      if (_contextHandle != GSS_C_NO_CONTEXT)
      {
        gss_delete_sec_context(&minorStatus, &_contextHandle, GSS_C_NO_BUFFER);
      }
      gssCallFailure("gss_init_sec_context", majorStatus, minorStatus);
    }
  }

  inline void AMPSKerberosGSSAPIAuthenticator::importServiceName()
  {
    OM_uint32 majorStatus = 0U;
    OM_uint32 minorStatus = 0U;

    gss_buffer_desc nameBuf;
    nameBuf.value = (void*)_spn.c_str();
    nameBuf.length = _spn.length() + 1;

    majorStatus = gss_import_name(&minorStatus, &nameBuf, GSS_C_NT_HOSTBASED_SERVICE, &_targetName);
    if (majorStatus != GSS_S_COMPLETE)
    {
      gssCallFailure("gss_import_name", majorStatus, minorStatus);
    }
  }

  inline void AMPSKerberosGSSAPIAuthenticator::releaseName(gss_name_t& name_) const
  {
    if (name_ == GSS_C_NO_NAME)
    {
      return;
    }
    OM_uint32 minorStatus = 0U;
    gss_release_name(&minorStatus, &name_);
    name_ = 0;
  }

  inline void AMPSKerberosGSSAPIAuthenticator::releaseContextHandle()
  {
    if (_contextHandle == GSS_C_NO_CONTEXT)
    {
      return;
    }
    OM_uint32 minorStatus = 0U;
    gss_delete_sec_context(&minorStatus, &_contextHandle, GSS_C_NO_BUFFER);
    _contextHandle = GSS_C_NO_CONTEXT;
  }

  inline void AMPSKerberosGSSAPIAuthenticator::releaseCredentialsHandle()
  {
    if (_credentialsHandle == GSS_C_NO_CREDENTIAL)
    {
      return;
    }
    OM_uint32 minorStatus = 0U;
    gss_release_cred(&minorStatus, &_credentialsHandle);
    _credentialsHandle = GSS_C_NO_CREDENTIAL;
  }

  inline void AMPSKerberosGSSAPIAuthenticator::gssCallFailure(const std::string& gssFuncName_, OM_uint32 majorStatus_,
                                                              OM_uint32 minorStatus_) const
  {
    throw AMPS::AuthenticationException("A call to " + gssFuncName_ + " resulted in a failure: " + getStatusString(
                                          majorStatus_, minorStatus_));
  }

  inline std::string AMPSKerberosGSSAPIAuthenticator::getStatusString(OM_uint32 majorStatus_,
                                                                      OM_uint32 minorStatus_) const
  {
    return "{GSSAPI Status: "    + convertStatusToString(majorStatus_, GSS_C_GSS_CODE)  + "} " +
           "{Kerberos Status: "  + convertStatusToString(minorStatus_, GSS_C_MECH_CODE) + "}";
  }

  inline std::string AMPSKerberosGSSAPIAuthenticator::convertStatusToString(OM_uint32 status_, int statusCodeType_) const
  {
    OM_uint32 majorStatus = 0U;
    OM_uint32 minorStatus = 0U;
    OM_uint32 mctx = 0U;
    gss_buffer_desc msg = GSS_C_EMPTY_BUFFER;
    std::string statusString;

    majorStatus = gss_display_status(&minorStatus, status_, statusCodeType_, GSS_C_NULL_OID, &mctx, &msg);
    if (majorStatus == GSS_S_COMPLETE)
    {
      statusString = (const char*)msg.value;
    }

    if (statusString.empty())
    {

      std::ostringstream emptyStatusOss;
      emptyStatusOss << "Status string was empty for status " << status_ << " and status code " << statusCodeType_;
      statusString = emptyStatusOss.str();
    }

    gss_release_buffer(&minorStatus, &msg);

    return statusString;
  }

  inline std::string AMPSKerberosGSSAPIAuthenticator::convertNameToString(const gss_name_t& name_) const
  {
    OM_uint32 majorStatus = 0U;
    OM_uint32 minorStatus = 0U;
    gss_buffer_desc nameBuffer;

    majorStatus = gss_display_name(&minorStatus, name_, &nameBuffer, 0);
    if (majorStatus != GSS_S_COMPLETE)
    {
      gssCallFailure("gss_display_name", majorStatus, minorStatus);
    }

    std::string nameStr = (const char*)nameBuffer.value;
    gss_release_buffer(&minorStatus, &nameBuffer);

    return nameStr;
  }

} // end namespace AMPS

#endif

