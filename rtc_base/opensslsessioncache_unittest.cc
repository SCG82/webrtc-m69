/*
 *  Copyright 2018 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <openssl/ssl.h>
#include <stdlib.h>

#include <map>
#include <memory>

#include "rtc_base/gunit.h"
#include "rtc_base/openssl.h"
#include "rtc_base/opensslsessioncache.h"

// josemrecio - dirty workaround, this must be done properly
#ifndef OPENSSL_IS_BORINGSSL
#warning "SSL_SESSION_new should be properly addressed"
#define SSL_SESSION_new(x) SSL_SESSION_new()
#endif

namespace rtc {

TEST(OpenSSLSessionCache, DTLSModeSetCorrectly) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLSv1_2_client_method());
#endif

  OpenSSLSessionCache session_cache(SSL_MODE_DTLS, ssl_ctx);
  EXPECT_EQ(session_cache.GetSSLMode(), SSL_MODE_DTLS);

  SSL_CTX_free(ssl_ctx);
}

TEST(OpenSSLSessionCache, TLSModeSetCorrectly) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(TLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());
#endif

  OpenSSLSessionCache session_cache(SSL_MODE_TLS, ssl_ctx);
  EXPECT_EQ(session_cache.GetSSLMode(), SSL_MODE_TLS);

  SSL_CTX_free(ssl_ctx);
}

TEST(OpenSSLSessionCache, SSLContextSetCorrectly) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLSv1_2_client_method());
#endif

  OpenSSLSessionCache session_cache(SSL_MODE_DTLS, ssl_ctx);
  EXPECT_EQ(session_cache.GetSSLContext(), ssl_ctx);

  SSL_CTX_free(ssl_ctx);
}

TEST(OpenSSLSessionCache, InvalidLookupReturnsNullptr) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLSv1_2_client_method());
#endif

  OpenSSLSessionCache session_cache(SSL_MODE_DTLS, ssl_ctx);
  EXPECT_EQ(session_cache.LookupSession("Invalid"), nullptr);
  EXPECT_EQ(session_cache.LookupSession(""), nullptr);
  EXPECT_EQ(session_cache.LookupSession("."), nullptr);

  SSL_CTX_free(ssl_ctx);
}

TEST(OpenSSLSessionCache, SimpleValidSessionLookup) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLSv1_2_client_method());
#endif
  SSL_SESSION* ssl_session = SSL_SESSION_new(ssl_ctx);

  OpenSSLSessionCache session_cache(SSL_MODE_DTLS, ssl_ctx);
  session_cache.AddSession("webrtc.org", ssl_session);
  EXPECT_EQ(session_cache.LookupSession("webrtc.org"), ssl_session);

  SSL_CTX_free(ssl_ctx);
}

TEST(OpenSSLSessionCache, AddToExistingReplacesPrevious) {
#if (OPENSSL_VERSION_NUMBER >= 0x10100000)
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLS_method());
#else
  SSL_CTX* ssl_ctx = SSL_CTX_new(DTLSv1_2_client_method());
#endif
  SSL_SESSION* ssl_session_1 = SSL_SESSION_new(ssl_ctx);
  SSL_SESSION* ssl_session_2 = SSL_SESSION_new(ssl_ctx);

  OpenSSLSessionCache session_cache(SSL_MODE_DTLS, ssl_ctx);
  session_cache.AddSession("webrtc.org", ssl_session_1);
  session_cache.AddSession("webrtc.org", ssl_session_2);
  EXPECT_EQ(session_cache.LookupSession("webrtc.org"), ssl_session_2);

  SSL_CTX_free(ssl_ctx);
}

}  // namespace rtc
