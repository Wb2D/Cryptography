#include <QtCore>

#include <QString>
#include <QVector>
#include <QTextStream>

#include "LetterIndexConverter.h"

/// USED:
/// https://www.geeksforgeeks.org/caesar-cipher-in-cryptography/
/// https://www.dcode.fr/caesar-cipher


const QVector<QPair<QString, int>> ALPHABET = {{ "а", 0 }, { "б", 1 },  { "в", 2 },  { "г", 3 },  { "д", 4 }, { "е", 5 },
                                          { "ё", 6 }, { "ж", 7 }, { "з", 8 }, { "и", 9 }, { "й", 10 }, { "к", 11 }, { "л", 12 }, {"м", 13 },
                                          { "н", 14 }, { "о", 15 }, { "п", 16 }, { "р", 17 }, { "с", 18 }, { "т", 19 }, { "у", 20 }, { "ф", 21 },
                                          { "х", 22 }, { "ц", 23 }, { "ч", 24 }, { "ш", 25 }, { "щ", 26 }, { "ъ", 27 }, { "ы", 28 }, { "ь", 29 },
                                          { "э", 30 }, { "ю", 31 }, { "я", 32 }};
 const int N = 33;


// function for encoding
QVector<int> encode(const QVector<int> &data, const uint &shift) {
    // encoded result
    QVector<int> result = {};
    for(const int &index : data) {
        result.append((index + shift) % N);
    }
    // success!
    return result;
}

// function for decoding
QVector<int> decode(const QVector<int> &data, const uint &shift) {
    // decoded result
    QVector<int> result = {};
    for(const int &index : data) {
        result.append((index - shift + N) % N);
    }
    // success!
    return result;
}


int main(int argc, char *argv[])
{
    // avoid compiler warnings
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    // input and output streams
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP866"));
    QTextStream in(stdin, QIODevice::ReadOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);
    // encoding data and shift
    QString data = {};
    uint shift = 0;
    // user actions
    const QStringList listCommands = {"encode", "decode", "exit"};
    QString userCommand = {};
    // control menu
    while(QString::compare(userCommand, "exit")) {
        // input data
        out << "Input data: " << flush;
        data = in.readLine();
        QVector<int> dataIndex = LetterIndexConverter::stringToIndices(ALPHABET, data);
        // input shift
        out << "Input shift: " << flush;
        shift = in.readLine().toUInt();
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0:
            // encoding
            out << "Success!\nEncoded data: " << LetterIndexConverter::indicesToString(ALPHABET, encode(dataIndex, shift)) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " <<  LetterIndexConverter::indicesToString(ALPHABET, decode(dataIndex, shift)) << "\n>--------------------<" << endl;
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
