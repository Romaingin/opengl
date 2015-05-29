#include "../includes/math.h"
#include <math.h>

Matrix<float> IdentityMatrix(int n)
{
      Matrix<float> result(n, n, 0.0f);

      for (int i = 0; i < n; i++)
            result(i,i) = 1.0f;

      return result;
}

Matrix<float> RotationMatrix(float angle, float x, float y, float z)
{
      Matrix<float> result(4, 4, 0.0f);

      // Normalize; x, y and z must be smaller than 1
      /*
      if (abs(x) > 1 || abs(y) > 1 || abs(z) > 1)
      {
        // My own implementation of max which allows 3 parameters
        float M = Math::Max(abs(x), abs(y), abs(z));
        x /= M; y /= M; z /= M;
      }*/

      float s = sin(angle);
      float c = cos(angle);

      result(0,0) = x * x * (1 - c) + c;
      result(0,1) = x * y * (1 - c) - z * s;
      result(0,2) = x * z * (1 - c) + y * s;
      result(1,0) = y * x * (1 - c) + z * s;
      result(1,1) = y * y * (1 - c) + c;
      result(1,2) = y * z * (1 - c) - x * s;
      result(2,1) = y * z * (1 - c) + x * s;
      result(2,0) = x * z * (1 - c) - y * s;
      result(2,2) = z * z * (1 - c) + c;
      result(3,3) = 1.0f;

      return result;
}

Matrix<float> TranslationMatrix(float x, float y, float z)
{
    Matrix<float> result = IdentityMatrix(4);

    result(0,3) = x;
    result(1,3) = y;
    result(2,3) = z;

    return result;
}
