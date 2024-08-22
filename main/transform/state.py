id_cnt = 0

class State:
    # len(assertion_dict) == len(assumptions_dict)
    def __init__(self, assertion_dict:dict, assumptions_dict:dict, transformations_lst, single_transformations_lst, max_ttl):
        global id_cnt
        self.id = id_cnt
        id_cnt+=1
        self.MAX_TTL = max_ttl
        self.ttl = max_ttl
        self.transformations_lst=transformations_lst
        self.single_transformations_lst=single_transformations_lst
        self.assertions_dict=assertion_dict
        self.assumptions_dict = assumptions_dict
        # Notice that storing this as a set comes at the price of not being able to represent that the same assertion
        # can be in multiple LOCs
        self.__failing_assertions__ = None

    def get_all_assertions(self) -> set:
        return set(sum(self.assertions_dict.values(),[]))

    def get_all_assumptions(self) -> set:
        return set(sum(self.assumptions_dict.values(),[]))

    def get_succeeding_assertions(self) -> set:
        all_assertions = self.get_all_assertions()
        assert all_assertions.issuperset(self.__failing_assertions__)
        return all_assertions.difference(self.__failing_assertions__)

    def get_failing_assertions(self):
        if self.__failing_assertions__ is None:
            return None
        return self.__failing_assertions__.copy()

    def set_failing_assertions(self, s: set):
        self.__failing_assertions__ = s

    def has_assertions_at(self, loc_nr):
        return self.assertions_dict[loc_nr] != []

    def has_failing_assertions_at(self, loc_nr):
        return any(assertion in self.__failing_assertions__ for assertion in self.assertions_dict[loc_nr])

    def has_succeeding_assertions_at(self, loc_nr):
        return any(assertion in self.get_succeeding_assertions() for assertion in self.assertions_dict[loc_nr])

    def has_assumptions_at(self, loc_nr):
        return self.assumptions_dict[loc_nr] != []

    def __str__(self):
        result = ""
        for line_nr in range(0,len(self.assertions_dict)):
            result+=(str(line_nr) + " => assert: " + str(list(map(str, self.assertions_dict[line_nr]))) + ", assume: " +
                     str(list(map(str,self.assumptions_dict[line_nr]))) + "\n")
        return result

def initial_state(loc_cnt, max_ttl):
    assertion_dict = {}
    assumptions_dict = {}
    for i in range(0,loc_cnt):
        assertion_dict.update({i:[]})
        assumptions_dict.update({i:[]})
    return State(assertion_dict, assumptions_dict, [], [], max_ttl)
