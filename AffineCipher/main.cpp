#include <QtCore>

#include <QString>
#include <QTextStream>

/// USED:
/// https://www.geeksforgeeks.org/implementation-affine-cipher/
/// https://www.dcode.fr/affine-cipher


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
    for(int i = 0; i < 26; ++i) {
        if(((a * i) % 26) == 1) {
            a_inv = i;
        }
    }
    return a_inv;
}

// function for encoding
QString Encode(const QString &data, const uint &a, const uint &b) {
    // check for mutual primeness of a and b
    if(GCD(a, b) == 1) {
        // encoded result
        QString result = {};
        for(const QChar &ch : data) {
            // check on letter
            if(ch.isLetter()) {
                // what not to check twice in the code below
                bool flag = ch.isLower();
                // convert character to numeric value in range 0-25 for letters
                uint x = ch.toLatin1() - (flag ? 'a' : 'A');
                // applying affine transformation: E(x) = ax + b (mod 26)
                uint y = (a * x + b) % 26;
                // putting into result
                result.append(QChar(y + (flag ? 'a' : 'A')));
            }
            // not letter
            else {
                break;
            }
        }
        // success!
        return result;
    }
    // a and b not mutual primeness
    return QString("something went wrong");
}

// function for decoding
QString Decode(const QString &data, const uint &a, const uint &b) {
    // check for mutual primeness of a and b
    if(GCD(a, b) == 1) {
        // decoded result
        QString result = {};
        for(const QChar &ch : data) {
            // check on letter
            if(ch.isLetter()) {
                // what not to check twice in the code below
                bool flag = ch.isLower();
                // convert character to numeric value in range 0-25 for letters
                uint x = ch.toLatin1() - (flag ? 'a' : 'A');
                // multiplicative inverse of a
                uint a_inv = MMI(a);
                // applying decryption formula: D(x) = a_inv (x - b) (mod 26)
                uint y = a_inv * (x - b + 26) % 26;
                // putting into result
                result.append(QChar(y + (flag ? 'a' : 'A')));
            }
            // not letter
            else {
                break;
            }
        }
        // success!
        return result;
    }
    // a and b not mutual primeness
    return QString("something went wrong");
}

int main(int argc, char *argv[])
{
    // avoid compiler warnings
    Q_UNUSED(argc)
    Q_UNUSED(argv);
    // input and output streams
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
            out << "Success!\nEncoded data: " << Encode(data, a, b) << "\n>--------------------<" << endl;
            break;
        case 1:
            // decoding
            out << "Success!\nDecoded data: " << Decode(data, a, b) << "\n>--------------------<" << endl;
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
