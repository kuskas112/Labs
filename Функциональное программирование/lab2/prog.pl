intersection([], _, []).
intersection([H|T], L2, [H|R]) :- member(H, L2), intersection(T, L2, R).
intersection([_|T], L2, R) :- intersection(T, L2, R).

union([], L2, L2).
union([H|T], L2, [H|R]) :- \+member(H, L2), union(T, L2, R).
union([_|T], L2, R) :- union(T, L2, R).

difference([], _, []).
difference([H|T], L2, [H|R]) :- \+member(H, L2), difference(T, L2, R).
difference([_|T], L2, R) :- difference(T, L2, R).