// tinygettext - A gettext replacement that works directly on .po files
// Copyright (c) 2009 Ingo Ruhnke <grumbel@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "tinygettext/windows_file_system.hpp"

#include <sys/types.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#ifdef WINRT
#include <locale>
#include <codecvt>
#include <ppltasks.h>
#endif

using namespace concurrency;

using namespace Windows::Foundation::Collections;

namespace tinygettext {

WindowsFileSystem::WindowsFileSystem()
{
}


std::vector<std::string>
WindowsFileSystem::open_directory(const std::string& pathname)
{
	
	std::wstring intermediateForm(pathname.begin(), pathname.end());

	std::replace(intermediateForm.begin(), intermediateForm.end(), '/', '\\');

	Platform::String^ folder_path = ref new Platform::String(intermediateForm.c_str());

	Windows::Storage::StorageFolder^ appFolder =
		Windows::ApplicationModel::Package::Current->InstalledLocation;

	auto return_files = std::make_shared<std::vector<std::string> >();

	auto folder = PerformSynchronously(appFolder->GetFolderAsync(folder_path));
	auto files = PerformSynchronously(folder->GetFilesAsync());

	for (unsigned int i = 0; i < files->Size; ++i) {

		Platform::String^ file = files->GetAt(i)->DisplayName;
		Platform::String^ extension = files->GetAt(i)->FileType;

		std::wstring temp_file(file->Begin());
		std::string file_path(temp_file.begin(), temp_file.end());

		std::wstring temp_extension(extension->Begin());
		std::string file_extension(temp_extension.begin(), temp_extension.end());

		file_path = file_path + file_extension;

		return_files->push_back(file_path);
		// Process File 
	}

	return *return_files;
}

std::unique_ptr<std::istream>
WindowsFileSystem::open_file(const std::string& filename)
{
  return std::unique_ptr<std::istream>(new std::ifstream(filename.c_str()));
}

} // namespace tinygettext

/* EOF */
