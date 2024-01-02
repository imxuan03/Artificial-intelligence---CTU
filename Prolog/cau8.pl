% Marcus là một người đàn ông.
nguoi_dan_ong(marcus).

% Marcus là người Pompeian.
nguoi_pompeian(marcus).

% Marcus được sinh ra vào năm 40 (sau công nguyên).
nam_sinh(marcus, 40).

% Mọi người đều phải chết.
phai_chet(Nguoi) :- nguoi_dan_ong(Nguoi).

% Tất cả người Pompeian đều bị chết khi núi lửa phun trào vào năm 79 (sau công nguyên).
chay_nui_lua(Nguoi) :- nguoi_pompeian(Nguoi), nam_sinh(Nguoi, NamSinh), NamSinh < 79.

% Không cái gì phải chết sống lâu hơn 150 năm.
khong_chet_sau_150_nam(Nguoi) :- nguoi_dan_ong(Nguoi), nam_sinh(Nguoi, NamSinh), NamSinh + 150 >= 2000.

% Bây giờ là năm 2000.
nam_hien_tai(2000).

% Còn sống nghĩa là không chết.
con_song(Nguoi) :- nguoi_dan_ong(Nguoi), nam_hien_tai(HienTai), \+ chay_nui_lua(Nguoi), khong_chet_sau_150_nam(Nguoi), nam_sinh(Nguoi, NamSinh), NamSinh < HienTai.

% Nếu một người bị chết, người đó sẽ chết từ đó về sau.
chet(Nguoi) :- \+ con_song(Nguoi).

% Truy vấn kiểm tra liệu Marcus còn sống không trong năm 2000.
?- con_song(marcus).
