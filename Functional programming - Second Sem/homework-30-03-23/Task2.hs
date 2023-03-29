main :: IO()
main = do
    print (getNthSevenlikeNum 1) -- 1
    print (getNthSevenlikeNum 2) -- 7
    print (getNthSevenlikeNum 3) -- 8
    print (getNthSevenlikeNum 4) -- 49

getNthSevenlikeNum :: Int -> Int
getNthSevenlikeNum 1 = 1
getNthSevenlikeNum 2 = 7

getNthSevenlikeNum a
    | (a <= 0) = error "Invalid input! Positive number expected!"
    | odd a = getNthSevenlikeNum(a - 1) + 1
    | even a = getNthSevenlikeNum(a `div` 2) * 7