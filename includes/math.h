#ifndef MATH_H
#define MATH_H

#include <vector>

template<typename T>
class Matrix {
public:
      Matrix(unsigned _rows, unsigned _cols, const T& _initial);
      Matrix(const Matrix<T>& rhs);
      virtual ~Matrix();

      // Operator overloading

      Matrix<T>& operator=(const Matrix<T>& rhs);
      Matrix<T> operator+(const Matrix<T>& rhs);
      Matrix<T>& operator+=(const Matrix<T>& rhs);
      Matrix<T> operator-(const Matrix<T>& rhs);
      Matrix<T>& operator-=(const Matrix<T>& rhs);
      Matrix<T> operator*(const Matrix<T>& rhs);
      Matrix<T>& operator*=(const Matrix<T>& rhs);

      Matrix<T> operator+(const T& rhs);
      Matrix<T> operator-(const T& rhs);
      Matrix<T> operator*(const T& rhs);
      Matrix<T> operator/(const T& rhs);

      T& operator()(const unsigned& row, const unsigned& col);
      const T& operator()(const unsigned& row, const unsigned& col) const;

      unsigned get_rows() const;
      unsigned get_cols() const;
private:
      std::vector< std::vector<T> > mat;
      unsigned rows;
      unsigned cols;
};

template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) {
      mat.resize(_rows);
      for (unsigned i = 0 ; i < mat.size() ; i++) {
            mat[i].resize(_cols, _initial);
      }
      rows = _rows;
      cols = _cols;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
      mat = rhs.mat;
      rows = rhs.get_rows();
      cols = rhs.get_cols();
}
template<typename T>
Matrix<T>::~Matrix() {}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
      if (&rhs == this)
            return *this;

      unsigned new_rows = rhs.get_rows();
      unsigned new_cols = rhs.get_cols();

      mat.resize(new_rows);
      for (unsigned i=0; i<mat.size(); i++) {
            mat[i].resize(new_cols);
      }

      for (unsigned i=0; i<new_rows; i++) {
            for (unsigned j=0; j<new_cols; j++) {
                  mat[i][j] = rhs(i, j);
            }
      }
      rows = new_rows;
      cols = new_cols;

      return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
      Matrix result(rows, cols, 0.0);

      for (unsigned i=0; i<rows; i++) {
            for (unsigned j=0; j<cols; j++) {
                  result(i,j) = this->mat[i][j] + rhs(i,j);
            }
      }

      return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
      unsigned rows = rhs.get_rows();
      unsigned cols = rhs.get_cols();

      for (unsigned i=0; i<rows; i++) {
            for (unsigned j=0; j<cols; j++) {
                  this->mat[i][j] += rhs(i,j);
            }
      }

      return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
      unsigned rows = rhs.get_rows();
      unsigned cols = rhs.get_cols();
      Matrix result(rows, cols, 0.0);

      for (unsigned i=0; i<rows; i++) {
            for (unsigned j=0; j<cols; j++) {
                  result(i,j) = this->mat[i][j] - rhs(i,j);
            }
      }

      return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
      unsigned rows = rhs.get_rows();
      unsigned cols = rhs.get_cols();

      for (unsigned i=0; i<rows; i++) {
            for (unsigned j=0; j<cols; j++) {
                  this->mat[i][j] -= rhs(i,j);
            }
      }

      return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
      unsigned rows = rhs.get_rows();
      unsigned cols = rhs.get_cols();
      Matrix result(rows, cols, 0.0);

      for (unsigned i=0; i<rows; i++) {
            for (unsigned j=0; j<cols; j++) {
                  for (unsigned k=0; k<rows; k++) {
                        result(i,j) += this->mat[i][k] * rhs(k,j);
                  }
            }
      }

      return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
      Matrix result = (*this) * rhs;
      (*this) = result;
      return *this;
}

template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
      return this->mat[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
      return this->mat[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
      return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const {
      return this->cols;
}

#endif
