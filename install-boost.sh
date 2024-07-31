#!/bin/bash
set -ex

RIME_ROOT="$(cd "$(dirname "$0")"; pwd)"

boost_version="${boost_version=1_85_0}"

BOOST_ROOT="${BOOST_ROOT=${RIME_ROOT}/deps/boost_${boost_version}}"

boost_tarball="boost_${boost_version}.tar.gz"
download_url="https://archives.boost.io/release/1.85.0/source/${boost_tarball}"
boost_tarball_sha256sum="be0d91732d5b0cc6fbb275c7939974457e79b54d6f07ce2e3dfdd68bef883b0b  ${boost_tarball}"

download_boost_source() {
    cd "${RIME_ROOT}/deps"
    if ! [[ -f "${boost_tarball}" ]]; then
        curl -LO "${download_url}"
    fi
    echo "${boost_tarball_sha256sum}" | shasum -a 256 -c
    tar -xJf "${boost_tarball}"
    [[ -f "${BOOST_ROOT}/bootstrap.sh" ]]
}

boost_cxxflags='-arch arm64 -arch x86_64'

build_boost_macos() {
    cd "${BOOST_ROOT}"
    ./bootstrap.sh --with-toolset=clang --with-libraries="${boost_libs}"
    ./b2 -q -a link=static architecture=arm cxxflags="${boost_cxxflags}" stage
    for lib in stage/lib/*.a; do
        lipo $lib -info
    done
}

if [[ $# -eq 0 || " $* " =~ ' --download ' ]]; then
    if [[ ! -f "${BOOST_ROOT}/bootstrap.sh" ]]; then
        download_boost_source
    else
        echo "found boost at ${BOOST_ROOT}"
    fi
    cd "${BOOST_ROOT}"
    ./bootstrap.sh
    ./b2 headers
fi
if [[ ($# -eq 0 || " $* " =~ ' --build ') && -n "${boost_libs}" ]]; then
    if [[ "$OSTYPE" =~ 'darwin' ]]; then
        build_boost_macos
    fi
fi
