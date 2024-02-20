#include <QtCore>

#include <QString>
#include <QTextStream>
#include <QPair>

#include "LetterIndexConverter.h"

/// USED:
/// https://www.geeksforgeeks.org/implementing-atbash-cipher/
/// https://www.dcode.fr/atbash-cipher


const QVector<QPair<QString, int>> ALPHABET = {{ "а", 0 }, { "б", 1 },  { "в", 2 },  { "г", 3 },  { "д", 4 }, { "е", 5 },
                                          { "ё", 6 }, { "ж", 7 }, { "з", 8 }, { "и", 9 }, { "й", 10 }, { "к", 11 }, { "л", 12 }, {"м", 13 },
                                          { "н", 14 }, { "о", 15 }, { "п", 16 }, { "р", 17 }, { "с", 18 }, { "т", 19 }, { "у", 20 }, { "ф", 21 },
                                          { "х", 22 }, { "ц", 23 }, { "ч", 24 }, { "ш", 25 }, { "щ", 26 }, { "ъ", 27 }, { "ы", 28 }, { "ь", 29 },
                                          { "э", 30 }, { "ю", 31 }, { "я", 32 }};
 const int N = 33;


// function reverse
int reverse(const int &index) {
    return N - index - 1;
}

// function for encoding/decoding
QVector<int> code(const QVector<int> &data) {
    // encoded/decoded result
    QVector<int> result = {};
    for(const int &index : data) {
        result.push_back(reverse(index));
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
    // data to encoding or decoding
    QString data = {};
    // user actions
    const QStringList listCommands = {"encode", "decode", "exit"};
    QString userCommand = {};
    // control menu
    while(QString::compare(userCommand, "exit")) {
        // input data
        out << "Input data: " << flush;
        data = in.readLine();
        QVector<int> dataIndex = LetterIndexConverter::stringToIndices(ALPHABET, data);
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0:
            // encoding
            out << "Success!\nEncoded data: " << LetterIndexConverter::indicesToString(ALPHABET, code(dataIndex)) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << LetterIndexConverter::indicesToString(ALPHABET, code(dataIndex)) << "\n>--------------------<" << endl;
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
