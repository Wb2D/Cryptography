#include <QtCore>
#include <QString>

#include "matrix.h"

/// I'm tired of leaving comments ...
///
/// USED:
/// https://habr.com/ru/articles/332714/

// Extended Euclidean algorithm also finds integer coefficients x and y such that: ax + by = gcd(a, b)
int gcdExtended(int a, int b, int &x, int &y) {
    if(a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

Matrix Encode(const Matrix &data, const Matrix &key) {
    Matrix result(data.getRows(), data.getColumns());
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << "D = " << QString::number(key.determinant()) << endl;
    // split data and multiply each fragment by the key matrix : E = C * K
    for(int i = 0; i < data.getRows(); ++i) {
        result.replace("row", data.cut("row", i) * key, i);
    }
    // alphabet: English + _
    return result % 27;
}

Matrix Decode(const Matrix &data, const Matrix &key) {
    int det = key.determinant(), x, y;
    QTextStream out(stdout, QIODevice::WriteOnly);
    out << "D = " << QString::number(det) << endl;
    int gcd = gcdExtended(27, det, x, y);
    if(gcd != 1) {
        out << "\nGCD(dit, 27) != 1 => Dinv not exist\n" << flush;
    }
    int invDet = 0;
    // обратный детерминанту элемент в кольце по модулю [мощности алфавита], в моем случа 27
    if(det < 0 && y > 0) {
        invDet = y;
    } else if(det > 0 && y < 0) {
        invDet = 27 + y;
    } else if(det > 0 && y > 0) {
        invDet = y;
    } else if(det < 0 && y < 0) {
        invDet = -y;
    }
    Matrix inverseKey = (key.getAdjMatrix() % 27 * invDet % 27).transpose();

    for(int i = 0; i < inverseKey.getRows(); ++i) {
        for(int j = 0; j < inverseKey.getColumns(); ++j) {
            if(inverseKey(i, j) < 0) {
                inverseKey(i, j) += 27;
            }
        }
    }
    out << "Inv key matrix:\n" << (inverseKey).toString("-f") << flush;
    out << "Key * Inv_key:\n" << ((key * inverseKey) % 27).toString("-f") << flush;
    Matrix result(data.getRows(), data.getColumns());
    // split data and multiply each fragment by the key matrix : D = E * K
    for(int i = 0; i < data.getRows(); ++i) {
        result.replace("row", data.cut("row", i) * inverseKey, i);
    }
    // alphabet: English + _
    return result % 27;
}

int main(int argc, char *argv[])
{
    // avoid compiler warnings
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    // input and output streams
    QTextStream in(stdin, QIODevice::ReadOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);
    // encoding data and key
    QString data = {};
    QString key = {};
    int matrixValue = 0;
    // user actions
    const QStringList listCommands = {"encode", "decode", "exit"};
    QString userCommand = {};
    // control menu
    while(QString::compare(userCommand, "exit")) {
       // input matrix size
        out << "Input size matrix key (NxN): " << flush;
        matrixValue = in.readLine().toInt();
        // input key
        out << "Input key: " << flush;
        key = in.readLine();
        if(key.length() != 4 && key.length() != 9) {
            out << "Key matrix must be square" << endl;
            break;
        }
        Matrix keyMatrix(key, matrixValue);
        // input data
        out << "Input data: " << flush;
        data = in.readLine();
        Matrix dataMatrix(data, matrixValue);
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0: {
            // encoding
            out << "Key matrix:\n" << keyMatrix.toString("-f") << flush;
            out << "Data matrix:\n" << dataMatrix.toString("-r") << flush;
            Matrix resultMatrix = Encode(dataMatrix, keyMatrix);
            out << "Encoded matrix:\n" << resultMatrix.toString("-r") << flush;
            out << "Success!\nEncoded data: " << resultMatrix.toLetters(true) << "\n>--------------------<" << endl;
            break;
        }
        case 1: {
            // decoding
            out << "Key matrix:\n" << keyMatrix.toString("-f") << flush;
            out << "Data matrix:\n" << dataMatrix.toString("-r") << flush;
            Matrix resultMatrix = Decode(dataMatrix, keyMatrix);
            out << "Decoded matrix:\n" << resultMatrix.toString("-r") << flush;
            out << "Success!\nDecoded data: " << resultMatrix.toLetters(true) << "\n>--------------------<" << endl;
            break;
        }
        case 2:
            // exit
            out << "Exiting..." << endl;
            break;
        default:
            // error in command
            out << "Invalid command\nPlease enter 1, 2, or 3\n>--------------------<" << endl;
            break;
        }
    }
    // end of program
    out << "Program ended.\n" << endl;
    return 0;
}
