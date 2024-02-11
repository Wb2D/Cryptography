#include <QtCore>

#include <QString>
#include <QTextStream>

/// USED:
/// https://www.cipherchallenge.org/wp-content/uploads/2020/12/Five-ways-to-crack-a-Vigenere-cipher.pdf
/// https://pages.mtu.edu/~shene/NSF-4/Tutorial/VIG/Vig-Recover.html?source=post_page-----cee60db3a966--------------------------------





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



    return 0;
}
