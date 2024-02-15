from text_processing import *
import time


def decrypt(ciphertext, key):
    plaintext = ''
    for i in range(len(ciphertext)):
        p = ALPHABET.index(ciphertext[i])
        k = ALPHABET.index(key[i % len(key)])
        c = (p - k) % 26
        plaintext += ALPHABET[c]
    return plaintext


if __name__ == '__main__':
    # input_file_path = 'Data/setWorlds.txt'
    # output_file_path = 'Data/data.txt'
    # process_text_in_file(input_file_path, output_file_path)
    check_letters("Data/data.txt")
    with open('Data/data.txt', 'r', encoding='utf-8') as file:
        text = file.read()
    tetrafrequencies = calc_tetragraph(text)
    from random import randrange
    ciphertext = input("Input text: ")
    period = find_period(ciphertext)
    print("Period:", period)
    key = ['A'] * period
    fit = -100
    iterations = 0
    start_time = time.time()
    while fit < -10:
        K = key[:]
        x = randrange(period)
        for i in range(26):
            iterations += 1
            K[x] = ALPHABET[i]
            pt = decrypt(ciphertext, K)
            F = calc_fitness(pt, tetrafrequencies)
            print(f'{F} : {pt[:20]}')
            if F > fit:
                key = K[:]
                fit = F
    end_time = time.time()
    plaintext = decrypt(ciphertext, key)
    print("Decrypted text:", plaintext)
    print("Keyword:", key)
    print("Iterations:", iterations)
    print("Decryption time:", end_time - start_time)
