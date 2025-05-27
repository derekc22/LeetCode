class Solution:

    translation_dict = {"I": 1, "V":5, "X":10, "L":50, "C":100, "D":500, "M":1000}

    def romanToInt(self, s: str) -> int:


        new_list = [Solution.translation_dict[char] for char in s]

        integer = sum(new_list)

        return integer

        

