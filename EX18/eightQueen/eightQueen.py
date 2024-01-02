SIZE = 8

Queens = [[0 for Cols in range(SIZE)] for Rows in range(SIZE)]
def Can_Put_Queens(Rows, Cols):
    for I in range(Rows):
        if Queens[I] == Cols or abs(I-Rows) == abs(Queens[I]-Cols):
            return False
    return True

def Show_Queens():
    for I in range(SIZE):
        for J in range(SIZE):
            if Queens[I] == J:
                print("Q",end='  ')
            else:
                print("0",end='  ')
        print("")
    Y_Or_No = int(input("Bạn có muốn xem tiếp???(1 to continue and any number to exit):"))
    if Y_Or_No == 1:
        print()
    else:
        exit()

def Put_Queens(Rows):
    for Cols in range(SIZE):
        if Can_Put_Queens(Rows,Cols) == True:
            Queens[Rows] = Cols
            if Rows == SIZE - 1:
                Show_Queens()
            else:
                Put_Queens(Rows+1)
            Queens[Rows] = 0

Put_Queens(0)