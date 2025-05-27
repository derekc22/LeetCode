class Solution(object):




    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """



if __name__ == '__main__':

    """latest working"""
    # def p(n):

    #     if n == 1:
    #         return []

    #     if n == 2:
    #         return ["1+1"]
        
    #     else:
    #         return [i+"+1" for i in p(n-1)] + [f"{n-1}+1"] 
    



    """latest working"""

    # def pp(r):
    #     return "sp"

    # def pn(n):


    #     if n%2 == 0:
    #         return [f"{n-r}+{r if r < 4 else pp(r)}" for r in range(2, n-1)]
        
    #     else:
    #         return [f"{n-r}+{r if r < 4 else pp(r)}" for r in range(2, n-2)]
    

    # def p(n):

    #     if n == 1:
    #         return []

    #     if n == 2:
    #         return ["1+1"]
        
    #     else:
    #         return [i+"+1" for i in p(n-1) + [f"{n-1}"]] + pn(n)

    # print(p(6))


    """latest working"""


    def pp(r, m):
        print(r,m,"*")
        if r < 4:
            return [r]
        else:
            return pn(r, m)


    def pn(n, m):


        k = n-1 if n%2 == 0 else n-2
        print(n,m,k,"!")
        # return [ f"{n-r}+{ pp(r, r-(n-r)) }" for r in range(m, k)]
        # return [ [n-r] + pp(r, r-(n-r)) for r in range(m, k) ]

        # return [ f"{n-r}+{j}"  for r in range(m, k) for j in pp(r, r-(n-r)) ]
        return [ f"{n-r}+{j}"  for r in range(m, k) for j in pp(r, n-(n-r)) ]



    def p(n):

        print(n)

        if n == 1:
            return []

        if n == 2:
            return ["1+1"]
        
        else:
            return [i+"+1" for i in p(n-1) + [f"{n-1}"]] + pn(n, 2)

    num = 8
    max_val = 3
    print(pn(10, 7))
    # print(pp(1, -2))





    # def partitions(num):
        
        

    # partitions(5)

