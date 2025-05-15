def custom_pow(base, exponent, modulus=None):
    res = 1
    cur = base
    square_count = 0
    mult_count = 0
    traced_exp = 1;

    while exponent != 0:

        r = exponent & 1
        if r == 1:
            res = (res * cur) % modulus
            mult_count += 1

            # if modulus:
                # res %= modulus
            print(f"\texp: {traced_exp}, base^exp: {cur}, result: {res}")
        else:
            print(f"\texp: {traced_exp}, base^exp: {cur}, result: -")

        exponent >>= 1
        traced_exp <<= 1

        if exponent != 0:
            cur = cur * cur
            square_count += 1

            if modulus:
                cur %= modulus

    print(f"Final result: {res}, square count: {square_count}, mult count: {mult_count}")
    return res


print(pow(4,31,11))
custom_pow(4,31,11)

print(pow(4,5,11))
custom_pow(4,5,11)

print(pow(4,4,11))
custom_pow(4,4,11)

print(pow(4,18,11))
custom_pow(4,18,11)

print(pow(5,701,11))
custom_pow(5,701,11)