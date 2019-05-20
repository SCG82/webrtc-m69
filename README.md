**WebRTC is a free, open software project** that provides browsers and mobile
applications with Real-Time Communications (RTC) capabilities via simple APIs.
The WebRTC components have been optimized to best serve this purpose.

**Our mission:** To enable rich, high-quality RTC applications to be
developed for the browser, mobile platforms, and IoT devices, and allow them
all to communicate via a common set of protocols.

The WebRTC initiative is a project supported by Google, Mozilla and Opera,
amongst others.

## Development

See http://www.webrtc.org/native-code/development for more information.

### Build from source
* RECOMMENDED *

Note: do not clone/download this repository

``` bash
export DEV_DIR=~/dev # or any directory with full permissions

mkdir $DEV_DIR && cd $DEV_DIR
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

export "PATH=$PATH:$DEV_DIR/depot_tools"

mkdir webrtc-checkout && cd webrtc-checkout
fetch --nohooks webrtc
gclient sync

curl -L -O https://raw.githubusercontent.com/SCG82/webrtc-m69/m69/webrtc69.patch

cd src
git checkout -b m69 refs/remotes/branch-heads/69
gclient sync

git apply ../webrtc69.patch

gn gen out/Release --args='use_rtti=true is_debug=false rtc_use_h264=true ffmpeg_branding="Chrome" rtc_include_tests=false'
ninja -C out/Release

mkdir ../include
mkdir ../lib

rsync -avh --prune-empty-dirs --exclude="build" --exclude="out" --include="*/" --include="*.h" --exclude="*" ./* ../include/
cp -p out/Release/obj/libwebrtc.a ../lib/
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
