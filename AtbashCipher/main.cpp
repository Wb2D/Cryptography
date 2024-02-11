#include <QtCore>

#include <QString>
#include <QTextStream>

/// USED:
/// https://www.geeksforgeeks.org/implementing-atbash-cipher/
/// https://www.dcode.fr/atbash-cipher


// function shift by 25 to get the required key value
QChar reverseLetter(const QChar &ch) {
    bool flag = ch.isLower();
    return QChar((flag ? 'z' : 'Z') - ch.toLatin1() + (flag ? 'a' : 'A'));
}

// function for encoding/decoding
QString code(const QString &data) {
    // encoded/decoded result
    QString result = {};
    for(const QChar &ch : data) {
        // check on letter
        if(ch.isLetter()) {
            // putting into result
            result.append(reverseLetter(ch));
        }
        // not letter
        else {
            return QString("something went wrong");
        }
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
        // input command
        out << "Command: " << flush;
        userCommand = in.readLine();
        // selecting a use case
        switch (listCommands.indexOf(userCommand)) {
        case 0:
            // encoding
            out << "Success!\nEncoded data: " << code(data) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << code(data) << "\n>--------------------<" << endl;
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
