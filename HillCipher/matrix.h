#ifndef MATRIX_H
#define MATRIX_H

#include <QException>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <random>
#include <QtMath>

#include "LetterIndexConverter.h"



class Matrix
{
public:
    // make empty vector size rows x columns
    Matrix(const int &rows, const int &columns) : _rows(rows), _columns(columns) {
        if(rows <= 0 || columns <= 0) {
            throw std::invalid_argument("Matrix size is wrong : Matrix(int, int)");
        }
        _data.resize(rows * columns);
    }

    Matrix(const QString &data, const int &col) :  _columns(col) {
        if(col <= 0 || col > 3) {
            throw std::invalid_argument("Matrix size is wrong : Matrix(QString, int)");
        }
        bool flagSize = data.length() % col == 0 ? true : false;
        for(const QChar &ch : data) {
            int index = LetterIndexConverter::indexOfLetter(ALPHABET, ch);
            if(index != QString("-1")) {
                _data.push_back(index);
            } else {
                std::invalid_argument("Letter is wrong : Matrix(QString, int)");
            }
        }
        _rows = flagSize ? data.length() / col : data.length() / col + 1;
        if(!flagSize) {
            int j = 0;
            while(j < col -data.length() % col) {
                _data.push_back(33);
                ++j;
            }
        }
    }

    Matrix(const QVector<int> data, const int &rows, const int &columns) : _rows(rows), _columns(columns) {
        if(data.size() != rows * columns) {
            throw std::invalid_argument("Size of data not consistent with size matrix : Matrix(QVector, int, int)");
        }
        this->_data = data;
    }

    int &operator()( int row,  int column) {
        if (row < 0 || row >= _rows || column < 0 || column >= _columns) {
            throw std::out_of_range("Index is out of range : operator()(int, int)");
        }
        return _data[row * this->_columns + column];
    }

    const   int &operator()(const int &row, const int &column) const {
        if (row < 0 || row >= _rows || column < 0 || column >= _columns) {
            throw std::out_of_range("Index is out of range : operator()(int, int) const");
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
            throw std::invalid_argument("Wrong matrix size for multiplication : operator*(Matrix)");
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

    Matrix operator*(const int &num) const {
        Matrix result(this->_rows, this->_columns);
        int i = 0;
        while(i != this->_data.size()) {
            result._data[i] = this->_data[i] * num;
            ++i;
        }
        return result;
    }

    Matrix operator%(const int& num) const {
        Matrix result(this->_rows, this->_columns);
        int i = 0;
        while(i != this->_data.size()) {
            result._data[i] = this->_data[i] % num;
            ++i;
        }
        return result;
    }

    Matrix cut(const QString &objKey, const int &num) const {
        const QStringList listObjects = {"row", "column"};
        switch(listObjects.indexOf(objKey)) {
        case 0: {
            Matrix result(1, this->_columns);
            for(int i = 0; i < this->_columns; ++i) {
                result(0, i) = (*this)(num, i);
            }
            return result;
            break;
        }
        case 1: {
            Matrix result(this->_rows, 1);
            for(int i = 0; i < this->_rows; ++i) {
                result(i, 0) = (*this)(i, num);
            }
            return result;
            break;
        }
        default:
            throw std::invalid_argument("Wrong object key : cut(QString, int)");
            break;
        }
    }

    void replace(const QString &objKey, const Matrix &data, const int &num) {
        const QStringList listObjects = {"row", "column"};
        switch(listObjects.indexOf(objKey)) {
        case 0: {
            if(this->_columns != data._columns) {
                throw std::invalid_argument("Columns in the matrices is unequal : replace(QString, Matrix, int)");
            }
            if(data._rows != 1) {
                throw std::invalid_argument("Replacement row > 1 : replace(QString, Matrix, int)");
            }
            for(int i = 0; i < this->_columns; ++i) {
                (*this)(num, i) = data(0, i);
            }
            break;
        }
        case 1: {
            if(this->_rows != data._rows) {
                throw std::invalid_argument("Rows in the matrices is unequal : replace(QString, Matrix, int)");
            }
            if(data._columns != 1) {
                throw std::invalid_argument("Replacement column > 1 : replace(QString, Matrix, int)");
            }
            for(int i = 0; i < this->_rows; ++i) {
                (*this)(i, num) = data(i, 0);
            }
            break;
        }
        default:
            throw std::invalid_argument("Wrong object key : replace(QString, Matrix, int)");
            break;
        }
    }

    Matrix transpose() const {
        if(this->_rows != this->_columns) {
            std::invalid_argument("Matrix not square : transpose()");
        }
        int size = this->_rows;
        Matrix result(size, size);
        if(size == 1) {
            result = *this;
        } else {
            for(int i = 0; i < size; ++i) {
                for(int j = 0; j < size; ++j) {
                    result(i, j) = (*this)(j, i);
                }
            }
        }
        return result;
    }

    int determinant() const {
        if(this->_rows != this->_columns) {
            std::invalid_argument("Matrix not square : determinant()");
        }
        int result = 0;
        if(this->_rows == 1) {
            result = _data[0];
        } else if(this->_rows == 2) {
            result = _data[0] * _data[3] - _data[1] * _data[2];
        } else if(this->_rows == 3)  {
            result = _data[0] * _data[4] * _data[8] +
                    _data[1] *_data[5] * _data[6] +
                    _data[2] * _data[3] * _data[7] -
                    _data[2] * _data[4] * _data[6] -
                    _data[1] * _data[3] * _data[8] -
                    _data[0] * _data[5] * _data[7];
        } else {
            std::invalid_argument("Matrix size > 3 : determinant()");
        }
        return result;
    }

    int minor(const int &row, const int &column) const {
        if(this->_rows != this->_columns) {
            std::invalid_argument("Matrix must be square : minor(int, int)");
        }
        int size = this->_rows;
        if(size < 2 || size > 3) {
            std::invalid_argument("Unsupported matrix size : minor(int, int)");
        }
        QVector<int> data = {};
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if(i != row && j != column) {
                    data.push_back((*this)(i, j));
                }
            }
        }
        return Matrix(data, size - 1, size - 1).determinant();
    }

    int adj(const int &row, const int &column) const {
        int result = this->minor(row, column);
        return (row + column) % 2 == 0 ? result : -result;
    }

    Matrix getAdjMatrix() const {
        Matrix result(this->_rows, this->_columns);
        for(int i = 0; i < this->_rows; ++i) {
            for(int j = 0; j < this->_columns; ++j) {
                result(i, j) = this->adj(i, j);
            }
        }
        return result;
    }

    QString toString(const QString &flag) const {
        const QStringList listObjects = {"-f", "-r", "-c"};
        QString result = {};
        switch(listObjects.indexOf(flag)) {
        case 0: {
            result += this->makeTable();
            break;
        }
        case 1: {
            for(int i = 0; i < this->_rows; ++i) {
                result += this->cut("row", i).makeTable();
            }
            break;
        }
        default: {
            throw std::invalid_argument("Wrong object key : replace(QString, Matrix, int)");
            break;
        }
        }
        return result;
    }


    QString toLetters(const bool &flag) const {
        return LetterIndexConverter::indicesToString(ALPHABET, this->_data);
    }

private:
    QString makeTable() const {
        QString result = QString::number(this->_rows) + " x " + QString::number(this->_columns) + "\n";
        // Create the horizontal line
        QString horizontalLine = "+";
        for(int j = 0; j < this->_columns; ++j) {
            horizontalLine += "------+";
        }
        horizontalLine += "\n";
        result += horizontalLine;
        for(int i = 0; i < this->_rows; ++i) {
            result += "|";
            for(int j = 0; j < this->_columns; ++j) {
                result += QString(" %1 |").arg((*this)(i, j), 4);
            }
            result += "\n" + horizontalLine;
        }
        return result;
    }

    int _rows;
    int _columns;
    QVector<int> _data;
};

#endif // MATRIX_H
