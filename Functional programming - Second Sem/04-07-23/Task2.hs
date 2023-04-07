main :: IO()
main = do
    print (insert 3 [1, 2, 3, 4, 5, 6])

insert :: Int -> [Int] -> [Int]
insert n [] = [n]
insert n ks@(k:tks) =
    if n < k then n:ks
    else k:insert n tks