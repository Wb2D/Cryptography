#include <QtCore>

#include <QString>
#include <QVector>
#include <QTextStream>

#include "LetterIndexConverter.h"

/// USED:
/// https://www.geeksforgeeks.org/vigenere-cipher/
/// https://www.dcode.fr/vigenere-cipher


const QVector<QPair<QString, int>> ALPHABET = {{ "а", 0 }, { "б", 1 },  { "в", 2 },  { "г", 3 },  { "д", 4 }, { "е", 5 },
                                          { "ё", 6 }, { "ж", 7 }, { "з", 8 }, { "и", 9 }, { "й", 10 }, { "к", 11 }, { "л", 12 }, {"м", 13 },
                                          { "н", 14 }, { "о", 15 }, { "п", 16 }, { "р", 17 }, { "с", 18 }, { "т", 19 }, { "у", 20 }, { "ф", 21 },
                                          { "х", 22 }, { "ц", 23 }, { "ч", 24 }, { "ш", 25 }, { "щ", 26 }, { "ъ", 27 }, { "ы", 28 }, { "ь", 29 },
                                          { "э", 30 }, { "ю", 31 }, { "я", 32 }};
 const int N = 33;


// function generates the key in a cyclic until key.length != data.length
QString generateKey(const QString &data, const QString &keyword) {
    if((data.isLower() && keyword.isLower()) || (data.isUpper() && keyword.isUpper())) {
        // construct and return a key
        return QString(keyword.repeated(data.length() / keyword.length()) +
                       keyword.left(data.length() % keyword.length()));
    }
    else {
        // not letter or/and different registers
        return QString("-1");
    }
}

// function for encoding
QString encode(const QString &data, const QString &keyword) {
    // encoded result
    QVector<int> result = {};
    // get key to encode
    QVector<int> keyInd = LetterIndexConverter::stringToIndices(ALPHABET, generateKey(data, keyword));
    QVector<int> dataInd = LetterIndexConverter::stringToIndices(ALPHABET, data);
    for(auto i = 0; i < dataInd.size(); ++i) {
        // E[i] = (Data[i] + Key[i]) mod 26
        result.append((dataInd[i] + keyInd[i]) % N);
    }
    // success!
    return LetterIndexConverter::indicesToString(ALPHABET, result);
}

// function for decoding
QString decode(const QString &data, const QString &keyword) {
    // decoded result
     QVector<int> result = {};
    // get key to decode
     QVector<int> keyInd = LetterIndexConverter::stringToIndices(ALPHABET, generateKey(data, keyword));
     QVector<int> dataInd = LetterIndexConverter::stringToIndices(ALPHABET, data);
    for(auto i = 0; i < dataInd.size(); ++i) {
        // Data[i] = (E[i] - Key[i]) mod 26
        result.append((dataInd[i] - keyInd[i] + N) % N);
    }
    // success!
    return LetterIndexConverter::indicesToString(ALPHABET, result);
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
    // data to encoding or decoding and key
    QString data = {};
    QString keyword = {};
    // user actions
    const QStringList listCommands = {"encode", "decode", "exit"};
    QString userCommand = {};
    // control menu
    while(QString::compare(userCommand, "exit")) {
        // input data
        out << "Input data: " << flush;
        data = in.readLine();
        // input key value a
        out << "Input keyword: " << flush;
        keyword = in.readLine();
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0:
            // encoding
            out << "Success!\nEncoded data: " << encode(data, keyword) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << decode(data, keyword) << "\n>--------------------<" << endl;
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
