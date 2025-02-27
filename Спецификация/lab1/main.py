frm = int(input())
to = int(input())

neibs = "123456789876543210"
for num in range(frm, to+1):
    if str(num) in neibs:
        print(num)