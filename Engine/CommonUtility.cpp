#include "CommonUtility.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


namespace Engine
{
	void * LoadFile( const char * i_pFilename, size_t & o_sizeFile )
	{
		assert( i_pFilename != NULL );

		FILE * pFile = NULL;

		errno_t fopenError = fopen_s( &pFile, i_pFilename, "rb" );
		if ( fopenError != 0 )
			return NULL;

		assert( pFile != NULL );

		int FileIOError = fseek( pFile, 0, SEEK_END );
		assert( FileIOError == 0 );

		long FileSize = ftell( pFile );
		assert( FileSize >= 0 );

		FileIOError = fseek( pFile, 0, SEEK_SET );
		assert( FileIOError == 0 );

		uint8_t * pBuffer = new uint8_t[FileSize];
		assert( pBuffer );

		size_t FileRead = fread( pBuffer, 1, FileSize, pFile );
		assert( FileRead == FileSize );

		fclose( pFile );

		o_sizeFile = FileSize;

		return pBuffer;
	}

	float RandomInRange( float min, float max )
	{
		// Prevent the situation while the max equals the min.
		if ( max - min == 0 )
		{
			return 0;
		}
		return min + static_cast<float>( rand() / ( static_cast<float>( RAND_MAX / ( max - min ) ) ) );
	}
}