class State:
    def __init__(self):
        self.Glasses = [1,-1,1,-1,1,-1]

    def Up_Side_Down(self, Result, Index):
        for I in range(6):
            Result.Glasses[I] = self.Glasses[I]
        for I in range(Index,Index+2+1,1):
            Result.Glasses[I] *= -1
        return Result

    def Print_State(self):
        print("State:",end=" ")
        for I in range(6):
            print(self.Glasses[I],end=" ")
        print()

    def Is_Goal(self):
        for I in range(6):
            if self.Glasses[I] == -1:
                return False
        return True

def Compare_States(S1, S2):
    for I in range(6):
        if S1.Glasses[I] != S2.Glasses[I]:
            return False
    return True

class Node:
    def __init__(self, State, Dad = None, Order = 0):
        self.State = State
        self.Dad = Dad
        self.Order = Order

def Find_State(State, List):
    for Item in List:
        if Compare_States(Item.State,State):
            return True
    return False

def Get_Path(Goal):
    List = []
    while Goal.Dad != None:
        List.append(Goal)
        Goal = Goal.Dad
    List.append(Goal)
    List.reverse()
    for Item in List:
        Position = Item.Order+1
        print("Lật ngược các l ở các vị trí:",Position,Position+1,Position+2)
        Item.State.Print_State()

def DFS(First_State):
    IsOpen = []
    Closed = []
    Root = Node(First_State)
    IsOpen.append(Root)
    while len(IsOpen) != 0:
        Top = IsOpen.pop(0)
        Closed.append(Top)
        if Top.State.Is_Goal():
            Get_Path(Top)
            return
        for Index in range(4):
            Child_State = State()
            Child_State = Top.State.Up_Side_Down(Child_State,Index)
            Existed_IsOpen = Find_State(Child_State,IsOpen)
            Existed_Closed = Find_State(Child_State,Closed)
            if not Existed_IsOpen and not Existed_Closed:
                Child_Node = Node(Child_State,Top,Index)
                IsOpen.insert(0,Child_Node)
    return None

DFS(State())