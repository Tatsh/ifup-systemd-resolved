#include <QtDBus/QtDBus>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "up.h"

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::ReturnRef;

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
};

TEST(DoSetLinkDnsTests, Failure) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Resolve1ManagerContainer<MockResolve1Manager> container{iface};
    EXPECT_CALL(iface, SetLinkDNS(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(doSetLinkDns(container, 1));
}

TEST(DoSetLinkDnsTests, Success) {
    qputenv("DNS1", QByteArrayLiteral("20.0.0.1"));
    MockReply reply;
    MockResolve1Manager iface;
    Resolve1ManagerContainer<MockResolve1Manager> container{iface};
    EXPECT_CALL(iface, SetLinkDNS(1, _)).WillOnce(Return(reply));
    ASSERT_TRUE(doSetLinkDns(container, 1));
}

TEST(doSetLinkDomainsTests, Failure) {
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Resolve1ManagerContainer<MockResolve1Manager> container{iface};
    EXPECT_CALL(iface, SetLinkDomains(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(doSetLinkDomains(container, 1));
}

TEST(doSetLinkDomainsTests, Success) {
    qputenv("DNS_SUFFIX", QByteArrayLiteral("example.com example.org"));
    MockReply reply;
    MockResolve1Manager iface;
    Resolve1ManagerContainer<MockResolve1Manager> container{iface};
    EXPECT_CALL(iface, SetLinkDomains(1, _)).WillOnce(Return(reply));
    ASSERT_TRUE(doSetLinkDomains(container, 1));
}

TEST(doSetLinkDnssecTests, Failure) {
    qputenv("DNSSEC", QByteArrayLiteral("default"));
    MockReply reply;
    reply.setError(true);
    MockResolve1Manager iface;
    Resolve1ManagerContainer<MockResolve1Manager> container{iface};
    EXPECT_CALL(iface, SetLinkDNSSEC(1, _)).WillOnce(Return(reply));
    ASSERT_FALSE(doSetLinkDnssec(container, 1));
}
