// MatrixUnitTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "assert.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "stdio.h"

int main()
{
	{
		using namespace Engine;

		// Write some simple test instances to test them out.
		// For 'Vector3' and 'Vector4'
		Vector3 vec3_1 = Vector3( 2, 3, 4 );
		vec3_1.Printout();
		Vector4 vec4_1 = Vector4( vec3_1, 1.0f );
		vec4_1.Printout();

		// For Matrix
		// Test for the rotation matrix
		Matrix4x4 rotateMatrix = Matrix4x4::CreateRotationZ( -90 );
		printf( "The rotation matrix: \n" );
		rotateMatrix.PrintOut();
		printf( "The scale matrix: \n" );
		Matrix4x4 scaleMatrix = Matrix4x4::CreateScale( 2, 5, 9 );
		scaleMatrix.PrintOut();
		printf( "The translate matrix: \n" );
		Matrix4x4 translateMatrix = Matrix4x4::CreateTranslation( 2, 4, 5 );
		translateMatrix.PrintOut();

		Matrix4x4 invertMatrix;
		if ( scaleMatrix.Invert( invertMatrix ) )
		{
			printf( "The inversion for scale matrix: \n" );
			invertMatrix.PrintOut();
			Vector4 vec4_afterScaled = invertMatrix * vec4_1;
			vec4_afterScaled.Printout();
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
