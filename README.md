# RISC-V Emulator

This is a simple RISC-V emulator that support RV32I instruction set. It can run minimal RISC-V linux kernel (no MMU support) and some simple programs. Follow the instructions below to build and run the emulator.

## Build and Run
1. Clone the repository:
    ```bash
    git clone https://github.com/dakshinatharindu/riscv-emulator.git
    cd riscv-emulator
    ```
2. Initialize and update the submodules:
    ```bash
    git submodule update --init --recursive
    ```
3. Build the emulator:
    ```bash
    cd remu
    mkdir build
    cd build
    cmake ..
    make
    ```
4. Build the minimal RISC-V linux kernel:
    ```bash
    cd ../..
    make buildroot
    ```
5. Run the emulator with the built kernel:
    ```bash
    make run
    ```

You should see the emulator booting up and running the minimal RISC-V linux kernel. You can interact with the kernel through the terminal. Following is a screenshot of the emulator booting up:

![Booting terminal](https://private-user-images.githubusercontent.com/79160102/614301590-a1a0fe86-5b28-4b95-b44b-6ffdba03502e.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3ODI2ODg4MTIsIm5iZiI6MTc4MjY4ODUxMiwicGF0aCI6Ii83OTE2MDEwMi82MTQzMDE1OTAtYTFhMGZlODYtNWIyOC00Yjk1LWI0NGItNmZmZGJhMDM1MDJlLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNjA2MjglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjYwNjI4VDIzMTUxMlomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWMzMGE0NjViYjUyZTBkNjU1MjhkNWM2ZDY2NDVlOTgyZWVlN2M0MmI4NDg3YTE2NjQwZDQwMThhNjViYWMxMDImWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JnJlc3BvbnNlLWNvbnRlbnQtdHlwZT1pbWFnZSUyRnBuZyJ9.VVSivKGVvAZX-hVdF8gKXia-bHWmzPzOJBknIdHnXeo)