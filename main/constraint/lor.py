import copy
import random

from .compound import CompoundInterface
class Or(CompoundInterface):
    def __init__(self, s_vars, c_vars, code_constants, is_symbolic, form_tps):
        CompoundInterface.__init__(self,s_vars,c_vars, code_constants, '||', form_tps)
        # guarantee the first disjunct to be symbolic - if 'is_symbolic'
        self.forms.append(self.get_random_form(is_symbolic))
        if random.choice([True, False]):
            self.forms.append(self.get_random_form(False))

    def weaken(self):
        new_or = copy.copy(self)
        new_or.forms = new_or.__weaken__forms__()
        if random.choice([True, False]):
            new_or.forms.append(self.get_random_form(False))
        return self.__return_self_on_eq__(new_or)

    def strengthen(self):
        new_or = copy.copy(self)
        new_or.forms = new_or.__strengthen__forms__()
        # possibly remove an atom
        if len(new_or.forms) > 1 and random.choice([True,False]):
            new_or.forms.remove(random.choice(new_or.forms))
        return self.__return_self_on_eq__(new_or)