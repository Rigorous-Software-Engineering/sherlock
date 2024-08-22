import random

class FormInterface:
    def __init__(self, s_vars, c_vars, code_constants, form_tps):
        self.s_vars = s_vars
        self.c_vars = c_vars
        self.code_constants = code_constants
        self.form_tps = form_tps

    def get_random_form(self, require_symbolic, allow_atoms = True):
        #dynamic imports to avoid circular dependency
        from .atom import Atom
        rand = random.random()
        if allow_atoms and rand > 0.4 :
            form_tp =  Atom
        else:
            form_tp = random.choice(self.form_tps)
        return form_tp(self.s_vars, self.c_vars, self.code_constants, require_symbolic, self.form_tps)
    def weaken(self):
        pass

    def strengthen(self):
        pass

    # will return 'self' is the string representation of 'other' is the same as the one from 'self'
    def __return_self_on_eq__(self, other):
        if str(self) == str(other):
            return self, False
        else:
            return other, True