#pragma once

#include <memory>
#include <json/json.h>


class WebToken {
public:
    std::string mHeader;
    unsigned char mHeaderInfo[40]{};
    std::string mData;
    unsigned char mDataInfo[40]{};
    std::string mSignature;

    WebToken() = default;
};

class UnverifiedCertificate {
public:
    class WebToken const                   mRawToken;
    std::unique_ptr<UnverifiedCertificate> mParentUnverifiedCertificate;

    UnverifiedCertificate() = default;
};

class Certificate {
public:
    class UnverifiedCertificate  mUnverifiedCertificate;
    std::unique_ptr<Certificate> mParentCertificate;
    bool                         mIsValid;

    Certificate() = default;
};

class ConnectionRequest {
public:
    // prevent constructor by default
    ConnectionRequest& operator=(ConnectionRequest const&);
    ConnectionRequest() = default;

    std::unique_ptr<class UnverifiedCertificate> mCertificateData;
    std::unique_ptr<class Certificate>           mCertificate;
    std::unique_ptr<class WebToken>              mRawToken;
    unsigned char                                mClientSubId;
};



class LoginPacket {
public:
    char data[0x30]{};
    int                                mClientNetworkVersion; // this+0x30
    std::unique_ptr<ConnectionRequest> mConnectionRequest;    // this+0x38

    // prevent constructor by default
    LoginPacket& operator=(LoginPacket const&);
    LoginPacket(LoginPacket const&);
    LoginPacket() = default;
};