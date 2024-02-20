#ifndef LETTERINDEXCONVERTER_H
#define LETTERINDEXCONVERTER_H

#include <QVector>
#include <QPair>
#include <QString>

const QVector<QPair<QString, int>> ALPHABET = {{ "а", 0 }, { "б", 1 },  { "в", 2 },  { "г", 3 },  { "д", 4 }, { "е", 5 },
                                          { "ё", 6 }, { "ж", 7 }, { "з", 8 }, { "и", 9 }, { "й", 10 }, { "к", 11 }, { "л", 12 }, {"м", 13 },
                                          { "н", 14 }, { "о", 15 }, { "п", 16 }, { "р", 17 }, { "с", 18 }, { "т", 19 }, { "у", 20 }, { "ф", 21 },
                                          { "х", 22 }, { "ц", 23 }, { "ч", 24 }, { "ш", 25 }, { "щ", 26 }, { "ъ", 27 }, { "ы", 28 }, { "ь", 29 },
                                               { "э", 30 }, { "ю", 31 }, { "я", 32 }, {"_", 33}};
 const int N = 34;

class LetterIndexConverter {
public:
    static QVector<int> stringToIndices(const QVector<QPair<QString, int>>& alphabet, const QString& text) {
        QVector<int> indices;
        for (const QChar &letter : text) {
            int index = indexOfLetter(alphabet, letter);
            if(index != - 1) {
                indices.append(index);
            } else {
                std::invalid_argument("wrong letter : stringToIndices(QVector<QPair<QString, int>>, QString)");
            }
        }
        return indices;
    }

    static QString indicesToString(const QVector<QPair<QString, int>>& alphabet, const QVector<int>& indices) {
        QString result;
        for (int index : indices) {
            QString letter = indexToLetter(alphabet, index);
            if(QString::compare(letter, QString())) {
                result +=letter;
            } else {
                std::invalid_argument("wrong index : indicesToString(QVector<QPair<QString, int>>, const QVector<int>)");
                break;
            }
        }
        return result;
    }

    static int indexOfLetter(const QVector<QPair<QString, int>> &alphabet, const QChar &letter) {
        QString strLetter = QString(letter);
        for (const QPair<QString, int> &pair : alphabet) {
            if (strLetter == pair.first) {
                return pair.second;
            }
        }
        return -1; // -1 if letter not found in alphabet
    }

    static QString indexToLetter(const QVector<QPair<QString, int>>& alphabet, int index) {
        for (const QPair<QString, int>& pair : alphabet) {
            if (index == pair.second) {
                return pair.first;
            }
        }
        return QString(); //  empty string if index not found in alphabet
    }
};

#endif // LETTERINDEXCONVERTER_H
