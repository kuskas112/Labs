module Main where

un :: Eq a => [a] -> [a] -> [a]
un [] ys = ys
un xs [] = xs
un (x:xs) ys
  | x `elem` ys = un xs ys
  | otherwise   = x : un xs ys

intersection :: Eq a => [a] -> [a] -> [a]
intersection [] ys = []
intersection xs [] = []
intersection (x:xs) ys
  | x `elem` ys = x: intersection xs ys
  | otherwise = intersection xs ys 

diff :: Eq a => [a] -> [a] -> [a]
diff [] ys = []
diff xs [] = xs
diff (x:xs) ys
  | x `elem` ys = diff xs ys
  | otherwise   = x : diff xs ys


main :: IO ()
main = do
    let list1 = [1, 2, 3, 5]
        list2 = [3, 5, 7, 6]
        completedUnion = un list1 list2
        completedInter = intersection list1 list2
        completedDiff = diff list1 list2
    print completedUnion
    print completedInter
    print completedDiff