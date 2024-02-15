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

    Matrix matrix(3, 3);
    matrix.fillAuto(0, 26);

    out << matrix.toString() << flush;
    out << QString::number(matrix.determinant()) << flush;

    return 0;
}
