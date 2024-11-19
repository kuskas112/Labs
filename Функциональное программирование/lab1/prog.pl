% Родители
parent(mary, john).
parent(mary, jane).
parent(mary, david).
parent(michael, john).
parent(michael, jane).
parent(michael, david).

parent(sarah, mark).
parent(sarah, lisa).
parent(robert, mark).
parent(robert, lisa).

% Бабушки и дедушки
parent(lucy, robert).
parent(ivan, robert).
parent(marta, sarah).

% Пол
male(john).
male(david).
male(mark).
male(michael).
male(robert).
male(ivan).

female(mary).
female(jane).
female(lisa).
female(sarah).
female(lucy).
female(marta).

% Братья и сестры
brother(john, jane).
brother(john, david).
brother(david, jane).
brother(david, john).
brother(robert, mary).
brother(mark, lisa).

sister(jane, john).
sister(jane, david).
sister(jane, mark).
sister(lisa, mark).

% Браки
married(robert, sarah).
married(sarah, robert).



cousin_sister(X, Y) :-
    female(X),
    parent(Parx, X),
    parent(Pary, Y),
    sibling(Parx, Pary).

sibling(X, Y) :-
    (
        (sister(X, Y); sister(Y, X));
        (brother(X, Y); brother(Y, X))
    ),
    X \= Y.

husband_mother(X, Y) :-
    female(X),
    female(Y),
    parent(X, Son),
    married(Y, Son).

ancestor(X, Y) :-
    female(X),
    parent(X, Y).

ancestor(X, Y) :-
    parent(Z, Y),
    ancestor(X, Z).

ib(X, Y) :-
    female(X),
    ancestor(X, Y).

