import random

from .transformation import TransformationExpectationInterface

class WeakenInvariantTransformationExpectation(TransformationExpectationInterface):

    def __init__(self, f_ctx):
        TransformationExpectationInterface.__init__(self, f_ctx, "weaken-invariant")


    def can_be_applied_for(self, state, line_nr):
        return state.has_assertions_at(line_nr)

    def __new_condition_lists__(self, assertions_lst, assumptions_lst, line_nr):
        new_assumptions_lst = assumptions_lst.copy()
        new_assertions_lst = []
        for assertion in assertions_lst:
            if assertion in self.__curr_state__.get_failing_assertions():
                new_assertions_lst.append(assertion)
            else:
                weakened_assertion, had_effect = assertion.weaken()
                if had_effect:
                    self.applied_single_transformations.add("WeakenVerifiedAssert")
                if random.choice([True, False]): # add as an assumption/assertion?
                    self.applied_single_transformations.add("AssumeAssert")
                    new_assumptions_lst.append(weakened_assertion)
                else:
                    new_assertions_lst.append(weakened_assertion)
        return new_assertions_lst, new_assumptions_lst


    def get_expectation_failure_witnesses(self) -> set:
        return self.__curr_state__.get_failing_assertions().symmetric_difference(self.__new_state__.get_failing_assertions())