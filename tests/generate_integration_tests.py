import sys
from random import randint


def print_help():
    print(f"Usage: {sys.argv[0]} <number of tests> <amount of keys>\
 <lower bound> <upper bound> <prefix>")
    print("""
number of tests - number of test files to generate
amount of keys - number of keys to put in each test
lower bound - the lowest possible key value that will be generated
upper bound - the highest value that will be generated
prefix - the prefix that will be added to all test's filenames
          """)


if (len(sys.argv) != 6):
    print_help()

try:
    NUM_OF_TESTS = int(sys.argv[1])
    NUM_OF_KEYS = int(sys.argv[2])
    LOWER_KEY_BOUND = int(sys.argv[3])
    UPPER_KEY_BOUND = int(sys.argv[4])
    PREFIX = sys.argv[5]
except Exception as e:
    print(f"[ERROR] {e}\n")
    print_help()

for test_num in range(NUM_OF_TESTS):
    keys = [randint(LOWER_KEY_BOUND, UPPER_KEY_BOUND) for _ in range(NUM_OF_KEYS)]
    ans = []
    with open(f"integration/{PREFIX}_{test_num}.dat", "w") as f:
        for i in range(len(keys)):
            f.write(f"k {keys[i]}\n")
            if (randint(0, 3) == 0):
                upper = randint(LOWER_KEY_BOUND + 1, UPPER_KEY_BOUND)
                lower = randint(LOWER_KEY_BOUND, upper)
                ans.append(list(set(list(filter(lambda x: lower <= x <= upper, 
                                                keys[:i+1])))))
                ans[-1].sort()
                f.write(f"q {lower} {upper}\n")

    with open(f"integration/{PREFIX}_{test_num}.ans", "w") as f:
        for e in ans:
            f.write(" ".join(map(str, e)) + "\n")
