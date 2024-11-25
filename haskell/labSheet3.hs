isEven :: Int -> Bool
isEven num = num `mod` 2 == 0


mult :: [Int] -> Int
mult [] = 0
mult list = foldr (*) 1 list

posList :: [Int] -> [Int]
posList [] = []
posList list = filter (> 0) list

trueList :: [Bool] -> Bool
trueList list = foldr (==) True list

evenList :: [Int] -> Bool
evenList list = foldr (==) True (map isEven list)

-- maxList :: [Int] -> Int

inRange :: Int -> Int -> [Int] -> [Int]
inRange s e list = filter (<= e) (filter (>= s) list)

countPositives :: [Int] -> Int
countPositives list = length(filter (> 0) list)