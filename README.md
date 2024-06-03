# RISC-V Emulator

## Installing RISC-V toolchain

### Getting the sources
    git clone https://github.com/riscv/riscv-gnu-toolchain

### Prerequisites
    sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev libslirp-dev

### Configure
    ./configure --prefix=/opt/riscv --with-arch=rv32ima --with-abi=ilp32 --with-multilib-generator="rv32i-ilp32--;rv32ima-ilp32--"

### Make and install
    make

## Installing QEMU

### Getting the sources
    git clone https://github.com/qemu/qemu

### Prerequisites
    sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git

### Configure
    ./configure --target-list=riscv32-softmmu,riscv32-linux-user --prefix=/opt/qemu-riscv32

### Make and install
    make -j$(nproc)
    sudo make install

