// Use the preprocessor to guard that this cpp file is only compiled in Windows platform.
#if defined(PLATFORM_WINDOWS)
#include "sContext.h"
#include "sChannel.h"
#include "sSoundSource.h"

//--------------------------------------------------------------------------------------
// Helper function to try to find the location of a media file
//--------------------------------------------------------------------------------------

namespace
{
	_Use_decl_annotations_
		HRESULT FindMediaFileCch( WCHAR* strDestPath, int cchDest, LPCWSTR strFilename )
	{
		bool bFound = false;

		if (!strFilename || strFilename[0] == 0 || !strDestPath || cchDest < 10)
			return E_INVALIDARG;

		// Get the exe name, and exe path
		WCHAR strExePath[MAX_PATH] = { 0 };
		WCHAR strExeName[MAX_PATH] = { 0 };
		WCHAR* strLastSlash = nullptr;
		GetModuleFileName( nullptr, strExePath, MAX_PATH );
		strExePath[MAX_PATH - 1] = 0;
		strLastSlash = wcsrchr( strExePath, TEXT( '\\' ) );
		if (strLastSlash)
		{
			wcscpy_s( strExeName, MAX_PATH, &strLastSlash[1] );

			// Chop the exe name from the exe path
			*strLastSlash = 0;

			// Chop the .exe from the exe name
			strLastSlash = wcsrchr( strExeName, TEXT( '.' ) );
			if (strLastSlash)
				* strLastSlash = 0;
		}

		wcscpy_s( strDestPath, cchDest, strFilename );
		if (GetFileAttributes( strDestPath ) != 0xFFFFFFFF)
			return S_OK;

		// Search all parent directories starting at .\ and using strFilename as the leaf name
		WCHAR strLeafName[MAX_PATH] = { 0 };
		wcscpy_s( strLeafName, MAX_PATH, strFilename );

		WCHAR strFullPath[MAX_PATH] = { 0 };
		WCHAR strFullFileName[MAX_PATH] = { 0 };
		WCHAR strSearch[MAX_PATH] = { 0 };
		WCHAR* strFilePart = nullptr;

		GetFullPathName( L".", MAX_PATH, strFullPath, &strFilePart );
		if (!strFilePart)
			return E_FAIL;

		while (strFilePart && *strFilePart != '\0')
		{
			swprintf_s( strFullFileName, MAX_PATH, L"%s\\%s", strFullPath, strLeafName );
			if (GetFileAttributes( strFullFileName ) != 0xFFFFFFFF)
			{
				wcscpy_s( strDestPath, cchDest, strFullFileName );
				bFound = true;
				break;
			}

			swprintf_s( strFullFileName, MAX_PATH, L"%s\\%s\\%s", strFullPath, strExeName, strLeafName );
			if (GetFileAttributes( strFullFileName ) != 0xFFFFFFFF)
			{
				wcscpy_s( strDestPath, cchDest, strFullFileName );
				bFound = true;
				break;
			}

			swprintf_s( strSearch, MAX_PATH, L"%s\\..", strFullPath );
			GetFullPathName( strSearch, MAX_PATH, strFullPath, &strFilePart );
		}
		if (bFound)
			return S_OK;

		// On failure, return the file as the path but also return an error code
		wcscpy_s( strDestPath, cchDest, strFilename );

		return HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND );
	}
}


bool Audio::Sound::sSoundSource::Initialize( const Audio::Sound::sSoundInitializationParameters& i_initializationParameters )
{
	auto result = true;
	WCHAR strFilePath[MAX_PATH];
	HRESULT hr = FindMediaFileCch( strFilePath, MAX_PATH, LPCWSTR( i_initializationParameters.m_soundFilePath ) );
	if (FAILED( hr ))
	{
		std::wstring errorMsg;
		errorMsg += L"Failed to find audio file: ";
		errorMsg += i_initializationParameters.m_soundFilePath;
		_ASSERT_EXPR( false, errorMsg.c_str() );
		result = false;
		return result;
	}

	//
	// Read in the wave file
	//
	if (FAILED( hr = DirectX::LoadWAVAudioFromFileEx( strFilePath, m_pData, m_wavData ) ))
	{
		std::wstring errorMsg;
		errorMsg += L"Failed to load the Wav audio file: ";
		errorMsg += strFilePath;
		_ASSERT_EXPR( false, errorMsg.c_str() );
		result = false;
		return result;
	}
	return result;
}

bool Audio::Sound::sSoundSource::CleanUp()
{
	auto result = true;
	{
		std::lock_guard<std::mutex> lock( m_mutex );
		for (auto pChannel : m_pActiveChannels)
		{
			pChannel->Stop();
		}
	}
	bool allChannelsDeactivated = false;
	do
	{
		std::lock_guard<std::mutex> lock( m_mutex );
		allChannelsDeactivated = m_pActiveChannels.size() == 0;
	} while (!allChannelsDeactivated);
	return result;
}

void Audio::Sound::sSoundSource::PopulateSoundInitializationParameters(
	Audio::Sound::sSoundInitializationParameters& o_soundInitializationParams,
	const wchar_t* i_soundFilePath
)
{
	o_soundInitializationParams.m_soundFilePath = i_soundFilePath;
}
#endif