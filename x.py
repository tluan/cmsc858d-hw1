import random

DNA_TYPE = 'ACGT'


def gen_random_dna(size):
    return ''.join(random.choice(DNA_TYPE) for _ in range(size))


def write_rand_dna(size):
    with open('%d.random.dna.txt' % size, 'w') as fp:
        for _ in range(size):
            rand_dna = gen_random_dna(10)
            fp.write(rand_dna)
            fp.write('\n')


write_rand_dna(1000)
write_rand_dna(10000)
write_rand_dna(100000)
write_rand_dna(1000000)
