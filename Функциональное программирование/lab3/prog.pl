suffixes([], []).
suffixes([H|T], [[H|T]|S]) :-
    suffixes(T, S).

dellast([_],[]):-!.
dellast([X|T],[X|Y]):-dellast(T,Y).

prefixes([], []).
prefixes([H|T], [[H|T]|P]) :-
    dellast([H|T], R),
    prefixes(R, P).

segments([], []).
segments([H|T], [Pref|Rest]) :-
    prefixes([H|T], Pref),
    segments(T, Rest).

permutation([],[]).
permutation(L,[H|T]):-
    select(H,L,T1),
    permutation(T1,T).

select(H,[H|T],T).
select(H,[Y|T],[Y|T1]):-
    select(H,T,T1).
