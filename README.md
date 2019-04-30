# AMPS C++ Client Kerberos Authentication

## Dependencies

The C++ Kerberos authenticator for Linux (GSSAPI) has a dependency on the GSSAPI libs that are part of the [krb5 distribution](http://web.mit.edu/Kerberos/dist).

## Example

For Kerberos authentication using C++ there are two different `Authenticator` implmentations, one for GSSAPI based authentication and one for SSPI based authentication. GSSAPI is the only option for authentication when running on Linux, but, unlike Java, it is not supported on Windows. Specifically, `AMPSKerberosGSSAPIAuthenticator` is used when running on Linux and `AMPSKerberosSSPIAuthenticator` is used when running on Windows.

```cpp
#include <ampsplusplus.hpp>
#include <string>

#ifdef _WIN32
  #include "AMPSKerberosSSPIAuthenticator.hpp"
#else
  #include "AMPSKerberosGSSAPIAuthenticator.hpp"
#endif

int main ()
{
  std::string username("username");
  std::string hostname("hostname");

  std::string amps_spn = std::string("AMPS/") + hostname;
  std::string amps_uri = std::string("tcp://") + username + "@" + hostname + ":10304/amps/json";

#ifdef _WIN32
  AMPS::AMPSKerberosSSPIAuthenticator authenticator(amps_spn);
#else
  AMPS::AMPSKerberosGSSAPIAuthenticator authenticator(amps_spn);
#endif
  AMPS::Client client("KerberosExampleClient");
  client.connect(amps_uri);
  client.logon(5000, authenticator);
}
```

## See Also

[Kerberos Authentication Blog Article]()
[libamps_multi_authentication](http://devnull.crankuptheamps.com/documentation/html/5.3.0.0/user-guide/html/chapters/auxiliary_modules.html#authentication-with-the-amps-multimechanism-authentication-module) AMPS Server Module

