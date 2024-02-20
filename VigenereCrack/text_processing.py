import re
from math import log

ALPHABET = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'
N = 33


def process_text_in_file(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as file_in, open(output_file, 'w', encoding='utf-8') as file_out:
        for line in file_in:
            cleaned_line = ''.join(filter(lambda x: 'а' <= x.lower() <= 'я', line.lower()))
            file_out.write(cleaned_line)


def process_text(input_text):
    processed_text = ""
    for line in input_text.split('\n'):
        cleaned_line = ''.join(filter(lambda x: 'а' <= x.lower() <= 'я', line.lower()))
        processed_text += cleaned_line
    return processed_text


def check_letters(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        text = file.read()
        for char in text:
            if not ('а' <= char.lower() <= 'я'):
                print("Wrong letter: ", char)
                return
    print("True")


def calc_tetragraph(text):
    # list to store tetragraph frequencies
    tetrafrequencies = [0] * N * N * N * N
    # iterate over the text to calculate tetragraph
    for i in range(len(text) - 3):
        # calc the current index
        x = (ALPHABET.index(text[i]) * N * N * N +
             ALPHABET.index(text[i + 1]) * N * N +
             ALPHABET.index(text[i + 2]) * N +
             ALPHABET.index(text[i + 3]))
        # inc frequency count for the tetragraph
        tetrafrequencies[x] += 1
    # normalization of values, calc of their frequency
    for i in range(N * N * N * N):
        tetrafrequencies[i] /= (len(text) - 3)
    return tetrafrequencies


def calc_fitness(text, tetrafrequencies):
    result = 0
    for i in range(len(text) - 3):
        substr = text[i:i + 4]
        if all(char in ALPHABET for char in substr):
            x = (ALPHABET.index(substr[0]) * N * N * N +
                 ALPHABET.index(substr[1]) * N * N +
                 ALPHABET.index(substr[2]) * N +
                 ALPHABET.index(substr[3]))
            y = tetrafrequencies[x]
            if y == 0:
                result += -15
            else:
                result += log(y)
    result /= len(text) - 3
    return result


def index_of_coincidence(text):
    counts = [0] * N
    for char in text:
        counts[ALPHABET.index(char)] += 1
    numer = 0
    total = 0
    for i in range(N):
        numer += counts[i] * (counts[i] - 1)
        total += counts[i]
    return N * numer / (total * (total - 1))


def find_period(ciphertext):
    found = False
    period = 0
    while not found:
        period += 1
        slices = [''] * period
        for i in range(len(ciphertext)):
            slices[i % period] += ciphertext[i]
        sum_ioc = 0
        for i in range(period):
            sum_ioc += index_of_coincidence(slices[i])
        average_ioc = sum_ioc / period
        if average_ioc > 1.8:
            found = True
    return period
