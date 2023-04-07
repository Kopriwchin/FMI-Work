main :: IO()
main = do

maximize :: (Ord a, Num a) => [(a -> a)] -> (a -> a)
maximize fs
    = \ x -> snd (maximum [(abs fx, fx) | fx <- [f x | f <- fs]])