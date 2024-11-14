import Data.Char (toUpper, toLower)

square x = x * x

pyth x y = (square x) + (square y)

isTriple :: Int -> Int -> Int -> Bool
isTriple a b c = pyth a b == square c

isTripleAny :: Int -> Int -> Int -> Bool
isTripleAny a b c = pyth a b == square c || pyth a c == square b || pyth c b == square a

integerDivide :: Int -> Int -> Int
integerDivide x y = x `div` y

halfEvens :: [Int] -> [Int]
halfEvens l = [if even x then integerDivide x 2 else x | x <- l]

inRange :: Int -> Int -> [Int] -> [Int]
inRange s e l = [x | x <- l, x >= s && x <= e]

countPositives :: [Int] -> Int
countPositives l = length [x | x <- l, x > 0]

capitalised :: String -> String
capitalised s = [if i == 0 then toUpper c else toLower c | (i, c) <- zip [0..] s]

lower :: String -> String
lower s = [toLower c | c <- s]

title :: [String] -> [String]
title l = [if length s > 3 || i == 0 then capitalised s else lower s | (i, s) <- zip [0..] l]