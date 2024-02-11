#include <QtCore>

#include <QString>
#include <QTextStream>

/// USED:
/// https://www.geeksforgeeks.org/caesar-cipher-in-cryptography/
/// https://www.dcode.fr/caesar-cipher


// function for encoding
QString Encode(const QString &data, const uint &shift) {
    // encoded result
    QString result = {};
    for(const QChar &ch : data) {
        // check on letter
        if(ch.isLetter()) {
            QChar shiftedCh = ch;
            // if is lower letter
            if(ch.isLower()) {
                // convert character to numeric value and shift
                shiftedCh = QChar((ch.toLatin1() - 'a' + shift) % 26 + 'a');
            // if is upper letter
            } else if(ch.isUpper()) {
                // // convert character to numeric value and shift
                shiftedCh = QChar((ch.toLatin1() - 'A' + shift) % 26 + 'A');
            }
            // putting into result
            result.append(shiftedCh);
        }
        else {
            // not letter
            return QString("something went wrong");
        }
    }
    // success!
    return result;
}

// function for decoding
QString Decode(const QString &data, const uint &shift) {
    // decoded result
    QString result = {};
    for(const QChar &shiftedCh : data) {
        // check on letter
        if(shiftedCh.isLetter()) {
            QChar ch = shiftedCh;
            // if is lower letter
            if(shiftedCh.isLower()) {
                // convert character to numeric value and back shift
                ch = QChar((shiftedCh.toLatin1() - 'a' - shift + 26) % 26 + 'a');
            // if is upper letter
            } else if(ch.isUpper()) {
                // convert character to numeric value and back shift
                ch = QChar((shiftedCh.toLatin1() - 'A' - shift + 26) % 26 + 'A');
            }
            // putting into result
            result.append(ch);
        }
        else {
            // not letter
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
            out << "Success!\nEncoded data: " << Encode(data, shift) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << Decode(data, shift) << "\n>--------------------<" << endl;
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
