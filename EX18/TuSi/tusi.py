from typing import Any


class State:
    
    def __init__(self, Monk = 3, Ghost = 3, Edge = 'A'):
        self.Monk = Monk 
        self.Ghost = Ghost 
        self.Edge = Edge 

   
    def Move_1_Monk(self, Result):
        if self.Edge=='A' and self.Monk>0: 
            Result.Monk = self.Monk - 1 
            Result.Ghost = self.Ghost 
            Result.Edge = 'B' 
            return Result
        elif self.Edge=='B' and self.Monk<3: 
            Result.Monk = self.Monk+1
            Result.Ghost = self.Ghost 
            Result.Edge = 'A' 
            return Result
        return None

    # Phương thức di chuyển 2 nhà sư
    def Move_2_Monks(self, Result):
        if self.Edge=='A' and self.Monk>1: 
            Result.Monk = self.Monk - 2 
            Result.Ghost = self.Ghost 
            Result.Edge = 'B'
            return Result
        elif self.Edge=='B' and self.Monk<2: 
            Result.Monk = self.Monk + 2 
            Result.Ghost = self.Ghost 
            Result.Edge = 'A' 
            return Result
        return None

    # Phương thức di chuyển 1 hồn ma
    def Move_1_Ghost(self, Result):
        if self.Edge=='A' and self.Ghost>0: 
            Result.Ghost = self.Ghost - 1 
            Result.Monk = self.Monk 
            Result.Edge = 'B' 
            return Result
        elif self.Edge=='B' and self.Ghost<3: 
            Result.Ghost = self.Ghost + 1 
            Result.Monk = self.Monk 
            Result.Edge = 'A' 
            return Result
        return None

    # Phương thức di chuyển 2 hồn ma
    def Move_2_Ghosts(self, Result):
        if self.Edge=='A' and self.Ghost>1: 
            Result.Ghost = self.Ghost - 2
            Result.Monk = self.Monk
            Result.Edge = 'B' 
            return Result
        elif self.Edge=='B' and self.Ghost<2: 
            Result.Ghost = self.Ghost + 2 
            Result.Monk = self.Monk 
            Result.Edge = 'A' 
            return Result
        return None

    # Phương thức di chuyển 1 nhà sư và 1 hồn ma
    def Move_1_Each_Kind(self, Result):
        if self.Edge=='A' and self.Monk>0 and self.Ghost>0:
            Result.Monk = self.Monk - 1 
            Result.Ghost = self.Ghost - 1 
            Result.Edge = 'B' 
            return Result
        elif self.Edge=='B' and self.Monk<3 and self.Ghost<3: 
            Result.Monk = self.Monk + 1 
            Result.Ghost = self.Ghost + 1 
            Result.Edge = 'A' 
            return Result
        return None

    # Phương thức gọi các phương thức di chuyển khác nhau dựa trên giá trị của Option
    def Call(self, Result, Option):
        if Option == 1:
            return self.Move_1_Monk(Result)
        elif Option == 2:
            return self.Move_2_Monks(Result)
        elif Option == 3:
            return self.Move_1_Ghost(Result)
        elif Option == 4:
            return self.Move_2_Ghosts(Result)
        elif Option == 5:
            return self.Move_1_Each_Kind(Result)
        else:
            return None

    # Phương thức kiểm tra trạng thái hiện tại có hợp lệ hay không
    def Valid_State(self):
        if self.Edge=='A' and self.Ghost > self.Monk and self.Monk != 0:
            return False
        if self.Edge=='A' and self.Ghost < self.Monk and self.Monk != 3: 
            return False
        if self.Edge=='B' and self.Ghost > self.Monk and self.Monk != 0:
            return False
        if self.Edge=='B' and self.Ghost < self.Monk and self.Monk != 3:
            return False
        return True

    # Phương thức kiểm tra xem đã đạt được mục tiêu hay chưa (tất cả các nhà sư và hồn ma đã chuyển sang bờ B)
    def Is_Goal(self):
        return self.Ghost==0 and self.Monk==0 and self.Edge=='B'

    # Phương thức in ra trạng thái hiện tại của các thuộc tính Monk, Ghost và Edge
    def Print_State(self):
        print("Nhà sư:",self.Monk,"| Hồn ma:",self.Ghost,"| Bờ:",self.Edge)

class Node:
    # Khởi tạo lớp Node với các thuộc tính State, Dad và Order
    def __init__(self, State, Dad = None, Order = 0):
        self.State = State 
        self.Dad = Dad 
        self.Order = Order 

# Hàm so sánh hai trạng thái S1 và S2 có giống nhau hay không
def Compare_States(S1, S2):
    return S1.Edge==S2.Edge and S1.Monk==S2.Monk and S1.Ghost==S2.Ghost

# Hàm tìm kiếm trạng thái S trong danh sách List
def Find_State(S, List):
    for Item in List:
        if Compare_States(Item.State, S):
            return True
    return False

# Danh sách các hành động có thể thực hiện
Action = ["First state","Move one monk","Move two monks","Move one ghost","Move two ghosts","Move one each kind"]

# Hàm lấy đường đi từ trạng thái ban đầu đến trạng thái mục tiêu
def Get_Path(Goal):
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
        Order+=1

# Hàm tìm kiếm theo chiều sâu (Depth-First Search)
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
        for Option in range(1,5+1,1):
            Child_State = State()
            Child_State = Top.State.Call(Child_State,Option) 
            if Child_State != None: 
                Existed_IsOpen = Find_State(Child_State,IsOpen) 
                Existed_Closed = Find_State(Child_State,Closed)
                if not Existed_IsOpen and not Existed_Closed and Child_State.Valid_State():
                    Child_Node = Node(Child_State, Top, Option) 
                    IsOpen.insert(0,Child_Node)
    return None

DFS(State()) 