**WebRTC is a free, open software project** that provides browsers and mobile
applications with Real-Time Communications (RTC) capabilities via simple APIs.
The WebRTC components have been optimized to best serve this purpose.

**Our mission:** To enable rich, high-quality RTC applications to be
developed for the browser, mobile platforms, and IoT devices, and allow them
all to communicate via a common set of protocols.

The WebRTC initiative is a project supported by Google, Mozilla and Opera,
amongst others.

### Development

See http://www.webrtc.org/native-code/development for instructions on how to get
started developing with the native code.

``` bash
gn gen out/Release --args='rtc_libvpx_build_vp9=true rtc_enable_sctp=true rtc_use_h264=true use_rtti=true rtc_build_examples=false rtc_include_tests=false is_debug=false rtc_builtin_ssl_root_certificates=true'

# to build with OpenSSL 1.1.0g instead of BoringSSL
# gn gen out/Release --args='use_rtti=true rtc_include_tests=false is_debug=false rtc_build_ssl=false rtc_ssl_root="../../obsdeps"'

ninja -C out/Release

mkdir ../include
mkdir ../lib

find . -iname "*.h" -exec rsync -R \{\} ../include/ \;

cd out/Release/obj

find . -iname "*.a" -exec rsync -R \{\} ../../../../lib/ \;
#find . -iname "*.a" -exec cp \{\} ../../../../lib/ \; # if a library isn't found try this
```

[Authoritative list](native-api.md) of directories that contain the
native API header files.

### More info

 * Official web site: http://www.webrtc.org
 * Master source code repo: https://webrtc.googlesource.com/src
 * Samples and reference apps: https://github.com/webrtc
 * Mailing list: http://groups.google.com/group/discuss-webrtc
 * Continuous build: http://build.chromium.org/p/client.webrtc
 * [Coding style guide](style-guide.md)
 * [Code of conduct](CODE_OF_CONDUCT.md)
