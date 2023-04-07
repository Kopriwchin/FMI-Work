main:: IO()
main = do
    print (myIdentity 5)
    print (myCompose (/k -> k * 2) (/k -> k + 5) 2)
    print (myNegate 5)
    print ((myNegate even) 11)

--Ex.1
--a)
myIdentity :: n -> myNegate
myIdentity n = n

--b)
myCompose :: (x -> y) -> (z -> x) -> (z -> y)
myCompose f g = /k -> f (g k) --lambda func

--c)
myNegate :: (a -> Bool) -> (a -> Bool)
myNegate p = /x -> not (p x)