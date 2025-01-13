import Data.List (unfoldr)
newtype Horse = Horse [String] deriving (Show, Eq)

horse :: Horse
horse = Horse ["     ,//)     "
             , "     ;;'\\    "
             , "  ,;;' ( '\\  "
             , "      / '\\-) " 
             ]

sampleHorse :: Horse
sampleHorse = Horse ["aaza","bbzb","cczc","ddzd"]

transposeHelper :: [[a]] -> [[a]]
transposeHelper [] = []
transposeHelper ([] : xss) = transposeHelper xss
transposeHelper xss = map head xss : transposeHelper (map tail xss)

transpose :: Horse -> Horse
transpose (Horse lines) = Horse $ reverse $ foldr f [] $ padLines lines
  where
    maxLen = maximum $ map length lines
    padLines = map (\line -> line ++ replicate (maxLen - length line) ' ')
    f line acc = zipWith (:) line (acc ++ repeat [])

mirror :: Horse -> Horse
mirror (Horse lines) = Horse $ map reverse lines

rotate180 :: Horse -> Horse
rotate180 = transpose . transpose

rotate270 :: Horse -> Horse
rotate270 = transpose . transpose . transpose

tribonacci :: Int -> [Int]
tribonacci n = take n $ unfoldr nextTrib [0,0,1]
  where
    nextTrib (x:y:z:xs) = Just (x, y:z:x+y+z:xs)
    nextTrib _ = Nothing

lazyCaterer :: Int -> [Int]
lazyCaterer n = take n [divisions k | k <- [0..]]
  where
    divisions k = (k * k + k + 2) `div` 2

pretty :: Horse -> IO ()
pretty (Horse lines) = mapM_ putStrLn lines

horseSeq :: (Int -> [Int]) -> Int -> Horse -> IO ()
horseSeq f n h = 
  case filter (> 0) (f n) of
    [] -> pure ()
    counts -> mapM_ (\count -> pretty (replicateHorse count h) >> putStrLn "") counts  
  where
    replicateHorse count = foldr1 concatHorse . replicate count
    concatHorse (Horse xs) (Horse ys) = Horse (zipWith (++) xs ys)

shead :: [a] -> Maybe a
shead [] = Nothing
shead (x:_) = Just x

stail :: [a] -> Maybe [a]
stail [] = Nothing
stail (_:xs) = Just xs