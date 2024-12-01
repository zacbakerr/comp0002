isEven :: Int -> Bool
isEven num = num `mod` 2 == 0


mult :: Num a => [a] -> a
mult [] = 0
mult list = foldr (*) 1 list

posList :: (Num a, Ord a) => [a] -> [a]
posList [] = []
posList list = filter (> 0) list

trueList :: [Bool] -> Bool
trueList list = foldr (&&) True list

evenList :: [Int] -> Bool
evenList list = trueList (map (isEven) list)

-- maxList :: [Int] -> Int

inRange :: Ord a => a -> a -> [a] -> [a]
inRange s e list = filter (<= e) (filter (>= s) list)

countPositives :: (Num a, Ord a) => [a] -> Int
countPositives list = length(filter (> 0) list)

myLength :: String -> Int
myLength str = foldr (+) 0 (map (\_ -> 1) str)

myMap :: (a -> b) -> [a] -> [b]
myMap func list = foldr (\x acc -> func x : acc) [] list

myLength' :: String -> Int
myLength' str = foldr (+) 0 (foldr (\x acc -> (\_ -> 1) x : acc) [] str)