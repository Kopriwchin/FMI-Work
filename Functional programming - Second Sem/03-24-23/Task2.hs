main :: IO()
main = do
    print(filterSmallerThan [10,20,30,40,50] 25)

filterSmallerThan :: [Int] -> Int -> [Int]
filterSmallerThan xs x = filter (>=x) xs