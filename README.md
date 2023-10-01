# SPSC queue over IPC

Using single producer single consumer queue to communicate between two processes.

## Build

The project is built using `conan` and `cmake`. Run following commands to create a local conan environment and build the project.

```bash
python -m venv .venv
pip3 install conan

export CONAN_HOME=$PWD/.conan
conan profile detect --force

conan install . --output-folder=build/debug --build=missing -s build_type=Debug
cd build/debug
cmake  ../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja

ninja
```

Remove created directories to cleanup the project root:

```bash
rm -rf .venv .conan build
```
