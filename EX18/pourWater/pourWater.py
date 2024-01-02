TANK_CAPACITY_X = 10
TANK_CAPACITY_Y = 5
TANK_CAPACITY_Z = 6
EMPTY = 0
GOAL = 8

class State:
    def __init__(self, X = 0, Y = 0, Z = 0):
        self.X = X
        self.Y = Y
        self.Z = Z

    def Print_State(self):
        print("X:",self.X,"Y:",self.Y,"Z:",self.Z)

    def Is_GOAL(self):
        return self.X==GOAL or self.Y==GOAL or self.Z==GOAL

    def Pour_Milk_Empty_X(self, Result):
        if self.X > 0:
            Result.X = EMPTY
            Result.Y = self.Y
            Result.Z = self.Z
            return Result
        return None

    def Pour_Milk_Empty_Y(self, Result):
        if self.Y > 0:
            Result.X = self.X
            Result.Y = EMPTY
            Result.Z = self.Z
            return Result
        return None


    def Pour_Milk_Empty_Z(self, Result):
        if self.Z > 0:
            Result.X = self.X
            Result.Y = self.Y
            Result.Z = EMPTY
            return Result
        return None

    def Pour_Milk_X_To_Y(self, Result):
        if self.X > 0 and self.Y < TANK_CAPACITY_Y:
            Remaining_Y = TANK_CAPACITY_Y - self.Y
            Result.X = max(self.X-Remaining_Y,EMPTY)
            Result.Y = min(self.X+self.Y,TANK_CAPACITY_Y)
            Result.Z = self.Z
            return Result
        return None

    def Pour_Milk_X_To_Z(self, Result):
        if self.X > 0 and self.Z < TANK_CAPACITY_Z:
            Remaining_Z = TANK_CAPACITY_Z - self.Z
            Result.X = max(self.X-Remaining_Z,EMPTY)
            Result.Z = min(self.X+self.Z,TANK_CAPACITY_Z)
            Result.Y = self.Y
            return Result
        return None

    def Pour_Milk_Y_To_X(self, Result):
        if self.Y > 0 and self.X < TANK_CAPACITY_X:
            Remaining_X = TANK_CAPACITY_X - self.X
            Result.Y = max(self.Y-Remaining_X,EMPTY)
            Result.X = min(self.Y+self.X,TANK_CAPACITY_X)
            Result.Z = self.Z
            return Result
        return None

    def Pour_Milk_Y_To_Z(self, Result):
        if self.Y > 0 and self.Z < TANK_CAPACITY_Z:
            Remaining_Z = TANK_CAPACITY_Z - self.Z
            Result.Y = max(self.Y-Remaining_Z,EMPTY)
            Result.Z = min(self.Y+self.Z,TANK_CAPACITY_Z)
            Result.X = self.X
            return Result
        return None

    def Pour_Milk_Z_To_X(self, Result):
        if self.Z > 0 and self.X < TANK_CAPACITY_X:
            Remaining_X = TANK_CAPACITY_X - self.X
            Result.Z = max(self.Z - Remaining_X,EMPTY)
            Result.X = min(self.Z+self.X,TANK_CAPACITY_X)
            Result.Y = self.Y
            return Result
        return None

    def Pour_Milk_Z_To_Y(self, Result):
        if self.Z > 0 and self.Y < TANK_CAPACITY_Y:
            Remaining_Y = TANK_CAPACITY_Y - self.Y
            Result.Z = max(self.Z - Remaining_Y,EMPTY)
            Result.Y = min(self.Z+self.Y,TANK_CAPACITY_Y)
            Result.X = self.X
            return Result
        return None


    def Call_Operator(self, Result, Option):
        if Option == 1:
            return self.Pour_Milk_Empty_X(Result)
        elif Option == 2:
            return self.Pour_Milk_Empty_Y(Result)
        elif Option == 3:
            return self.Pour_Milk_Empty_Z(Result)
        elif Option == 4:
            return self.Pour_Milk_X_To_Y(Result)
        elif Option == 5:
            return self.Pour_Milk_X_To_Z(Result)
        elif Option == 6:
            return self.Pour_Milk_Y_To_X(Result)
        elif Option == 7:
            return self.Pour_Milk_Y_To_Z(Result)
        elif Option == 8:
            return self.Pour_Milk_Z_To_X(Result)
        elif Option == 9:
            return self.Pour_Milk_Z_To_Y(Result)
        else:
            return None # Trả về None nếu không có tùy chọn nào được chọn.

Action = [
    "First state",
    "Pour water empty X",
    "Pour water empty Y",
    "Pour water empty Z",
    "Pour water X to Y",
    "Pour water X to Z",
    "Pour water Y to X",
    "Pour water Y to Z",
    "Pour water Z to X",
    "Pour water Z to Y"
    ]

class Node:
    def __init__(self, State, Dad = None, Order = 0):
        self.State = State
        self.Dad = Dad
        self.Order = Order

def Compare_States(A, B):
    return A.X == B.X and A.Y == B.Y and A.Z == B.Z

def Find_State(S, List):
    for Item in List:
        if Compare_States(S,Item.State):
            return 1
    return 0

def Get_Path_Goal(Goal):
    List = []
    while Goal.Dad != None:
        List.append(Goal)
        Goal = Goal.Dad
    List.append(Goal)
    List.reverse()
    Order = 0
    for Item in List:
        print("Action:",Order,Action[Item.Order])
        Item.State.Print_State()
        Order += 1

def BFS(Start_State):
    IsOpen = []
    Closed = []
    Root = Node(Start_State)
    IsOpen.append(Root)
    while len(IsOpen) != 0:
        Top_Node = IsOpen.pop(0)
        Closed.append(Top_Node)
        if Top_Node.State.Is_GOAL():
            Get_Path_Goal(Top_Node)
            return
        for Option in range(1,9+1,1):
            Child_State = State()
            Child_State = Top_Node.State.Call_Operator(Child_State, Option)
            if Child_State != None:
                Existed_IsOpen = Find_State(Child_State,IsOpen)
                Existed_Closed = Find_State(Child_State, Closed)
                if not Existed_IsOpen and not Existed_Closed:
                    Child_Node = Node(Child_State,Dad=Top_Node, Order=Option)
                    IsOpen.append(Child_Node)
    return None

BFS(State(10,0,0))