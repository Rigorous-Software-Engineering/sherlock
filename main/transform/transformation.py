import random

from .state import State


class TransformationExpectationInterface:

    def __init__(self, f_ctx, name):
        self.f_ctx = f_ctx
        self.name = name
        self.__curr_state__ = None
        self.__new_state__ = None
        self.applied_single_transformations = set() # to be reset when we call transform(), to be appended in subclasses

    def __new_condition_lists__(self, assertions_lst, assumptions_lst, line_nr) -> tuple:
        pass

    def __build_new_state__(self, instrumentable_line_nrs, start_loc_nr) -> tuple:
        new_assertions_dict = self.__curr_state__.assertions_dict.copy()
        new_assumptions_dict = self.__curr_state__.assumptions_dict.copy()
        num_mut = random.choice([1,2,4,8,16,32])
        max_tries = num_mut*10
        mut_cnt = 0
        loc_nr = start_loc_nr
        for tries in range(0, max_tries):
            if mut_cnt == num_mut:
                # reached max number of mutations
                break
            if self.can_be_applied_for(self.__curr_state__, loc_nr):
                new_assertions_dict[loc_nr], new_assumptions_dict[loc_nr] = \
                    self.__new_condition_lists__(new_assertions_dict[loc_nr], new_assumptions_dict[loc_nr], loc_nr)
                mut_cnt+=1
            loc_nr = random.choice(instrumentable_line_nrs)
        return State(new_assertions_dict, new_assumptions_dict, self.__curr_state__.transformations_lst + [self.name],
                     self.__curr_state__.single_transformations_lst + [self.applied_single_transformations], self.__curr_state__.MAX_TTL), mut_cnt

    def can_be_applied_for(self, state, line_nr):
        pass

    # transformations need to leave self.__curr_state__ unchanged!! (--> create a copy)
    def transform(self, state, querier, line_nrs_to_modify, start_loc_nr) -> tuple:
        self.__curr_state__ = state
        self.applied_single_transformations = set()
        print("trying transformation " + self.name)
        self.__new_state__, _  = self.__build_new_state__(line_nrs_to_modify, start_loc_nr) # nullable field
        if self.__new_state__ is None:
            return None, 0
        else:

            exec_time = querier.set_failing_assertions_for(self.__new_state__)
            return self.__new_state__, exec_time

    # to be used after transform(...)
    def __get_untouched_assertions__(self):
        return self.__curr_state__.get_all_assertions().intersection(self.__new_state__.get_all_assertions())

    def get_expectation_failure_witnesses(self) -> set:
        pass