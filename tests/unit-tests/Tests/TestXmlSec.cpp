#include "stdafx.h"
#include <Util/XML/Xml.hpp>
#include <Util/XML/Sec/X509Cert.h>
#include <Util/XML/Sec/RsaKey.h>

using namespace Util::XML;
using namespace Util::XML::Sec;

namespace
{
    X509CertPtr x509Cert;
    RsaKeyPtr   rsaKey;
}

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

    const std::string xmlToValidate = "\
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

    const std::string xmlToSign = "\
<Letter>\n\
<ToAddress>The address of the Recipient</ToAddress>\n\
<FromAddress>The address of the Sender</FromAddress>\n\
<Text>\n\
To whom it may concern\n\
\n\
...\n\
</Text>\n\
</Letter>\n";
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
    const std::string issuer    { "C=AU, ST=Vic, L=Melbourne, O=XML-Security-C Project, OU=XSEC-CA, CN=XSEC-CA Root" };
    const std::string serial    { "4099" };
    const std::string algorithm { "rsaEncryption" };
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

TEST(XmlSec, ValidateSignature)
{
    XmlSignaturePtr signature{};
    
    const XmlDoc doc(xmlToValidate);

    ASSERT_NO_THROW(
        signature = std::make_shared<XmlSignature>(doc);
        );

    EXPECT_TRUE(signature->validate(*rsaKey));
    EXPECT_EQ("", signature->error());
}

namespace
{ 
    XmlDocPtr docToSign; 
    XmlSignaturePtr signature;
}

TEST(XmlSec, SignXmlDoc)
{
    ASSERT_NE(nullptr, rsaKey);

    docToSign = std::make_shared<XmlDoc>(xmlToSign);

    ASSERT_NO_THROW(
        signature = std::make_shared<XmlSignature>();
        signature->sign(*docToSign, *rsaKey);
    );

    XmlElementPtr root{ docToSign->root() };

    XmlElementPtr signatureNode{ root->find(XmlNode("Signature")) };
    ASSERT_NE(nullptr, signatureNode);

    const std::string digestValue{ "pzg30SuDz5s45pYl3AR7cAjq23k=" };
    XmlElementPtr digestValueNode{ root->find(XmlNode("DigestValue")) };
    ASSERT_NE(nullptr, digestValueNode);
    EXPECT_EQ(digestValue, digestValueNode->text());

    const std::string signatureValue{ "QBQo9HcWJLJDZz/Jcer7NoGX97IlrNbc/95TXdOSvznN8/c4WXF26gD8QVo1UGfZ\nVicjATMx7puEgoTGi+XhoLSxU3rUbse0jiBMK3LKKyxvw7JAQLij750bfUeyPKXp\nO8ZgdKvBJEufS5N7wlQEcgt8cJJp5xhMHAKENQozPRM=" };
    XmlElementPtr signatureValueNode{ root->find(XmlNode("SignatureValue")) };
    ASSERT_NE(nullptr, signatureValueNode);
    EXPECT_EQ(signatureValue, signatureValueNode->text());
}

TEST(XmlSec, AddCertificateInfo)
{
    ASSERT_NE(nullptr, docToSign);
    ASSERT_NE(nullptr, x509Cert);
    
    ASSERT_NO_THROW(
        signature->addCertificateInfo(*x509Cert);
        );

    XmlElementPtr root{ docToSign->root() };

    XmlElementPtr x509CertificateNode{ root->find(XmlNode("X509Certificate")) };
    ASSERT_NE(nullptr, x509CertificateNode);
    ASSERT_EQ(x509Cert->base64Encoded(), x509CertificateNode->text());

    XmlElementPtr x509IssuerNameNode{ root->find(XmlNode("X509IssuerName")) };
    ASSERT_NE(nullptr, x509IssuerNameNode);
    ASSERT_EQ(x509Cert->issuer(), x509IssuerNameNode->text());

    XmlElementPtr x509SerialNumberNode{ root->find(XmlNode("X509SerialNumber")) };
    ASSERT_NE(nullptr, x509SerialNumberNode);
    ASSERT_EQ(x509Cert->serial(), x509SerialNumberNode->text());
}
