import copy
import random
from .compound import CompoundInterface


class And(CompoundInterface):
    def __init__(self, s_vars, c_vars, code_constants, is_symbolic, form_tps):
        CompoundInterface.__init__(self,s_vars,c_vars, code_constants, '&&', form_tps)
        self.forms.append(self.get_random_form(is_symbolic))
        if random.choice([True, False]):
            self.forms.append(self.get_random_form(is_symbolic))
        self.is_symbolic = is_symbolic


    def weaken(self):
        new_and = copy.copy(self)
        new_and.forms = new_and.__weaken__forms__()
        # possibly remove an atom
        if len(new_and.forms) > 1 and random.choice([True,False]):
            new_and.forms.remove(random.choice(new_and.forms))
        return self.__return_self_on_eq__(new_and)

    def strengthen(self):
        new_and = copy.copy(self)
        new_and.forms = new_and.__strengthen__forms__()
        if random.choice([True, False]):
            new_and.forms.append(self.get_random_form(self.is_symbolic))
        return self.__return_self_on_eq__(new_and)