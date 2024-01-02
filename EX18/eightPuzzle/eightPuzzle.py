import copy

class State:
    def __init__(self):
        self.Puzzle = [[0 for x in range(3)] for y in range(3)] 
        self.Empty_Row = 0 
        self.Empty_Col = 0 

    def Is_Goal(self, Goal): 
        return Compare_States(self, Goal) 
    def Print_State(self): 
        for Row in range(3): 
            for Col in range(3): 
                print(self.Puzzle[Row][Col],end=" ")
            print()

    def Heuristic(self, Goal): 
        Count = 0 
        for Row in range(3): 
            for Col in range(3):
                if self.Puzzle[Row][Col] != Goal.Puzzle[Row][Col]: 
                    Count+=1
        return Count 

    def Push_U(self, Result): # Hàm di chuyển ô trống lên trên nếu có thể và trả về trạng thái mới sau khi di chuyển
        Result = copy.deepcopy(self) # Tạo một bản sao của đối tượng hiện tại bằng cách sử dụng hàm deepcopy của module copy
        Empty_Row = self.Empty_Row
        Empty_Col = self.Empty_Col
        if Empty_Row > 0: # Nếu ô trống không nằm ở hàng đầu tiên thì có thể di chuyển lên trên
            Result.Empty_Row = Empty_Row - 1
            Result.Empty_Col = Empty_Col
            Result.Puzzle[Empty_Row][Empty_Col] = self.Puzzle[Empty_Row-1][Empty_Col]
            Result.Puzzle[Empty_Row-1][Empty_Col] = 0
            return Result
        return None

    def Pull_D(self, Result): # Hàm di chuyển ô trống xuống dưới nếu có thể và trả về trạng thái mới sau khi di chuyển
        Result = copy.deepcopy(self)
        Empty_Row = self.Empty_Row
        Empty_Col = self.Empty_Col
        if Empty_Row < 2: # Nếu ô trống không nằm ở hàng cuối cùng thì có thể di chuyển xuống dưới
            Result.Empty_Row = Empty_Row + 1
            Result.Empty_Col = Empty_Col
            Result.Puzzle[Empty_Row][Empty_Col] = self.Puzzle[Empty_Row+1][Empty_Col]
            Result.Puzzle[Empty_Row+1][Empty_Col] = 0
            return Result
        return None

    def Left(self, Result): # Hàm di chuyển ô trống sang trái nếu có thể và trả về trạng thái mới sau khi di chuyển
        Result = copy.deepcopy(self)
        Empty_Row = self.Empty_Row
        Empty_Col = self.Empty_Col
        if Empty_Col > 0: # Nếu ô trống không nằm ở cột đầu tiên thì có thể di chuyển sang trái
            Result.Empty_Row = Empty_Row
            Result.Empty_Col = Empty_Col - 1
            Result.Puzzle[Empty_Row][Empty_Col] = self.Puzzle[Empty_Row][Empty_Col-1]
            Result.Puzzle[Empty_Row][Empty_Col-1] = 0
            return Result
        return None

    def Right(self, Result): # Hàm di chuyển ô trống sang phải nếu có thể và trả về trạng thái mới sau khi di chuyển
        Result = copy.deepcopy(self)
        Empty_Row = self.Empty_Row
        Empty_Col = self.Empty_Col
        if Empty_Col < 2: # Nếu ô trống không nằm ở cột cuối cùng thì có thể di chuyển sang phải
            Result.Empty_Row = Empty_Row
            Result.Empty_Col = Empty_Col + 1
            Result.Puzzle[Empty_Row][Empty_Col] = self.Puzzle[Empty_Row][Empty_Col+1]
            Result.Puzzle[Empty_Row][Empty_Col+1] = 0
            return Result
        return None

    def Call_Operator(self, Result, Option): # Hàm gọi các toán tử di chuyển ô trống dựa trên giá trị Option
        if Option == 1: # Nếu Option là 1 thì gọi hàm Push_U
            return self.Push_U(Result)
        elif Option == 2: # Nếu Option là 2 thì gọi hàm Pull_D
            return self.Pull_D(Result)
        elif Option == 3: # Nếu Option là 3 thì gọi hàm Left
            return self.Left(Result)
        elif Option == 4: # Nếu Option là 4 thì gọi hàm Right
            return self.Right(Result)
        else:
            return None


def Compare_States(S1, S2): # Định nghĩa hàm so sánh hai trạng thái
    if S1.Empty_Row != S2.Empty_Row or S1.Empty_Col != S2.Empty_Col: # Nếu vị trí ô trống không giống nhau thì trả về False
        return False
    for Row in range(3): # Duyệt qua từng hàng trong mảng 2 chiều
        for Col in range(3): # Duyệt qua từng cột trong mảng 2 chiều
            if S1.Puzzle[Row][Col] != S2.Puzzle[Row][Col]: # So sánh giá trị tương ứng
                return False # Nếu không giống nhau thì trả về False
    return True # Nếu tất cả các giá trị đều giống nhau thì trả về True

class Node: # Định nghĩa lớp Node để lưu trữ thông tin cho thuật toán A*
    def __init__(self, State, Dad = None, Order = 0, G = 0, H = 0): # Hàm khởi tạo
        self.State = State # Lưu trữ trạng thái hiện tại
        self.Dad = Dad # Lưu trữ cha của node hiện tại
        self.Order = Order # Lưu trữ thứ tự của node hiện tại
        self.G = G # Lưu trữ giá trị G (chi phí từ node gốc đến node hiện tại)
        self.H = H # Lưu trữ giá trị H (giá trị heuristic từ node hiện tại đến node đích)
        self.F = self.G + self.H # Tính giá trị F (tổng của G và H)

    def Find_State(self, List): # Hàm tìm kiếm một trạng thái trong danh sách các node
        for Index in range(len(List)): # Duyệt qua từng phần tử trong danh sách
            if Compare_States(List[Index].State,self.State): # So sánh trạng thái của node hiện tại với trạng thái cần tìm kiếm
                return List[Index],Index # Nếu giống nhau thì trả về node và chỉ số tương ứng
        return None,-1 # Nếu không tìm thấy thì trả về None và -1

Action = ["Trạng thái bắt đầu"
          ,"Đẩy ô trống lên trên",
          "Kéo ô trống xuống dưới",
          "Đẩy ô trống qua trái",
          "Đẩy ô trống qua phải"] # Định nghĩa danh sách các hành động có thể

def Get_Path(Goal): # Hàm lấy đường đi từ node gốc đến node đích
    List = [] # Khởi tạo danh sách lưu trữ đường đi
    while Goal.Dad != None: # Lặp cho đến khi đến node gốc (node cha bằng None)
        List.append(Goal) # Thêm node hiện tại vào danh sách
        Goal = Goal.Dad # Chuyển sang xét node cha của node hiện tại
    List.append(Goal) # Thêm node gốc vào danh sách
    List.reverse() # Đảo ngược danh sách để có đường đi từ gốc đến đích
    for Item in List: # Duyệt qua từng phần tử trong danh sách
        print("Action:",Action[Item.Order]) # In ra hành động tương ứng
        Item.State.Print_State() # In ra trạng thái tương ứng

def A_Star(First_State, Goal_State): # Định nghĩa hàm giải thuật toán A*
    IsOpen = [] # Khởi tạo danh sách Open (chứa các node chưa xét)
    Closed = [] # Khởi tạo danh sách Closed (chứa các node đã xét)
    Root = Node(First_State,H=First_State.Heuristic(Goal_State)) # Khởi tạo node gốc
    IsOpen.append(Root) # Thêm node gốc vào danh sách Open
    while len(IsOpen) != 0: # Lặp cho đến khi danh sách Open rỗng
        Top = IsOpen.pop(0) # Lấy ra node đầu tiên trong danh sách Open
        Closed.append(Top) # Thêm node đó vào danh sách Closed
        if Top.State.Is_Goal(Goal_State): # Kiểm tra xem node đó có phải là node đích hay không
            Get_Path(Top) # Nếu đúng thì lấy đường đi và kết thúc thuật toán
            return
        for Option in range(1,4+1,1): # Duyệt qua từng hành động có thể
            Child_State = State()
            Child_State = Top.State.Call_Operator(Child_State,Option)
            if Child_State != None: # Nếu trạng thái mới hợp lệ (không phải None)
                Child_Node = Node(State=Child_State,Dad=Top,Order=Option,G=Top.G+1,H=Child_State.Heuristic(Goal_State))
                Existed_IsOpen, Pos_IsOpen = Child_Node.Find_State(IsOpen)
                Existed_Closed, Pos_Closed = Child_Node.Find_State(Closed)
                if Existed_IsOpen == None and Existed_Closed == None: # Nếu trạng thái mới chưa tồn tại trong cả hai danh sách Open và Closed
                    IsOpen.append(Child_Node) # Thêm trạng thái mới vào danh sách Open
                elif Existed_IsOpen != None and Existed_IsOpen.G > Child_Node.G: # Nếu trạng thái mới đã tồn tại trong danh sách Open và có giá trị G nhỏ hơn
                    IsOpen.pop(Pos_IsOpen) # Xóa trạng thái cũ khỏi danh sách Open
                    IsOpen.insert(Pos_IsOpen,Child_Node) # Thêm trạng thái mới vào vị trí cũ trong danh sách Open
                elif Existed_Closed != None and Existed_Closed.G > Child_Node.G: # Nếu trạng thái mới đã tồn tại trong danh sách Closed và có giá trị G nhỏ hơn
                    Closed.pop(Pos_Closed) # Xóa trạng thái cũ khỏi danh sách Closed
                    IsOpen.append(Child_Node) # Thêm trạng thái mới vào danh sách Open
        IsOpen.sort(key=lambda x: x.G) # Sắp xếp lại danh sách Open theo giá trị G
    return None

First_State = State()
First_State.Empty_Row = 1
First_State.Empty_Col = 1
First_State.Puzzle = [[1,2,3],[8,0,4],[7,6,5]]

Goal_State = State()
Goal_State.Empty_Row = 1
Goal_State.Empty_Col = 0
Goal_State.Puzzle = [[2,8,1],[0,4,3],[7,6,5]]

A_Star(First_State,Goal_State)