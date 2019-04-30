# AMPS C# Client Kerberos Authentication

## Dependencies

The C# Kerberos authenticator has a single dependency on the [NSspi NuGet package](https://www.nuget.org/packages/NSspi).

## Example

For Kerberos authentication using C# there is a single module, `AMPSKerberosAuthenticator`, for authentication on Windows.

```csharp

using AMPS.Client;
using AMPSKerberos;

class KerberosAuthExample
{
    static void Main(string[] args)
    {
        string username = "username";
        string hostname = "hostname";

        string amps_spn = string.Format("AMPS/{0}", hostname);
        string amps_uri = string.Format("tcp://{0}@{1}:10304/amps/json", username, hostname);

        AMPSKerberosAuthenticator authenticator = new AMPSKerberosAuthenticator(amps_spn);
  
        using (Client client = new Client("KerberosExampleClient"))
        {
            client.connect(amps_uri);
            client.logon(5000, authenticator);
        }
    }
}

```

## See Also

[Kerberos Authentication Blog Article]()
[libamps_multi_authentication](http://devnull.crankuptheamps.com/documentation/html/5.3.0.0/user-guide/html/chapters/auxiliary_modules.html#authentication-with-the-amps-multimechanism-authentication-module) AMPS Server Module

