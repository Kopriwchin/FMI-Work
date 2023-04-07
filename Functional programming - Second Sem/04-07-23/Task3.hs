main :: IO()
main = do
    print (insertionSort [2, 1, 3])
    

insert :: Int -> [Int] -> [Int]
insert n [] = [n]
insert n ks@(k:tks) =
    if n < k then n:ks
    else k:insert n tks

-- insert + foldr
insertionSort :: [Int] -> [Int]
insertionSort = foldr insert []