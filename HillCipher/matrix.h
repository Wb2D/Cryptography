#ifndef MATRIX_H
#define MATRIX_H

#include <QException>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <random>

class Matrix
{
public:
    Matrix(const int &rows, const int &columns) : _rows(rows), _columns(columns) {
        if(rows <= 0 || columns <= 0) {
            throw std::invalid_argument("Matrix size is wrong : Matrix()") ;
        }
        _data.resize(rows * columns);
    }

    int &operator()( int &row, const int &column) {
        if (row < 0 || row >= _rows || column < 0 || column >= _columns) {
            throw std::out_of_range("Index is out of range : operator()");
        }
        return _data[row * column + column];
    }

    const   int &operator()(const int &row, const int &column) const {
        if (row < 0 || row >= _rows || column < 0 || column >= _columns) {
            throw std::out_of_range("Index is out of range : operator()");
        }
        return _data[row * this->_columns + column];
    }

    int getRows() const { return _rows; }
    int getColumns() const { return  _columns; }

    void fill() {
        // input and output streams
        QTextStream in(stdin, QIODevice::ReadOnly);
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << "Filling out the matrix manually...\n" << flush;
        for(int i = 0; i < this->_rows; ++i) {
            for(int j = 0; j < this->_columns; ++j) {
                out << "a" + QString::number(i) + QString::number(j) + " = " << flush;
                (*this)(i, j) = in.readLine().toInt();
            }
        }
    }

    void fillAuto(const int &left, const int &right) {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dis(left, right);
        // input and output streams
        QTextStream in(stdin, QIODevice::ReadOnly);
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << "Auto matrix filling...\n" << flush;
        for(int i = 0; i < this->_rows; ++i) {
            for(int j = 0; j < this->_columns; ++j) {
                 (*this)(i, j) = dis(gen);
            }
        }
    }

    Matrix operator*(const Matrix &matrix2) const {
        if (this->_columns != matrix2._rows) {
            throw std::invalid_argument("Wrong matrix size for multiplication : operator*");
        }
        Matrix result(this->_rows, matrix2._columns);
        for (int i = 0; i < this->_rows; ++i) {
            for (int j = 0; j < matrix2._columns; ++j) {
                int sum = 0;
                for (int k = 0; k < this->_columns; ++k) {
                    sum += (*this)(i, k) * matrix2(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }


    int determinant() const {
        if(this->_rows != this->_columns) {
            std::invalid_argument("Matrix not square : determinant");
        }
        if(this->_rows == 1) {
            return _data[0];
        } else if(this->_rows == 2) {
            return _data[0] * _data[3] - _data[1] * _data[2];
        } else if(this->_rows == 3)  {
            return _data[0] * _data[4] * _data[8] +
                    _data[1] *_data[5] * _data[6] +
                    _data[2] * _data[3] * _data[7] -
                    _data[2] * _data[4] * _data[6] -
                    _data[1] * _data[3] * _data[8] -
                    _data[0] * _data[5] * _data[7];
        } else {
            std::invalid_argument("Matrix size > 3 : determinant");
        }
    }

    Matrix inverse(const Matrix &matrix) const {
        if(matrix.getRows() != matrix.getColumns()) {
            std::invalid_argument("Matrix not square : inverse");
        }
        int det = this->determinant();
        if(det == 0) {
            std::invalid_argument("det Matrix = 0 : inverse");
        }
        Matrix result(matrix.getRows(), matrix.getColumns());
        for(int i = 0; i < matrix.getRows(); ++i) {
            for(int j = 0; j < matrix.getColumns(); ++j) {
                result(i, j) = matrix(j, i) / det;
            }
        }
        return result;
    }

    QString  toString() const {
        QString result = {};
        for(int i = 0; i < this->_rows; ++i) {
            for(int j = 0; j < this->_columns; ++j) {
                result += QString::number((*this)(i, j) )+ " ";
            }
            result += "\n";
        }
        return result;
    }

private:
    int _rows;
    int _columns;
    QVector<int> _data;
};

#endif // MATRIX_H
