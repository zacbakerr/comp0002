inRange :: Int -> Int -> [Int] -> [Int]
inRange s e [] = []
inRange s e (x:xs)
  | x >= s && x <= e = [x] ++ inRange s e xs
  | otherwise = inRange s e xs

countPositives :: [Int] -> Int
countPositives [] = 0
countPositives (x:xs)
  | x > 0 = 1 + countPositives xs
  | otherwise = countPositives xs

insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys)
  | x <= y    = x : y : ys
  | otherwise = y : insert x ys

isort :: Ord a => [a] -> [a]
isort [] = []
isort [x] = [x]
isort [x, y] = if x <= y then [x, y] else [y, x]
isort (x:xs) = insert x (isort xs)

merge :: Ord a => [a] -> [a] -> [a]
merge [] [] = []
merge [] y = y
merge x [] = x
merge (x:xs) (y:ys)
  | x > y = [y] ++ merge ([x] ++ xs) ys
  | y > x = [x] ++ merge xs ([y] ++ ys)
  | otherwise = [x,y] ++ merge xs ys