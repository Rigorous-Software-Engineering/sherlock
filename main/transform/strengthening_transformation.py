import random

from .transformation import TransformationExpectationInterface


def __build_condition_list_with__(old_condition_lst):
    res = []
    any_was_applied = False
    for c in old_condition_lst:
        modified_c, was_applied = c.strengthen()
        if was_applied:
            any_was_applied=True
        res.append(modified_c)
    return res, any_was_applied


class StrengtheningTransformationExpectation(TransformationExpectationInterface):

    def __init__(self, f_ctx, cb):
        self.__cb__ = cb
        TransformationExpectationInterface.__init__(self, f_ctx, "strengthen")

    def can_be_applied_for(self, state, line_nr):
        return True

    def __try_add_condition__(self, condition_list, line_nr):
        symbolic_lvars_list, concrete_lvars_list = self.f_ctx.lvars_partition
        new_cond = self.__cb__.new_constraint(symbolic_lvars_list[line_nr], concrete_lvars_list[line_nr],
                                              self.f_ctx.code_constants)
        if new_cond is None:
            print("cannot create a new condition for line %d" % line_nr)
        else:
            condition_list.append(new_cond)


    def __new_condition_list_with__(self, old_condition_lst, line_nr, adding_transform_name, strengthening_transform_name):
        if random.choice([True, False]):
            new_condition_lst, was_applied = __build_condition_list_with__(old_condition_lst)
            if was_applied:
                self.applied_single_transformations.add(strengthening_transform_name)
        else:
            new_condition_lst =old_condition_lst.copy()
        if random.choice([True, False]):
            self.applied_single_transformations.add(adding_transform_name)
            self.__try_add_condition__(new_condition_lst, line_nr)
        return new_condition_lst


    def __new_condition_lists__(self, assertions_lst, assumptions_lst, line_nr):
        return (self.__new_condition_list_with__(assertions_lst, line_nr, "AddAssert", "StrengthenAssert"),
                self.__new_condition_list_with__(assumptions_lst, line_nr, "AddAssume", "StrengthenAssume"))


    def get_expectation_failure_witnesses(self) -> set:
        witnesses = set()
        # check: Ensure that all untouched assertions that fail in new state, also failed previously
        print("checking %d assertions" % len(self.__get_untouched_assertions__()))
        for assertion in self.__get_untouched_assertions__():
            if assertion in self.__curr_state__.get_succeeding_assertions() and assertion in self.__new_state__.get_failing_assertions():
                print("assertion %s succeeds in initial file but fails in transformed file" % str(assertion))
                witnesses.add(assertion)
        return witnesses