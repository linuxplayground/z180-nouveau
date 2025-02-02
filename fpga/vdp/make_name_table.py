for i in range(0, 767):
    print("{0:02X} ".format(0), end="")
    if i % 32 == 31:
        print()
print("00")
