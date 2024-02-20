#include <QtCore>

#include <QString>
#include <QVector>
#include <QTextStream>

#include "LetterIndexConverter.h"

/// USED:
/// https://www.geeksforgeeks.org/implementation-affine-cipher/
/// https://www.dcode.fr/affine-cipher


const QVector<QPair<QString, int>> ALPHABET = {{ "а", 0 }, { "б", 1 },  { "в", 2 },  { "г", 3 },  { "д", 4 }, { "е", 5 },
                                          { "ё", 6 }, { "ж", 7 }, { "з", 8 }, { "и", 9 }, { "й", 10 }, { "к", 11 }, { "л", 12 }, {"м", 13 },
                                          { "н", 14 }, { "о", 15 }, { "п", 16 }, { "р", 17 }, { "с", 18 }, { "т", 19 }, { "у", 20 }, { "ф", 21 },
                                          { "х", 22 }, { "ц", 23 }, { "ч", 24 }, { "ш", 25 }, { "щ", 26 }, { "ъ", 27 }, { "ы", 28 }, { "ь", 29 },
                                          { "э", 30 }, { "ю", 31 }, { "я", 32 }};
 const int N = 33;


// function search greatest common divisor
//(classic Euclidean algorithm)
uint GCD(int a, int b) {
    if(a == b) {
        return a;
    }
    if(a > b) {
        return GCD(a - b, b);
    }
    else {
        return GCD(a, b - a);
    }
}

// function to search multiplicative inverse of a
/*
 * Need to find a number a_inv such that:
 * if we find the number a_inv such that the equation
 *          a * a_inv mod26 = 1
 * is true, then a_inv is the inverse of a.
 * The easiest way to solve this equation is to search each of the numbers 1 to 25,
 * and see which one satisfies the equation
*/
uint MMI(const uint &a) {
    uint a_inv = 0;
    for(int i = 0; i < N; ++i) {
        if(((a * i) % N) == 1) {
            a_inv = i;
        }
    }
    return a_inv;
}

// function for encoding
QVector<int> encode(const QVector<int> &data, const uint &a, const uint &b) {
    // check for mutual primeness of a and b
    if(GCD(a, N) != 1) {
        std::invalid_argument("gcd(a, N) != 1");
    }
    // encoded result
    QVector<int> result = {};
    for(const int &x : data) {
        // check on letter
        result.append((a * x + b) % N);
    }
    // success!
    return result;
}

// function for decoding
QVector<int> decode(const QVector<int> &data, const uint &a, const uint &b) {
    // check for mutual primeness of a and b
    if(GCD(a, N) != 1) {
        std::invalid_argument("gcd(a, N) != 1");
    }
    // decoded result
    QVector<int> result = {};
    for(const int &x : data) {
        // multiplicative inverse of a
        uint a_inv = MMI(a);
        result.append(a_inv * (x - b + N) % N);
    }
    // success!
    return result;
}

int main(int argc, char *argv[])
{
    // avoid compiler warnings
    Q_UNUSED(argc)
    Q_UNUSED(argv);
    // input and output streams
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP866"));
    QTextStream in(stdin, QIODevice::ReadOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);
    // data to encoding or decoding and key values a and b
    QString data = {};
    uint a = 0;
    uint b = 0;
    // user actions
    const QStringList listCommands = {"encode", "decode", "exit"};
    QString userCommand = {};
    // control menu
    while(QString::compare(userCommand, "exit")) {
        // input data
        out << "Input data: " << flush;
        data = in.readLine();
        QVector<int> dataIndex = LetterIndexConverter::stringToIndices(ALPHABET, data);
        // input key value a
        out << "Input key value a: " << flush;
        a = in.readLine().toUInt();
        // input key value b
        out << "Input key value b: " << flush;
        b = in.readLine().toUInt();
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0:
            // encoding
            out << "Success!\nEncoded data: " <<  LetterIndexConverter::indicesToString(ALPHABET, encode(dataIndex, a, b)) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " <<  LetterIndexConverter::indicesToString(ALPHABET, decode(dataIndex, a, b)) << "\n>--------------------<" << endl;
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

    return 0;
}
