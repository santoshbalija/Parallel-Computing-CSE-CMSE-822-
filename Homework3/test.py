from itertools import product
from os import sched_getaffinity
from subprocess import run
from sys import stdout


def cpu_count():
    return len(sched_getaffinity(0))


optimizations = [3, 2, 1, 0]
repeats_for_average = 10
num_threads = range(1, min(cpu_count(), 64) + 1)
iterations = 100_000_000


def main():
    """Run through each set of options and compile/benchmark the test code."""
    for opt in optimizations:
        compile_command = ["g++", "main.cpp", f"-O{opt}", "-lpthread"]
        run(compile_command, check=True)
        for threads in num_threads:
            print(f"{opt=}, {threads=}", end="")
            stdout.flush()
            test_command = ['./a.out', str(iterations), str(threads)]
            total = 0
            for samples in range(1, repeats_for_average + 1):
                print(".", end="")
                stdout.flush()
                output = run(test_command, check=True, capture_output=True).stdout
                total += int(output.split()[-2]) / 1000
            print(f"\t{total / samples:.03f}")


if __name__ == '__main__':
    main()
