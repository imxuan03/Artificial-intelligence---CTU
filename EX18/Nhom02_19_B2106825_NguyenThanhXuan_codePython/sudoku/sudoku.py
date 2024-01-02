
class Coord:
    def __init__(self, X = 0, Y = 0):
        self.X = X
        self.Y = Y


NB_ROWS = 9
NB_COLS = 9


def Index_Of(COORD):
    return (NB_ROWS*COORD.X+COORD.Y)


def Position_Of_Vertex(Vertex):
    COORD = Coord()
    COORD.X = Vertex // NB_ROWS
    COORD.Y = Vertex % NB_COLS
    return COORD

def Add_Constrain(CONSTRAINS, Sourse, Target):
    U = Index_Of(Sourse)
    V = Index_Of(Target)
    if CONSTRAINS[U][V] == 0:
        CONSTRAINS[U][V] = 1
        CONSTRAINS[V][U] = 1
        return CONSTRAINS
    return None

def Get_Constrains(CONSTRAINS, COORD):
    V = Index_Of(COORD)
    Result = []
    for I in range(NB_ROWS*NB_COLS):
        if CONSTRAINS[V][I] == 1:
            Result.append(Position_Of_Vertex(I))
    return Result

MAX_VALUE = 10
AREA_SQUARE_SIZE = 3

class Sudoku:
    def __init__(self):
        self.Cells = [[0 for Col in range(NB_COLS)] for Row in range(NB_ROWS)]
        self.Constrains = [[0 for Col in range(NB_ROWS*NB_COLS)] for Row in range(NB_ROWS*NB_COLS)]

    def Init_Sudoku_With_Values(self, Input_Matrix):
        for Row in range(NB_ROWS):
            for Col in range(NB_COLS):
                self.Cells[Row][Col] = Input_Matrix[Row][Col]

    def Print_Sudoku(self):
        print("Sudoku:")
        for Row in range(NB_ROWS):
            if Row % AREA_SQUARE_SIZE == 0:
                print("----------------------")
            for Col in range(NB_COLS):
                if Col % AREA_SQUARE_SIZE == 0:
                    print("|",end='')
                print(self.Cells[Row][Col],end=' ')
            print("|")
        print("----------------------")

    def Is_Fill_Sudoku(self):
        for Row in range(NB_ROWS):
            for Col in range(NB_COLS):
                if self.Cells[Row][Col] == 0:
                    return False
        return True

def Spread_Constrains_From(Position, CONSTRAINS, Changeds):
    Row = Position.X
    Col = Position.Y
    for A in range(NB_ROWS):
        if A != Row:
            Pos = Coord(A,Col)
            if Add_Constrain(CONSTRAINS, Position, Pos):
                Changeds.append(Pos)
    for B in range(NB_COLS):
        if B != Col:
            Pos = Coord(Row,B)
            if Add_Constrain(CONSTRAINS, Position, Pos):
                Changeds.append(Pos)
    for C in range(AREA_SQUARE_SIZE):
        for D in range(AREA_SQUARE_SIZE):
            Area_X = (Row//AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE
            Area_Y = (Col//AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE
            if Area_X+C != Row or Area_Y+D != Col:
                Pos = Coord(Area_X+C, Area_Y+D)
                if Add_Constrain(CONSTRAINS, Position, Pos):
                    Changeds.append(Pos)
    return CONSTRAINS, Changeds

def Get_Available_Values(Position, SUDOKU):
    Pos_List = Get_Constrains(SUDOKU.Constrains, Position)
    Available = [0 for X in range(MAX_VALUE)]
    for I in range(1,MAX_VALUE,1):
        Available[I] = 1
    for Y in range(len(Pos_List)):
        Pos = Pos_List[Y]
        if SUDOKU.Cells[Pos.X][Pos.Y] != 0:
            Available[SUDOKU.Cells[Pos.X][Pos.Y]] = 0
    Result = []
    for M in range(1,MAX_VALUE,1):
        if Available[M]:
            Result.append(M)
    return Result

def Get_Next_Empty_Cell(SUDOKU):
    for I in range(NB_ROWS):
        for J in range(NB_COLS):
            Pos = Coord(I,J)
            if SUDOKU.Cells[I][J] == 0:
                return Pos
    return -1,-1

Explored_Counter = 0

def Sudoku_Back_Tracking(SUDOKU):
    if SUDOKU.Is_Fill_Sudoku():
        return SUDOKU
    Position = Get_Next_Empty_Cell(SUDOKU)
    Available = Get_Available_Values(Position, SUDOKU)
    if len(Available) == 0:
        return None
    global Explored_Counter
    for I in range(len(Available)):
        Value = Available[I]
        SUDOKU.Cells[Position.X][Position.Y] = Value
        Explored_Counter+=1
        if Sudoku_Back_Tracking(SUDOKU):
            return SUDOKU
        SUDOKU.Cells[Position.X][Position.Y] = 0
    return None

def Solve_Sudoku(SUDOKU):
    for I in range(NB_ROWS):
        for J in range(NB_COLS):
            History = []
            Pos = Coord(I,J)
            SUDOKU.Constrains, History = Spread_Constrains_From(Pos,SUDOKU.Constrains, History)
    global Explored_Counter
    SUDOKU = Sudoku_Back_Tracking(SUDOKU)
    if SUDOKU != None:
        print("Solve")
    else:
        print("Can't solve")
    print("Explored:",Explored_Counter,"states")
    return SUDOKU

Input = [
    [0,0,0,7,0,4,9,0,2],
    [0,5,0,0,0,0,0,0,0],
    [0,9,0,0,0,1,0,0,4],
    [0,0,8,0,0,0,0,0,0],
    [0,0,0,0,3,0,0,0,0],
    [0,0,0,1,0,0,8,0,0],
    [1,0,0,0,0,7,0,0,0],
    [0,0,3,0,0,0,2,0,0],
    [0,0,0,0,0,5,0,0,0],
]
if __name__ == "__main__":
    SUDOKU = Sudoku()
    SUDOKU.Init_Sudoku_With_Values(Input)
    SUDOKU.Print_Sudoku()
    Result = Solve_Sudoku(SUDOKU)
    Result.Print_Sudoku()