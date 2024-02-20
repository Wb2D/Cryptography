#ifndef LETTERINDEXCONVERTER_H
#define LETTERINDEXCONVERTER_H

#include <QVector>
#include <QPair>
#include <QString>

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

private:
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
