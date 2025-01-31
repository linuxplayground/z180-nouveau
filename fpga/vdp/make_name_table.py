for i in range(0, 767):
    print("{0:02X} ".format(i % 256), end="")
    if i % 32 == 31:
        print()
print("FF")
