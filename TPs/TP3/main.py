#!/usr/bin/python3
import sys


def main():

    for line in sys.stdin:
        print(f"Processing Message from sys.stdin *****{line}*****")
    print("Done")

    """
    while True:
        data = input("Please enter the message:\n")
        if "exit" == data:
            break
        print(f'Processing Message from input() *****{data}*****')

    print("Done")
    """


main()
