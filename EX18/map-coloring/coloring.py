Colors = list()
States = list()
Neighbor_Graph = dict()
Colors_States = dict()

def Valid_Coloring(State, Color):
    for Neighbor in Neighbor_Graph[State]:
        Colors_Of_Neighbor = Colors_States.get(Neighbor)
        if Colors_Of_Neighbor == Color:
            return False
    return True

def Get_Color_For_State(State):
    for Color in Colors:
        if Valid_Coloring(State, Color):
            return Color

def Map_Coloring():
    for State in States:
        Colors_States[State] = Get_Color_For_State(State)
    for State in Colors_States:
        print("Tiểu bang( {0} ) = {1}".format(State,Colors_States[State]))

def Read_File():
    with open("C:\\Users\\a\\Documents\\TriTueNhanTao\\EX18\\map-coloring\\text.txt",'r') as File:
        Lines = File.readlines()
        Colors.extend(Lines[0].split())
        for i in range(1,len(Lines)):
            Line = Lines[i].split()
            States.append(Line[0])
            Neighbor_Graph[Line[0]] = Line[1:]

Read_File()
Map_Coloring()