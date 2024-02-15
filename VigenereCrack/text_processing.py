import re
from math import log

ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def process_text_in_file(input_file, output_file):
    # open files for reading and writing
    with open(input_file, 'r', encoding='utf-8') as file_in, open(output_file, 'w', encoding='utf-8') as file_out:
        # rad text from the input file line by line and write the processed text to the output file
        for line in file_in:
            # remove all characters except letters
            cleaned_line = ''.join(filter(str.isalpha, line))
            # convert all words to uppercase and write them to the file
            file_out.write(cleaned_line.upper())


def process_text(input_text):
    processed_text = ""
    for line in input_text.split('\n'):
        cleaned_line = ''.join(filter(str.isalpha, line))
        cleaned_line = cleaned_line.upper()
        processed_text += cleaned_line
    return processed_text


def check_letters(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        # read the text from the file
        text = file.read()
        # iterate through each character in the text
        for char in text:
            # check if the character is within the ASCII range for A-Z or a-z
            if not (65 <= ord(char) <= 90 or 97 <= ord(char) <= 122):
                # If the character is not a letter, print it and exit the method
                print("Wrong letter:", char)
                return
    # if no non-alphabetic characters are found, print a message
    print("True")


def calc_tetragraph(text):
    # list to store tetragraph frequencies
    tetrafrequencies = [0] * 26 * 26 * 26 * 26
    # iterate over the text to calculate tetragraph
    for i in range(len(text) - 3):
        # calc the current index
        x = (ALPHABET.index(text[i]) * 26 * 26 * 26 +
             ALPHABET.index(text[i + 1]) * 26 * 26 +
             ALPHABET.index(text[i + 2]) * 26 +
             ALPHABET.index(text[i + 3]))
        # inc frequency count for the tetragraph
        tetrafrequencies[x] += 1
    # normalization of values, calc of their frequency
    for i in range(26 * 26 * 26 * 26):
        tetrafrequencies[i] /= (len(text) - 3)
    return tetrafrequencies


def calc_fitness(text, tetrafrequencies):
    result = 0
    for i in range(len(text) - 3):
        substr = text[i:i + 4]
        if all(char in ALPHABET for char in substr):
            x = (ALPHABET.index(substr[0]) * 26 * 26 * 26 +
                 ALPHABET.index(substr[1]) * 26 * 26 +
                 ALPHABET.index(substr[2]) * 26 +
                 ALPHABET.index(substr[3]))
            y = tetrafrequencies[x]
            if y == 0:
                result += -15
            else:
                result += log(y)
    result /= len(text) - 3
    return result


def index_of_coincidence(text):
    counts = [0] * 26
    for char in text:
        counts[ALPHABET.index(char)] += 1
    numer = 0
    total = 0
    for i in range(26):
        numer += counts[i] * (counts[i] - 1)
        total += counts[i]
    return 26 * numer / (total * (total - 1))


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
        if average_ioc > 1.6:
            found = True
    return period
