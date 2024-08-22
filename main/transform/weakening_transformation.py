import random

from .transformation import TransformationExpectationInterface


def __build_condition_list_with__(old_condition_lst):
    res = []
    effectively_transformed_constraints = []
    for old_c in old_condition_lst:
        modified_c, was_applied = old_c.weaken()
        if was_applied:
            effectively_transformed_constraints.append(old_c)
        res.append(modified_c)
    return res, effectively_transformed_constraints

class WeakeningTransformationExpectation(TransformationExpectationInterface):

    def __init__(self, f_ctx):
        TransformationExpectationInterface.__init__(self, f_ctx, "weaken")


    def can_be_applied_for(self, state, line_nr):
        return state.has_assumptions_at(line_nr) or state.has_assertions_at(line_nr)

    def __new_condition_lists__(self, assertions_lst, assumptions_lst, line_nr):
        if assertions_lst != [] and assumptions_lst != []:
            # modify only one of assertions and assumptions
            if random.choice([True, False]):
                new_assertion_lst, effectively_transformed_assertions = __build_condition_list_with__(assertions_lst)
                new_assumption_lst = assumptions_lst
                effectively_transformed_assumptions = []
            else:
                new_assertion_lst = assertions_lst
                effectively_transformed_assertions = []
                new_assumption_lst, effectively_transformed_assumptions = __build_condition_list_with__(assumptions_lst)
        else:

            new_assertion_lst, effectively_transformed_assertions = __build_condition_list_with__(assertions_lst)
            new_assumption_lst, effectively_transformed_assumptions = __build_condition_list_with__(assumptions_lst)
        if len(self.__curr_state__.get_failing_assertions().intersection(effectively_transformed_assertions)) > 0:
            self.applied_single_transformations.add("WeakenUnverifiedAssert")
        if len(self.__curr_state__.get_succeeding_assertions().intersection(effectively_transformed_assertions)) > 0:
            self.applied_single_transformations.add("WeakenVerifiedAssert")
        if effectively_transformed_assumptions:
            self.applied_single_transformations.add("WeakenAssume")
        return new_assertion_lst, new_assumption_lst


    def get_expectation_failure_witnesses(self) -> set:
        witnesses = set()
        # check: Ensure that all untouched assertions that fail in new state, also failed previously
        for assertion in self.__get_untouched_assertions__():
            if assertion in self.__curr_state__.get_failing_assertions() and assertion in self.__new_state__.get_succeeding_assertions():
                witnesses.add(assertion)
        return witnesses