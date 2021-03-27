#include <assert.h>
#include <iostream>
#include "Engine/Math/Matrix4x4.h"

void test() {

    // test regular ctor
    Matrix4x4 matrix1(1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
    // test equality operator
    assert(matrix1 == Matrix4x4::IDENTITY);

    // test Set()
    matrix1.Set(1.0f, 2.0f, 3.0f, 4.0f,
                1.0f, 2.0f, 3.0f, 4.0f,
                1.0f, 2.0f, 3.0f, 4.0f,
                1.0f, 2.0f, 3.0f, 4.0f);

    // determinant test 1
    float determinant1 = matrix1.GetDeterminant();
    assert(determinant1== 0.0f);

    Matrix4x4 matrix2(2.0f, 5.0f, 1.0f, 9.0f,
                      4.0f, 6.0f, 1.0f, 2.0f,
                      6.0f, 1.0f, 6.0f, 2.0f,
                      8.0f, 8.0f, 2.0f, 3.0f);

    // determinant test 2
    float determinant2 = matrix2.GetDeterminant();
    assert(determinant2== -532.0f);

    // AI = A
    Matrix4x4 matrix1TheSame(matrix1 * Matrix4x4::IDENTITY);
    assert(matrix1 == matrix1TheSame);

    // AB != BA
    Matrix4x4 matrix1_2(matrix1 * matrix2);
    Matrix4x4 matrix2_1(matrix2 * matrix1);
    assert(!(matrix1_2 == matrix2_1));

    // V = M * V
    Vector4 vec(10.f, 30.f, 20.f, 0.0f);
    Matrix4x4 matrixRotZ = Matrix4x4::GetRotationZ(3.14159265358979323846f);
    Vector4 vecRight = matrixRotZ * vec;
    // V = V * M
    Vector4 vecLeft = vec * matrixRotZ;
    assert(vecLeft == vecRight);

    Vector4 vecRotated = vec * matrixRotZ;
    Vector4 vecUnrotated = vecRotated * Matrix4x4::GetRotationZ(-3.14159265358979323846f);
    assert(vec == vecUnrotated);

    // transpose test 1
    Matrix4x4 matrix1Transpose = matrix1.GetTranspose();
    Matrix4x4 matrix1TransposeTheSame(1.0f, 1.0f, 1.0f, 1.0f,
                                      2.0f, 2.0f, 2.0f, 2.0f,
                                      3.0f, 3.0f, 3.0f, 3.0f,
                                      4.0f, 4.0f, 4.0f, 4.0f);
    assert(matrix1Transpose == matrix1TransposeTheSame);

    // (AB)' = B'A'
    Matrix4x4 matrix1_2Transpose(matrix1_2.GetTranspose());
    Matrix4x4 matrix1Transpose_2Transpose(matrix2.GetTranspose() * matrix1Transpose);
    assert(matrix1_2Transpose == matrix1Transpose_2Transpose);

    // (A')' = A
    Matrix4x4 mat_01tr_transpose(matrix1Transpose.GetTranspose());
    assert(mat_01tr_transpose == matrix1);

    Matrix4x4 mat_01_inverse = matrix1.GetInverse();
    assert(mat_01_inverse == matrix1);

    // inverse test 2
    Matrix4x4 mat_02_inverse = matrix2.GetInverse();
    Matrix4x4 check_mat_02_inverse(-0.009398f, -0.622180f, -0.054511f,  0.479323f,
                                   -0.033835f,  0.560150f,  0.003759f, -0.274436f,
                                   -0.030075f,  0.609023f,  0.225564f, -0.466165f,
                                    0.135338f, -0.240602f, -0.015038f,  0.097744f);
    assert(mat_02_inverse == check_mat_02_inverse);

    // A * A^ = I
    Matrix4x4 mat_02_mult_01 = matrix2 * mat_02_inverse;
    assert(mat_02_mult_01 == Matrix4x4::IDENTITY);

    // A^ * A = I
    Matrix4x4 mat_02_mult_02 = mat_02_inverse * matrix2;
    assert(mat_02_mult_02 == Matrix4x4::IDENTITY);

    // (A^)^ = A
    Matrix4x4 mat_02in_inverse(mat_02_inverse.GetInverse());
    assert(mat_02in_inverse == matrix2);

    Matrix4x4 matrix3(1.0f, -5.0f, 9.0f, 2.0f,
                     -3.0f, 6.0f, -4.0f, -9.0f,
                     -6.0f, -2.0f, 0.0f, 7.0f,
                     11.0f, 5.0f, 8.0f, 4.0f);

    // (AB)^ = B^A^
    Matrix4x4 matrix2_3Inverse((matrix2 * matrix3).GetInverse());
    Matrix4x4 matrix2Inverse_3Inverse(matrix3.GetInverse() * mat_02_inverse);
    assert(matrix2_3Inverse == matrix2Inverse_3Inverse);

    Matrix4x4 matrix3TransposeInverse(matrix3.GetTranspose().GetInverse());
    Matrix4x4 matrix3InverseTranspose(matrix3.GetInverse().GetTranspose());
    assert(matrix3TransposeInverse == matrix3InverseTranspose);

    const Vector4           aPoint(1.0f, 0.0f, 0.0f, 1.0f);
    const Matrix4x4           matrixRotate(Matrix4x4::GetRotationZ(3.14159265358979323846f / 2));
    const Matrix4x4           matrixTranslate(Matrix4x4::GetTranslation(Vector2(0.0f, 10.0f)));

    const Matrix4x4           matrixTransform(matrixTranslate * matrixRotate);
    const Matrix4x4           matrixTransformInverse(matrixTransform.GetInverse());

    const Vector4           rotatedPoint(matrixRotate * aPoint);
    assert(rotatedPoint == Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    const Vector4           translatedPoint(matrixTranslate * aPoint);
    assert(translatedPoint == Vector4(1.0f, 10.0f, 0.0f, 1.0f));

    const Vector4           transformedPoint(matrixTransform * aPoint);
    assert(transformedPoint == Vector4(0.0f, 11.0f, 0.0f, 1.0f));

    const Vector4           initialPoint(matrixTransformInverse * transformedPoint);
    assert(initialPoint == aPoint);

    std::cout << "all test passsed";

}

int main() {
    test();
}