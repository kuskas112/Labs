union([], L2, L2).
union(L1, [], L1).
union([], [], []).
union([X|Xs], [Y|Ys], [X|Merged]) :-
    X < Y,
    !,
    union(Xs, [Y|Ys], Merged).
union([X|Xs], [Y|Ys], [Y|Merged]) :-
    X > Y,
    !,
    union([X|Xs], Ys, Merged).
union([X|Xs], [X|Ys], [X|Merged]) :-
    !,
    union(Xs, Ys, Merged).


inter([], L2, []).
inter(L1, [], []).
inter([], [], []).
inter([X|Xs], [Y|Ys], Merged) :-
    X < Y,
    !,
    inter(Xs, [Y|Ys], Merged).
inter([X|Xs], [Y|Ys], Merged) :-
    X > Y,
    !,
    inter([X|Xs], Ys, Merged).
inter([X|Xs], [X|Ys], [X|Merged]) :-
    !,
    inter(Xs, Ys, Merged).


diff([], L2, []).
diff(L1, [], L1).
diff([], [], []).
diff([X|Xs], [Y|Ys], [X|Merged]) :-
    X < Y,
    !,
    diff(Xs, [Y|Ys], Merged).
diff([X|Xs], [Y|Ys], Merged) :-
    X > Y,
    !,
    diff([X|Xs], Ys, Merged).
diff([X|Xs], [X|Ys], Merged) :-
    !,
    diff(Xs, Ys, Merged).


simdiff([], L2, L2).
simdiff(L1, [], L1).
simdiff([], [], []).
simdiff([X|Xs], [Y|Ys], [X|Merged]) :-
    X < Y,
    !,
    simdiff(Xs, [Y|Ys], Merged).
simdiff([X|Xs], [Y|Ys], [Y|Merged]) :-
    X > Y,
    !,
    simdiff([X|Xs], Ys, Merged).
simdiff([X|Xs], [X|Ys], Merged) :-
    !,
    simdiff(Xs, Ys, Merged).