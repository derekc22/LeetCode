#https://leetcode.com/problems/palindrome-number/

import math

class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        strNum = str(x)
        length = len(strNum)

        if length == 0:
            return True
        if "-" in strNum:
            return False

        midpoint = int(math.floor(length/2))
        return strNum[0:midpoint] == strNum[midpoint:][::-1] if length % 2 == 0 else strNum[0:midpoint] == strNum[midpoint+1:][::-1]


