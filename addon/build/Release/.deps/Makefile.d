cmd_Makefile := cd ..; /usr/local/lib/node_modules/node-gyp/gyp/gyp_main.py -fmake --ignore-environment "--toplevel-dir=." -I/home/lihang/git/cnode/build/config.gypi -I/usr/local/lib/node_modules/node-gyp/addon.gypi -I/home/lihang/.node-gyp/0.10.33/common.gypi "--depth=." "-Goutput_dir=." "--generator-output=build" "-Dlibrary=shared_library" "-Dvisibility=default" "-Dnode_root_dir=/home/lihang/.node-gyp/0.10.33" "-Dmodule_root_dir=/home/lihang/git/cnode" binding.gyp
