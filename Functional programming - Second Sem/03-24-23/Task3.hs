main:: IO()
main = do
    print (isAscending 1243)

toList::Int -> [Int]
toList n =
    if n < 10 then [n]
    else n `mod` 10 : toList (n `div` 10);

ascendingList::[Int]->Bool
ascendingList [] = True
ascendingList [_] = True
ascendingList(x1:x2:xs)= x1>x2 && ascendingList(x2:xs)

isAscending::Int->Bool
isAscending n = ascendingList(toList n);