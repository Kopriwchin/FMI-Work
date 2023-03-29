main :: IO()
main = do
    print $ eqSumPowDig 100 2 == 0 -- True
    print $ eqSumPowDig 1000 2 == 0 -- True
    print $ eqSumPowDig 2000 2 == 0 -- True
    print $ eqSumPowDig 200 3 == 153 -- True
    print $ eqSumPowDig 370 3 == 523 -- True
    print $ eqSumPowDig 371 3 == 894 -- True
    print $ eqSumPowDig 400 3 == 894 -- True
    print $ eqSumPowDig 500 3 == 1301 -- True
    print $ eqSumPowDig 1000 3 == 1301 -- True
    print $ eqSumPowDig 1500 3 == 1301 -- True

eqSumPowDig :: Int -> Int -> Int
eqSumPowDig hMax power
    | hMax <= 1 || power <= 1 = error "Invalid input!"
    | otherwise = sumSpecial 2 0
    where
        sumSpecial x total
            | x > hMax = total
            | isSpecial x power = sumSpecial (x + 1) (total + x)
            | otherwise = sumSpecial (x + 1) total
        
        isSpecial x power = x == (sumDigitsPow x power)
        sumDigitsPow 0 _ = 0
        sumDigitsPow x power = (mod x 10) ^ power + sumDigitsPow (div x 10) power