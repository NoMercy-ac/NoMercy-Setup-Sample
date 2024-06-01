Server changes/Player validation part is only supported by premium plan, so if you are not a premium user disable ENABLE_NOMERCY_SERVER macro from service.h, otherwise don't forget change your license ID and API key in same file.

Add the new NoMercy***.cpp file names to your Makefile/CMakeLists.txt/VS project source files index list, and add these files to your game/src path.

If you purchase a license, move the NoMercy_heartbeat_priv.key file to all your channel core folders (creating a symlink with ln is also acceptable) or add a static path to the load function in main.cpp.

Make the other explained changes in the file contents as well.

