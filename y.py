import random


with open('build_in.txt', 'r') as fp:
    BUILD_IN_DNA = fp.read().strip()
    BUILD_IN_DNA_SIZE = len(BUILD_IN_DNA)


def gen_random_dna(size):
    start_idx = random.randint(0, BUILD_IN_DNA_SIZE - size)
    return BUILD_IN_DNA[start_idx:start_idx + size]


def write_rand_dna(size):
    with open('%d.substr.dna.txt' % size, 'w') as fp:
        for _ in range(size):
            rand_dna = gen_random_dna(10)
            fp.write(rand_dna)
            fp.write('\n')


write_rand_dna(1000)
write_rand_dna(10000)
write_rand_dna(100000)
write_rand_dna(1000000)
