main :: IO()
main = do
    print (merge [3,4,7,8,9] [1,2,5,6,10])

-- merge :: Ord a => [a] -> [a] -> [a]
merge :: [Int] -> [Int] -> [Int]
merge [] bs = bs
merge as [] = as
merge as@(a:tas) bs@(b:tbs) =
    if a < b then a:merge tas bs
    else b:merge as t