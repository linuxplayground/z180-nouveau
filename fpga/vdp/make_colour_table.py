for i in range(0, 127):
    print("{0:02X} ".format((i % 16) << 4), end="")
    if i % 32 == 31:
        print()
print("F0")

for i in range(0, 127):
    print("{0:02X} ".format((i % 16)), end="")
    if i % 32 == 31:
        print()
print("0F")
