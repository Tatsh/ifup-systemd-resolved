#include <QtDBus/QtDBus>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "up.h"

using ::testing::_;
using ::testing::Return;

TEST(GenerateAddressesTests, EmptyVars) {
    auto x = generateAddresses();
    ASSERT_EQ(x.length(), 0);
}

TEST(GenerateAddressesTests, OneVarIPV4) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    auto x = generateAddresses();
    ASSERT_EQ(x.length(), 1);
    ASSERT_EQ(x[0].family, AF_INET);
}

TEST(GenerateAddressesTests, OneVarIPV6) {
    qputenv("DNS1", QByteArrayLiteral("2001:db8::ff00:42:8329"));
    auto x = generateAddresses();
    ASSERT_EQ(x.length(), 1);
    ASSERT_EQ(x[0].family, AF_INET6);
}

TEST(GenerateAddressesTests, TwoVarsMixed) {
    qputenv("DNS1", QByteArrayLiteral("2001:db8::ff00:42:8329"));
    qputenv("DNS2", QByteArrayLiteral("20.0.0.1"));
    auto x = generateAddresses();
    ASSERT_EQ(x.length(), 2);
    ASSERT_EQ(x[0].family, AF_INET6);
    ASSERT_EQ(x[1].family, AF_INET);
}

TEST(GenerateDomainsTests, EmptyVars) {
    auto x = generateDomains();
    ASSERT_EQ(x.length(), 0);
}

TEST(GenerateDomainsTests, Basic) {
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    auto x = generateDomains();
    ASSERT_EQ(x.length(), 2);
    ASSERT_EQ(x[0].domain, QStringLiteral("example.com"));
    ASSERT_EQ(x[1].domain, QStringLiteral("example.org"));
}

class MockReply {
public:
    void waitForFinished() {
    }
    bool isError() {
        return error_;
    }
    void setError(bool error) {
        error_ = error;
    }

private:
    bool error_ = false;
};

class MockResolve1Manager {
public:
    MOCK_METHOD(MockReply, SetLinkDNS, (int, const LinkDnsIpList &), (const));
    MOCK_METHOD(MockReply, SetLinkDomains, (int, const LinkDomainList &), (const));
    MOCK_METHOD(MockReply, SetLinkDNSSEC, (int, const QString &), (const));
    MOCK_METHOD(bool, isValid, (), (const));
    MOCK_METHOD(QString, lastError, (), (const));
};

class MockUp : public Up<MockResolve1Manager> {
public:
    MockUp(MockResolve1Manager &iface) : Up<MockResolve1Manager>(iface) {
    }
    MOCK_METHOD(bool, doSetLinkDns, (int), (override));
    MOCK_METHOD(bool, doSetLinkDomains, (int), (override));
    MOCK_METHOD(bool, doSetLinkDnssec, (int), (override));
};

TEST(DoSetLinkDnsTests, Failure) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDNS(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(mup.doSetLinkDns(1));
}

TEST(DoSetLinkDnsTests, Success) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    MockReply reply;
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDNS(1, _)).WillOnce(Return(reply));
    ASSERT_TRUE(mup.doSetLinkDns(1));
}

TEST(doSetLinkDomainsTests, Failure) {
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDomains(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(mup.doSetLinkDomains(1));
}

TEST(doSetLinkDomainsTests, Success) {
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    MockReply reply;
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDomains(1, _)).WillOnce(Return(reply));
    ASSERT_TRUE(mup.doSetLinkDomains(1));
}

TEST(doSetLinkDnssecTests, Failure) {
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDNSSEC(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(mup.doSetLinkDnssec(1));
}

TEST(doSetLinkDnssecTests, Success) {
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    MockReply reply;
    MockResolve1Manager iface;
    Up<MockResolve1Manager> mup(iface);
    EXPECT_CALL(iface, SetLinkDNSSEC(1, _)).WillOnce(Return(reply));
    ASSERT_TRUE(mup.doSetLinkDnssec(1));
}

TEST(upTests, Success) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    qputenv("PPP_IFACE", QByteArrayLiteral("lo"));
    MockResolve1Manager iface;
    MockUp mup(iface);
    int expectedDeviceIndex = QNetworkInterface::interfaceIndexFromName(QStringLiteral("lo"));
    EXPECT_CALL(iface, isValid()).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDns(expectedDeviceIndex)).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDomains(expectedDeviceIndex)).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDnssec(expectedDeviceIndex)).WillOnce(Return(true));
    ASSERT_TRUE(mup.up());
}

TEST(upTests, Failure) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    qputenv("PPP_IFACE", QByteArrayLiteral("lo"));
    MockResolve1Manager iface;
    MockUp mup(iface);
    int expectedDeviceIndex = QNetworkInterface::interfaceIndexFromName(QStringLiteral("lo"));
    EXPECT_CALL(iface, isValid()).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDns(expectedDeviceIndex)).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDomains(expectedDeviceIndex)).WillOnce(Return(true));
    EXPECT_CALL(mup, doSetLinkDnssec(expectedDeviceIndex)).WillOnce(Return(false));
    ASSERT_FALSE(mup.up());
}

TEST(upTests, FailureInvalidInterface) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    qputenv("PPP_IFACE", QByteArrayLiteral("lo"));
    MockResolve1Manager iface;
    MockUp mup(iface);
    EXPECT_CALL(iface, isValid()).WillOnce(Return(false));
    ASSERT_FALSE(mup.up());
}

TEST(upTests, FailureInvalidDeviceIndex) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    MockResolve1Manager iface;
    MockUp mup(iface);
    EXPECT_CALL(iface, isValid()).WillOnce(Return(true));
    ASSERT_FALSE(mup.up());
}
