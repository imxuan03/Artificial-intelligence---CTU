cha(X, Y).
me(X, Y).
vo(X, Y).
chong(X, Y).
nam(X).
nu(X).
tuoi(X, Y).
tuoi(anh, tu).
nam(tu).

anh_ruot(X, Y):- nam(X), tuoi(X, Y), cha(C, X), cha(C, Y), me(M, X), me(M, Y).
chi_ruot(X, Y):- nu(X), tuoi(X, Y), cha(C, X), cha(C, Y), me(M, X), me(M, Y).
em_trai_ruot(X, Y):- nam(X), tuoi(Y, X), cha(C, X), cha(C, Y), me(M, X), me(M, Y).
em_gái_ruot(X, Y):- nu(X), tuoi(Y, X), cha(C, X), cha(C, Y), me(M, X), me(M, Y).

chu(X, Y):- em_trai_ruot(X, C), cha(C, Y).
bac_trai(X, Y):- anh_ruot(X, C), cha(C, Y).
cau(X, Y):- em_trai_ruot(X, M), me(M, Y).
cau(X, Y):- anh_ruot(X, M), me(M, Y).


co(X, Y):- em_gai_ruot(X, C), cha(C, Y).
co(X, Y):- chi_ruot(X, C), cha(C, Y).
di(X, Y):- em_gái_ruot(X, M), me(M, Y).
di(X, Y):- chi_ruot(X, M), me(M, Y).
mo(X, Y):- vo(X, C), cau(C, Y).
thim(X, Y):- vo(X, C), chu(C, Y).
bac_gai(X, Y):- vo(X, B), bac_trai(B, Y).

ong_noi(X, Y):- cha(X, C), cha(C, Y).
ong_ngoai(X, Y):- cha(X, M), me(M, Y).

ba_noi(X, Y):- me(X, C), cha(C, Y).
ba_noi(X, Y):- me(X, M), me(M, Y).

cha_vo(X, Y):- cha(X, V), vo(V, Y).
me_vo(X, Y):- me(X, V), vo(V, Y).
cha_chong(X, Y):- cha(X, C), chong(C, Y).
me_chong(X, Y):- me(X, C), chong(C, Y).