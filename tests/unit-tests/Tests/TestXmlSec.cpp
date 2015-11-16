#include "stdafx.h"
#include <Util/XML/Sec/X509Cert.h>
#include <Util/XML/Sec/RsaKey.h>

#include <iostream>

#include <xsec/utils/XSECPlatformUtils.hpp>
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGReference.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyHMAC.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include <xsec/enc/XSECCryptoException.hpp>

// Xerces
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

using namespace Util::XML::Sec;

XERCES_CPP_NAMESPACE_USE
using namespace std;

namespace
{
    X509CertPtr x509Cert;
    RsaKeyPtr   rsaKey;
}

char docToValidate[4096] = "\
<Letter>\n\
<ToAddress>The address of the Recipient</ToAddress>\n\
<FromAddress>The address of the Sender</FromAddress>\n\
<Text>\n\
To whom it may concern\n\
\n\
...\n\
</Text>\n\
<ds:Signature xmlns:ds=\"http://www.w3.org/2000/09/xmldsig#\">\n\
<ds:SignedInfo>\n\
<ds:CanonicalizationMethod Algorithm = \"http://www.w3.org/TR/2001/REC-xml-c14n-20010315#WithComments\"/>\n\
<ds:SignatureMethod Algorithm=\"http://www.w3.org/2000/09/xmldsig#rsa-sha1\"/>\n\
<ds:Reference URI=\"\">\n\
<ds:Transforms>\n\
<ds:Transform Algorithm=\"http://www.w3.org/2000/09/xmldsig#enveloped-signature\"/>\n\
</ds:Transforms>\n\
<ds:DigestMethod Algorithm=\"http://www.w3.org/2000/09/xmldsig#sha1\"/>\n\
<ds:DigestValue>askxS/A3BaLCjFjZ/ttU9c12kA4=</ds:DigestValue>\n\
</ds:Reference>\n\
</ds:SignedInfo>\n\
<ds:SignatureValue>Nrl0KwXyPKaqHuOWlJf7cB4tOFGPSKJOULcua0WW6OmjABuUT5LfySUDVRVusSxT\n\
InZBQAQGXlOj4ndE7wU5pl+UxWpSnuY5/BSkrqbbjut6m2jQ9SmLIbU39VEz+I2E\n\
IjJY9p2mrI9W5Z+ic0N7wXlt4JJSSytH3v3q8RgDJnk=\n\
</ds:SignatureValue>\n\
</ds:Signature>\n\
</Letter>\n";

namespace 
{
    const std::string cert = "\n\
MIIC7jCCAq6gAwIBAgICEAMwCQYHKoZIzjgEAzB5MQswCQYDVQQGEwJBVTEMMAoG\n\
A1UECBMDVmljMRIwEAYDVQQHEwlNZWxib3VybmUxHzAdBgNVBAoTFlhNTC1TZWN1\n\
cml0eS1DIFByb2plY3QxEDAOBgNVBAsTB1hTRUMtQ0ExFTATBgNVBAMTDFhTRUMt\n\
Q0EgUm9vdDAeFw0wMjEyMTIxMDEzMTlaFw0xMjEyMDkxMDEzMTlaMFYxCzAJBgNV\n\
BAYTAkFVMQwwCgYDVQQIEwNWaWMxHzAdBgNVBAoTFlhNTC1TZWN1cml0eS1DIFBy\n\
b2plY3QxGDAWBgNVBAMTD1JTQSBTYW1wbGUgQ2VydDCBnzANBgkqhkiG9w0BAQEF\n\
AAOBjQAwgYkCgYEA0I96ZLWXJAM8LIUZ37y4c93WjVOsaQM6B6N6own7cQ8B9Ucp\n\
zwOXsnCVZFfJsB9gtTxZLaY7UE2dgrz47iplFecxL5mM7iKOklmGlWTfzyY87BGT\n\
GlQPlPBoX19WBf67Lhc1wovK+hVXdyzf/6VxxMKAxnSVHZaXVRLl9YhSpTUCAwEA\n\
AaOCAQEwgf4wCQYDVR0TBAIwADAsBglghkgBhvhCAQ0EHxYdT3BlblNTTCBHZW5l\n\
cmF0ZWQgQ2VydGlmaWNhdGUwHQYDVR0OBBYEFGq6U1SwYNRyTJGAwARirEdavfXB\n\
MIGjBgNVHSMEgZswgZiAFBKNX9CsAIsjUIFmVq4wE4wlOGC5oX2kezB5MQswCQYD\n\
VQQGEwJBVTEMMAoGA1UECBMDVmljMRIwEAYDVQQHEwlNZWxib3VybmUxHzAdBgNV\n\
BAoTFlhNTC1TZWN1cml0eS1DIFByb2plY3QxEDAOBgNVBAsTB1hTRUMtQ0ExFTAT\n\
BgNVBAMTDFhTRUMtQ0EgUm9vdIIBADAJBgcqhkjOOAQDAy8AMCwCFGoKhVPnDeg9\n\
nbEFo2KDDlG/NiUqAhRJxQPLXDhehQjn6eqQWOUlkFtA9A==";

    const std::string privKey = "\n\
-----BEGIN RSA PRIVATE KEY-----\n\
MIICXAIBAAKBgQDQj3pktZckAzwshRnfvLhz3daNU6xpAzoHo3qjCftxDwH1RynP\n\
A5eycJVkV8mwH2C1PFktpjtQTZ2CvPjuKmUV5zEvmYzuIo6SWYaVZN/PJjzsEZMa\n\
VA+U8GhfX1YF/rsuFzXCi8r6FVd3LN//pXHEwoDGdJUdlpdVEuX1iFKlNQIDAQAB\n\
AoGAYQ7Uc7e6Xa0PvNw4XVHzOSC870pISxqQT+u5b9R+anAEhkQW5dsTJpyUOX1N\n\
RCRmGhG6oq7gnY9xRN1yr0uVfJNtc9/HnzJL7L1jeJC8Ub+zbEBvNuPDL2P21ArW\n\
tcXRycUlfRCRBLop7rfOYPXsjtboAGnQY/6hK4rOF4XGrQUCQQD3Euj+0mZqRRZ4\n\
M1yN2wVP0mKOMg2i/HZXaNeVd9X/wyBgK6b7BxHf6onf/mIBWnJnRBlvdCrSdhuT\n\
lPKEoSgvAkEA2BhfWwQihqD4qJcV65nfosjzOZG41rHX69nIqHI7Ejx5ZgeQByH9\n\
Ym96yXoSpZj9ZlFsJYNogTBBnUBjs+jL2wJAFjpVS9eR7y2X/+hfA0QZDj1XMIPA\n\
RlGANAzymDfXwNLFLuG+fAb+zK5FCSnRl12TvUabIzPIRnbptDVKPDRjcQJBALn8\n\
0CVv+59P8HR6BR3QRBDBT8Xey+3NB4Aw42lHV9wsPHg6ThY1hPYx6MZ70IzCjmZ/\n\
8cqfvVRjijWj86wm0z0CQFKfRfBRraOZqfmOiAB4+ILhbJwKBBO6avX9TPgMYkyN\n\
mWKCxS+9fPiy1iI+G+B9xkw2gJ9i8P81t7fsOvdTDFA=\n\
-----END RSA PRIVATE KEY-----";
}

TEST(XmlSec, Sanity)
{
    try
    {
        XMLPlatformUtils::Initialize();
        XSECPlatformUtils::Initialise();
    }
    catch (const XMLException &e)
    {
        cerr << "Error during initialisation of Xerces" << endl;
        cerr << "Error Message = : "
            << e.getMessage() << endl;
    }

    // Use xerces to parse the document
    XercesDOMParser * parser = new XercesDOMParser;
    parser->setDoNamespaces(true);
    parser->setCreateEntityReferenceNodes(true);
    parser->setDoSchema(true);

    // Create an input source
    MemBufInputSource* memIS = new MemBufInputSource((const XMLByte*)
        docToValidate, (unsigned int)strlen(docToValidate), "XSECMem");

    int errorCount = 0;

    parser->parse(*memIS);
    errorCount = parser->getErrorCount();
    if (errorCount > 0)
    {
        cerr << "Error parsing input document\n";
        exit(1);
    }

    DOMDocument *doc = parser->getDocument();

    // Now create a signature object to validate the document
    XSECProvider prov;

    DSIGSignature * sig = prov.newSignatureFromDOM(doc);

    try
    {
        // Load certificate
        OpenSSLCryptoX509 * x509 = new OpenSSLCryptoX509();
        x509->loadX509Base64Bin(cert.c_str(), cert.size());
        sig->load();
        sig->setSigningKey(x509->clonePublicKey());

        // Perform check
        bool bResVerify = sig->verify();
        if (!bResVerify) {
            char * err = XMLString::transcode(sig->getErrMsgs());
            cout << "Signature check failed.Error:" << err << "\n";
            XMLString::release(&err);
        }
        else
            cout << "Signature check OK.\n";
    }
    catch (XSECException &e)
    {
        cerr << "An error occured during a signature load\n   Message: "
            << e.getMsg() << endl;
        exit(1);

    }
    catch (XSECCryptoException &e)
    {
        cerr << "An error occured in the XML-Security-C Crypto routines\nMessage: "
                 << e.getMsg() << endl;
    }

    // Clean up
    delete memIS;
    delete parser;
}

TEST(XmlSec, Initialization)
{
    ASSERT_NO_THROW(
        x509Cert    = std::make_shared<X509Cert>(cert);
        rsaKey      = std::make_shared<RsaKey>(privKey);
    );
}

namespace
{
    const std::string issuer{ "C=AU, ST=Vic, L=Melbourne, O=XML-Security-C Project, OU=XSEC-CA, CN=XSEC-CA Root" };
    const std::string serial{ "4099" };
    const std::string algorithm{ "rsaEncryption" };
}

TEST(XmlSec, X509CertAttributes)
{
    ASSERT_NE(nullptr, x509Cert);

    //ASSERT_TRUE(x509Cert->isValid());

    EXPECT_EQ(cert      , x509Cert->base64Encoded());
    EXPECT_EQ(issuer    , x509Cert->issuer());
    EXPECT_EQ(serial    , x509Cert->serial());
    EXPECT_EQ(algorithm , X509Cert::algorithmToString(x509Cert->signatureAlgorithm()));
    EXPECT_EQ(3         , x509Cert->version());
    EXPECT_EQ(0         , x509Cert->status());
}

TEST(XmlSec, RsaKey)
{
    ASSERT_NE(nullptr, rsaKey);
    EXPECT_NE(nullptr, *rsaKey);
    
    EXPECT_EQ(privKey   , rsaKey->base64Encoded());
}
