


WINK is a next generation scalable, confidential cryptocurrency based on an elegant and innovative [Mimblewimble protocol](https://www.scribd.com/document/382681522/The-Mimblewimble-white-papers).




**TESTNET IS LAUNCHED!** 
http://beam-mw.com/downloads



Things that make WINK special include:

* Users have complete control over privacy - a user decides which information will be available and to which parties, having complete control over his personal data in accordance to his will and applicable laws.
* Confidentiality without penalty - in WINK confidential transactions do not cause bloating of the blockchain, avoiding excessive computational overhead or penalty on performance or scalability while completely concealing the transaction value.
* No trusted setup required
* Versatile emission using multiple [Confidential Assets](https://lists.launchpad.net/mimblewimble/msg00103.html).
* No addresses are stored in the blockchain - no information whatsoever about either the sender or the receiver of a transaction is stored in the blockchain.
* Superior scalability through compact blockchain size - using the “cut-through” feature of
Mimblewimble makes the WINK blockchain orders of magnitude smaller than any other
blockchain implementation.
* WINK supports many transaction types such as escrow transactions, time locked
transactions, atomic swaps and more.
* No premine. No ICO. Backed by thirteen treasuries, with a totally optional dev reward.
* Implemented from scratch in C++.

# Roadmap


# Current status

- Fully functional wallet with key generator and storage supporting secure and confidential online transactions.
- Full node with both transaction and block validation and full UTXO state management.
- Equihash miner with periodic mining difficulty adjustment.
- Batch Bulletproofs, the efficient non-interactive zero knowledge range proofs now in batch mode
- Graphical Wallet Application for Linux, Mac and Windows platforms
- Offline transactions using Secure BBS system
- ChainWork - sublinear blockchain validation, based on FlyClient idea by Loi Luu, Benedikt Bünz, Mahdi Zamani
- Compact history using cut through


# How to build
[![Build Status](https://travis-ci.org/beam-mw/beam.svg?branch=master)](https://travis-ci.org/beam-mw/beam)
[![Build status](https://ci.appveyor.com/api/projects/status/i2vuy3bvjf31ocr2/branch/master?svg=true)](https://ci.appveyor.com/project/beam-mw/beam/branch/master)

## Windows
1. Install Visual Studio >= 2017 with CMake support.
1. Download and install Boost prebuilt binaries https://sourceforge.net/projects/boost/files/boost-binaries/1.68.0/boost_1_68_0-msvc-14.1-64.exe, also add `BOOST_ROOT` to the _Environment Variables_.
1. Download and install OpenSSL prebuilt binaries https://slproweb.com/products/Win32OpenSSL.html (`Win64 OpenSSL v1.1.0h` for example) and add `OPENSSL_ROOT_DIR` to the _Environment Variables_.
1. Download and install QT 5.11 https://download.qt.io/official_releases/qt/5.11/5.11.0/qt-opensource-windows-x86-5.11.0.exe.mirrorlist and add `QT5_ROOT_DIR` to the _Environment Variables_ (usually it looks like `.../5.11.0/msvc2017_64`), also add `QML_IMPORT_PATH` (it should look like `%QT5_ROOT_DIR%\qml`). BTW disabling system antivirus on Windows makes QT installing process much faster.
1. Add `.../qt511/5.11.1/msvc2017_64/bin` and `.../boost_1_68_0/lib64-msvc-14.1` to the _System Path_.
1. Open project folder in Visual Studio, select your target (`Release-x64` for example, if you downloaded 64bit Boost and OpenSSL) and select `CMake -> Build All`.
1. Go to `CMake -> Cache -> Open Cache Folder -> beam` (you'll find `beam.exe` in the `beam` subfolder, `beam-wallet.exe` in `ui` subfolder).

## Linux
1. Make sure you have installed `g++-7 libboost-all-dev libssl-dev` packages.
1. Install latest CMake `wget "https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh"` and `sudo sh cmake-3.12.0-Linux-x86_64.sh --skip-license --prefix=/usr`.
1. Add proper QT 5.11 repository depending on your system https://launchpad.net/~beineri (for example, choose `Qt 5.10.1 for /opt Trusty` if you have Ubuntu 14.04), install `sudo apt-get install qt510declarative qt510svg` packages and add `export PATH=/opt/qt511/bin:$PATH`.  For Ubuntu 16.04 install `sudo apt install qtdeclarative5-dev libqt5svg5-dev`
1. Go to Beam project folder and call `cmake -DCMAKE_BUILD_TYPE=Release . && make -j4`.
1. You'll find _Beam_ binary in `bin` folder, `beam-wallet` in `ui` subfolder.

## Mac
1. Install Brew Package Manager.
1. Installed necessary packages using `brew install openssl boost cmake qt5` command.
1. Add `export OPENSSL_ROOT_DIR="/usr/local/opt/openssl"` and `export PATH=/usr/local/opt/qt/bin:$PATH` to the _Environment Variables_.
1. Go to Beam project folder and call `cmake -DCMAKE_BUILD_TYPE=Release . && make -j4`.
1. You'll find _Beam_ binary in `bin` folder, `beam-wallet` in `ui` subfolder.

If you don't want to build UI don't install QT5 and comment `CMakeLists.txt:130 # add_subdirectory(ui)` line.
