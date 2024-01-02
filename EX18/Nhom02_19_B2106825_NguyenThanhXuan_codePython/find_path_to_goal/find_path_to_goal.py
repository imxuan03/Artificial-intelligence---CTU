MAX_VERTICES = 5

class Vertice:
    def __init__(self):
        self.Neighbor = [0 for x in range(MAX_VERTICES)]
        self.H = 0

Graph = [Vertice() for x in range(MAX_VERTICES)]

Name = ['A','B','C','D','G']

class Node:
    def __init__(self, Vertex = -1, Dad = None, G = 0, H = 0):
        self.State = Vertex
        self.Dad = Dad
        self.G = G
        self.H = 0
        self.F = self.G + self.H

    def Print_State(self):
        print(Name[self.State],end=' ')

    def Compare_States(self, S):
        return self.State == S

    def Find_State(self, List):
        for I in range(len(List)):
            if self.Compare_States(List[I].State):
                return List[I], I
        return None, -1

    def Is_Goal(self, Goal):
        return self.Compare_States(Goal)

def Get_Path(Goal):
    List = []
    while Goal.Dad != None:
        List.append(Goal)
        Goal = Goal.Dad
    List.append(Goal)
    List.reverse()
    print("Đường đi từ đầu đến đích:",end=' ')
    for Item in List:
        Item.Print_State()

def A_Star(Start_Vertex, Goal_Vertex):
    IsOpen = []
    Closed = []
    Root = Node(Vertex = Start_Vertex, H = Graph[Start_Vertex].H)
    IsOpen.append(Root)
    while len(IsOpen) != 0:
        Top_Node = IsOpen.pop(0)
        Closed.append(Top_Node)
        if Top_Node.Is_Goal(Goal_Vertex):
            return Top_Node
        for Option in range(MAX_VERTICES):
            if Graph[Top_Node.State].Neighbor[Option] > 0:
                Child_Node = Node(Vertex = Option,Dad = Top_Node, G = Top_Node.G + Graph[Top_Node.State].Neighbor[Option], H = Graph[Option].H)
                Existed_IsOpen, Index_IsOpen = Child_Node.Find_State(IsOpen)
                Existed_Closed, Index_Closed = Child_Node.Find_State(Closed)
                if Existed_IsOpen == None and Existed_Closed == None:
                    IsOpen.append(Child_Node)
                elif Existed_IsOpen != None and Existed_IsOpen.G > Child_Node.G:
                    IsOpen.pop(Index_IsOpen)
                    IsOpen.insert(Index_IsOpen, Child_Node)
                elif Existed_Closed != None and Existed_Closed.G > Child_Node.G:
                    Closed.pop(Index_Closed)
                    IsOpen.append(Child_Node)
        IsOpen.sort(key = lambda x:x.G)
    return None

with open("C:\\Users\\a\\Documents\\TriTueNhanTao\\EX18\\find_path_to_goal\\text.txt","r") as File:
    for I in range(MAX_VERTICES):
        Line = File.readline()
        Heuristic = [int(x) for x in Line.split()]
        Graph[I].H = Heuristic[0]
        for J in range(MAX_VERTICES):
            Graph[I].Neighbor[J] = Heuristic[J+1]

Start = 0
Goal = 4
Result = A_Star(Start, Goal)
if Result != None:
    Get_Path(Result)
else:
    print("Không tìm thấy đường đi từ Start đến Goal")