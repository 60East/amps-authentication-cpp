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

#ifndef _AMPS_KERBEROS_SSPI_STATUS_HPP_
#define _AMPS_KERBEROS_SSPI_STATUS_HPP_

#include <sstream>
#include <sspi.h>
#include <windows.h>

namespace AMPS
{

  class AMPSKerberosSSPIStatus
  {

  public:

    static std::string getStatusString(SECURITY_STATUS ss)
    {
      switch (ss)
      {
      case SEC_E_ALGORITHM_MISMATCH: return
          "SEC_E_ALGORITHM_MISMATCH: The client and server cannot communicate because they do not possess a common algorithm.";
      case SEC_E_BAD_BINDINGS: return "SEC_E_BAD_BINDINGS: The SSPI channel bindings supplied by the client are incorrect.";
      case SEC_E_BAD_PKGID: return "SEC_E_BAD_PKGID: The requested package identifier does not exist.";
      case SEC_E_BUFFER_TOO_SMALL: return
          "SEC_E_BUFFER_TOO_SMALL: The buffers supplied to the function are not large enough to contain the information.";
      case SEC_E_CANNOT_INSTALL: return
          "SEC_E_CANNOT_INSTALL: The security package cannot initialize successfully and should not be installed.";
      case SEC_E_CANNOT_PACK: return "SEC_E_CANNOT_PACK: The package is unable to pack the context.";
      case SEC_E_CERT_EXPIRED: return "SEC_E_CERT_EXPIRED: The received certificate has expired.";
      case SEC_E_CERT_UNKNOWN: return "SEC_E_CERT_UNKNOWN: An unknown error occurred while processing the certificate.";
      case SEC_E_CERT_WRONG_USAGE: return "SEC_E_CERT_WRONG_USAGE: The certificate is not valid for the requested usage.";
      case SEC_E_CONTEXT_EXPIRED: return
          "SEC_E_CONTEXT_EXPIRED: The application is referencing a context that has already been closed. A properly written application should not receive this error.";
      case SEC_E_CROSSREALM_DELEGATION_FAILURE: return
          "SEC_E_CROSSREALM_DELEGATION_FAILURE: The server attempted to make a Kerberos-constrained delegation request for a target outside the server's realm.";
      case SEC_E_CRYPTO_SYSTEM_INVALID: return
          "SEC_E_CRYPTO_SYSTEM_INVALID: The cryptographic system or checksum function is not valid because a required function is unavailable.";
      case SEC_E_DECRYPT_FAILURE: return "SEC_E_DECRYPT_FAILURE: The specified data could not be decrypted.";
      case SEC_E_DELEGATION_REQUIRED: return
          "SEC_E_DELEGATION_REQUIRED: The requested operation cannot be completed. The computer must be trusted for delegation, and the current user account must be configured to allow delegation.";
      case SEC_E_DOWNGRADE_DETECTED: return
          "SEC_E_DOWNGRADE_DETECTED: The system detected a possible attempt to compromise security. Verify that the server that authenticated you can be contacted.";
      case SEC_E_ENCRYPT_FAILURE: return "SEC_E_ENCRYPT_FAILURE: The specified data could not be encrypted.";
      case SEC_E_ILLEGAL_MESSAGE: return "SEC_E_ILLEGAL_MESSAGE: The message received was unexpected or badly formatted.";
      case SEC_E_INCOMPLETE_CREDENTIALS: return
          "SEC_E_INCOMPLETE_CREDENTIALS: The credentials supplied were not complete and could not be verified. The context could not be initialized.";
      case SEC_E_INCOMPLETE_MESSAGE: return
          "SEC_E_INCOMPLETE_MESSAGE: The message supplied was incomplete. The signature was not verified.";
      case SEC_E_INSUFFICIENT_MEMORY: return
          "SEC_E_INSUFFICIENT_MEMORY: Not enough memory is available to complete the request.";
      case SEC_E_INTERNAL_ERROR: return "SEC_E_INTERNAL_ERROR: An error occurred that did not map to an SSPI error code.";
      case SEC_E_INVALID_HANDLE: return "SEC_E_INVALID_HANDLE: The handle passed to the function is not valid.";
      case SEC_E_INVALID_TOKEN: return "SEC_E_INVALID_TOKEN: The token passed to the function is not valid.";
      case SEC_E_ISSUING_CA_UNTRUSTED: return
          "SEC_E_ISSUING_CA_UNTRUSTED: An untrusted certification authority (CA) was detected while processing the smart card certificate used for authentication.";
      case SEC_E_ISSUING_CA_UNTRUSTED_KDC: return
          "SEC_E_ISSUING_CA_UNTRUSTED_KDC: An untrusted CA was detected while processing the domain controller certificate used for authentication. The system event log contains additional information.";
      case SEC_E_KDC_CERT_EXPIRED: return
          "SEC_E_KDC_CERT_EXPIRED: The domain controller certificate used for smart card logon has expired.";
      case SEC_E_KDC_CERT_REVOKED: return
          "SEC_E_KDC_CERT_REVOKED: The domain controller certificate used for smart card logon has been revoked.";
      case SEC_E_KDC_INVALID_REQUEST: return "SEC_E_KDC_INVALID_REQUEST: A request that is not valid was sent to the KDC.";
      case SEC_E_KDC_UNABLE_TO_REFER: return
          "SEC_E_KDC_UNABLE_TO_REFER: The KDC was unable to generate a referral for the service requested.";
      case SEC_E_KDC_UNKNOWN_ETYPE: return
          "SEC_E_KDC_UNKNOWN_ETYPE: The requested encryption type is not supported by the KDC.";
      case SEC_E_LOGON_DENIED: return "SEC_E_LOGON_DENIED: This status code is obsolete.";
      case SEC_E_MAX_REFERRALS_EXCEEDED: return
          "SEC_E_MAX_REFERRALS_EXCEEDED: The number of maximum ticket referrals has been exceeded.";
      case SEC_E_MESSAGE_ALTERED: return "SEC_E_MESSAGE_ALTERED: The message supplied for verification has been altered.";
      case SEC_E_MULTIPLE_ACCOUNTS: return
          "SEC_E_MULTIPLE_ACCOUNTS: The received certificate was mapped to multiple accounts.";
      case SEC_E_MUST_BE_KDC: return
          "SEC_E_MUST_BE_KDC: The local computer must be a Kerberos domain controller (KDC), but it is not.";
      case SEC_E_NO_AUTHENTICATING_AUTHORITY: return
          "SEC_E_NO_AUTHENTICATING_AUTHORITY: No authority could be contacted for authentication.";
      case SEC_E_NO_CREDENTIALS: return "SEC_E_NO_CREDENTIALS: No credentials are available.";
      case SEC_E_NO_IMPERSONATION: return "SEC_E_NO_IMPERSONATION: No impersonation is allowed for this context.";
      case SEC_E_NO_IP_ADDRESSES: return
          "SEC_E_NO_IP_ADDRESSES: Unable to accomplish the requested task because the local computer does not have any IP addresses.";
      case SEC_E_NO_KERB_KEY: return "SEC_E_NO_KERB_KEY: No Kerberos key was found.";
      case SEC_E_NO_PA_DATA: return
          "SEC_E_NO_PA_DATA: Policy administrator (PA) data is needed to determine the encryption type, but cannot be found.";
      case SEC_E_NO_S4U_PROT_SUPPORT: return
          "SEC_E_NO_S4U_PROT_SUPPORT: The Kerberos subsystem encountered an error. A service for user protocol request was made against a domain controller which does not support service for a user.";
      case SEC_E_NO_TGT_REPLY: return
          "SEC_E_NO_TGT_REPLY: The client is trying to negotiate a context and the server requires a user-to-user connection, but did not send a TGT reply.";
      case SEC_E_NOT_OWNER: return "SEC_E_NOT_OWNER: The caller of the function does not own the credentials.";
      case SEC_E_OK: return "SEC_E_OK: The operation completed successfully.";
      case SEC_E_OUT_OF_SEQUENCE: return "SEC_E_OUT_OF_SEQUENCE: The message supplied for verification is out of sequence.";
      case SEC_E_PKINIT_CLIENT_FAILURE: return
          "SEC_E_PKINIT_CLIENT_FAILURE: The smart card certificate used for authentication is not trusted.";
      case SEC_E_PKINIT_NAME_MISMATCH: return
          "SEC_E_PKINIT_NAME_MISMATCH: The client certificate does not contain a valid UPN or does not match the client name in the logon request.";
      case SEC_E_QOP_NOT_SUPPORTED: return
          "SEC_E_QOP_NOT_SUPPORTED: The quality of protection attribute is not supported by this package.";
      case SEC_E_REVOCATION_OFFLINE_C: return
          "SEC_E_REVOCATION_OFFLINE_C: The revocation status of the smart card certificate used for authentication could not be determined.";
      case SEC_E_REVOCATION_OFFLINE_KDC: return
          "SEC_E_REVOCATION_OFFLINE_KDC: The revocation status of the domain controller certificate used for smart card authentication could not be determined. The system event log contains additional information.";
      case SEC_E_SECPKG_NOT_FOUND: return "SEC_E_SECPKG_NOT_FOUND: The security package was not recognized.";
      case SEC_E_SECURITY_QOS_FAILED: return
          "SEC_E_SECURITY_QOS_FAILED: The security context could not be established due to a failure in the requested quality of service (for example, mutual authentication or delegation).";
      case SEC_E_SHUTDOWN_IN_PROGRESS: return "SEC_E_SHUTDOWN_IN_PROGRESS: A system shutdown is in progress.";
      case SEC_E_SMARTCARD_CERT_EXPIRED: return
          "SEC_E_SMARTCARD_CERT_EXPIRED: The smart card certificate used for authentication has expired.";
      case SEC_E_SMARTCARD_CERT_REVOKED: return
          "SEC_E_SMARTCARD_CERT_REVOKED: The smart card certificate used for authentication has been revoked. Additional information may exist in the event log.";
      case SEC_E_SMARTCARD_LOGON_REQUIRED: return
          "SEC_E_SMARTCARD_LOGON_REQUIRED: Smart card logon is required and was not used.";
      case SEC_E_STRONG_CRYPTO_NOT_SUPPORTED: return
          "SEC_E_STRONG_CRYPTO_NOT_SUPPORTED: The other end of the security negotiation requires strong cryptography, but it is not supported on the local machine.";
      case SEC_E_TARGET_UNKNOWN: return "SEC_E_TARGET_UNKNOWN: The target was not recognized.";
      case SEC_E_TIME_SKEW: return "SEC_E_TIME_SKEW: The clocks on the client and server computers do not match.";
      case SEC_E_TOO_MANY_PRINCIPALS: return
          "SEC_E_TOO_MANY_PRINCIPALS: The KDC reply contained more than one principal name.";
      case SEC_E_UNFINISHED_CONTEXT_DELETED: return
          "SEC_E_UNFINISHED_CONTEXT_DELETED: A security context was deleted before the context was completed. This is considered a logon failure.";
      case SEC_E_UNKNOWN_CREDENTIALS: return "SEC_E_UNKNOWN_CREDENTIALS: The credentials provided were not recognized.";
      case SEC_E_UNSUPPORTED_FUNCTION: return "SEC_E_UNSUPPORTED_FUNCTION: The requested function is not supported.";
      case SEC_E_UNSUPPORTED_PREAUTH: return
          "SEC_E_UNSUPPORTED_PREAUTH: An unsupported preauthentication mechanism was presented to the Kerberos package.";
      case SEC_E_UNTRUSTED_ROOT: return
          "SEC_E_UNTRUSTED_ROOT: The certificate chain was issued by an authority that is not trusted.";
      case SEC_E_WRONG_CREDENTIAL_HANDLE: return
          "SEC_E_WRONG_CREDENTIAL_HANDLE: The supplied credential handle does not match the credential associated with the security context.";
      case SEC_E_WRONG_PRINCIPAL: return "SEC_E_WRONG_PRINCIPAL: The target principal name is incorrect.";
      default:
        std::ostringstream unknownOss;
        unknownOss << "UNKNOWN SECURITY STATUS: " << ss;
        return unknownOss.str();
      }
    }

  };

} // end namespace AMPS

#endif

