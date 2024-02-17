#include <QtCore>
#include <QString>

#include "matrix.h"

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
        out << "Input size matrix key (NxN):  = " << flush;
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
        case 0:
            // encoding

            out << "Success!\nEncoded data: " << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << "\n>--------------------<" << endl;
            break;
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

    /*
    Matrix matrix(3, 3);
    matrix.fillAuto(0, 26);

    out << matrix.toString() << flush;
    out << QString::number(matrix.determinant()) << flush;
    */
    return 0;
}
