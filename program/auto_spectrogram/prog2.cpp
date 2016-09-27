#include <cstring>
#include <fstream>	//	Write to file
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>	//sort

/**
 *	The first line piped into the problem should be the file name.
 * 	Then all the information until the "end of file" should be
 * 	the raw spectrogram data, which is in 4bit float.
 *
 * 	The first output should be the file name.
 * 	Then the output should be the position of the spikes
 * 	in ms.
 * 	The last output should be an "end of file".
 */


int main( int argc, char **argv ){
	bool DEBUG = false;
	int height = 513; //	The height of the spectrogram
	
	if( DEBUG ){ std::cout << "Starting prog2"; }

	while(true)
	{
		for( std::string filename; std::getline(std::cin, filename); ){
			FILE * pFile;
			long lSize;
			float * buffer;
			size_t result;

			if( DEBUG ){ std::cout << " Read from stdin: "<< filename << std::endl; }

			//	Open the data file
			pFile = fopen ( filename.c_str(), "rb" );
			if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

			//	Get file size
			fseek( pFile, 0, SEEK_END );
			lSize = ftell( pFile );
			rewind( pFile );

			if( DEBUG ){
				std::cout << lSize << " mod "<< height << " = " << lSize%height << std::endl;
				std::cout << lSize << " / "  << height << " = " << lSize/height << std::endl;
			}

			//	Allocate memory to contain the whole file:
			//buffer = (float*) malloc( sizeof(float)*lSize );
			buffer = (float*) malloc( lSize );
			if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

			//	Copy file content into the buffer
			result = fread( buffer, 1, lSize, pFile );
			if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

			//	Close file
			fclose( pFile );
			//free( buffer );

			//	Insert the data from the buffer, into the array.
			int width = (lSize/height)/sizeof(float);
			float arr[width];
		
			for( int i=0; i<width; i++ )
			{
				for( int j=0; j<height; j++ )
				{
					arr[i] += buffer[i*513+j];
				}
				if( DEBUG ){ std::cout << i << " " << arr[i] << std::endl; }
			}

			//	Write the content of the array, into a file
			if( DEBUG ){
				std::ofstream mFile( "output", std::ios::out | std::ofstream::binary );
				if( mFile.is_open() )
				{
					//for( int i=0; i<width/4;i++ )
					for( int i=0; i<width;i++ )
					{
						mFile << arr[i] << std::endl;
					}
					mFile.close();
				}
				else std::cout << "Unable to open the output file";
			}
			//	Error right now is that the array is 4 times too large. it is 4264, but should be 1066.
			//	Somewhere we need to divide by the size of a float.
			//	This error might have been resolved.

			/*
			 * 	Now with the file done (also having the data in a array),
			 *	we look through it to find the threshold. then we will
			 *	continiue to look forward, until the energy level is low.
			 */

			int count = 0;
			std::vector<float> spike;

			/**
			*	To find the treshold we use the following:
			*/
			if( true ){
				std::sort( arr, arr+width );
				for( int i = 0; i< width; i++ ){
					std::cout << arr[i] << std::endl;
				}
			}

			int tresUpper = -24000;
			int tresLower = -50000;

			/**
			 *	Start the output sequence.
			 *	Filename
			 *	Spikes
			 *	EOF
			 */

			std::cout << filename << std::endl;

			for( int i = 0; i < width; i++ ){
				if( arr[i] < tresUpper && arr[i] > tresLower ){
					if( arr[i-1] < tresLower ){
						spike.push_back(arr[i]);
						count++;
						std::cout << i << std::endl;
					}
				}
				if( i > 10 && false ){break;}
			}

			std::cout << "done" << std::endl;
			if( DEBUG ){ std::cout << "DONE - " << count << std::endl; }
		}
	}

	return 0;
}
