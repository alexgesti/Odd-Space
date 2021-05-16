#include "Assets.h"
#include "App.h"
#include "External/PhysFS/include/physfs.h"


Assets* Assets::instance = nullptr;
Assets* Assets::GetInstance()
{
	if (instance == nullptr) instance = new Assets();

	return instance;
}
void Assets::ResetInstance()
{
	delete instance;
	instance = nullptr;
}
Assets::Assets()
{
	// Initialize the library
	if (PHYSFS_init(nullptr) == 0)
	{
		LOG("Error loading PHYSFS");
	}
	else
	{
		LOG("PHYSFS loaded successfully");
	}
	
}
Assets::~Assets()
{
	// Deinitialize the library
	PHYSFS_deinit();
}
bool Assets::Init()
{
	// Add the search path
	PHYSFS_mount("assets.zip", NULL, 0);
	return true;
}
bool Assets::DeleteBuffer() {
	delete[] buffer;
	return true;
}
char* Assets::GetLastBuffer() {
	return buffer;
}
int Assets::MakeLoad(const char* fileName)
{
	int ret = 0;
	// Get the information buffer, and its size with the functions and variables of the library
	PHYSFS_file* data_file = PHYSFS_openRead(fileName);

	if (data_file != nullptr)
	{
		int file_lenght = PHYSFS_fileLength(data_file);
		buffer = new char[(int)file_lenght];
		int readed = PHYSFS_read(data_file, buffer, 1, (int)file_lenght);
		if (readed != file_lenght)
		{
			delete[] buffer;
		}
		ret = readed;
		PHYSFS_close(data_file);
	}


	return ret;
}
SDL_RWops* Assets::Load(const char* fileName)
{
	// Call the MakeLoad function and get the RWops structure to load the data
	int size = MakeLoad(fileName);
	return SDL_RWFromConstMem(buffer, size);
}