import random
from enum import Enum

INT_MIN=-2147483648
INT_MAX=2147483647
UINT_MAX=4294967295
predefined_constants_dict = {'~(2147483646)': -2147483647, '4294967294UL': -2, '0LL': 0, '~(2147483647)': -2147483648, '2147483647ULL': 2147483647, '2147483647UL': 2147483647, '2147483646L': 2147483646, '4294967294U': -2, '2147483646UL': 2147483646, '2147483647': 2147483647, '-2147483648LL': -2147483648, '0U': 0, '0UL': 0, '4294967295U': -1, '~(4294967294U)': 1, '2147483647LL': 2147483647, '~(0)': -1, '1U': 1, '~(4294967295U)': 0, '~(0U)': -1, '4294967295ULL': -1, '~(2147483646U)': -2147483647, '~(-2147483648)': 2147483647, '1LL': 1, '0': 0, '-2147483647LL': -2147483647, '2147483648UL': -2147483648, '1': 1, '1UL': 1, '~(1U)': -2, '4294967294ULL': -2, '-1L': -1, '~(1)': -2, '-2147483648L': -2147483648, '2147483646': 2147483646, '2147483646U': 2147483646, '2147483647U': 2147483647, '2147483646LL': 2147483646, '~(-1)': 0, '2147483648ULL': -2147483648, '0ULL': 0, '1L': 1, '2147483648U': -2147483648, '-1LL': -1, '~(2147483648U)': 2147483647, '1ULL': 1, '2147483647L': 2147483647, '~(-2147483647)': 2147483646, '0L': 0, '-2147483648': -2147483648, '4294967295UL': -1, '~(2147483647U)': -2147483648, '-2147483647L': -2147483647, '2147483646ULL': 2147483646, '-2147483647': -2147483647, '-1': -1}

Comparator = Enum('Comparator', [('LE', '<'), ('LEQ', '<='), ('NEQ', '!='), ('GEQ', '>='), ('GE', '>')])

# chooses from list 'elements' the value elements[i] with probability 1/(2^(i+1))
def ordered_choice(elements):
    for elem in elements:
        if random.choice([True,False]):
            return elem
    return elements[-1]


# chooses v1 OP v2 s.t. v1 in vars1 and v2 in vars1 + vars2 + code_constants_set with descending probability
# this method will modify 'vars1' and 'vars2'
def new_binary_constraint(vars1, vars2, code_constants_set):
    comparator = random.choice(list(Comparator))
    lhs = random.choice(vars1)
    allowed_constants_set = set()
    for c in predefined_constants_dict:
        if comparator in [Comparator.LE, Comparator.LEQ]:
            if predefined_constants_dict[c] > INT_MIN + 1:
                # only add constants which are not too small
                allowed_constants_set.add(c)
        elif comparator in [Comparator.GE, Comparator.GEQ]:
            if predefined_constants_dict[c] < INT_MAX - 1:
                allowed_constants_set.add(c)
        else:
            allowed_constants_set.add(c)
    allowed_constants_set = allowed_constants_set.union(code_constants_set)
    random.shuffle(vars1)
    random.shuffle(vars2)
    allowed_vars = vars1 + vars2
    allowed_vars.remove(lhs) # do not create constraints of form v OP v
    allowed_constants = sorted(allowed_constants_set)
    random.shuffle(allowed_constants)
    rhs = ordered_choice(allowed_vars + allowed_constants)
    return BinaryConstraint(lhs, comparator, rhs)

# do not change the signs of the smaller/bigger ints which are returned to avoid unsigned/signed comparisons in
# transformed file
def smaller_int(const):
    if const < 0:
        return random.randint(int(INT_MIN), const)
    else:
        return random.randint(0, const)


def bigger_int(const):
    if const < 0:
        return random.randint(const, -1)
    else:
        return random.randint(const, int(INT_MAX))

class BinaryConstraint:

    def __init__(self, literal_lhs, comparator, literal_rhs):
        self.literal_lhs=literal_lhs
        self.comparator=comparator
        self.literal_rhs=literal_rhs

    def __str__(self):
        return str(self.literal_lhs) + " " + self.comparator.value + " " + str(self.literal_rhs)

    def __get_new_const__(self, const_fnc1, const_fnc2) -> int :
        try:
            # change the constant with 50% probability
            if random.choice([True,False]):
                orig_const=int(self.literal_rhs)
                if self.comparator in [Comparator.LE, Comparator.LEQ]:
                    new_literal_rhs = const_fnc1(orig_const)
                elif self.comparator in [Comparator.GE, Comparator.GEQ]:
                    new_literal_rhs = const_fnc2(orig_const)
                else:
                    new_literal_rhs = self.literal_rhs
                return new_literal_rhs
            else:
                return self.literal_rhs
        except ValueError:
            return self.literal_rhs

    def weaken(self):
        if self.comparator == Comparator.LE:
            new_op = random.choice([self.comparator.LEQ, self.comparator.NEQ])
        elif self.comparator == Comparator.GE:
            new_op = random.choice([self.comparator.GEQ, self.comparator.NEQ])
        else:
            new_op = self.comparator
        return BinaryConstraint(self.literal_lhs, new_op,  self.__get_new_const__(bigger_int, smaller_int))


    def strengthen(self):
     if self.comparator == Comparator.LEQ:
         new_op = self.comparator.LE
     elif self.comparator == Comparator.GEQ:
         new_op = self.comparator.GE
     elif self.comparator == Comparator.NEQ:
         new_op = random.choice([self.comparator.LE, self.comparator.GE])
     else:
         new_op = self.comparator
     return BinaryConstraint(self.literal_lhs, new_op,  self.__get_new_const__(smaller_int, bigger_int))
