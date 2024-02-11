#include <QtCore>

#include <QString>
#include <QTextStream>

/// USED:
/// https://www.geeksforgeeks.org/vigenere-cipher/
/// https://www.dcode.fr/vigenere-cipher


// function generates the key in a cyclic until key.length != data.length
QString generateKey(const QString &data, const QString &keyword) {
    if((data.isLower() && keyword.isLower()) || (data.isUpper() && keyword.isUpper())) {
        // construct and return a key
        return QString(keyword.repeated(data.length() / keyword.length()) +
                       data.left(data.length() % keyword.length()));
    }
    else {
        // not letter or/and different registers
        return QString("-1");
    }
}

// function for encoding
QString Encode(const QString &data, const QString &keyword) {
    // encoded result
    QString result = {};
    // get key to encode
    QString key = generateKey(data, keyword);
    // check on lower or upper text
    bool flag = data.isLower();
    if(!QString::compare(key, QString("-1"))) {
        // register dont matching in input data and keyword
        return QString("something went wrong");
    }
    for(auto i = 0; i < data.length(); ++i) {
        // E[i] = (Data[i] + Key[i]) mod 26
        uint x = (data.at(i).toLatin1() + key.at(i).toLatin1() - 2 * (flag ? 'a' : 'A')) % 26;
        // putting into result
        result.append(QChar(x + (flag ? 'a' : 'A')));
    }
    // success!
    return result;
}

// function for decoding
QString Decode(const QString &data, const QString &keyword) {
    // decoded result
    QString result = {};
    // get key to decode
    QString key = generateKey(data, keyword);
    // check on lower or upper text
    bool flag = data.isLower();
    if(!QString::compare(key, QString("-1"))) {
        // register dont matching in input data and keyword
        return QString("something went wrong");
    }
    for(auto i = 0; i < data.length(); ++i) {
        // Data[i] = (E[i] - Key[i]) mod 26
        uint x = (data.at(i).toLatin1() - key.at(i).toLatin1() + 26) % 26;
        // putting into result
        result.append(QChar(x + (flag ? 'a' : 'A')));
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
            out << "Success!\nEncoded data: " << Encode(data, keyword) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << Decode(data, keyword) << "\n>--------------------<" << endl;
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
