
# Clone
git clone --recurse-submodules https://github.com/libopencm3/libopencm3-template.git your-project

If you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)

# Directories
* my-project contains your application
* my-common-code contains something shared.

# Build & Flash
    1. make -C libopencm3 # (Only needed once)
    2. make -C my-project


