module Main where

union :: Ord a => [a] -> [a] -> [a]
union [] [] = []
union [] xs = xs
union ys [] = ys
union (x:xs) (y:ys)
 | x < y = x : (union xs (y:ys))
 | x > y = y : (union (x:xs) ys)
 | otherwise = x : (union xs ys)

inter :: Ord a => [a] -> [a] -> [a]
inter [] [] = []
inter [] xs = []
inter ys [] = []
inter (x:xs) (y:ys)
 | x < y = inter xs (y:ys)
 | x > y = inter (x:xs) ys
 | otherwise = x : (inter xs ys)

diff :: Ord a => [a] -> [a] -> [a]
diff [] [] = []
diff [] xs = []
diff ys [] = ys
diff (x:xs) (y:ys)
 | x < y = x : (diff xs (y:ys))
 | x > y = diff (x:xs) ys
 | otherwise = diff xs ys

simdiff :: Ord a => [a] -> [a] -> [a]
simdiff [] [] = []
simdiff [] xs = xs
simdiff ys [] = ys
simdiff (x:xs) (y:ys)
 | x < y = x : (simdiff xs (y:ys))
 | x > y = y : (simdiff (x:xs) ys)
 | otherwise = simdiff xs ys