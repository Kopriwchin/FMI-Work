main :: IO()
main = do
    print(myMin 5 5)
    print(isInside 5 1 10)
    print(calcAverage 3 4)
    print(fibRec 5)
    print(fibIter 50)

{- example comment -}

myMin :: Int -> Int -> Int
myMin a b = if a < b then a else b

isInside :: Int -> Int -> Int -> Bool
isInside x a b = a <= x && x <= b

calcAverage :: Double -> Double -> Double
calcAverage a b = (a ** 2 + b ** 2) / 2


-- slow factoriel
fibRec :: Int -> Integer
fibRec n = 
    if n == 0 || n == 1 then 1 else fibRec(n - 1) + fibRec (n - 2)


-- fast factoriel with helper function
fibIter :: Int -> Integer
fibIter n = helper 0 1 0 n

helper :: Integer -> Integer -> Int -> Int -> Integer
helper prev cur i n = 
    if i == n then cur else helper cur (prev + cur) (i + 1) n