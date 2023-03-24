main:: IO()
main = do
    print(multiplyAllBy [1, 2, 3] 10)

multiplyAllBy :: [Int] -> Int -> [Int]
multiplyAllBy as x = [a * x | a <- as]