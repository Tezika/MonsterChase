#pragma once
namespace Engine
{
	struct Vector3;
	struct Vector4;

	struct Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44
		);
		~Matrix4x4();

		void operator*=( const Matrix4x4 & i_other );
		Matrix4x4  operator*( const Matrix4x4 & i_other );

		static Matrix4x4 Transpose( Matrix4x4 & i_other );
		static Matrix4x4 Invert( const Matrix4x4 & i_other );

	private:
		float m_matrix[4][4];
	};
};